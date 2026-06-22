
//モード切替を行う＋ゲームクリアを所持する

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
	void SetGameClear(const bool is_game_clear);
	void SetAllGameClear(const bool is_all_game_clear);

private:

	bool m_bBlack_mode;
	bool m_bBuild_mode;
	
	bool m_is_gameclear;
	bool m_is_all_gameclear;

	GameSystem() { m_bBlack_mode = false; m_bBuild_mode = false; m_is_gameclear = false; m_is_all_gameclear = false; }

	~GameSystem() = default;
};