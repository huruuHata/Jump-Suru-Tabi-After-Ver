
#define _USING_V110_SDK71_ 1

#include "GameSystem.h"

bool GameSystem::GetBlackMode() const
{
	return m_bBlack_mode;
}

bool GameSystem::GetBuildMode() const
{
	return m_bBuild_mode;
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
	m_bBlack_mode = bBlack_mode;
	m_bBuild_mode = bBuild_mode;
}

void GameSystem::SetGameClearTrue()
{
	m_is_gameclear = true;
}

void GameSystem::SetAllGameClearTrue()
{
	m_is_all_gameclear = true;
}
