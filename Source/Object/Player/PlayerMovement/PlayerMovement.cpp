
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
	
	if (key_flag & PlayerInput::LEFT_KEY)
	{
		m_look_dir = LEFT;
	    int next_x = (int)(draw.position.x - move_speed * delta_time);

		if (CanMoveX(field, next_x, draw))
		{
			out.move_x = -1;
		}
	}

	if (key_flag & PlayerInput::RIGHT_KEY)
	{
		m_look_dir = RIGHT;

		int next_x = (int)(draw.position.x + move_speed * delta_time);

		if (CanMoveX(field, next_x + m_block_width - 1, draw))
		{
			out.move_x = 1;
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
	int map_x = Stage::ToMapX(next_pixel_x, m_block_width);
	int top_y = Stage::ToMapY(draw.position.y, m_block_height);
	int bottom_y = Stage::ToMapY(draw.position.y + m_block_height - 1, m_block_height);

	for (int y = top_y; y <= bottom_y; y++)
	{
		if (field.map[y][map_x] >= CANT_PASS)
		{
			return false;
		}

		if (field.map[y][map_x] == JAGGED)
		{
			m_bGameover = true;
		}

		if (field.map[y][map_x] == GOAL)
		{
			m_bGoal = true;
		}
	}

	return true;
}