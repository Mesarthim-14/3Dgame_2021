//=======================================================================================
//
// ゲーム処理 [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// インクルード
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "meshfield.h"
#include "bg.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "fire.h"
#include "enemy.h"
#include "life_frame.h"
#include "life_bar.h"
#include "crab.h"
#include "quest_logo.h"

//=======================================================================================
// マクロ定義
//=======================================================================================

//=======================================================================================
// static初期化
//=======================================================================================
CCamera *CGame::m_pCamera = NULL;
CLight *CGame::m_pLight = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CBg *CGame::m_pBg = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CPause *CGame::m_pPause = NULL;
CSea *CGame::m_pSea = NULL;

//=======================================================================================
// コンストラクタ
//=======================================================================================
CGame::CGame(PRIORITY Priority) : CScene(Priority)
{
	m_bGameEnd = false;
	m_nTimeCounter = 0;
}

//=======================================================================================
// デストラクタ
//=======================================================================================
CGame::~CGame()
{
}

//=======================================================================================
// クリエイト
//=======================================================================================
CGame* CGame::Create(void)
{
	// メモリ確保
	CGame* pGame = new CGame();

	// 初期化処理
	pGame->Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pGame;
}

//=======================================================================================
// 初期化処理
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// カメラクラスのクリエイト
	m_pCamera = CCamera::Create();

	//ライトクラスの生成
	m_pLight = new CLight;

	// ライトの初期化処理
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// プレイヤーの生成
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));	
	}

	// メッシュフィールド
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create();
	}

	// 背景
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	// 蟹の生成
	CCrab::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//BGM
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//フォントの生成
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//=======================================================================================
// 終了処理
//=======================================================================================
void CGame::Uninit(void)
{
	if (m_pCamera != NULL)
	{
		//カメラクラスの終了処理呼び出す
		m_pCamera->Uninit();

		//メモリの破棄
		delete m_pCamera;

		//メモリのクリア
		m_pCamera = NULL;
	}

	// メッシュフィールド
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	// 背景
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}

	// ライトの終了処理
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// プレイヤーの終了処理
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;
	}

	//サウンド情報取得
	CSound *pSound = CManager::GetSound();

	//ゲームBGM停止
	pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);

	//オブジェクトの破棄
	Release();
}

//=======================================================================================
// 更新処理
//=======================================================================================
void CGame::Update(void)
{
	if (m_pCamera != NULL)
	{
		//カメラクラスの更新処理
		m_pCamera->Update();
	}

	// メッシュフィールド
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Update();
	}

	for (int nCount = 0; nCount < FIRE_NUM; nCount++)
	{
		// 炎の生成
	//	CFire::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f), FIRE_LIFE);
	}

	// ゲームの設定
	SetGame();

}

//=======================================================================================
// 描画処理
//=======================================================================================
void CGame::Draw(void)
{
	// メッシュフィールド
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Draw();
	}

	// 背景
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}

	if (m_pLight != NULL)
	{
		m_pLight->ShowLightInfo();
	}
}

//=======================================================================================
// ゲームの設定
//=======================================================================================
void CGame::SetGame(void)
{
	m_nTimeCounter++;

	// クエストロゴ生成
	if (m_nTimeCounter == 60)
	{
		CQuestLogo::Create();
	}
}


//=======================================================================================
// カメラの情報
//=======================================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=======================================================================================
// ライトの情報
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// プレイヤーの情報
//=======================================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=======================================================================================
// コンテニューの情報
//=======================================================================================
CPause * CGame::GetPause(void)
{
	return m_pPause;
}