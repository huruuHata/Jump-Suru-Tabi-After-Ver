
#define _USING_V110_SDK71_ 1

#include "BaseObject.h"

namespace
{
	constexpr int CHIP_COL = 5;
}

void BaseObject::Draw(Engine * pEngine)
{
	RECT sour, dest;

	int x, y;

	x = m_draw.texture_num % CHIP_COL * m_draw.image_width;
	y = m_draw.texture_num / CHIP_COL * m_draw.image_height;
	SetRect(&sour, x, y, x + m_draw.image_width, y + m_draw.image_height);

	x = m_draw.position.x;
	y = m_draw.position.y;
	SetRect(&dest, x, y, x + m_draw.draw_width, y + m_draw.draw_height);

	pEngine->Blt(&dest, m_draw.filename, &sour);
}
