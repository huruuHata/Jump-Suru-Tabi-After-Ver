#define _USING_V110_SDK71_ 1

#include "SceneTitle.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;
using namespace Common;

//=============================================================================
// コンストラクタ
//=============================================================================
SceneTitle::SceneTitle(Engine* pEngine)
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
// 開始処理
//=============================================================================
void SceneTitle::Start()
{
	m_setting.SceneResourceSetting(m_pEngine, SCENE_TITLE);

	m_pEngine->PlayBGM();

	LoadSaveData();

	m_gameData.map_no = 0;

	bDecide = false;
}

//=============================================================================
// セーブデータ読込
//=============================================================================
void SceneTitle::LoadSaveData()
{
	const SaveGame::SaveData data = m_save.LoadFile();

	m_system.SetGameClear(data.is_game_clear);

	m_system.SetAllGameClear(data.is_all_game_clear);
}

//=============================================================================
// 更新処理
//=============================================================================
void SceneTitle::Update()
{
	m_titleUI.Update();

	ProcessInput();

	CheckSceneTransition();
}

//=============================================================================
// 入力処理
//=============================================================================
void SceneTitle::ProcessInput()
{
	if (bDecide)
	{
		return;
	}

	if (m_pEngine->GetKeyStateSync(DIK_RETURN))
	{
		Decide(false, false);
		return;
	}

	if (!m_system.GetGameClear())
	{
		return;
	}

	if (m_pEngine->GetKeyStateSync(DIK_K))
	{
		Decide(true, false);
		return;
	}

	if (m_pEngine->GetKeyStateSync(DIK_S))
	{
		Decide(false, true);
	}
}

//=============================================================================
// シーン遷移判定
//=============================================================================
void SceneTitle::CheckSceneTransition()
{
	if (m_timer_start_wait.GetTiming())
	{
		m_nowSceneData.Set(SCENE_GAME);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void SceneTitle::Draw()
{
	m_pEngine->SpriteBegin();

	m_titleUI.Draw(m_pEngine, m_system.GetAllGameClear());

	m_pEngine->SpriteEnd();
}

//=============================================================================
// 終了処理
//=============================================================================
void SceneTitle::Exit()
{
	m_setting.SceneResourceRelease(m_pEngine);
}

//=============================================================================
// ポストエフェクト準備
//=============================================================================
void SceneTitle::PreparePostEffect()
{

}

//=============================================================================
// 初心者用ポストエフェクト
//=============================================================================
void SceneTitle::PostEffectForBeginners()
{

}

//=============================================================================
// プレイモードの決定
//=============================================================================
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