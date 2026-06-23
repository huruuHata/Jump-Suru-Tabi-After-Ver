#define _USING_V110_SDK71_ 1

#include "PlayerMovement.h"

using namespace KeyString;

PlayerMovement::PlayerMovement() : m_look_dir(UP)
                                 , m_is_goal(false)
	                             , m_is_gameover(false)
{
}

PlayerMovement::Output PlayerMovement::Update(const Field& field, BaseObject::DrawSet& draw, const int move_speed, const int block_width, const int block_height, unsigned int key_flag, const float delta_time)
{
	Output out{};
	out.move_x = 0;

	if (key_flag & PlayerInput::UP_KEY)    m_look_dir = UP;
	if (key_flag & PlayerInput::DOWN_KEY)  m_look_dir = DOWN;

	if (key_flag & PlayerInput::LEFT_KEY)  out.move_x -= 1;
	if (key_flag & PlayerInput::RIGHT_KEY) out.move_x += 1;

	if (out.move_x < 0)
	{
		m_look_dir = LEFT;

		int next_x = (int)(draw.position.x - move_speed * delta_time);

		if (!CanMoveX(field, draw, next_x, block_width, block_height))
		{
			out.move_x = 0;
		}
	}
	else if(out.move_x > 0)
	{
		m_look_dir = RIGHT;

		int next_x = (int)(draw.position.x + move_speed * delta_time);

		if (!CanMoveX(field, draw, next_x + block_width - 1, block_width, block_height))
		{
			out.move_x = 0;
		}
	}

	out.look_dir = m_look_dir;

	return out;
}

bool PlayerMovement::IsGoal() const
{
	return m_is_goal;
}

bool PlayerMovement::IsGameover() const
{
	return m_is_gameover;
}

bool PlayerMovement::CanMoveX(const Field& field, BaseObject::DrawSet& draw, const int next_pixel_x, const int block_width, const int block_height)
{
	int result = m_collide.CheckHorizontal(field, next_pixel_x, draw.position.y + PlayerCollide::COLLIDE_MARGIN, draw.position.y + draw.draw_height - 1 - PlayerCollide::COLLIDE_MARGIN, block_width, block_height);

	if (result >= Stage::CANT_PASS)
	{
		return false;
	}

	if (result == Stage::GOAL)
	{
		m_is_goal = true;
	}

	return true;
}