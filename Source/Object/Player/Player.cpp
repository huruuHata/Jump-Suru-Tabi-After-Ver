
#define _USING_V110_SDK71_ 1

#include "Player.h"

using namespace KeyString;
using namespace InputKey;

Player::Player()
{
	m_data = FileCheck::FileOpenCheck(FILE_PLAYER);

	m_draw.position = Vector2Int(m_data["Position"]["x"], m_data["Position"]["y"]);
	
	m_draw.image_width  = m_data["Image"]["Width"];
	m_draw.image_height = m_data["Image"]["Height"];
	m_draw.draw_width  = m_data["Draw"]["Width"];
	m_draw.draw_height = m_data["Draw"]["Height"];

	m_draw.filename = m_data["Texture"]["White"];
	m_draw.texture_num = m_data["Texture"]["Num"];

	m_white_texture = m_data["Texture"]["White"];
	m_black_texture = m_data["Texture"]["Black"];

	m_move_speed = m_data["Speed"]["Move"];
}

void Player::Initialize(const bool bBlack_mode, const int block_width, const int block_height, const Vector2Int start_pos)
{
	if (!bBlack_mode) m_draw.filename = m_white_texture;
	else              m_draw.filename = m_black_texture;

	m_draw.position = Vector2Int(start_pos.x * m_draw.draw_width, start_pos.y * m_draw.draw_height);

	m_draw.filename = bBlack_mode ? m_black_texture : m_white_texture;

	m_block_width = block_width;
	m_block_height = block_height;

	m_jump_physics.Initialize(m_data, m_block_width, m_block_height);
	m_movement.Initialzie(m_block_width, m_block_height);

	m_collide.Initialize();
}

void Player::Update(Engine * pEngine, const Field& field, const float delta_time)
{
	m_input.Update(pEngine);

	Move(pEngine, field, delta_time);
	JumpAndPhysics(pEngine, field, delta_time);

	m_collide.Update();
}

bool Player::IsGoal() const
{
	return m_movement.IsGoal() || m_jump_physics.IsGoal();
}

bool Player::IsGameover() const
{
	return m_movement.IsGameover() || m_jump_physics.IsGameover();
}

void Player::Move(Engine * pEngine, const Field& field, float delta_time)
{
	auto moves = m_movement.Update(field, m_draw, m_move_speed, m_input.GetKeyFlag(), delta_time);

	//向く方向を変える
	m_draw.texture_num = moves.look_dir;

	m_draw.position.x += (int)((moves.move_x * m_move_speed) * delta_time);
}

void Player::JumpAndPhysics(Engine * pEngine, const Field& field, float delta_time)
{
	if ((m_input.GetKeyFlag() & PlayerInput::JUMP_KEY))
	{
		m_jump_physics.JumpCheck(pEngine, m_draw, false);
	}

	m_jump_physics.Update(field, m_draw, delta_time);
}

