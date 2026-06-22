//*****************************************************************************
//
// ゲームシーン
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "SceneGame.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;
using namespace Common;

//=============================================================================
// コンストラクタ
// 引　数：Engine* エンジンクラスのアドレス
//=============================================================================
SceneGame::SceneGame(Engine *pEngine)
	: Scene(pEngine)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
SceneGame::~SceneGame()
{
	Exit();
}

//=============================================================================
// シーンの実行時に１度だけ呼び出される開始処理関数
//=============================================================================
void SceneGame::Start()
{
	m_setting.SceneResourceSetting(m_pEngine, SCENE_GAME, m_system.GetBlackMode(), m_system.GetBuildMode());

	m_gameUI.Initialize(m_system.GetBlackMode(), m_system.GetBuildMode());
	m_back.Initialize();
	m_stage.Initialize(m_system.GetBlackMode(), m_system.GetBuildMode(), m_gameData.map_no);
	m_player.Initialize(m_system.GetBlackMode(), m_stage.GetBlockWidth(), m_stage.GetBlockHeight(), m_stage.GetStartPlayerPosition());

	m_field = m_stage.GetMapArray();

	m_pEngine->PlayBGM();

	m_is_ready = false;
}

//=============================================================================
// シーンの実行時に繰り返し呼び出される更新処理関数
//=============================================================================
void SceneGame::Update()
{
	m_pEngine->LoopBGM();

	m_delta.DeltaTimeCount();

	//ステージビルドモードはステージが変わるため更新が必要
	if (m_system.GetBuildMode())
	{
		m_field = m_stage.GetMapArray();
		m_stage.Update(m_pEngine);
	}

	//プレイヤーがロード中に動けてしまう事象への対策用(m_is_ready)
	if(m_is_ready) m_player.Update(m_pEngine, m_field, m_system.GetBlackMode(), m_delta.GetDeltaTime());

	if (m_player.IsGoal())
	{
		m_nowSceneData.Set(SCENE_CLEAR);
	}
	if (m_player.IsGameover())
	{
		m_nowSceneData.Set(SCENE_GAMEOVER);
	}

	if (m_system.GetBuildMode())
	{
		//ステージビルド説明表示非表示

		if (m_pEngine->GetKeyStateSync(DIK_RETURN))
		{
			m_gameUI.SetDisplayBuildModeExplain(false);
		}
		if (m_pEngine->GetKeyStateSync(DIK_F2))
		{
			m_gameUI.SetDisplayBuildModeExplain(true);
		}

		if (m_pEngine->GetKeyStateSync(DIK_F1))
		{
			m_nowSceneData.Set(SCENE_TITLE);
		}
	}

	m_is_ready = true;
}

//=============================================================================
// シーンの実行時に繰り返し呼び出される描画処理関数
//=============================================================================
void SceneGame::Draw()
{
	m_pEngine->SpriteBegin();

	if(!m_system.GetBlackMode()) m_back.Draw(m_pEngine);

	m_stage.Draw(m_pEngine);
	m_gameUI.Draw(m_pEngine, m_gameData.map_no, m_system.GetBlackMode(), m_system.GetBuildMode());
	m_player.Draw(m_pEngine);

	m_pEngine->SpriteEnd();
}

//=============================================================================
// シーンの終了時に呼び出される終了処理関数
//=============================================================================
void SceneGame::Exit()
{
	m_setting.SceneResourceRelease(m_pEngine);
}

//=============================================================================
// シーンの実行時に繰り返し呼び出されるポストエフェクト（シェーダー）準備関数
//=============================================================================
void SceneGame::PreparePostEffect()
{

}

//=============================================================================
// シーンの実行時に繰り返し呼び出される初心者用ポストエフェクト関数
//=============================================================================
void SceneGame::PostEffectForBeginners()
{

}

#ifndef IMGUI_DISABLE
//=============================================================================
// 日本語入力用
//=============================================================================
void SceneGame::ImGuiFrameProcess()
{

}
#endif