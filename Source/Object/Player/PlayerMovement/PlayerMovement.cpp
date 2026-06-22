#define _USING_V110_SDK71_ 1

#include "PlayerMovement.h"

using namespace KeyString;

PlayerMovement::PlayerMovement() : m_look_dir(UP)
{
}

void PlayerMovement::Initialize(const int block_width, const int block_height)
{
	m_block_width = block_width;
	m_block_height = block_height;

	m_bGoal = false;
	m_bGameover = false;
}

PlayerMovement::Output PlayerMovement::Update(const Field& field, BaseObject::DrawSet& draw, const int move_speed, unsigned int key_flag, const float delta_time)
{
	Output out{};
	out.move_x = 0;

	if (key_flag & PlayerInput::UP_KEY)    m_look_dir = UP;
	if (key_flag & PlayerInput::DOWN_KEY)  m_look_dir = DOWN;

	if (key_flag & PlayerInput::LEFT_KEY) out.move_x -= 1;
	if (key_flag & PlayerInput::RIGHT_KEY) out.move_x += 1;

	if (out.move_x < 0)
	{
		m_look_dir = LEFT;

		int next_x = (int)(draw.position.x - move_speed * delta_time);

		if (!CanMoveX(field, next_x, draw))
		{
			out.move_x = 0;
		}
	}
	else if(out.move_x > 0)
	{
		m_look_dir = RIGHT;

		int next_x = (int)(draw.position.x + move_speed * delta_time);

		if (!CanMoveX(field, next_x + m_block_width - 1, draw))
		{
			out.move_x = 0;
		}
	}

	out.look_dir = m_look_dir;

	return out;
}

bool PlayerMovement::IsGoal() const
{
	return m_bGoal;
}

bool PlayerMovement::IsGameover() const
{
	return m_bGameover;
}

bool PlayerMovement::CanMoveX(const Field& field, const int next_pixel_x, BaseObject::DrawSet& draw)
{
	int result = m_collide.CheckHorizontal(field, next_pixel_x, draw.position.y + PlayerCollide::COLLIDE_MARGIN, draw.position.y + draw.draw_height - 1 - PlayerCollide::COLLIDE_MARGIN, m_block_width, m_block_height);

	if (result >= Stage::CANT_PASS)
	{
		return false;
	}

	if (result == Stage::GOAL)
	{
		m_bGoal = true;
	}

	return true;
}