
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
	bool GetGameClear() const;
	bool GetAllGameClear() const;

	void SetGameMode(const bool bBlack_mode, const bool bBuild_mode);
	void SetGameClearTrue();
	void SetAllGameClearTrue();

private:

	bool m_bBlack_mode;
	bool m_bBuild_mode;
	
	bool m_is_gameclear;
	bool m_is_all_gameclear;

	GameSystem() { m_bBlack_mode = false; m_bBuild_mode = false; m_is_gameclear = false; m_is_all_gameclear = false; }

	~GameSystem() = default;
};