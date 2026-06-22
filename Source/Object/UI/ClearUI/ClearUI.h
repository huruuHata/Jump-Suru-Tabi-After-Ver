
//ゲーム、ステージクリア画面のUIの初期化、更新、描画 
//画面切り替え用State

#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class ClearUI : public BaseUI
{
public:

	enum class State
	{
		StageClear,
		NextStage,
		GameClear,
		NewMode
	};

	ClearUI();

	void Update();
	void Draw(Engine* pEngine);

	void ChangeState(State state);

	bool IsClearTelopDropFinish() const;
	bool IsGameClearFadeInFinish() const;

	State GetState() const;

private:

	void TelopDrop();
	void FadeIn();

	//条件によって描画分岐
	void DrawStageClear(Engine* pEngine);
	void DrawNextStage(Engine* pEngine);
	void DrawGameClear(Engine* pEngine);
	void DrawNewMode(Engine* pEngine);

	State m_state;

	UIData m_stage_clear_back;
	UIData m_stage_clear_telop;
	UIData m_next_stage;
	UIData m_game_clear_back;
	UIData m_game_clear;
	UIData m_new_mode;

	bool m_is_drop_finish;
	bool m_is_fade_in_finish;
};