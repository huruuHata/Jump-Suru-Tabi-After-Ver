
//モード切替用

#pragma once

#include "..\\..\\..\\GameBase.h"

class GameSystem
{
public:

	static GameSystem& getInstance()
	{
		static GameSystem instance;
		return instance;
	}

	bool GetBlackMode() const;
	bool GetBuildMode() const;

	void SetGameMode(const bool bBlack_mode, const bool bBuild_mode);

private:

	bool m_bBlack_mode;
	bool m_bBuild_mode;

	GameSystem() { m_bBlack_mode = false; m_bBuild_mode = false; }

	~GameSystem() = default;
};