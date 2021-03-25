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
// テクスチャの名前
#define TEXTURE_NAME_FIRE			("data/Texture/fire111.jpg")				// 炎
#define TEXTURE_NAME_LIFEBAR		("data/Texture/LifeBar.png")				// ライフの枠
#define TEXTURE_NAME_LIFEGAGE		("data/Texture/LifeBar000.png")				// ライフバー(緑)
#define TEXTURE_NAME_TITLE_BG		("data/Texture/bg001.png")					// タイトル画面の背景
#define TEXTURE_NAME_PARTICLE		("data/Texture/effect003.png")				// パーティクル
#define TEXTURE_NAME_SKILL_UI		("data/Texture/skill_ui.png")				// スキルのUI
#define TEXTURE_NAME_SWORD_LOCUS	("data/Texture/sword_locus000.png")			// 剣の軌跡
#define TEXTURE_NAME_SLASH_EFFECT	("data/Texture/magic24.jpg")				// 斬撃のエフェクト
#define TEXTURE_NAME_SKILL_START	("data/Texture/Sword_Skill_Start001.png")	// スキルの待機時
#define TEXTURE_NAME_QUEST_START	("data/Texture/QuestStart_Logo.png")		// クエストの開始
#define TEXTURE_NAME_OPERATION		("data/Texture/button_ui.png")				// 操作ボタンのUI
#define TEXTURE_NAME_JUMP_IMPACT	("data/Texture/inpact.tga")					// ジャンプの衝撃
#define TEXTURE_NAME_ROAR_IMPACT	("data/Texture/inpact_red.tga")				// 咆哮の衝撃
#define TEXTURE_NAME_HIT_IMPACT_000	("data/Texture/Hit_Impact002.tga")			// 攻撃時の衝撃
#define TEXTURE_NAME_FLOOR			("data/Texture/floor.jpg")					// 床のテクスチャ
#define TEXTURE_NAME_DUSH_IMPACT	("data/Texture/Hit_Impact003.tga")			// ダッシュの衝撃
#define TEXTURE_NAME_ENEMY_LOCUS	("data/Texture/sword_locus002.png")			// ボスの軌跡
#define TEXTURE_NAME_HIT_UI			("data/Texture/hit_ui.png")					// HITのUI
#define TEXTURE_NAME_DAMAGE_UI		("data/Texture/damage_ui.png")				// ダメージのUI

// 分割テクスチャの名前
#define SEPARATE_TEX_NAME_SHARP				("data/Texture/sharp_effect.png")			// 鋭いエフェクト
#define SEPARATE_TEX_NAME_ELECTRICITY		("data/Texture/Electricity_Effect000.png")	// 電撃エフェクト
#define SEPARATE_TEX_NAME_SMOKE				("data/Texture/smoke000.png")				// 煙エフェクト
#define SEPARATE_TEX_NAME_HIT_EFFECT		("data/Texture/hit_effect000.png")			// ヒットエフェクト
#define SEPARATE_TEX_NAME_HIT_IMPACT		("data/Texture/slash_impact.png")			// ヒット時の衝撃
#define SEPARATE_TEX_NAME_SAND_SMOKE		("data/Texture/sand_smoke.png")				// ヒット時の衝撃
#define SEPARATE_TEX_NAME_CIRCLE			("data/Texture/circle.png")					// サークルエフェクト
#define SEPARATE_TEX_NAME_ATTACK_LIGHT		("data/Texture/attack_light_001.png")		// 攻撃時の光
#define SEPARATE_TEX_NAME_KOBOLD_SMOKE		("data/Texture/smoke_101.png")				// コボルトの煙
#define SEPARATE_TEX_NAME_JUMP_SMOKE		("data/Texture/smoke_effect000.png")			// ジャンプの煙
#define SEPARATE_TEX_NAME_ATTACK_CIRCLE		("data/Texture/attack_circle000.png")		// 攻撃の円
#define SEPARATE_TEX_NAME_DAMAGE_NUMBER		("data/Texture/damage_number.png")			// ダメージの数字テクスチャ
#define SEPARATE_TEX_NAME_ARM_LIGHT			("data/Texture/arm_light.png")				// 手の光
#define SEPARATE_TEX_NAME_DAMAGE_EFFECT		("data/Texture/damage_impact100.tga")		// ダメージ時のエフェクト
#define SEPARATE_TEX_NAME_ROAR_FIRE			("data/Texture/roar_attack000.png")			// 咆哮時のファイア
#define SEPARATE_TEX_NAME_ROAR_LIGHT		("data/Texture/roar_light000.png")			// 咆哮時の光
#define SEPARATE_TEX_NAME_COMBO_NUMBER		("data/Texture/combo_damage.png")			// コンボのナンバー
#define SEPARATE_TEX_NAME_COMBO_NUMBER_000	("data/Texture/combo_damage000.png")		// コンボのダメージナンバー

//=============================================================================
// コンストラクタ
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// デストラクタ
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CTexture * CTexture::Create(void)
{
	CTexture *pTexture = new CTexture;

	return pTexture;
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
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_OPERATION, &m_apTexture[TEXTURE_NUM_OPERATION]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_JUMP_IMPACT, &m_apTexture[TEXTURE_NUM_JUMP_IMPACT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ROAR_IMPACT, &m_apTexture[TEXTURE_NUM_ROAR_IMPACT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_HIT_IMPACT_000, &m_apTexture[TEXTURE_NUM_HIT_IMPACT_000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_FLOOR, &m_apTexture[TEXTURE_NUM_FLOOR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_DUSH_IMPACT, &m_apTexture[TEXTURE_NUM_DUSH_IMPACT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_LOCUS, &m_apTexture[TEXTURE_NUM_ENEMY_LOCUS]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_HIT_UI, &m_apTexture[TEXTURE_NUM_HIT_UI]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_DAMAGE_UI, &m_apTexture[TEXTURE_NUM_DAMAGE_UI]);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CTexture::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// 分割テクスチャのロード
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_SHARP, &m_apSeparateTexture[SEPARATE_TEX_SHARP].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ELECTRICITY, &m_apSeparateTexture[SEPARATE_TEX_ELECTRICITY].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_SMOKE, &m_apSeparateTexture[SEPARATE_TEX_SMOKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_HIT_EFFECT, &m_apSeparateTexture[SEPARATE_TEX_HIT_EFFECT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_HIT_IMPACT, &m_apSeparateTexture[SEPARATE_TEX_HIT_IMPACT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_SAND_SMOKE, &m_apSeparateTexture[SEPARATE_TEX_SAND_SMOKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_CIRCLE, &m_apSeparateTexture[SEPARATE_TEX_CIRCLE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ATTACK_LIGHT, &m_apSeparateTexture[SEPARATE_TEX_ATTACK_LIGHT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_KOBOLD_SMOKE, &m_apSeparateTexture[SEPARATE_TEX_KOBOLD_SMOKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_JUMP_SMOKE, &m_apSeparateTexture[SEPARATE_TEX_JUMP_SMOKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ATTACK_CIRCLE, &m_apSeparateTexture[SEPARATE_TEX_ATTACK_CIRCLE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_DAMAGE_NUMBER, &m_apSeparateTexture[SEPARATE_TEX_DAMAGE_NUMBER].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ARM_LIGHT, &m_apSeparateTexture[SEPARATE_TEX_ARM_LIGHT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_DAMAGE_EFFECT, &m_apSeparateTexture[SEPARATE_TEX_DAMAGE_EFFECT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ROAR_FIRE, &m_apSeparateTexture[SEPARATE_TEX_ROAR_FIRE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ROAR_LIGHT, &m_apSeparateTexture[SEPARATE_TEX_ROAR_LIGHT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_COMBO_NUMBER, &m_apSeparateTexture[SEPARATE_TEX_COMBO_NUMBER].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_COMBO_NUMBER_000, &m_apSeparateTexture[SEPARATE_TEX_COMBO_NUMBER_000].pSeparateTexture);

	return S_OK;
}

//=============================================================================
// 分割テクスチャのアンロード
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// テクスチャの解放
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
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
		if (m_apTexture[Tex_Num] != nullptr)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// テクスチャ情報
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// 分割テクスチャの情報
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// 配列より小さかったら
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// テクスチャ情報
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}