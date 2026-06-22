#define _USING_V110_SDK71_ 1

#include "SceneGame.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;
using namespace Common;

//=============================================================================
// コンストラクタ
//=============================================================================
SceneGame::SceneGame(Engine* pEngine)
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
// 開始処理
//=============================================================================
void SceneGame::Start()
{
	const bool bBlack_mode = m_system.GetBlackMode();
	const bool bBuild_mode = m_system.GetBuildMode();

	m_setting.SceneResourceSetting(m_pEngine, SCENE_GAME, bBlack_mode, bBuild_mode);

	m_gameUI.Initialize(bBlack_mode, bBuild_mode);

	m_back.Initialize();
	m_stage.Initialize(bBlack_mode, bBuild_mode, m_gameData.map_no);
	m_player.Initialize(bBlack_mode, m_stage.GetBlockWidth(), m_stage.GetBlockHeight(), m_stage.GetStartPlayerPosition());

	m_field = m_stage.GetMapArray();

	m_pEngine->PlayBGM();

	m_is_ready = false;
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneGame::Update()
{
	m_pEngine->LoopBGM();

	m_delta.DeltaTimeCount();

	UpdateBuildMode();

	UpdatePlayer();

	CheckSceneTransition();

	ProcessBuildModeInput();

	m_is_ready = true;
}

//=============================================================================
// ステージビルドモード更新
//=============================================================================
void SceneGame::UpdateBuildMode()
{
	if (!m_system.GetBuildMode())
	{
		return;
	}

	m_field = m_stage.GetMapArray();

	m_stage.Update(m_pEngine);
}

//=============================================================================
// プレイヤー更新
//=============================================================================
void SceneGame::UpdatePlayer()
{
	if (!m_is_ready)
	{
		return;
	}

	m_player.Update(m_pEngine, m_field, m_system.GetBlackMode(), m_delta.GetDeltaTime());
}

//=============================================================================
// シーン遷移判定
//=============================================================================
void SceneGame::CheckSceneTransition()
{
	if (m_player.IsGoal())
	{
		m_nowSceneData.Set(SCENE_CLEAR);
		return;
	}

	if (m_player.IsGameover())
	{
		m_nowSceneData.Set(SCENE_GAMEOVER);
	}
}

//=============================================================================
// ビルドモード入力処理
//=============================================================================
void SceneGame::ProcessBuildModeInput()
{
	if (!m_system.GetBuildMode())
	{
		return;
	}

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

//=============================================================================
// 背景描画
//=============================================================================
void SceneGame::DrawBackground()
{
	if (!m_system.GetBlackMode())
	{
		m_back.Draw(m_pEngine);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneGame::Draw()
{
	m_pEngine->SpriteBegin();

	DrawBackground();

	m_stage.Draw(m_pEngine);

	m_gameUI.Draw(m_pEngine, m_gameData.map_no, m_system.GetBlackMode(), m_system.GetBuildMode());

	m_player.Draw(m_pEngine);

	m_pEngine->SpriteEnd();
}

//=============================================================================
// 終了処理
//=============================================================================
void SceneGame::Exit()
{
	m_setting.SceneResourceRelease(m_pEngine);
}

//=============================================================================
// ポストエフェクト準備
//=============================================================================
void SceneGame::PreparePostEffect()
{

}

//=============================================================================
// 初心者用ポストエフェクト
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