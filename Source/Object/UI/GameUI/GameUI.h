
#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class GameUI : public BaseUI
{
public:

	void Initialize(const bool bBlack_mode, const bool bBuild_mode);
	void Draw(Engine* pEngine, const int map_no, const bool bBlack_mode, const bool bBuild_mode);

	void SetDisplayBuildModeExplain(const bool bDisplay);

private:

	enum
	{
		FIRST_STAGE = 0,
		HIT_STAGE = 2,
		LAST_STAGE = 9,
	};

	//通常モード用
	UIData m_fall_explain;
	UIData m_goal_explain;
	UIData m_jump_explain;
	UIData m_key_explain;
	UIData m_hit_explain;

	UIData m_congratulations;

	//ステージビルドモード用
	UIData m_build_explain;
	UIData m_build_key_explain;

	bool m_bDisplay_build_mode;
};