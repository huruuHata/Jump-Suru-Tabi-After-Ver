
#define _USING_V110_SDK71_ 1

#include "BaseUI.h"

using namespace WindowSetting;
using namespace KeyString;

void BaseUI::InitializeImage(UIData& ui_data, json& data, const std::string& key)
{
	ui_data.filename = data[key]["Filename"];
	ui_data.image_width = data[key]["Image"]["Width"];
	ui_data.image_height = data[key]["Image"]["Height"];
	ui_data.draw_width = data[key]["Draw"]["Width"];
	ui_data.draw_height = data[key]["Draw"]["Height"];
	ui_data.alpha = data[key]["Alpha"];
	ui_data.draw_pos = Vector2Int(data[key]["Position"]["x"], data[key]["Position"]["y"]);
}

void BaseUI::DrawUI(Engine* pEngine, const UIData& ui)
{
	RECT sour, dest;

	int x, y;

	SetRect(&sour, 0, 0, ui.image_width, ui.image_height);

	x = (int)ui.draw_pos.x;
	y = (int)ui.draw_pos.y;
	SetRect(&dest, x, y, x + ui.draw_width, y + ui.draw_height);

	pEngine->Blt(&dest, ui.filename, &sour, ui.alpha);
}
