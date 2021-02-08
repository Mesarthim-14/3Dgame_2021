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
#define TEXTURE_NAME_FIRE			("data/Texture/fire111.jpg")				// 炎
#define TEXTURE_NAME_LIFEBAR		("data/Texture/LifeBar.png")				// ライフの枠
#define TEXTURE_NAME_LIFEGAGE		("data/Texture/LifeBar000.png")				// ライフバー(緑)
#define TEXTURE_NAME_TITLE_BG		("data/Texture/title.png")					// タイトル画面の背景
#define TEXTURE_NAME_PARTICLE		("data/Texture/effect003.png")				// パーティクル
#define TEXTURE_NAME_SKILL_UI		("data/Texture/skill_ui.png")				// スキルのUI
#define TEXTURE_NAME_SWORD_LOCUS	("data/Texture/SwordLocus003.png")			// 剣の軌跡
#define TEXTURE_NAME_SLASH_EFFECT	("data/Texture/magic24.jpg")				// 斬撃のエフェクト
#define TEXTURE_NAME_SKILL_START	("data/Texture/Sword_Skill_Start001.png")	// スキルの待機時
#define TEXTURE_NAME_QUEST_START	("data/Texture/QuestStart_Logo.png")		// クエストの開始

//=============================================================================
// static初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[TEXTURE_NUM_MAX] = {};				// テクスチャのポインタ
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTextureList = {};

//// テクスチャ名の設定
//FILENAME_LIST CTexture::m_aTexFileName =
//{
//	{ "data/Texture/fire111.png" },						// 炎
//	{ "data/Texture/sky.jpg" },							// ゲーム背景
//};

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
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LIFEBAR, &m_apTexture[TEXTURE_NUM_GAGEFLAME]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LIFEGAGE, &m_apTexture[TEXTURE_NUM_GAGEBAR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_TITLE_BG, &m_apTexture[TEXTURE_NUM_TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_PARTICLE, &m_apTexture[TEXTURE_NUM_PARTICLE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SKILL_UI, &m_apTexture[TEXTURE_NUM_SKILL_UI]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SWORD_LOCUS, &m_apTexture[TEXTURE_NUM_SWORD_LOCUS]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SLASH_EFFECT, &m_apTexture[TEXTURE_NUM_SLASH_EFFECT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SKILL_START, &m_apTexture[TEXTURE_NUM_SKILL_START]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_QUEST_START, &m_apTexture[TEXTURE_NUM_QUEST_START]);

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
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != NULL)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}