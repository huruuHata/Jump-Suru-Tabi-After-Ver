
#define _USING_V110_SDK71_ 1

#include "GameUI.h"

using namespace KeyString;

void GameUI::Initialize(const bool bBlack_mode, const bool bBuild_mode)
{
	json data = FileCheck::FileOpenCheck(FILE_GAME_UI);
	json explain = data["Explain"];

	if (bBuild_mode)
	{
		//ステージビルド説明
		BaseUI::InitializeImage(m_build_explain, explain, "Build");
		BaseUI::InitializeImage(m_build_key_explain, explain, "BuildKey");
	}
	else if(!bBlack_mode)
	{
		//ゲーム説明
		BaseUI::InitializeImage(m_fall_explain, explain, "Fall");
		BaseUI::InitializeImage(m_goal_explain, explain, "Goal");
		BaseUI::InitializeImage(m_key_explain, explain, "Key");
		BaseUI::InitializeImage(m_jump_explain, explain, "Jump");
		BaseUI::InitializeImage(m_hit_explain, explain, "Hit");
	}

	m_bDisplay_build_mode = true;
}

void GameUI::Draw(Engine * pEngine, const int map_no, const bool bBlack_mode, const bool bBuild_mode)
{
	if (bBuild_mode)
	{
		BaseUI::Draw(pEngine, m_build_key_explain);
		
		if (m_bDisplay_build_mode)
		{
			BaseUI::Draw(pEngine, m_build_explain);
		}
	}
	else if (!bBlack_mode)
	{
		if (map_no == 0)
		{
			BaseUI::Draw(pEngine, m_fall_explain);
			BaseUI::Draw(pEngine, m_goal_explain);
			BaseUI::Draw(pEngine, m_key_explain);
			BaseUI::Draw(pEngine, m_jump_explain);
		}
		if (map_no == 2)
		{
			BaseUI::Draw(pEngine, m_hit_explain);
		}
	}
}

void GameUI::SetDisplayBuildModeExplain(const bool bDisplay)
{
	m_bDisplay_build_mode = bDisplay;
}
