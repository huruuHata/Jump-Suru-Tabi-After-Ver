
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
	json data = FileCheck::FileOpenCheck(FILE_TITLE_UI);

	//背景
	BaseUI::InitializeImage(m_back, data, "Back");

	//キャラクター
	BaseUI::InitializeImage(m_white_chara, data, "WhiteChara");
	BaseUI::InitializeImage(m_black_chara, data, "BlackChara");

	//スタートテキスト
	BaseUI::InitializeImage(m_start, data, "Start");

    //タイトルボード
	BaseUI::InitializeImage(m_title_board, data, "Title");

	//ゲーム全クリアお祝い
	BaseUI::InitializeImage(m_congratulations, data, "Congratulations");
	
	m_bAlpha_max = false;
	m_bAlpha_min = true;
}

void TitleUI::Update(Engine * pEngine)
{
	TitleBoardDrop();
	CharaAppearance();
	TextBreathing();
}

void TitleUI::Draw(Engine * pEngine, const bool is_game_all_clear)
{
	BaseUI::Draw(pEngine, m_back);
	BaseUI::Draw(pEngine, m_white_chara);
	BaseUI::Draw(pEngine, m_black_chara);
	BaseUI::Draw(pEngine, m_start);
	BaseUI::Draw(pEngine, m_title_board);

	if(is_game_all_clear) BaseUI::Draw(pEngine, m_congratulations);

}

void TitleUI::TitleBoardDrop()
{
	if (m_title_board.draw_pos.y < 0)
	{
		m_title_board.draw_pos.y += BOARD_DROP_Y;
	}
	else
	{
		m_title_board.draw_pos.y = 0;
	}
}

void TitleUI::CharaAppearance()
{
	if (m_white_chara.draw_pos.x < 0 && m_white_chara.draw_pos.y > 0 &&
		m_black_chara.draw_pos.x > 0 && m_black_chara.draw_pos.y > 0)
	{
		m_white_chara.draw_pos.x += CHARA_APPEARANCE_SPEED;
		m_white_chara.draw_pos.y -= CHARA_APPEARANCE_SPEED;
		m_black_chara.draw_pos.x -= CHARA_APPEARANCE_SPEED;
		m_black_chara.draw_pos.y -= CHARA_APPEARANCE_SPEED;
	}
	else
	{
		m_white_chara.draw_pos.x = 0;
		m_white_chara.draw_pos.y = 0;
		m_black_chara.draw_pos.x = 0;
		m_black_chara.draw_pos.y = 0;
	}
}

void TitleUI::TextBreathing()
{
	if (m_bAlpha_max)
	{
		m_start.alpha -= BREATING_SPEED;

		if (m_start.alpha <= OPAQUE)
		{
			m_bAlpha_min = true;
			m_bAlpha_max = false;
		}
	}
	if (m_bAlpha_min)
	{
		m_start.alpha += BREATING_SPEED;

		if (m_start.alpha >= OPACITY)
		{
			m_bAlpha_max = true;
			m_bAlpha_min = false;
		}
	}
}
