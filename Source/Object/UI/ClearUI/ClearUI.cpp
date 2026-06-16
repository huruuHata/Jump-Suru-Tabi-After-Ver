
#define _USING_V110_SDK71_ 1

#include "ClearUI.h"

using namespace KeyString;

namespace
{
	constexpr int TELOP_DROP_Y = 8;
};

ClearUI::ClearUI()
{
	json data = FileCheck::FileOpenCheck(FILE_CLEAR_UI);

	//ステージクリア背景
	BaseUI::InitializeImage(m_stage_clear_back, data, "StageClearBack");

	//ステージクリアテロップ
	BaseUI::InitializeImage(m_stage_clear_telop, data, "StageClearTelop");

	//ネクストステージ画面
	BaseUI::InitializeImage(m_nextstage, data, "NextStage");

	m_is_drop_finish = false;
	m_is_nextstage_display = false;
}

void ClearUI::Update(Engine * pEngine)
{
	if (!m_is_nextstage_display) TelopDrop();
}

void ClearUI::Draw(Engine* pEngine)
{
	if(!m_is_nextstage_display)
	{
		BaseUI::Draw(pEngine, m_stage_clear_back);
		BaseUI::Draw(pEngine, m_stage_clear_telop);
	}
	else
	{
		BaseUI::Draw(pEngine, m_nextstage);
	}
}

void ClearUI::SetNextStageDisplayTrue()
{
	m_is_nextstage_display = true;
}

bool ClearUI::IsClearTelopDropFinish() const
{
	return m_is_drop_finish;
}

bool ClearUI::IsNextStageDisplay() const
{
	return m_is_nextstage_display;
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


