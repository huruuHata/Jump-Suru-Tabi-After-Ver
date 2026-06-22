
#define _USING_V110_SDK71_ 1

#include "GameUI.h"

using namespace KeyString;

void GameUI::Initialize(const bool is_black_mode, const bool is_build_mode)
{
	// UI設定ファイル読込

	json data = FileCheck::FileOpenCheck(FILE_GAME_UI);
	json explain = data["Explain"];

	if (is_build_mode)
	{
		BaseUI::InitializeImage(m_build_explain, explain, "Build");
		BaseUI::InitializeImage(m_build_key_explain, explain, "BuildKey");
	}
	else if (!is_black_mode)
	{
		BaseUI::InitializeImage(m_fall_explain, explain, "Fall");
		BaseUI::InitializeImage(m_goal_explain, explain, "Goal");
		BaseUI::InitializeImage(m_key_explain, explain, "Key");
		BaseUI::InitializeImage(m_jump_explain, explain, "Jump");
		BaseUI::InitializeImage(m_hit_explain, explain, "Hit");
	}
	else
	{
		BaseUI::InitializeImage(m_congratulations, explain,"Congratulations");
	}

	m_is_build_explain_visible = true;
}

void GameUI::Draw(Engine* pEngine, const int map_no, const bool is_black_mode, const bool is_build_mode)
{
	if (is_build_mode)
	{
		DrawBuildMode(pEngine);
		return;
	}

	if (!is_black_mode)
	{
		DrawNormalMode(pEngine, map_no);
		return;
	}

	DrawBlackMode(pEngine, map_no);
}

void GameUI::DrawBuildMode(Engine* pEngine)
{
	BaseUI::Draw(pEngine, m_build_key_explain);

	if (m_is_build_explain_visible)
	{
		BaseUI::Draw(pEngine, m_build_explain);
	}
}

void GameUI::DrawNormalMode(Engine* pEngine, const int map_no)
{
	switch (map_no)
	{
	case FIRST_STAGE:

		BaseUI::Draw(pEngine, m_fall_explain);
		BaseUI::Draw(pEngine, m_goal_explain);
		BaseUI::Draw(pEngine, m_key_explain);
		BaseUI::Draw(pEngine, m_jump_explain);

		break;

	case HIT_STAGE:

		BaseUI::Draw(pEngine, m_hit_explain);

		break;

	default:
		break;
	}
}

void GameUI::DrawBlackMode(Engine* pEngine, const int map_no)
{
	if (map_no == LAST_STAGE)
	{
		BaseUI::Draw(pEngine, m_congratulations);
	}
}

void GameUI::SetDisplayBuildModeExplain(const bool bDisplay)
{
	m_is_build_explain_visible = bDisplay;
}