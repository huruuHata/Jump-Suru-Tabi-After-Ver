
//Playerの各サブクラスから処理結果を受け取り、座標・テクスチャに反映する

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

	void Initialize(const bool is_black_mode, const int block_width, const int block_height, const Vector2Int start_pos);
	void Update(Engine* pEngine, const Field& field, const bool is_black_mode, const int block_width, const int block_height, const float delta_time);

	bool IsGoal() const;
	bool IsGameover() const;

private:

	void Move(const Field& field, const int block_width, const int block_height, const float delta_time);
	void JumpAndPhysics(Engine* pEngine, const Field& field, const bool is_black_mode, const int block_width, const int block_height, const float delta_time);

	std::string m_white_texture;
	std::string m_black_texture;

	int m_move_speed;
	
	PlayerInput m_input;
	PlayerMovement m_movement;
	PlayerJumpAndPhysics m_jump_physics;

	json m_data;
};

