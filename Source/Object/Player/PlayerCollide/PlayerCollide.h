
//プレイヤーが壁にヒットした際の処理

#pragma once

#include "..\\..\\..\\GameBase.h"

class PlayerCollide
{
public:

	PlayerCollide();

	void Initialize();

	void Update();
	

private:

	bool m_bHit; 	

};
