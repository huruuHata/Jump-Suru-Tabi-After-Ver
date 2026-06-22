
//プレイヤーのキー入力処理

#pragma once

#include "..\\..\\..\\GameBase.h"

class PlayerInput
{
public:

	PlayerInput();

	void Update(Engine* pEngine);

	unsigned int GetKeyFlag() const;

	enum
	{
		UP_KEY = 0x01,
		DOWN_KEY = 0x02,
		LEFT_KEY = 0x04,
		RIGHT_KEY = 0x08,	
		JUMP_KEY = 0x10,
	};

private:

	void KeyInput(Engine* pEngine);

	unsigned int m_key_flag;
};
