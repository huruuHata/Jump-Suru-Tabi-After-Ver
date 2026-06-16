
#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class ClearUI : public BaseUI
{
public:

	ClearUI();

	void Update(Engine* pEngine);
	void Draw(Engine* pEngine);

	void SetNextStageDisplayTrue();

	bool IsClearTelopDropFinish() const;
	bool IsNextStageDisplay() const;
	
private:

	void TelopDrop();

	UIData m_stage_clear_back;
	UIData m_stage_clear_telop;
	UIData m_nextstage;

	bool m_is_drop_finish; //クリアテロップが降り終わったかどうか
	bool m_is_nextstage_display; //NEXTSTAGE画面を表示してるかどうか

};