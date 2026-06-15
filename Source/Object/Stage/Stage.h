
#pragma once

#include<fstream>

#include "..\\..\\Object\\Base\\BaseObject\\BaseObject.h"
#include "..\\Engine\\FileCheck\\FileCheck.h"

class Stage : public BaseObject
{
public:

	void Initialize(const bool bBlack_mode, const bool bBuild_mode, const int map_no);
	void Updata();
	void Draw(Engine* pEngine);

	Vector2Int GetStartPlayerPosition();
	Field GetMapArray();
	
	int GetBlockWidth();
	int GetBlockHeight();

private:

	void FileSetting(json& data, const bool bBlack_mode, const bool bBuild_mode, const int map_no);

	int m_block_row;
	int m_block_col;
	int m_map_chip_col;

	Vector2Int m_start_pos;

	int m_map_array[12][12];
};

