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
}

//=============================================================================
// シーンの実行時に繰り返し呼び出される更新処理関数
//=============================================================================
void SceneTitle::Update()
{
	m_titleUI.Update(m_pEngine);

	//通常モード
	if (m_pEngine->GetKeyStateSync(DIK_RETURN))
	{
		m_system.SetGameMode(false, false);

		m_pEngine->PlaySE(SE_DECIDE);
		m_timer_start_wait.SetInterval(350);
	}
	//ブラックモード
	if (m_pEngine->GetKeyStateSync(DIK_K))
	{
		m_system.SetGameMode(true, false);

		m_pEngine->PlaySE(SE_DECIDE);
		m_timer_start_wait.SetInterval(350);
	}
	//ステージビルドモード
	if (m_pEngine->GetKeyStateSync(DIK_S))
	{
		m_system.SetGameMode(false, true);

		m_pEngine->PlaySE(SE_DECIDE);
		m_timer_start_wait.SetInterval(350);
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

	m_titleUI.Draw(m_pEngine);

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

#ifndef IMGUI_DISABLE
//=============================================================================
// 日本語入力用
//=============================================================================
void SceneTitle::ImGuiFrameProcess()
{

}
#endif
