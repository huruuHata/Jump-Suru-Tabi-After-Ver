//*****************************************************************************
//
// ＢＧＭ管理
//
// BGMManage.cpp
//
// K_Yamaoka
//
// 2011/11/14
//
// 2014/11/28 エラーメッセージを追加
//            Add関数がfalseを返していないバグを修正
//
// 2023/08/28 ボリューム、パン調整用関数を追加
//
// 2023/11/07 再生中チェック関数をPublicに変更、ファイル名を指定するオーバーロード関数を追加
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "BGMManage.h"

#include <cassert>

//=============================================================================
// メンバの初期化（コンストラクタ）
//=============================================================================
BGMManage::BGMManage()
	: m_pGraphBuilder(nullptr)
	, m_pMediaControl(nullptr)
	, m_pMediaEvent(nullptr)
	, m_pMediaSeeking(nullptr)
	, m_pBasicAudio(nullptr)
	, m_volume(0)
	, m_pan(0)
	, m_bPlaying(false)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
BGMManage::~BGMManage()
{
	ReleaseBGM();

	CoUninitialize();
}

//=============================================================================
// ＢＧＭ管理の初期化
//=============================================================================
void BGMManage::Initializie()
{
	if (FAILED(CoInitialize(nullptr))) {
		throw DxSystemException(DxSystemException::OM_INITCOM_ERROR);
	}

	m_loadedBGMFilename = "";
}

//=============================================================================
// DirectShow関連の初期化およびメディアファイルの読み込み
// 引　数：string メディアファイル名（mp3）
//=============================================================================
void BGMManage::AddBGM(std::string strFileName)
{
	assert(strFileName.length() > 0);

	//前のＢＧＭが削除されていなければ削除
	if (m_pGraphBuilder) {
		ReleaseBGM();
	}

	int length = strFileName.length() + 1;

	WCHAR* m_pMediaName;

	try {
		m_pMediaName = new WCHAR[length];
	}
	catch (std::bad_alloc) {
		throw DxSystemException(DxSystemException::OM_BGM_NAME_ALLOCATE_ERROR);
	}

	//マルチバイト文字をワイドキャラに変換
	MultiByteToWideChar(CP_ACP, 0, strFileName.c_str(), -1, m_pMediaName, length);

	//グラフビルダーの作成
	if (FAILED(CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGraphBuilder))) {
		if (m_pMediaName) { delete[] m_pMediaName; m_pMediaName = nullptr; }
		throw DxSystemException(DxSystemException::OM_BGM_CREATE_GRAPHBUILDER_ERROR);
	}

	//メディアコントロールの作成
	if (FAILED(m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&m_pMediaControl))) {
		if (m_pMediaName) { delete[] m_pMediaName; m_pMediaName = nullptr; }
		throw DxSystemException(DxSystemException::OM_BGM_CREATE_MEDIACONTROL_ERROR);
	}

	//メディアイベントの作成
	if (FAILED(m_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&m_pMediaEvent))) {
		if (m_pMediaName) { delete[] m_pMediaName; m_pMediaName = nullptr; }
		throw DxSystemException(DxSystemException::OM_BGM_CREATE_MEDIAEVENT_ERROR);
	}

	//メディアシーキングの作成
	if (FAILED(m_pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&m_pMediaSeeking))) {
		if (m_pMediaName) { delete[] m_pMediaName; m_pMediaName = nullptr; }
		throw DxSystemException(DxSystemException::OM_BGM_CREATE_MEDIASEEKING_ERROR);
	}

	//指定されたファイルをレンダリングするフィルタ グラフを作成
	if (FAILED(m_pGraphBuilder->RenderFile(m_pMediaName, nullptr))) {
		if (m_pMediaName) { delete[] m_pMediaName; m_pMediaName = nullptr; }
		throw DxSystemException(DxSystemException::OM_BGM_CREATE_FILTERGRAPH_ERROR);
	}

	//ボリューム、パン調整用ベーシックオーディオを作成
	if (FAILED(m_pGraphBuilder->QueryInterface(IID_IBasicAudio, (void**)&m_pBasicAudio))) {
		if (m_pMediaName) { delete[] m_pMediaName; m_pMediaName = nullptr; }
		throw DxSystemException(DxSystemException::OM_BGM_CREATE_BASICAUDIO_ERROR);
	}

	if (m_pMediaName) {
		delete[] m_pMediaName;
		m_pMediaName = nullptr;
	}

	m_loadedBGMFilename = strFileName;
}

//=============================================================================
// DirectShow関連領域の解放
//=============================================================================
void BGMManage::ReleaseBGM()
{
	///解放する際にＢＧＭを明示的に止める必要があるのか？
	StopBGM();

	if (m_pBasicAudio) {
		m_pBasicAudio->Release();
		m_pBasicAudio = nullptr;
	}

	if (m_pMediaSeeking) {
		m_pMediaSeeking->Release();
		m_pMediaSeeking = nullptr;
	}

	if (m_pMediaEvent) {
		m_pMediaEvent->Release();
		m_pMediaEvent = nullptr;
	}

	if (m_pMediaControl) {
		m_pMediaControl->Release();
		m_pMediaControl = nullptr;
	}

	if (m_pGraphBuilder) {
		m_pGraphBuilder->Release();
		m_pGraphBuilder = nullptr;
	}

	m_loadedBGMFilename = "";
}

//=============================================================================
// メディアの再生
//=============================================================================
void BGMManage::PlayBGM()
{
	if (m_pMediaControl) {

		if (!m_bPlaying) {
			Rewind();
		}

		if (FAILED(m_pMediaControl->Run())) {
			throw DxSystemException(DxSystemException::OM_BGM_PLAY_ERROR);
		}

		m_bPlaying = true;
	}
}

//=============================================================================
// メディアの停止
//=============================================================================
void BGMManage::StopBGM()
{
	if (m_pMediaControl) {

		if (FAILED(m_pMediaControl->Stop())) {
			throw DxSystemException(DxSystemException::OM_BGM_STOP_ERROR);
		}

		m_bPlaying = false;
	}
}

//=============================================================================
// ループ再生
//=============================================================================
void BGMManage::LoopBGM()
{
	if (EndCheck()) {
		PlayBGM();
	}
}

//=============================================================================
// ボリュームをリセット
//=============================================================================
void BGMManage::ResetBGMVolume()
{
	m_volume = 0;
	m_pBasicAudio->put_Volume(m_volume);
}

//=============================================================================
// ボリュームを調整
// 引　数：const int 増減させる数値
//=============================================================================
void BGMManage::ChangeBGMVolume(const int value)
{
	m_volume += value;
	
	if (m_volume > 0) m_volume = 0;
	if (m_volume < -10000) m_volume = -10000;

	m_pBasicAudio->put_Volume(m_volume);
}

//=============================================================================
// パンをリセット
//=============================================================================
void BGMManage::ResetBGMPan()
{
	m_pan = 0;
	m_pBasicAudio->put_Balance(m_pan);
}

//=============================================================================
// パンを調整
// 引　数：const int 増減させる数値
//=============================================================================
void BGMManage::ChangeBGMPan(const int value)
{
	m_pan += value;

	if (m_volume > 10000) m_volume = 10000;
	if (m_volume < -10000) m_volume = -10000;

	m_pBasicAudio->put_Balance(m_pan);
}

//=============================================================================
// 再生中チェック
// 戻り値：bool 再生中 true  それ以外 false
//=============================================================================
bool BGMManage::IsPlaying()
{
	return m_bPlaying;
}

//=============================================================================
// 再生中チェック
// 戻り値：bool 再生中 true  それ以外 false
// 引　数：string メディアファイル名（mp3）
//=============================================================================
bool BGMManage::IsPlaying(std::string strFileName)
{
	if (m_loadedBGMFilename == strFileName) {
		if (IsPlaying()) {
			return true;
		}
	}

	return false;
}



//wmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw
// private関数
//wmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw


//-----------------------------------------------------------------------------
// 終了チェック
// 戻り値：bool true 終了、false 再生中
//-----------------------------------------------------------------------------
bool BGMManage::EndCheck()
{
	bool bPlayEnd = false;

	if (m_pMediaEvent) {

		long evCode;
		long evParam1;
		long evParam2;

		//メディアからイベントを取得
		while (SUCCEEDED(m_pMediaEvent->GetEvent(&evCode, &evParam1, &evParam2, 0))) {

			//再生が終了していた場合falseを返す
			if (evCode == EC_COMPLETE) {
				bPlayEnd = true;
				m_bPlaying = false;
			}

			m_pMediaEvent->FreeEventParams(evCode, evParam1, evParam2);
		}
	}

	return bPlayEnd;
}

//-----------------------------------------------------------------------------
// メディアの巻き戻し
//-----------------------------------------------------------------------------
void BGMManage::Rewind()
{
	if (m_pMediaSeeking) {

		REFERENCE_TIME Start;
		REFERENCE_TIME End;

		bool  bCanSeek = false;

		DWORD caps = AM_SEEKING_CanSeekAbsolute | AM_SEEKING_CanGetDuration;

		bCanSeek = (S_OK == m_pMediaSeeking->CheckCapabilities(&caps));

		if (bCanSeek) {
			m_pMediaSeeking->GetAvailable(&Start, &End);
			m_pMediaSeeking->SetPositions(&Start, AM_SEEKING_AbsolutePositioning, &End, AM_SEEKING_AbsolutePositioning);
		}
	}
}




