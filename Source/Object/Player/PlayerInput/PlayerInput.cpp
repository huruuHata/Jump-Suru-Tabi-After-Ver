
#define _USING_V110_SDK71_ 1

#include "PlayerInput.h"

using namespace KeyString;

PlayerInput::PlayerInput() : m_key_flag(0x00)
{
}

void PlayerInput::Update(Engine * pEngine)
{
	KeyInput(pEngine);
}

void PlayerInput::KeyInput(Engine* pEngine)
{
	if (pEngine->GetKeyState(DIK_W)) m_key_flag |= UP_KEY;
	else							 m_key_flag &= ~UP_KEY;

	if (pEngine->GetKeyState(DIK_S)) m_key_flag |= DOWN_KEY;
	else							 m_key_flag &= ~DOWN_KEY;

	if (pEngine->GetKeyState(DIK_D)) m_key_flag |= RIGHT_KEY;
	else							 m_key_flag &= ~RIGHT_KEY;

	if (pEngine->GetKeyState(DIK_A)) m_key_flag |= LEFT_KEY;
	else						     m_key_flag &= ~LEFT_KEY;

	if (pEngine->GetKeyState(DIK_SPACE)) m_key_flag |= JUMP_KEY;
	else								 m_key_flag &= ~JUMP_KEY;
}

unsigned int PlayerInput::GetKeyFlag()
{
	return m_key_flag;
}
