
#define _USING_V110_SDK71_ 1

#include "Back.h"

using namespace KeyString;

void Back::Initialize()
{
	json data = FileCheck::FileOpenCheck(FILE_STAGE);
	json back = data["Back"];

	m_draw.position = Vector2Int(back["Position"]["x"], back["Position"]["y"]);

	m_draw.image_width = back["Image"]["Width"];
	m_draw.image_height = back["Image"]["Height"];
	m_draw.draw_width = back["Draw"]["Width"];
	m_draw.draw_height = back["Draw"]["Height"];
	
	m_draw.filename = back["Texture"];
	m_draw.texture_num = 0;
}