
//UIの基底クラス UIの描画と初期化用の関数を保有する

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\Engine\\Vector2Int\\Vector2Int.h"
#include "..\\..\\Engine\\FileCheck\\FileCheck.h"

class BaseUI
{
public:

	struct UIData
	{
		std::string filename;
		Vector2Int draw_pos;
		int image_width;
		int image_height;
		int draw_width;
		int draw_height;
		int alpha;
	};

protected:

	void Draw(Engine* pEngine, const UIData& ui);

	//UIData, json, キー
	void InitializeImage(UIData& ui_data, json& data, const std::string& key);

private:


};
