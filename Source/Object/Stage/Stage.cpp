
#define _USING_V110_SDK71_ 1

#include "Stage.h"

using namespace std;
using namespace KeyString;
using namespace InputKey;

void Stage::Initialize(const bool is_black_mode, const bool is_build_mode, const int map_no)
{
	json data = FileCheck::FileOpenCheck(FILE_STAGE);

	m_block_row = data["Block"]["Row"];
	m_block_col = data["Block"]["Col"];
	m_map_chip_col = data["Block"]["ChipCol"];

	FileSetting(data, is_black_mode, is_build_mode, map_no);

	m_draw.image_width = data["Image"]["Width"];
	m_draw.image_height = data["Image"]["Height"];
	m_draw.draw_width = data["Draw"]["Width"];
	m_draw.draw_height = data["Draw"]["Height"];
	
    m_draw.filename = is_black_mode ? data["Texture"]["Black"]:
								    data["Texture"]["White"];

	m_draw.position = Vector2Int(0, 0);
	m_draw.texture_num = 0;

	m_build_block_num = 0;
}

void Stage::Update(Engine* pEngine)
{
	StageBuild(pEngine);
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

//マップデータからプレイヤーの初期位置を取得
Vector2Int Stage::GetStartPlayerPosition() const
{
	return m_start_pos;
}

Field& Stage::GetMapArray() const
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

int Stage::GetBlockWidth() const
{
	return m_draw.draw_width;
}

int Stage::GetBlockHeight() const
{
	return m_draw.draw_height;
}

//ピクセル座標をマップ座標に変換
int Stage::ToMapX(const int pixel_x, const int block_width)
{
	return pixel_x / block_width;
}
int Stage::ToMapY(const int pixel_y, const int block_height)
{
	return pixel_y / block_height;
}

void Stage::FileSetting(json& data, const bool is_black_mode, const bool is_build_mode, const int map_no)
{
	string filename;
	fstream ifs_map;

	if (!is_build_mode)
	{
		if (!is_black_mode)
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

//ステージビルドモード用
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

		if (mx < 0 || mx >= m_block_col)
		{
			return;
		}

		if (my < 0 || my >= m_block_row)
		{
			return;
		}

		if (m_map_array[my][mx] != m_build_block_num)
		{
			m_map_array[my][mx] = m_build_block_num;
		}
		else
		{
			m_map_array[my][mx] = 0;
		}
	}
}
