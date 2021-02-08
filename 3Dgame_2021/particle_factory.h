#ifndef _PARTICLE_FACTORY_H_
#define _PARTICLE_FACTORY_H_
//=============================================================================
//
// パーティクル生成クラスヘッダー [particle_factory.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
//クラス宣言
//=============================================================================
class CParticleFactory
{
public:

	// パーティクルの構造体
	typedef struct
	{
		D3DXVECTOR3 size;		// サイズ
		D3DXVECTOR3 move;		// 移動量
		D3DXVECTOR3 Distance;	// 距離
		int nLife;				// ライフ
		int nNum;				// 数
		D3DXCOLOR color;		// 色
		bool bGravity;			// 重力
		bool bAlpha;			// アルファテスト
	}PARTICLE;

	// テクスチャの番号の列挙型
	typedef enum
	{
		PARTICLE_NUM_NONE = -1,		// 初期値
		PARTICLE_NUM_EXPLOSION,		// ダメージを受けたとき
		PARTICLE_NUM_SWORD_SKILL,	// スキルの待機時間中
		PARTICLE_NUM_SKILL_BLADE,	// スキル時の刀身
		PARTICLE_NUM_MAX
	}PARTICLE_TYPE;

	CParticleFactory();													// コンストラクタ
	~CParticleFactory();												// デストラクタ

	static HRESULT ReadFile(void);										// ファイルの読み込み
	static void CreateParticle(D3DXVECTOR3 pos, PARTICLE_TYPE type);									// パーティクルのクラス
private:
	static PARTICLE m_Particle[PARTICLE_NUM_MAX];			// パーティクル
};
#endif
