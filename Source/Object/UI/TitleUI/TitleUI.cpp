
#define _USING_V110_SDK71_ 1

#include "TitleUI.h"

using namespace KeyString;

namespace
{
	constexpr int BOARD_DROP_Y = 4;
	constexpr int CHARA_APPEARANCE_SPEED = 2;
	constexpr int BREATING_SPEED = 5;
};

TitleUI::TitleUI()
{
	// UI設定ファイル読込

	json data = FileCheck::FileOpenCheck(FILE_TITLE_UI);

	BaseUI::InitializeImage(m_back, data, "Back");
	BaseUI::InitializeImage(m_white_chara, data, "WhiteChara");
	BaseUI::InitializeImage(m_black_chara, data, "BlackChara");
	BaseUI::InitializeImage(m_start, data, "Start");
	BaseUI::InitializeImage(m_title_board, data, "Title");
	BaseUI::InitializeImage(m_congratulations, data, "Congratulations");
	
	m_alpha_state = ALPHA_INCREASE;
}

void TitleUI::Update()
{
	TitleBoardDrop();
	CharaAppearance();
	TextBreathing();
}

void TitleUI::Draw(Engine* pEngine, const bool is_game_all_clear)
{
	BaseUI::Draw(pEngine, m_back);

	DrawCharacters(pEngine);
	DrawTitle(pEngine);

	if (is_game_all_clear)
	{
		BaseUI::Draw(pEngine, m_congratulations);
	}
}

void TitleUI::DrawCharacters(Engine* pEngine)
{
	BaseUI::Draw(pEngine, m_white_chara);
	BaseUI::Draw(pEngine, m_black_chara);
}

void TitleUI::DrawTitle(Engine* pEngine)
{
	BaseUI::Draw(pEngine, m_start);
	BaseUI::Draw(pEngine, m_title_board);
}

//看板降下
void TitleUI::TitleBoardDrop()
{
	if (m_title_board.draw_pos.y < 0)
	{
		m_title_board.draw_pos.y += BOARD_DROP_Y;
		return;
	}

	m_title_board.draw_pos.y = 0;
}

//キャラクター出現
void TitleUI::CharaAppearance()
{
	const bool is_appearance = m_white_chara.draw_pos.x < 0 &&
					           m_white_chara.draw_pos.y > 0 &&
		                       m_black_chara.draw_pos.x > 0 &&
	                   	       m_black_chara.draw_pos.y > 0;

	if (is_appearance)
	{
		m_white_chara.draw_pos.x += CHARA_APPEARANCE_SPEED;
		m_white_chara.draw_pos.y -= CHARA_APPEARANCE_SPEED;

		m_black_chara.draw_pos.x -= CHARA_APPEARANCE_SPEED;
		m_black_chara.draw_pos.y -= CHARA_APPEARANCE_SPEED;

		return;
	}

	m_white_chara.draw_pos.x = 0;
	m_white_chara.draw_pos.y = 0;

	m_black_chara.draw_pos.x = 0;
	m_black_chara.draw_pos.y = 0;
}

//テキスト点滅
void TitleUI::TextBreathing()
{
	switch (m_alpha_state)
	{
	case ALPHA_INCREASE:

		m_start.alpha += BREATING_SPEED;

		if (m_start.alpha >= OPACITY)
		{
			m_start.alpha = OPACITY;
			m_alpha_state = ALPHA_DECREASE;
		}

		break;

	case ALPHA_DECREASE:

		m_start.alpha -= BREATING_SPEED;

		if (m_start.alpha <= OPAQUE)
		{
			m_start.alpha = OPAQUE;
			m_alpha_state = ALPHA_INCREASE;
		}

		break;
	}
}