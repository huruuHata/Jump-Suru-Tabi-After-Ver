
#define _USING_V110_SDK71_ 1

#include "GameSystem.h"

bool GameSystem::GetBlackMode() const
{
	return m_is_black_mode;
}

bool GameSystem::GetBuildMode() const
{
	return m_is_build_mode;
}

bool GameSystem::GetGameClear() const
{
	return m_is_gameclear;
}

bool GameSystem::GetAllGameClear() const
{
	return m_is_all_gameclear;
}

void GameSystem::SetGameMode(const bool bBlack_mode, const bool bBuild_mode)
{
	m_is_black_mode = bBlack_mode;
	m_is_build_mode = bBuild_mode;
}

void GameSystem::SetGameClear(const bool is_game_clear)
{
	m_is_gameclear = is_game_clear;
}

void GameSystem::SetAllGameClear(const bool is_all_game_clear)
{
	m_is_all_gameclear = is_all_game_clear;
}
