
#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class TitleUI : public BaseUI
{
public:

	TitleUI();

	void Update(Engine* pEngine);
	void Draw(Engine* pEngine, const bool is_game_all_clear);

private:

	void TitleBoardDrop();
	void CharaAppearance();
	void TextBreathing();

	UIData m_back; 
	UIData m_white_chara;
	UIData m_black_chara;
	UIData m_title_board;
	UIData m_start;
	UIData m_congratulations;

	bool m_bAlpha_max;
	bool m_bAlpha_min;
};