
//プレイヤーの動きを他クラスからもらい、反映する

#pragma once

#include "..\\..\\Object\\Base\\BaseObject\\BaseObject.h"
#include "..\\Engine\\FileCheck\\FileCheck.h"

#include "..\\Player\PlayerInput\PlayerInput.h"
#include "..\\Player\PlayerJumpAndPhysics\PlayerJumpAndPhysics.h"
#include "..\\Player\PlayerMovement\PlayerMovement.h"

class Player : public BaseObject
{
public:

	Player();

	void Initialize(const bool bBlack_mode, const int block_width, const int block_height, const Vector2Int start_pos);
	void Update(Engine* pEngine, const Field& field, const bool bBlack_mode, const float delta_time);

	bool IsGoal() const;
	bool IsGameover() const;

private:

	void Move(Engine* pEngine, const Field& field, float delta_time);
	void JumpAndPhysics(Engine* pEngine, const Field& field, const bool bBlack_mode, float delta_time);

	std::string m_white_texture;
	std::string m_black_texture;

	int m_block_width;
	int m_block_height;

	int m_move_speed;
	bool m_bJumping;

	PlayerInput m_input;
	PlayerMovement m_movement;
	PlayerJumpAndPhysics m_jump_physics;

	json m_data;
};

