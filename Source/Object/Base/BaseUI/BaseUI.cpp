
#define _USING_V110_SDK71_ 1

#include "BaseUI.h"

using namespace WindowSetting;
using namespace KeyString;

void BaseUI::Draw(Engine* pEngine, const UIData& ui)
{
	RECT sour, dest;

	int x, y;

	SetRect(&sour, 0, 0, ui.image_width, ui.image_height);

	x = (int)ui.draw_pos.x;
	y = (int)ui.draw_pos.y;
	SetRect(&dest, x, y, x + ui.draw_width, y + ui.draw_height);

	pEngine->Blt(&dest, ui.filename, &sour, ui.alpha);
}
