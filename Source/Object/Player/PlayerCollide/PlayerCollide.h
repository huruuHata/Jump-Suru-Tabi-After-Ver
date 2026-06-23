
//プレイヤーとマップとの当たり判定のみを行う(座標は変更しない)

#pragma once

#include "..\\..\\..\\GameBase.h"
#include "..\\..\\Stage\\Stage.h"

class PlayerCollide
{
public:

	//横方向の当たり判定
	int CheckHorizontal(const Field& field, int pixel_x, int top_y, int bottom_y, int block_width, int block_height) const;

	//縦方向の当たり判定
	int CheckVertical(const Field& field, int left_x, int right_x, int pixel_y, int block_width, int block_height) const;

	static const int COLLIDE_MARGIN = 4; //プレイヤーの当たり判定の余裕
};