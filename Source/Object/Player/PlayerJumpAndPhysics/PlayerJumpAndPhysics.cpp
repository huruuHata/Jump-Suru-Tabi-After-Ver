#define _USING_V110_SDK71_ 1

#include "PlayerJumpAndPhysics.h"

using namespace KeyString;
using namespace WindowSetting;

PlayerJumpAndPhysics::PlayerJumpAndPhysics() : m_is_grounded(true)	
	                                         , m_is_jumping(false)
	                                         , m_is_gameover(false)
											 , m_is_goal(false)
{
}

void PlayerJumpAndPhysics::Initialize(const json& data)
{
	m_jump_speed = data["Speed"]["Jump"];

	m_jump_power_white = data["JumpPower"]["White"];
	m_jump_power_black = data["JumpPower"]["Black"];

	m_fall_death_y = data["FallDeathY"];

	m_jump_power = 0;
	m_save_height = 0;
}

void PlayerJumpAndPhysics::Update(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height, const float delta_time)
{
	if (m_is_grounded) GroundProcess(field, draw, block_width, block_height);

	if (!m_is_jumping)
	{
		if (!m_is_grounded) Falling(field, draw, block_width, block_height, delta_time);
	}
	else
	{
		Jumping(field, draw, block_width, block_height, delta_time);
	}
}

bool PlayerJumpAndPhysics::IsGrounded() const
{
	return m_is_grounded;
}

bool PlayerJumpAndPhysics::IsGoal() const
{
	return m_is_goal;
}

bool PlayerJumpAndPhysics::IsGameover() const
{
	return m_is_gameover;
}
 
void PlayerJumpAndPhysics::JumpCheck(Engine* pEngine, BaseObject::DrawSet& draw, const bool is_black_mode)
{
	if (!m_is_jumping && m_is_grounded)
	{
		m_save_height = draw.position.y;
		m_is_jumping = true;
		m_is_grounded = false;

		pEngine->PlaySE(SE_JUMP);

		m_jump_power += is_black_mode ? m_jump_power_black : m_jump_power_white;
	}
}

void PlayerJumpAndPhysics::Jumping(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height, const float delta_time)
{
	draw.position.y -= (int)(m_jump_speed * delta_time);

	if (m_save_height - draw.position.y >= m_jump_power)
	{
		m_is_jumping = false;
	}
	else
	{
		UpCheck(field, draw, block_width, block_height);
	}
}

void PlayerJumpAndPhysics::GroundProcess(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height)
{
	int ground_y = 0;

	//着地
	if (CheckGround(field, ground_y, draw, block_width, block_height))
	{
		draw.position.y = ground_y;
		m_is_grounded = true;
	}
	else
	{
		m_is_grounded = false;
	}
}

void PlayerJumpAndPhysics::Falling(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height, const float delta_time)
{
	draw.position.y += (int)(m_jump_speed * delta_time);

	if (draw.position.y > m_fall_death_y)
	{
		m_is_gameover = true;
		return;
	}

	int ground_y;

	//着地
	if (CheckGround(field, ground_y, draw, block_width, block_height))
	{
		draw.position.y = ground_y;
		m_is_grounded = true;
	}

	int result = m_collide.CheckVertical(field, draw.position.x + PlayerCollide::COLLIDE_MARGIN, draw.position.x + draw.draw_width - 1 - PlayerCollide::COLLIDE_MARGIN, draw.position.y + draw.draw_height - 1, block_width, block_height);

	if (result == Stage::GOAL)
	{
		m_is_goal = true;
	}
}

void PlayerJumpAndPhysics::UpCheck(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height)
{
	//上との衝突

	int map_y = Stage::ToMapY(draw.position.y, block_height);

	int result = m_collide.CheckVertical(field, draw.position.x + PlayerCollide::COLLIDE_MARGIN, draw.position.x + draw.draw_width - 1 - PlayerCollide::COLLIDE_MARGIN, draw.position.y, block_width, block_height);

	if (result >= Stage::CANT_PASS)
	{
		if (result == Stage::JAGGED_UP)
		{
			m_is_gameover = true;
		}

		draw.position.y = (map_y + 1) * block_height;
		m_is_jumping = false;
	}
}

bool PlayerJumpAndPhysics::CheckGround(const Field& field, int& ground_y, BaseObject::DrawSet& draw, const int block_width, const int block_height)
{
	int map_y = Stage::ToMapY(draw.position.y + block_height, block_height);

	int result = m_collide.CheckVertical(field, draw.position.x + PlayerCollide::COLLIDE_MARGIN, draw.position.x + draw.draw_width - 1 - PlayerCollide::COLLIDE_MARGIN, draw.position.y + draw.draw_height, block_width, block_height);

	if (result >= Stage::CANT_PASS)
	{
		if (result == Stage::JAGGED_DOWN)
		{
			m_is_gameover = true;
		}

		//着地
		ground_y = (map_y - 1) * block_height;
		return true;
	}
	
	return false;
}