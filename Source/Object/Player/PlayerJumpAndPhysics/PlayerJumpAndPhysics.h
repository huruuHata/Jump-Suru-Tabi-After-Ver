
//プレイヤーのジャンプと落下の処理

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\Engine\\Vector2Int\\Vector2Int.h"
#include "..\\..\\Engine\\FileCheck\\FileCheck.h"
#include "..\\..\\Base\\BaseObject\\BaseObject.h"
#include "..\\..\\Player\\PlayerCollide\\PlayerCollide.h"

class PlayerJumpAndPhysics
{
public:

	PlayerJumpAndPhysics();

	void Initialize(const json& data);

	void Update(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height, const float delta_time);

	bool IsGrounded() const;
	bool IsGoal() const;
	bool IsGameover() const;

	void JumpCheck(Engine* pEngine, BaseObject::DrawSet& draw, const bool is_black_mode);

private:

	void Jumping(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height, const float delta_time);
	void GroundProcess(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height);
	void Falling(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height, const float delta_time);
	void UpCheck(const Field& field, BaseObject::DrawSet& draw, const int block_width, const int block_height);

	bool CheckGround(const Field& field, int& ground_y, BaseObject::DrawSet& draw, const int block_width, const int block_height);

	bool m_is_grounded;
	bool m_is_jumping;

	bool m_is_goal;
	bool m_is_gameover;

	int m_jump_speed;
	int m_jump_power;
	int m_save_height;

	int m_jump_power_white;
	int m_jump_power_black;

	int m_fall_death_y;

	PlayerCollide m_collide;
};
