
#define _USING_V110_SDK71_ 1

#include "Stage.h"

using namespace KeyString;

void Stage::Initialize(const bool bBlack_mode, const bool bBuild_mode, const int map_no)
{
	json data = FileCheck::FileOpenCheck(FILE_STAGE);

	m_block_row = data["Block"]["Row"];
	m_block_col = data["Block"]["Col"];
	m_map_chip_col = data["Block"]["ChipCol"];

	FileSetting(data, bBlack_mode, bBuild_mode, map_no);

	m_draw.image_width = data["Image"]["Width"];
	m_draw.image_height = data["Image"]["Height"];
	m_draw.draw_width = data["Draw"]["Width"];
	m_draw.draw_height = data["Draw"]["Height"];
	
    m_draw.filename = bBlack_mode ? data["Texture"]["Black"]:
								    data["Texture"]["White"];

	//後々入れるためここでは仮の初期化
	m_draw.position = Vector2Int(0, 0);
	m_draw.texture_num = 0;
}

void Stage::Updata()
{
}

void Stage::Draw(Engine* pEngine)
{
	for (int i = 0; i < m_block_row; i++)
	{
		for (int j = 0; j < m_block_col; j++)
		{
			m_draw.position = Vector2Int(j * m_draw.draw_width, i * m_draw.draw_height);
			m_draw.texture_num = m_map_array[i][j];

			BaseObject::Draw(pEngine);
		}
	}
}

Vector2Int Stage::GetStartPlayerPosition()
{
	return m_start_pos;
}

Field Stage::GetMapArray()
{
	Field field{};

	for (int i = 0; i < m_block_row; i++) {
		for (int j = 0; j < m_block_col; j++) {
			field.map[i][j] = m_map_array[i][j];
		}
	}

	return field;
}

int Stage::GetBlockWidth()
{
	return m_draw.draw_width;
}

int Stage::GetBlockHeight()
{
	return m_draw.draw_height;
}

void Stage::FileSetting(json& data, const bool bBlack_mode, const bool bBuild_mode, const int map_no)
{
	string filename;
	fstream ifs_map;

	if (!bBuild_mode)
	{
		if (!bBlack_mode){
			//表面マップ
			filename = data["WhiteStage"][map_no ];
		}
		else{
			//裏面マップ
			filename = data["BlackStage"][map_no];
		}
	}
	else
	{
		//ビルドモードステージ
		filename = data["BuildStage"];
	}

	ifs_map.open(filename, std::ios::in);

	if (!ifs_map) {
		throw DxSystemException(DxSystemException::OM_FILE_OPEN_ERROR);
	}

	//ファイルからPlayerの初期位置を取得
	ifs_map >> m_start_pos.x;
	ifs_map >> m_start_pos.y;

	for (int i = 0; i < m_block_row; i++) {
		for (int j = 0; j < m_block_col; j++) {
			ifs_map >> m_map_array[i][j];
		}
	}

	ifs_map.close();
}