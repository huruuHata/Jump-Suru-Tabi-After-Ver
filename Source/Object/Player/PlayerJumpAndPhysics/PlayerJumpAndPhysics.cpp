#define _USING_V110_SDK71_ 1

#include "PlayerJumpAndPhysics.h"

using namespace KeyString;
using namespace WindowSetting;

PlayerJumpAndPhysics::PlayerJumpAndPhysics() : m_bGrounded(true)	
	                                         , m_bJumping(false)
	                                         , m_bGameover(false)
{
}

void PlayerJumpAndPhysics::Initialize(const json& data, const int block_width, const int block_height)
{
	m_jump_speed = data["Speed"]["Jump"];

	m_jump_power_white = data["JumpPower"]["White"];
	m_jump_power_black = data["JumpPower"]["Black"];

	m_jump_power = 0;
	m_save_height = 0;

	m_block_width = block_width;
	m_block_height = block_height;

	m_bGoal = false;
}

PlayerJumpAndPhysics::Output PlayerJumpAndPhysics::Update(const Field& field, BaseObject::DrawSet& draw, const float delta_time)
{
	Output out{};

	if (m_bGrounded) GroundProcess(field, draw);

	if (!m_bJumping)
	{
		if (!m_bGrounded) Falling(field, draw, delta_time);
	}
	else
	{
		Jumping(field, draw, delta_time);
	}

	return out;
}

bool PlayerJumpAndPhysics::IsGrounded() const
{
	return m_bGrounded;
}

bool PlayerJumpAndPhysics::IsGoal() const
{
	return m_bGoal;
}

bool PlayerJumpAndPhysics::IsGameover() const
{
	return m_bGameover;
}
 
void PlayerJumpAndPhysics::JumpCheck(Engine* pEngine, BaseObject::DrawSet& draw, const bool bBlack_mode)
{
	if (!m_bJumping && m_bGrounded)
	{
		m_save_height = draw.position.y;
		m_bJumping = true;
		m_bGrounded = false;

		pEngine->PlaySE(SE_JUMP);

		m_jump_power += bBlack_mode ? m_jump_power_black : m_jump_power_white;
	}
}

void PlayerJumpAndPhysics::Jumping(const Field& field, BaseObject::DrawSet& draw, const float delta_time)
{
	draw.position.y -= (int)(m_jump_speed * delta_time);

	if (m_save_height - draw.position.y >= m_jump_power)
	{
		m_bJumping = false;
	}
	else
	{
		UpCheck(field, draw);
	}
}

void PlayerJumpAndPhysics::GroundProcess(const Field& field, BaseObject::DrawSet& draw)
{
	int ground_y;

	//着地
	if (CheckGround(field, ground_y, draw))
	{
		draw.position.y = ground_y;
		m_bGrounded = true;
	}
	else
	{
		m_bGrounded = false;
	}
}

void PlayerJumpAndPhysics::Falling(const Field& field, BaseObject::DrawSet& draw, const float delta_time)
{
	draw.position.y += (int)(m_jump_speed * delta_time);

	if (draw.position.y > WINDOW_HEIGHT - draw.draw_height)
	{
		m_bGameover = true;
		return;
	}

	int ground_y;

	//着地
	if (CheckGround(field, ground_y, draw))
	{
		draw.position.y = ground_y;
		m_bGrounded = true;
	}

	int result = m_collide.CheckVertical(field, draw.position.x + PlayerCollide::COLLIDE_MARGIN, draw.position.x + draw.draw_width - 1 - PlayerCollide::COLLIDE_MARGIN, draw.position.y + draw.draw_height - 1, m_block_width, m_block_height);

	if (result == Stage::GOAL)
	{
		m_bGoal = true;
	}
}

void PlayerJumpAndPhysics::UpCheck(const Field& field, BaseObject::DrawSet& draw)
{
	//上との衝突

	int map_y = Stage::ToMapY(draw.position.y, m_block_height);

	int result = m_collide.CheckVertical(field, draw.position.x + PlayerCollide::COLLIDE_MARGIN, draw.position.x + draw.draw_width - 1 - PlayerCollide::COLLIDE_MARGIN, draw.position.y, m_block_width, m_block_height);

	if (result >= Stage::CANT_PASS)
	{
		if (result == Stage::JAGGED_UP)
		{
			m_bGameover = true;
		}

		draw.position.y = (map_y + 1) * m_block_height;
		m_bJumping = false;
	}
}

bool PlayerJumpAndPhysics::CheckGround(const Field& field, int& ground_y, BaseObject::DrawSet& draw)
{
	int map_y = Stage::ToMapY(draw.position.y + m_block_height, m_block_height);

	int result = m_collide.CheckVertical(field, draw.position.x + PlayerCollide::COLLIDE_MARGIN, draw.position.x + draw.draw_width - 1 - PlayerCollide::COLLIDE_MARGIN, draw.position.y + draw.draw_height, m_block_width, m_block_height);

	if (result >= Stage::CANT_PASS)
	{
		if (result == Stage::JAGGED_DOWN)
		{
			m_bGameover = true;
		}

		//着地
		ground_y = (map_y - 1) * m_block_height;
		return true;
	}
	
	return false;
}