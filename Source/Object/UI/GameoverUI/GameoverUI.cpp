
#define _USING_V110_SDK71_ 1

#include "GameoverUI.h"

using namespace KeyString;

namespace
{
	constexpr int FADE_IN_ALPHA_PLUS = 5;
};


GameoverUI::GameoverUI()
{
	json data = FileCheck::FileOpenCheck(FILE_GAMEOVER_UI);

	//ゲームオーバー背景
	BaseUI::InitializeImage(m_gameover_back, data, "GameoverBack");

	//ゲームオーバー
	BaseUI::InitializeImage(m_gameover, data, "Gameover");

	m_is_fade_in_finish = false;
}

void GameoverUI::Update(Engine * pEngine)
{
	if (!m_is_fade_in_finish) FadeIn();
}

void GameoverUI::Draw(Engine * pEngine)
{
	BaseUI::Draw(pEngine, m_gameover_back);
	BaseUI::Draw(pEngine, m_gameover);
}

bool GameoverUI::IsFadeInFinish() const
{
	return m_is_fade_in_finish;
}

void GameoverUI::FadeIn()
{
	if (m_gameover.alpha < OPACITY)
	{
		m_gameover.alpha += FADE_IN_ALPHA_PLUS;
	}
	else
	{
		m_gameover.alpha = OPACITY;
		m_is_fade_in_finish = true;
	}
}
