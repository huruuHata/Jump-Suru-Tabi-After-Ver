//*****************************************************************************
//
// ゲーム全体で使用するリソース、構造体などの宣言
//
// GameBase.h
//
// K_Yamaoka
//
// 2013/03/04
//
//*****************************************************************************

#pragma once

//-----------------------------------------------------------------------------
//システム関係のヘッダファイルです。変更しないでください。
//-----------------------------------------------------------------------------

#include "System\\Engine\\Matrix\\Camera.h"
#include "System\\Engine\\Matrix\\Projection.h"
#include "System\\Engine\\Matrix\\Viewport.h"

#include "System\\Engine\\Light\\Ambient.h"
#include "System\\Engine\\Light\\Directional.h"

#include "System\\Engine\\Mesh\\Primitive.h"
#include "System\\Engine\\Billboard\\Billboard.h"
#include "System\\Engine\\Particle\\ParticleManage.h"

#include "System\\Engine\\Collision\\Collision.h"
#include "System\\Engine\\Collision\\BoundingBox.h"
#include "System\\Engine\\Collision\\BoundingSphere.h"

#include "System\\Engine\\Mesh\\Model.h"

#include "System\\Engine\\Engine.h"


//-----------------------------------------------------------------------------
//Ｃ言語でのdefine、構造体などはこちらで宣言します。
//-----------------------------------------------------------------------------

constexpr int ROW = 12;
constexpr int COL = 12;

struct Field
{
	int map[ROW][COL];
};

//-----------------------------------------------------------------------------
//ゲーム中で使用するテクスチャ、BGM、SE、フォントのパス付ファイル名を書きます。
//-----------------------------------------------------------------------------
namespace KeyString
{
	//****************
	//マップデータ
	//****************

	constexpr char* FILE_MAP1 = "Resource\\Map\\map.txt";
	constexpr char* FILE_MAP2 = "Resource\\Map\\map2.txt";
	constexpr char* FILE_MAP3 = "Resource\\Map\\map3.txt";
	constexpr char* FILE_MAP4 = "Resource\\Map\\map4.txt";
	constexpr char* FILE_MAP5 = "Resource\\Map\\map5.txt";
	constexpr char* FILE_MAP6 = "Resource\\Map\\map6.txt";
	constexpr char* FILE_MAP7 = "Resource\\Map\\map7.txt";
	constexpr char* FILE_MAP8 = "Resource\\Map\\map8.txt";
	constexpr char* FILE_MAP9 = "Resource\\Map\\map9.txt";
	constexpr char* FILE_MAP10 = "Resource\\Map\\map10.txt";

	constexpr char* FILE_MAP11 = "Resource\\Map\\map11.txt";
	constexpr char* FILE_MAP12 = "Resource\\Map\\map12.txt";
	constexpr char* FILE_MAP13 = "Resource\\Map\\map13.txt";
	constexpr char* FILE_MAP14 = "Resource\\Map\\map14.txt";
	constexpr char* FILE_MAP15 = "Resource\\Map\\map15.txt";
	constexpr char* FILE_MAP16 = "Resource\\Map\\map16.txt";
	constexpr char* FILE_MAP17 = "Resource\\Map\\map17.txt";
	constexpr char* FILE_MAP18 = "Resource\\Map\\map18.txt";
	constexpr char* FILE_MAP19 = "Resource\\Map\\map19.txt";
	constexpr char* FILE_MAP20 = "Resource\\Map\\map20.txt";

	constexpr char* FILE_BUILD = "Resource\\Map\\mapBuildMode.txt";


	//****************
	// ファイル
	//****************

	constexpr char* FILE_PLAYER = "Resource\\Data\\Json\\PlayerData.json";
	constexpr char* FILE_STAGE = "Resource\\Data\\Json\\StageData.json";

	//****************
	// テクスチャ
	//****************

	//タイトルシーン

	constexpr char* TEXTURE_TITLE = "Resource\\Texture\\Title\\Title.png";
	constexpr char* TEXTURE_TITLE_WHITE = "Resource\\Texture\\Title\\TitleWhiteChara.png";
	constexpr char* TEXTURE_TITLE_BLACK = "Resource\\Texture\\Title\\TitleBlackChara.png";
	constexpr char* TEXTURE_TITLE_START = "Resource\\Texture\\Title\\Start.png";
	constexpr char* TEXTURE_BACK = "Resource\\Texture\\Title\\WhiteBack.png";

	constexpr char* TEXTURE_CONGRATULATION_TITLE = "Resource\\Texture\\Title\\CongratulationTitle.png";

	//ゲームシーン

	constexpr char* TEXTURE_CHIP_WHITE = "Resource\\Texture\\Game\\Stage\\StageWhite.png";
	constexpr char* TEXTURE_CHIP_BLACK = "Resource\\Texture\\Game\\Stage\\StageBlack.png";
	constexpr char* TEXTURE_WHITE_CHARA = "Resource\\Texture\\Game\\Player\\WhiteChara.png";
	constexpr char* TEXTURE_BLACK_CHARA = "Resource\\Texture\\Game\\Player\\BlackChara.png";

	constexpr char* TEXTURE_EXPLAIN_GOAL = "Resource\\Texture\\Game\\Explain\\Game\\GoalExplain.png";
	constexpr char* TEXTURE_EXPLAIN_FALL = "Resource\\Texture\\Game\\Explain\\Game\\FallExplain.png";
	constexpr char* TEXTURE_EXPLAIN_KEY = "Resource\\Texture\\Game\\Explain\\Game\\KeyExplain.png";
	constexpr char* TEXTURE_EXPLAIN_JUMP = "Resource\\Texture\\Game\\Explain\\Game\\JumpExplain.png";
	constexpr char* TEXTURE_EXPLAIN_HIT = "Resource\\Texture\\Game\\Explain\\Game\\HitExplain.png";
	
	constexpr char* TEXTURE_BACK_GAME = "Resource\\Texture\\Game\\WhiteBack.png";
	constexpr char* TEXTURE_CONGRATULATION_GAME = "Resource\\Texture\\Game\\CongratulationGame.png";

	//ステージビルドモード

	constexpr char* TEXTURE_BUILD_KEY_EXPLAIN = "Resource\\Texture\\Game\\Explain\\StgaeBuildMode\\BuildModeKeyExplain.png";
	constexpr char* TEXTURE_BUILD_EXPALIN = "Resource\\Texture\\StgaeBuildMode\\BuildModeExplain.png";

	//ステージクリアシーン

	constexpr char* TEXTURE_NEXT = "Resource\\Texture\\Clear\\NextStage.png";
	constexpr char* TEXTURE_CLEAR_BACK = "Resource\\Texture\\Clear\\StageClearBack.png";
	constexpr char* TEXTURE_CLEAR = "Resource\\Texture\\Clear\\StageClear.png";

	//ゲームクリアシーン

	constexpr char* TEXTURE_GAMECLEAR_BACK = "Resource\\Texture\\Clear\\GameClearBack.png";
	constexpr char* TEXTURE_GAMECLEAR = "Resource\\Texture\\Clear\\GameClear.png";
	constexpr char* TEXTURE_NEWMODE = "Resource\\Texture\\Clear\\NewMode.png";

	//ゲームオーバーシーン

	constexpr char* TEXTURE_GAMEOVER_BACK = "Resource\\Texture\\Gameover\\GameoverBack.png";
	constexpr char* TEXTURE_GAMEOVER = "Resource\\Texture\\Gameover\\Gameover.png";

	//エンドロールシーン

	constexpr char* TEXTURE_ENDROLL = "Resource\\Texture\\EndRoll.png";

	//****************
	// ＢＧＭ
	//****************

	constexpr char* BGM_START = "Resource\\BGM\\TitleBGM.wav";
	constexpr char* BGM_WHITE = "Resource\\BGM\\ShiromotiJump.wav";
	constexpr char* BGM_BLACK = "Resource\\BGM\\KuromotiJump.wav";
	constexpr char* BGM_END = "Resource\\BGM\\ENDROLL.wav";

	//****************
	// ＳＥ
	//****************

	constexpr char* SE_STAGECLEAR = "Resource\\SE\\StageClear.wav";
	constexpr char* SE_GAMECLEAR = "Resource\\SE\\GameClear.wav";
	constexpr char* SE_GAMEOVER = "Resource\\SE\\GameOver.wav";
	constexpr char* SE_JUMP = "Resource\\SE\\Jump.wav";
	constexpr char* SE_DECIDE = "Resource\\SE\\Decide.wav";

	//****************
	// フォント
	//****************

	constexpr char* FONT_GOTHIC100 = "100:ＭＳ ゴシック";
}
