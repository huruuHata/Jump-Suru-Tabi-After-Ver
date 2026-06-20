//*****************************************************************************
//
// タイトルシーン
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "SceneTitle.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;
using namespace Common;

//=============================================================================
// コンストラクタ
// 引　数：Engine* エンジンクラスのアドレス
//=============================================================================
SceneTitle::SceneTitle(Engine *pEngine)
	: Scene(pEngine)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
SceneTitle::~SceneTitle()
{
	Exit();
}

//=============================================================================
// シーンの実行時に１度だけ呼び出される開始処理関数
//=============================================================================
void SceneTitle::Start()
{
	m_setting.SceneResourceSetting(m_pEngine, SCENE_TITLE);

	m_pEngine->PlayBGM();

	m_gameData.map_no = 0;

	bDecide = false;
}

//=============================================================================
// シーンの実行時に繰り返し呼び出される更新処理関数
//=============================================================================
void SceneTitle::Update()
{
	m_titleUI.Update(m_pEngine);

	//通常モード

	if (!bDecide)
	{
		if (m_pEngine->GetKeyStateSync(DIK_RETURN)) Decide(false, false);

		else if (m_system.GetGameClear())
		{
			//ブラックモード
			if (m_pEngine->GetKeyStateSync(DIK_K)) Decide(true, false);

			//ステージビルドモード
			else if (m_pEngine->GetKeyStateSync(DIK_S)) Decide(false, true);
		}
	}

	if (m_timer_start_wait.GetTiming())
	{
		m_nowSceneData.Set(SCENE_GAME);
	}
}

//=============================================================================
// シーンの実行時に繰り返し呼び出される描画処理関数
//=============================================================================
void SceneTitle::Draw()
{
	m_pEngine->SpriteBegin();

	m_titleUI.Draw(m_pEngine, m_system.GetAllGameClear());

	m_pEngine->SpriteEnd();
}

//=============================================================================
// シーンの終了時に呼び出される終了処理関数
//=============================================================================
void SceneTitle::Exit()
{
	m_setting.SceneResourceRelease(m_pEngine);
}

//=============================================================================
// シーンの実行時に繰り返し呼び出されるポストエフェクト（シェーダー）準備関数
//=============================================================================
void SceneTitle::PreparePostEffect()
{

}

//=============================================================================
// シーンの実行時に繰り返し呼び出される初心者用ポストエフェクト関数
//=============================================================================
void SceneTitle::PostEffectForBeginners()
{

}

void SceneTitle::Decide(const bool bBlackMode, const bool bBuildMode)
{
	m_system.SetGameMode(bBlackMode, bBuildMode);
	m_pEngine->PlaySE(SE_DECIDE);
	m_timer_start_wait.SetInterval(350);

	bDecide = true;
}

#ifndef IMGUI_DISABLE
//=============================================================================
// 日本語入力用
//=============================================================================
void SceneTitle::ImGuiFrameProcess()
{

}
#endif
