//*****************************************************************************
//
// ポストエフェクト（シェーダー利用）
//
//*****************************************************************************

#define _USING_V110_SDK71_ 1

#include "PostEffect.h"

using namespace KeyString;
using namespace InputKey;
using namespace WindowSetting;

//=============================================================================
// コンストラクタ
//=============================================================================
PostEffect::PostEffect()
	: m_bUseEffect(false)
	, m_pDepthBuffer(nullptr)
	, m_pOldDepthBuffer(nullptr)
	, m_pFullScreenTexture(nullptr)
	, m_pFullScreenSurface(nullptr)
	, m_pOldSurface(nullptr)
	, m_pEffect(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
PostEffect::~PostEffect()
{
	Release();
}

//=============================================================================
// 初期化
// 引　数：Engine*    エンジンクラスのアドレス
// 　　　　const WORD エフェクトＩＤ（resource.hで定義）
// 　　　　string     テクニック名
//=============================================================================
void PostEffect::Initialize(Engine* pEngine, const WORD fxid, std::string technique)
{
	LPDIRECT3DDEVICE9 pDevice = pEngine->GetDevice();

	//確保したメモリの解放
	Release();

	//深度バッファ、レンダリング用テクスチャ、サーフェスの初期化
	InitializeDepthTextureSurce(pDevice);

	//シェーダーのロード
	LoadShader(pDevice, fxid, technique);

	//頂点情報の設定
	SetVertices();
	
	EffectON();
}

//=============================================================================
// 準備（シーンのPreparePostEffectから呼び出す）
// 引　数：Engine* エンジンクラスのアドレス
//=============================================================================
void PostEffect::Prepare(Engine* pEngine)
{
	if (!m_bUseEffect) return;

	LPDIRECT3DDEVICE9 pDevice = pEngine->GetDevice();

	//元のレンダリングターゲット（バックバッファ）を保管
	HRESULT hr = pDevice->GetRenderTarget(0, &m_pOldSurface);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_GET_RENDERTARGET_ERROR);
	}

	//元の深度バッファを保管
	hr = pDevice->GetDepthStencilSurface(&m_pOldDepthBuffer);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_GET_DEPTHSTENCIL_ERROR);
	}

	//新しいレンダリングターゲット（テクスチャ）をセット
	hr = pDevice->SetRenderTarget(0, m_pFullScreenSurface);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_SET_RENDERTARGET_ERROR);
	}

	//新しい深度バッファをセット
	hr = pDevice->SetDepthStencilSurface(m_pDepthBuffer);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_SET_DEPTHSTENCIL_ERROR);
	}
}

//=============================================================================
// レンダリング（シーンのDraw関数の最後に呼び出す）
// 引　数：Engine* エンジンクラスのアドレス
//=============================================================================
void PostEffect::Render(Engine * pEngine)
{
	if (!m_bUseEffect) return;

	LPDIRECT3DDEVICE9 pDevice = pEngine->GetDevice();

	//レンダリングターゲット（をバックバッファ）に戻す
	HRESULT hr = pDevice->SetRenderTarget(0, m_pOldSurface);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_SET_RENDERTARGET_ERROR);
	}

	m_pOldSurface->Release();
	m_pOldSurface = nullptr;

	//深度バッファを戻す
	hr = pDevice->SetDepthStencilSurface(m_pOldDepthBuffer);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_SET_DEPTHSTENCIL_ERROR);
	}

	m_pOldDepthBuffer->Release();
	m_pOldDepthBuffer = nullptr;

	//テクスチャのフィルター設定
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	//最前面に表示するためＺバッファを無効にする
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	//（レンダリングした）テクスチャをセット
	pDevice->SetTexture(0, m_pFullScreenTexture);

	m_pEffect->Begin(nullptr, 0);
	m_pEffect->BeginPass(0);

	//板ポリゴンの描画
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(POSTEFFECT_VERTEX_FORMAT));

	m_pEffect->EndPass();
	m_pEffect->End();

	//Ｚバッファを有効に戻す
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

//=============================================================================
// ポストエフェクト処理を止める（破棄する）
//=============================================================================
void PostEffect::End()
{
	EffectOFF();

	Release();
}

//=============================================================================
// ポストエフェクト処理を開始（再開）する
//=============================================================================
void PostEffect::EffectON()
{
	if (!m_pEffect) return;

	m_bUseEffect = true;
}

//=============================================================================
// ポストエフェクト処理を中断する
//=============================================================================
void PostEffect::EffectOFF()
{
	m_bUseEffect = false;
}

//=============================================================================
// ポストエフェクト処理が実行中かどうか調べる
//=============================================================================
bool PostEffect::IsUseEffect() const
{
	return m_bUseEffect;
}

//=============================================================================
// 値の転送（float）
// 引　数：const char* パラメータの名前
// 　　　　const float パラメータの数値
//=============================================================================
void PostEffect::SetFloat(const char * parameter, const float value)
{
	if (!m_pEffect) return;

	m_pEffect->SetFloat(parameter, value);
}


//-----------------------------------------------------------------------------
// 深度バッファ、レンダリング用テクスチャ、サーフェスの初期化
// 引　数：LPDIRECT3DDEVICE9 ３Ｄデバイスのアドレス
//-----------------------------------------------------------------------------
void PostEffect::InitializeDepthTextureSurce(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT hr = pDevice->CreateDepthStencilSurface(WINDOW_WIDTH, WINDOW_HEIGHT, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, true, &m_pDepthBuffer, nullptr);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_CREATE_DEPTHSTENCIL_ERROR);
	}

	hr = pDevice->CreateTexture(WINDOW_WIDTH, WINDOW_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pFullScreenTexture, nullptr);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_TEXTURE_CREATE_ERROR);
	}

	hr = m_pFullScreenTexture->GetSurfaceLevel(0, &m_pFullScreenSurface);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_GET_SURFACE_ERROR);
	}
}

//-----------------------------------------------------------------------------
// シェーダーのロード
// 引　数：LPDIRECT3DDEVICE9 ３Ｄデバイスのアドレス
// 　　　　const WORD        エフェクトＩＤ（resource.hで定義）
// 　　　　string            テクニック名
//-----------------------------------------------------------------------------
void PostEffect::LoadShader(LPDIRECT3DDEVICE9 pDevice, const WORD fxid, std::string technique)
{
	DWORD flag = 0;

#ifdef _DEBUG
	flag = D3DXSHADER_DEBUG;
#endif

	HRESULT hr = D3DXCreateEffectFromResource(pDevice, nullptr, MAKEINTRESOURCE(fxid), nullptr, nullptr, flag, nullptr, &m_pEffect, nullptr);

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_PRIMITIVE_LOAD_RESOURCE_ERROR);
	}

	hr = m_pEffect->SetTechnique(technique.c_str());

	if (FAILED(hr)) {
		throw DxSystemException(DxSystemException::OM_SET_TECHNIQUE_ERROR);
	}
}

//-----------------------------------------------------------------------------
// 頂点情報の設定
//-----------------------------------------------------------------------------
void PostEffect::SetVertices()
{
	vertices[0].position = { -1.0f, +1.0f, 0.1f };
	vertices[0].coord = { 0, 0 };
	vertices[1].position = { +1.0f, +1.0f, 0.1f };
	vertices[1].coord = { 1, 0 };
	vertices[2].position = { +1.0f, -1.0f, 0.1f };
	vertices[2].coord = { 1, 1 };
	vertices[3].position = { -1.0f, -1.0f, 0.1f };
	vertices[3].coord = { 0, 1 };
}

//-----------------------------------------------------------------------------
// 確保したメモリの解放
//-----------------------------------------------------------------------------
void PostEffect::Release()
{
	if (m_pEffect) {
		m_pEffect->Release();
		m_pEffect = nullptr;
	}

	if (m_pOldSurface) {
		m_pOldSurface->Release();
		m_pOldSurface = nullptr;
	}

	if (m_pFullScreenSurface) {
		m_pFullScreenSurface->Release();
		m_pFullScreenSurface = nullptr;
	}

	if (m_pFullScreenTexture) {
		m_pFullScreenTexture->Release();
		m_pFullScreenTexture = nullptr;
	}

	if (m_pOldDepthBuffer) {
		m_pOldDepthBuffer->Release();
		m_pOldDepthBuffer = nullptr;
	}

	if (m_pDepthBuffer) {
		m_pDepthBuffer->Release();
		m_pDepthBuffer = nullptr;
	}
}
