
#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\Engine\\Vector2Int\\Vector2Int.h"

using namespace std;

class BaseObject
{
public:

	struct DrawSet
	{
		Vector2Int position;
		int image_width;
		int image_height;
		int draw_width;
		int draw_height;
		int texture_num;
		string filename;
	};

	void Draw(Engine* pEngine);
	
protected:

	DrawSet m_draw;

};
