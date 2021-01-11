//=============================================================================
//
// テクスチャの管理クラス [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_NAME_FIRE		("data/Texture/fire111.png")	// 炎
#define TEXTURE_NAME_BG			("data/Texture/sky.jpg")		// ゲーム背景
#define TEXTURE_NAME_LIFEBAR	("data/Texture/LifeBar.png")	// ライフの枠
#define TEXTURE_NAME_LIFEGAGE	("data/Texture/Life002.png")	// ライフバー(緑)

//=============================================================================
// static初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEXTURE] = {};				// テクスチャのポインタ
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTextureList = {};

// テクスチャ名の設定
FILENAME_LIST CTexture::m_aTexFileName =
{
	{ "data/Texture/fire111.png" },						// 炎
	{ "data/Texture/sky.jpg" },							// ゲーム背景
};

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CTexture::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_FIRE, &m_apTexture[TEXTURE_NUM_FIRE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG, &m_apTexture[TEXTURE_NUM_BG]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LIFEBAR, &m_apTexture[TEXTURE_NUM_LIFEBAR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LIFEGAGE, &m_apTexture[TEXTURE_NUM_LIFEGAGE]);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	return m_apTexture[Tex_Num];
}
