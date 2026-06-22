
//ゲーム画面のUIの初期化、描画
//メインモードの説明UIなどを表示＋ステージビルドモードの説明画面の表示

#pragma once

#include "..\\..\\Base\\BaseUI\\BaseUI.h"

class GameUI : public BaseUI
{
public:

	void Initialize(const bool is_black_mode, const bool is_build_mode);
	void Draw(Engine* pEngine, const int map_no, const bool is_black_mode, const bool is_build_mode);

	void SetMapNo(int map_no);
	void SetDisplayBuildModeExplain(bool isDisplay);

private:

	enum
	{
		FIRST_STAGE = 0,
		HIT_STAGE = 2,
		LAST_STAGE = 9,
	};

	//条件によって描画分岐
	void DrawBuildMode(Engine* pEngine);
	void DrawNormalMode(Engine* pEngine, const int map_no);
	void DrawBlackMode(Engine* pEngine, const int map_no);

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

	int m_map_no;

	bool m_is_build_explain_visible;
};