//=======================================================================================
//
// タイトルクラスの処理 [title.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルードファイル
//=======================================================================================
#include "title.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "title_bg.h"
#include "titlelogo.h"
#include "sound.h"
#include "joypad.h"

//=======================================================================================
//静的メンバ変数宣言
//=======================================================================================
CTitleBg *CTitle::m_pTitleBg = NULL;
CTitlelogo *CTitle::m_pTitlelogo = NULL;

//=======================================================================================
// タイトルクラスのコンストラクタ
//=======================================================================================
CTitle::CTitle(PRIORITY Priority) : CScene(Priority)
{
}

//=======================================================================================
// タイトルクラスのデストラクタ
//=======================================================================================
CTitle::~CTitle()
{

}

//=======================================================================================
// タイトルクラスのクリエイト処理
//=======================================================================================
CTitle* CTitle::Create(void)
{
	// メモリ確保
	CTitle* pTitle = new CTitle;

	if (pTitle != NULL)
	{
		// 初期化処理
		pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	return pTitle;
}

//=======================================================================================
// タイトルクラスの初期化処理
//=======================================================================================
HRESULT CTitle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// タイトル背景の処理
	if (m_pTitleBg == NULL)
	{
		// オブジェクト生成
		m_pTitleBg = CTitleBg::Create(TITLE_BG_POS, TITLE_BG_SIZE);
	}

	//// タイトルロゴの処理
	//if (m_pTitlelogo == NULL)
	//{
	//	// オブジェクト生成
	//	m_pTitlelogo = CTitlelogo::Create(
	//		D3DXVECTOR3(TITLE_UI_POS_X, TITLE_UI_POS_Y, 0.0f), 
	//		D3DXVECTOR3(TITLE_UI_SIZE, TITLE_UI_SIZE, 0.0f));
	//}

	// サウンドの情報
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=======================================================================================
// タイトルクラスの終了処理
//=======================================================================================
void CTitle::Uninit(void)
{
	// タイトルロゴの処理
	if (m_pTitlelogo != NULL)
	{
		// 終了処理
		m_pTitlelogo = NULL;
	}

	// タイトル背景の処理
	if (m_pTitleBg != NULL)
	{
		// オブジェクト生成
		m_pTitleBg = NULL;
	}

	//BGMを止める処理
	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);

	//オブジェクトの破棄
	Release();
}

//=======================================================================================
// タイトルクラスの更新処理
//=======================================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetSound();
	
	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE 
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TUTORIAL);
		pSound->Play(CSound::SOUND_LABEL_SE_START);
	}
}

//=======================================================================================
// タイトルクラスの描画処理
//=======================================================================================
void CTitle::Draw(void)
{

}