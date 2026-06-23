//*****************************************************************************
//
// クリアシーン
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "SceneClear.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;
using namespace Common;

//=============================================================================
// コンストラクタ
// 引　数：Engine* エンジンクラスのアドレス
//=============================================================================
SceneClear::SceneClear(Engine *pEngine)
	: Scene(pEngine)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
SceneClear::~SceneClear()
{
	Exit();
}

//=============================================================================
// シーンの実行時に１度だけ呼び出される開始処理関数
//=============================================================================
void SceneClear::Start()
{
	m_setting.SceneResourceSetting(m_pEngine, SCENE_CLEAR);

	m_pEngine->PlaySE(SE_STAGECLEAR);
}

//=============================================================================
// シーンの実行時に繰り返し呼び出される更新処理関数
//=============================================================================
void SceneClear::Update()
{
	m_clearUI.Update();

	if (m_pEngine->GetKeyStateSync(DIK_RETURN))
	{
		ProcessEnterKey();
	}
}

//=============================================================================
// シーンの実行時に繰り返し呼び出される描画処理関数
//=============================================================================
void SceneClear::Draw()
{
	m_pEngine->SpriteBegin();

	m_clearUI.Draw(m_pEngine);

	m_pEngine->SpriteEnd();
}

//=============================================================================
// シーンの終了時に呼び出される終了処理関数
//=============================================================================
void SceneClear::Exit()
{
	m_setting.SceneResourceRelease(m_pEngine);
}

//=============================================================================
// シーンの実行時に繰り返し呼び出されるポストエフェクト（シェーダー）準備関数
//=============================================================================
void SceneClear::PreparePostEffect()
{

}

//=============================================================================
// シーンの実行時に繰り返し呼び出される初心者用ポストエフェクト関数
//=============================================================================
void SceneClear::PostEffectForBeginners()
{

}

//=============================================================================
// Enterキー入力後の処理
//=============================================================================
void SceneClear::ProcessEnterKey()
{
	if (IsFinalStageClear())
	{
		ProcessGameClear();
	}
	else
	{
		ProcessNextStage();
	}
}

//=============================================================================
// 最終ステージクリア判定
//=============================================================================
bool SceneClear::IsFinalStageClear() const
{
	return m_gameData.map_no >= m_gameData.map_max;
}

//=============================================================================
// 次のステージの画面遷移
//=============================================================================
void SceneClear::ProcessNextStage()
{
	if (!m_clearUI.IsClearTelopDropFinish())
	{
		return;
	}

	if (m_system.GetBuildMode())
	{
		m_nowSceneData.Set(SCENE_GAME);
		return;
	}

	if (m_clearUI.GetState() == ClearUI::State::StageClear)
	{
		m_clearUI.ChangeState(ClearUI::State::NextStage);
		return;
	}

	if (m_clearUI.GetState() == ClearUI::State::NextStage)
	{
		m_gameData.map_no++;
		m_nowSceneData.Set(SCENE_GAME);
	}
}

//=============================================================================
// ゲームクリア画面の遷移
//=============================================================================
void SceneClear::ProcessGameClear()
{
	if (m_system.GetBlackMode())
	{
		ProcessBlackModeClear();
	}
	else
	{
		ProcessWhiteModeClear();
	}
}

//=============================================================================
// 白モードの画面遷移
//=============================================================================
void SceneClear::ProcessWhiteModeClear()
{
	switch (m_clearUI.GetState())
	{
	case ClearUI::State::StageClear:

		m_clearUI.ChangeState(ClearUI::State::GameClear);
		m_pEngine->PlaySE(SE_GAMECLEAR);

		break;

	case ClearUI::State::GameClear:

		if (!m_clearUI.IsGameClearFadeInFinish())
		{
			return;
		}

		m_system.SetGameClear(true);

		ClearDataSave();

		m_clearUI.ChangeState(ClearUI::State::NewMode);

		break;

	case ClearUI::State::NewMode:

		m_nowSceneData.Set(SCENE_TITLE);

		break;
	}
}

//=============================================================================
// 黒モードの画面遷移
//=============================================================================
void SceneClear::ProcessBlackModeClear()
{
	switch (m_clearUI.GetState())
	{
	case ClearUI::State::StageClear:

		if (!m_system.GetAllGameClear())
		{
			m_system.SetAllGameClear(true);
			ClearDataSave();
		}

		m_clearUI.ChangeState(ClearUI::State::GameClear);

		m_pEngine->PlaySE(SE_GAMECLEAR);

		break;

	case ClearUI::State::GameClear:

		if (m_clearUI.IsGameClearFadeInFinish())
		{
			m_nowSceneData.Set(SCENE_TITLE);
		}

		break;
	}
}

//=============================================================================
// データセーブ
//=============================================================================
void SceneClear::ClearDataSave()
{
	SaveGame::SaveData data;

	data.is_game_clear = m_system.GetGameClear();
	data.is_all_game_clear = m_system.GetAllGameClear();

	m_save.SaveFile(data);
}

#ifndef IMGUI_DISABLE
//=============================================================================
// 日本語入力用
//=============================================================================
void SceneClear::ImGuiFrameProcess()
{

}
#endif
