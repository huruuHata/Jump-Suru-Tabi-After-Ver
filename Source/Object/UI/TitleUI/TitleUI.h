
//タイトル画面のUIの初期化、更新、描画
//UIの落下、出現、点滅を行う

#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class TitleUI : public BaseUI
{
public:

	TitleUI();

	void Update();
	void Draw(Engine* pEngine, const bool is_game_all_clear);

private:

	enum AlphaState
	{
		ALPHA_INCREASE,
		ALPHA_DECREASE
	};

	AlphaState m_alpha_state;

	void TitleBoardDrop();
	void CharaAppearance();
	void TextBreathing();

	void DrawCharacters(Engine* pEngine);
	void DrawTitle(Engine* pEngine);

	UIData m_back;
	UIData m_white_chara;
	UIData m_black_chara;
	UIData m_title_board;
	UIData m_start;
	UIData m_congratulations;
};