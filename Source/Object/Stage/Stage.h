
#pragma once

#include<fstream>

#include "..\\..\\Object\\Base\\BaseObject\\BaseObject.h"
#include "..\\Engine\\FileCheck\\FileCheck.h"

class Stage : public BaseObject
{
public:

	void Initialize(const bool bBlack_mode, const bool bBuild_mode, const int map_no);
	void Update(Engine* pEngine);
	void Draw(Engine* pEngine);

	Vector2Int GetStartPlayerPosition();
	Field GetMapArray();
	
	int GetBlockWidth();
	int GetBlockHeight();

	static int ToMapX(int pixel_x, int block_width);
	static int ToMapY(int pixel_y, int block_height);

	enum
	{
		STAGE = 0,
		GOAL = 1,
		CANT_PASS = 2,
		BLOCK = 3,
		JAGGED_UP = 4,
		JAGGED_DOWN = 5,
	};

private:

	void FileSetting(json& data, const bool bBlack_mode, const bool bBuild_mode, const int map_no);
	void StageBuild(Engine* pEngine);

	int m_block_row;
	int m_block_col;
	int m_map_chip_col;

	int m_build_block_num;

	Vector2Int m_start_pos;

	int m_map_array[12][12];
};

