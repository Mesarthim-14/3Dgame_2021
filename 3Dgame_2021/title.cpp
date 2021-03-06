//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene2d.h"
#include "fade.h"
#include "keyboard.h"
#include "texture.h"
#include "sound.h"
#include "joypad.h"
#include "resource_manager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ROTATION_NUM		(0.1f)		// 回転の速さ

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[MAX_TITLE_UI_NUM] = {};

//=============================================================================
//リザルトクラスのコンストラクタ
//=============================================================================
CTitle::CTitle(PRIORITY Priority) : CScene(Priority)
{
	//メンバ変数のクリア
	m_pScene2D = NULL;
	m_pPress = NULL;
	m_pTitleName = NULL;
}

//=============================================================================
//リザルトクラスのデストラクタ
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
//リザルトクラスのクリエイト処理
//=============================================================================
CTitle * CTitle::Create(void)
{
	//リザルトクラスのポインタ変数
	CTitle *pTitle = new CTitle;

	//メモリが確保できていたら
	if (pTitle != NULL)
	{
		//初期化処理呼び出し
		pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	return pTitle;
}

//=============================================================================
// タイトルクラスのテクスチャ読み込み処理
//=============================================================================
HRESULT CTitle::Load(void)
{
	//デバイス情報の取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/Texture/magic22.jpg", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/StartLogo.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/title_name.png", &m_pTexture[2]);

	return S_OK;
}

void CTitle::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TITLE_UI_NUM; nCount++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}

}

//=============================================================================
//リザルトクラスの初期化処理
//=============================================================================
HRESULT CTitle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	if (m_pScene2D == NULL)
	{
		//2Dオブジェクトの生成
		m_pScene2D = CScene2D::Create(pos, size);

		if (m_pScene2D != NULL)
		{
			m_pScene2D->BindTexture(m_pTexture[0]);
		}
	}

	// PRESSロゴのポインタ
	if (m_pPress == NULL)
	{
		m_pPress = CScene2D::Create(D3DXVECTOR3(pos.x, pos.y + TITLE_PRESS_POS_Y, 0.0f), D3DXVECTOR3(TITLE_PRESS_SIZE_X, TITLE_PRESS_SIZE_Y, 0.0f));
		m_pPress->BindTexture(m_pTexture[1]);
	}

	if (m_pTitleName == NULL)
	{
		//2Dオブジェクトの生成
		m_pTitleName = CScene2D::Create(D3DXVECTOR3(pos.x, pos.y - 50.0f, 0.0f), D3DXVECTOR3(TITLE_SIZE_X, TITLE_SIZE_Y, 0.0f));

		if (m_pTitleName != NULL)
		{
			m_pTitleName->BindTexture(m_pTexture[2]);
		}

	}
	return S_OK;
}

//=============================================================================
//リザルトクラスの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	if (m_pTitleName != NULL)
	{
		m_pTitleName->Uninit();
		m_pTitleName = NULL;
	}
	
	if (m_pPress != NULL)
	{
		m_pPress->Uninit();
		m_pPress = NULL;
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
//リザルトクラスの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetResourceManager()->GetSoundClass();

	// コントローラのstartを押したときか、エンターキーを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_GAME);
	}

	if (m_pPress != NULL)
	{
	//	m_pPress->SetRotation(ROTATION_NUM);
	}

}

//=============================================================================
//リザルトクラスの描画処理
//=============================================================================
void CTitle::Draw(void)
{
}
