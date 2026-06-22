
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
	// UI設定ファイル読込

	json data = FileCheck::FileOpenCheck(FILE_CLEAR_UI);

	BaseUI::InitializeImage(m_stage_clear_back, data, "StageClearBack");
	BaseUI::InitializeImage(m_stage_clear_telop, data, "StageClearTelop");
	BaseUI::InitializeImage(m_next_stage, data, "NextStage");
	BaseUI::InitializeImage(m_game_clear_back, data, "GameClearBack");
	BaseUI::InitializeImage(m_game_clear, data, "GameClear");
	BaseUI::InitializeImage(m_new_mode, data, "NewMode");

	m_state = State::StageClear;

	m_is_drop_finish = false;
	m_is_fade_in_finish = false;
}

void ClearUI::Update()
{
	switch (m_state)
	{
	case State::StageClear:
		TelopDrop();
		break;

	case State::GameClear:
		FadeIn();
		break;

	default:
		break;
	}
}

void ClearUI::Draw(Engine* pEngine)
{
	switch (m_state)
	{
	case State::StageClear:
		DrawStageClear(pEngine);
		break;

	case State::NextStage:
		DrawNextStage(pEngine);
		break;

	case State::GameClear:
		DrawGameClear(pEngine);
		break;

	case State::NewMode:
		DrawNewMode(pEngine);
		break;
	}
}

void ClearUI::ChangeState(State state)
{
	m_state = state;
}

bool ClearUI::IsClearTelopDropFinish() const
{
	return m_is_drop_finish;
}

bool ClearUI::IsGameClearFadeInFinish() const
{
	return m_is_fade_in_finish;
}

ClearUI::State ClearUI::GetState() const
{
	return m_state;
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

void ClearUI::DrawStageClear(Engine* pEngine)
{
	BaseUI::Draw(pEngine, m_stage_clear_back);
	BaseUI::Draw(pEngine, m_stage_clear_telop);
}

void ClearUI::DrawNextStage(Engine* pEngine)
{
	BaseUI::Draw(pEngine, m_next_stage);
}

void ClearUI::DrawGameClear(Engine* pEngine)
{
	BaseUI::Draw(pEngine, m_game_clear_back);
	BaseUI::Draw(pEngine, m_game_clear);
}

void ClearUI::DrawNewMode(Engine* pEngine)
{
	BaseUI::Draw(pEngine, m_new_mode);
}




