
//プレイヤーのジャンプと落下の処理

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\Engine\\Vector2Int\\Vector2Int.h"
#include "..\\..\\Engine\\FileCheck\\FileCheck.h"
#include "..\\..\\Base\\BaseObject\\BaseObject.h"
#include "..\\..\\Stage\\Stage.h"

class PlayerJumpAndPhysics
{
public:

	PlayerJumpAndPhysics();

	struct Output
	{
		int new_y;
		int power_y;
		bool bGrounded;
	};

	void Initialize(const json& data, const int block_width, const int block_height);

	Output Update(const Field& field, BaseObject::DrawSet& draw, const float delta_time);

	bool IsGrounded() const;
	bool IsGoal() const;
	bool IsGameover() const;

	void JumpCheck(Engine* pEngine, BaseObject::DrawSet& draw, const bool bBlack_mode);

private:

	void Jumping(const Field& field, BaseObject::DrawSet& draw, const float delta_time);
	void GroundProcess(const Field& field, BaseObject::DrawSet& draw);
	void Falling(const Field& field, BaseObject::DrawSet& draw, const float delta_time);
	void UpCheck(const Field& field, BaseObject::DrawSet& draw);

	bool CheckGround(const Field& field, int& ground_y, BaseObject::DrawSet& draw);

	bool m_bGrounded;
	bool m_bJumping;
	
	int m_jump_speed;
	int m_jump_power;
	int m_save_height;

	int m_jump_power_white;
	int m_jump_power_black;

	int m_block_width;
	int m_block_height;

	bool m_bGoal;
	bool m_bGameover;
};
