
#define _USING_V110_SDK71_ 1

#include "Stage.h"

using namespace std;
using namespace KeyString;
using namespace InputKey;

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

	m_draw.position = Vector2Int(0, 0);
	m_draw.texture_num = 0;

	m_build_block_num = 0;
}

void Stage::Update(Engine* pEngine, const bool bBuild_mode)
{
	if (bBuild_mode) StageBuild(pEngine);
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

	for (int i = 0; i < m_block_row; i++)
	{
		for (int j = 0; j < m_block_col; j++) 
		{
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

//ピクセル座標をマップ座標に変換
int Stage::ToMapX(int pixel_x, int block_width)
{
	return pixel_x / block_width;
}
int Stage::ToMapY(int pixel_y, int block_height)
{
	return pixel_y / block_height;
}

void Stage::FileSetting(json& data, const bool bBlack_mode, const bool bBuild_mode, const int map_no)
{
	string filename;
	fstream ifs_map;

	if (!bBuild_mode)
	{
		if (!bBlack_mode)
		{
			//表面マップ
			filename = data["WhiteStage"][map_no ];
		}
		else
		{
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

	for (int i = 0; i < m_block_row; i++) 
	{
		for (int j = 0; j < m_block_col; j++)
		{
			ifs_map >> m_map_array[i][j];
		}
	}

	ifs_map.close();
}

void Stage::StageBuild(Engine* pEngine)
{
	if (pEngine->GetKeyStateSync(DIK_0))
	{
		m_build_block_num = 0;
	}

	//１～５までのキー入力に対応
	for (int i = 0; i <= 4; i++)
	{
		if (pEngine->GetKeyStateSync((BYTE)(DIK_1 + i - 1)))
		{
			m_build_block_num = i;
			break;
		}
	}

	if (pEngine->GetMouseButtonSync(DIK_LBUTTON)) 
	{
		POINT point = pEngine->GetMousePosition();

		int mx = point.x / m_draw.draw_width;
		int my = point.y / m_draw.draw_height;

		if (m_map_array[my][mx] != m_build_block_num)
		{
			m_map_array[my][mx] = m_build_block_num;
		}
		else if (m_map_array[my][mx] == m_build_block_num)
		{
			m_map_array[my][mx] = 0;
		}
	}
}
