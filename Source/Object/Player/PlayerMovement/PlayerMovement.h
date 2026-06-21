
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

	void Initialize(const int block_width, const int block_height);
	Output Update(const Field& field, BaseObject::DrawSet& draw, const int move_speed,  const unsigned int key_flag, const float delta_time);

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

	bool CanMoveX(const Field& field, const int next_pixel_x, BaseObject::DrawSet& draw);

	bool m_bGoal;
	bool m_bGameover;

	int m_look_dir;

	int m_block_width;
	int m_block_height;

	PlayerCollide m_collide;
};
