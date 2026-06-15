
#define _USING_V110_SDK71_ 1

#include "ClearUI.h"

ClearUI::ClearUI()
{
	json data = FileCheck::FileOpenCheck(FILE_CLEAR_UI);

	//ハート
	InitializeImage(m_heart, data, "Heart");

	//スタート
	InitializeImage(m_start, data, "Start");

}
