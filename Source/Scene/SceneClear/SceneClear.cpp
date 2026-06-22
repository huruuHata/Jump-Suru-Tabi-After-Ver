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
	m_clearUI.Update(m_pEngine);

	if (m_pEngine->GetKeyStateSync(DIK_RETURN))
	{
		if (!m_system.GetBlackMode())
		{
			//STAGECLEAR画面→GAMECLEAR画面→NEWMODE説明画面(しろステージクリア)

			if (m_gameData.map_no >= m_gameData.map_max)
			{
				if (!m_clearUI.IsGameClearDisplay())
				{
					m_clearUI.SetGameClearDisplayTrue();
					m_pEngine->PlaySE(SE_GAMECLEAR);
				}
				else if (m_clearUI.IsGameClearFadeInFinish() && m_clearUI.IsNewModeDisplay())
				{
					m_nowSceneData.Set(SCENE_TITLE);
				}
				else
				{
					m_system.SetGameClear(true);
					m_clearUI.SetNewModeDisplayTrue();

					ClearDataSave();
				}
			}
		}
		else
		{
			//STAGECLEAR画面→GAMECLEAR画面(くろステージクリア)

			if (m_gameData.map_no >= m_gameData.map_max)
			{
				if (!m_clearUI.IsGameClearDisplay())
				{
					m_clearUI.SetGameClearDisplayTrue();
					m_system.SetAllGameClear(true);
					m_pEngine->PlaySE(SE_GAMECLEAR);

					ClearDataSave();
				}

				else if (m_clearUI.IsGameClearFadeInFinish())
				{
					m_nowSceneData.Set(SCENE_TITLE);
				}
			}
		}

		//STAGECLEAR画面→NEXTSTAGE画面

		//NEXTSTAGE画面であれば次のステージ
		if (m_clearUI.IsNextStageDisplay() && m_gameData.map_no < m_gameData.map_max)
		{
			m_gameData.map_no++;

			m_nowSceneData.Set(SCENE_GAME);
		}
		//CLEAR画面のテロップが落ち切ったか
		else if (m_clearUI.IsClearTelopDropFinish())
		{
			//ステージビルドモードならNEXTSTAGE画面に行かずそのままゲームに戻す
			if (m_system.GetBuildMode())
			{
				m_nowSceneData.Set(SCENE_GAME);
			}
			//NEXTSTAGE画面を表示させる
			else
			{
				m_clearUI.SetNextStageDisplayTrue();
			}
		}
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
