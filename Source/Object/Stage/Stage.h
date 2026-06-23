
//ステージの初期化、更新、描画を行う
//ステージに関係するデータのゲッターあり

#pragma once

#include<fstream>

#include "..\\..\\Object\\Base\\BaseObject\\BaseObject.h"
#include "..\\Engine\\FileCheck\\FileCheck.h"

class Stage : public BaseObject
{
public:

	void Initialize(const bool is_black_mode, const bool is_build_mode, const int map_no);
	void Update(Engine* pEngine);
	void Draw(Engine* pEngine);

	Vector2Int GetStartPlayerPosition() const;
	Field GetMapArray() const;
	
	int GetBlockWidth() const;
	int GetBlockHeight() const;

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

	void FileSetting(json& data, const bool is_black_mode, const bool is_build_mode, const int map_no);
	void StageBuild(Engine* pEngine);

	int m_block_row;
	int m_block_col;
	int m_map_chip_col;

	int m_build_block_num;

	Vector2Int m_start_pos;

	static constexpr int MAP_ROW = 12;
	static constexpr int MAP_COL = 12;

	int m_map_array[MAP_ROW][MAP_COL];
};

