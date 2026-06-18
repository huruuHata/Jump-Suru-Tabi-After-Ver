
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

bool PlayerJumpAndPhysics::CheckGround(const Field& field, int& ground_y, BaseObject::DrawSet& draw)
{
	int left_x = ToMapX(draw.position.x);
	int right_x = ToMapX(draw.position.x + m_block_width - 1);
	int map_y = ToMapY(draw.position.y + m_block_height);

	bool hit_left = field.map[map_y][left_x] >= CANT_PASS;
	bool hit_right = field.map[map_y][right_x] >= CANT_PASS;

	if (field.map[map_y][left_x] == JAGGED || field.map[map_y][right_x] == JAGGED)
	{
		m_bGameover = true;
	}

	//着地
	if (hit_left || hit_right)
	{
		ground_y = (map_y - 1) * draw.draw_height;
		return true;
	}

	return false;
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

	int left_x = ToMapX(draw.position.x);
	int right_x = ToMapX(draw.position.x + m_block_width - 1);
	int map_y = ToMapY(draw.position.y + m_block_height);

	if (field.map[map_y][left_x] == GOAL || field.map[map_y][right_x] == GOAL)
	{
		m_bGoal = true;
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

void PlayerJumpAndPhysics::UpCheck(const Field& field, BaseObject::DrawSet& draw)
{
	//上との衝突

	int left_x = ToMapX(draw.position.x);
	int right_x = ToMapX(draw.position.x + m_block_width - 1);
	int map_y = ToMapY(draw.position.y);

	if (field.map[map_y][left_x] >= CANT_PASS || field.map[map_y][right_x] >= CANT_PASS)
	{
		if (field.map[map_y][left_x] == JAGGED || field.map[map_y][right_x] == JAGGED)
		{
			m_bGameover = true;
		}

		draw.position.y = (map_y + 1) * draw.draw_height;
		m_bJumping = false;
	}
}

//ピクセル座標をマップ座標に変換
int PlayerJumpAndPhysics::ToMapX(int pixel_x) const
{
	return pixel_x / m_block_width;
}
int PlayerJumpAndPhysics::ToMapY(int pixel_y) const
{
	return pixel_y / m_block_height;
}