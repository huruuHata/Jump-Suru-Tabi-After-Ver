
//プレイヤーの動きの信号を送る

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\Base\\BaseObject\\BaseObject.h"
#include "..\\PlayerInput\\PlayerInput.h"
#include "..\\..\\Engine\\Vector2Int\\Vector2Int.h"
#include "..\\..\\Player\\PlayerCollide\\PlayerCollide.h"

class PlayerMovement 
{
public:

	PlayerMovement();

	struct Output
	{
		int move_x;
		int look_dir;
	};

	Output Update(const Field& field, BaseObject::DrawSet& draw, const int move_speed,  const int block_width, const int block_height, const unsigned int key_flag, const float delta_time);

	bool IsGoal() const;
	bool IsGameover() const;

private:

	enum
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	bool CanMoveX(const Field& field, BaseObject::DrawSet& draw, const int next_pixel_x, const int block_width, const int block_height);

	bool m_is_goal;
	bool m_is_gameover;

	int m_look_dir;

	PlayerCollide m_collide;
};
