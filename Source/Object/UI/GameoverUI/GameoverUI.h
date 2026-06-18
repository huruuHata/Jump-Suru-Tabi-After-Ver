
#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class GameoverUI : public BaseUI
{
public:

	GameoverUI();

	void Update(Engine* pEngine);
	void Draw(Engine* pEngine);

	bool IsFadeInFinish() const;

private:

	void FadeIn();

	bool m_is_fade_in_finish;

	UIData m_gameover_back;
	UIData m_gameover;
};