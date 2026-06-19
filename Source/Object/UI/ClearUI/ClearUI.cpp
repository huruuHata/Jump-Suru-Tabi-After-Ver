
#define _USING_V110_SDK71_ 1

#include "ClearUI.h"

using namespace KeyString;

namespace
{
	constexpr int TELOP_DROP_Y = 8;
	constexpr int FADE_IN_ALPHA = 5;
};

ClearUI::ClearUI()
{
	json data = FileCheck::FileOpenCheck(FILE_CLEAR_UI);

	//ステージクリア背景
	BaseUI::InitializeImage(m_stage_clear_back, data, "StageClearBack");

	//ステージクリアテロップ
	BaseUI::InitializeImage(m_stage_clear_telop, data, "StageClearTelop");

	//ネクストステージ画面
	BaseUI::InitializeImage(m_next_stage, data, "NextStage");

	//ゲームクリア背景
	BaseUI::InitializeImage(m_game_clear_back, data, "GameClearBack");

	//ゲームクリア
	BaseUI::InitializeImage(m_game_clear, data, "GameClear");

	//新モード説明画面
	BaseUI::InitializeImage(m_new_mode, data, "NewMode");

	m_is_drop_finish = false;
	m_is_nextstage_display = false;
	m_is_game_clear_display = false;
	m_is_new_mode_display = false;
	m_is_fade_in_finish = false;
}

void ClearUI::Update(Engine * pEngine)
{
	if (!m_is_nextstage_display) TelopDrop();

	if (m_is_game_clear_display) FadeIn();
}

void ClearUI::Draw(Engine* pEngine)
{
	if (m_is_game_clear_display)
	{
		if (m_is_new_mode_display)
		{
			BaseUI::Draw(pEngine, m_new_mode);
		}
		else
		{
			BaseUI::Draw(pEngine, m_game_clear_back);
			BaseUI::Draw(pEngine, m_game_clear);
		}
	}

	else if(!m_is_nextstage_display)
	{
		BaseUI::Draw(pEngine, m_stage_clear_back);
		BaseUI::Draw(pEngine, m_stage_clear_telop);
	}
	else
	{
		BaseUI::Draw(pEngine, m_next_stage);
	}
}

void ClearUI::SetNextStageDisplayTrue()
{
	m_is_nextstage_display = true;
}

void ClearUI::SetGameClearDisplayTrue()
{
	m_is_game_clear_display = true;
}

void ClearUI::SetNewModeDisplayTrue()
{
	m_is_new_mode_display = true;
}

bool ClearUI::IsClearTelopDropFinish() const
{
	return m_is_drop_finish;
}

bool ClearUI::IsNextStageDisplay() const
{
	return m_is_nextstage_display;
}

bool ClearUI::IsGameClearFadeInFinish() const
{
	return m_is_fade_in_finish;
}

bool ClearUI::IsGameClearDisplay() const
{
	return m_is_game_clear_display;
}

bool ClearUI::IsNewModeDisplay() const
{
	return m_is_new_mode_display;
}

void ClearUI::TelopDrop()
{
	if (m_stage_clear_telop.draw_pos.y < 0)
	{
		m_stage_clear_telop.draw_pos.y += TELOP_DROP_Y;
	}
	else
	{
		m_stage_clear_telop.draw_pos.y = 0;
		m_is_drop_finish = true;
	}
}

void ClearUI::FadeIn()
{
	if (m_is_fade_in_finish) return;

	if (m_game_clear.alpha < OPACITY)
	{
		m_game_clear.alpha += FADE_IN_ALPHA;
	}
	else
	{
		m_game_clear.alpha = OPACITY;
		m_is_fade_in_finish = true;
	}
}


