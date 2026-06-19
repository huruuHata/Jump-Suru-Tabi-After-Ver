
#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class ClearUI : public BaseUI
{
public:

	ClearUI();

	void Update(Engine* pEngine);
	void Draw(Engine* pEngine);

	void SetNextStageDisplayTrue();
	void SetGameClearDisplayTrue();
	void SetNewModeDisplayTrue();

	bool IsClearTelopDropFinish() const;
	bool IsNextStageDisplay() const;

	bool IsGameClearFadeInFinish() const;
	bool IsGameClearDisplay() const;
	bool IsNewModeDisplay() const;

private:

	void TelopDrop();
	void FadeIn();

	UIData m_stage_clear_back;
	UIData m_stage_clear_telop;
	UIData m_next_stage;
	UIData m_game_clear_back;
	UIData m_game_clear;
	UIData m_new_mode;

	bool m_is_drop_finish; //クリアテロップが降り終わったかどうか
	bool m_is_nextstage_display; //NEXTSTAGE画面を表示してるかどうか

	bool m_is_fade_in_finish; //GAMECLEAR画面がフェードインしきったかどうか
	bool m_is_game_clear_display; //GAMECLEAR画面を表示してるかどうか
	bool m_is_new_mode_display; //NEWMODE説明画面を表示してるかどうか
};