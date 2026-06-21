
#define _USING_V110_SDK71_ 1

#include "PlayerCollide.h"

using namespace KeyString;

int PlayerCollide::CheckHorizontal(const Field& field, int pixel_x, int top_y, int bottom_y, int block_width, int block_height) const
{
	int map_x = Stage::ToMapX(pixel_x, block_width);
	int top_map_y = Stage::ToMapY(top_y, block_height);
	int bottom_map_y = Stage::ToMapY(bottom_y, block_height);

	int result = Stage::STAGE;

	for (int y = top_map_y; y <= bottom_map_y; y++)
	{
		int check = field.map[y][map_x];

		if (check != Stage::STAGE)
		{
			result = check;
		}
	}

	return result;
}

int PlayerCollide::CheckVertical(const Field& field, int left_x, int right_x, int pixel_y, int block_width, int block_height) const
{
	int map_left_x = Stage::ToMapX(left_x, block_width);
	int map_right_x = Stage::ToMapX(right_x, block_width);
	int map_y = Stage::ToMapY(pixel_y, block_height);

	int left_result = field.map[map_y][map_left_x];
	int right_result = field.map[map_y][map_right_x];

	//死亡、ゴール判定が優先されるようにする
	if (left_result == Stage::JAGGED_UP || right_result == Stage::JAGGED_UP)
	{
		return Stage::JAGGED_UP;
	}
	if (left_result == Stage::JAGGED_DOWN || right_result == Stage::JAGGED_DOWN)
	{
		return Stage::JAGGED_DOWN;
	}
	if (left_result == Stage::GOAL || right_result == Stage::GOAL)
	{
		return Stage::GOAL;
	}

	if (left_result != Stage::STAGE) return left_result;
	if (right_result != Stage::STAGE) return right_result;

	return Stage::STAGE;
}
