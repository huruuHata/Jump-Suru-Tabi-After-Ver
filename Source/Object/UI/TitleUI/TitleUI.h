
#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class TitleUI : public BaseUI
{
public:

	TitleUI();

	void Update(Engine* pEngine);
	void Draw(Engine* pEngine);

private:

	void TitleBoardDrop();
	void CharaAppearance();
	void TextBreathing();

	UIData m_back; 
	UIData m_white_chara;
	UIData m_black_chara;
	UIData m_title_board;
	UIData m_start;

	bool m_bAlpha_max;
	bool m_bAlpha_min;
};