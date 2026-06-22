
//ゲームオーバー画面のUIの初期化、更新、描画
//UIのフェードインを行う


#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class GameoverUI : public BaseUI
{
public:

	GameoverUI();

	void Update();
	void Draw(Engine* pEngine);

	bool IsFadeInFinish() const;

private:

	void FadeIn();

	bool m_is_fade_in_finish;

	UIData m_gameover_back;
	UIData m_gameover;
};