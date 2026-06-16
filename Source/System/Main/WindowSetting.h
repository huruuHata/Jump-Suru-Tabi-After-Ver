//*****************************************************************************
//
// ウィンドウ設定用ヘッダ
//
// WindowSetting.h
//
// K_Yamaoka
//
// 2013/05/28
//
// 2014/11/28 MODE_WINDOWを追加
//            WINDOW_CLASS_NAMEを追加
//
//*****************************************************************************

#pragma once

//=============================================================================
// ウィンドウ設定
//=============================================================================
namespace WindowSetting
{
	//ウィンドウモード（falseでフルスクリーンモード）
	constexpr bool MODE_WINDOW = true;

	//ウィンドウのサイズ
	constexpr int WINDOW_WIDTH = 768;
	constexpr int WINDOW_HEIGHT = 576;

	//ウィンドウタイトル名（ゲーム名に変更すること）
	constexpr char* WINDOW_TITLE_NAME = "ジャンプする旅";

	//ウィンドウクラス名（基本的には変更しないこと）
	constexpr char* WINDOW_CLASS_NAME = "3DSystemWindow";
}
