#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//=====================================================
//
// パーティクルヘッダー [particle.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"

//=====================================================
// マクロ定義
//=====================================================
#define EXPLOSION_SIZE_X	(90.0f)		// サイズ
#define EXPLOSION_SIZE_Y	(90.0f)		// サイズ
#define EXPLOSION_DISTANCE	(150)		// 距離
#define EXPLOSION_SPEED		(10)		// 速度
#define EXPLOSION_LIFE		(35)		// ライフ
#define EXPLOSION_NUM		(40)		// 数

#define EXPLOSION_SIZE		(D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f))		// サイズ
#define EXPLOSION_COLOR		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))							// カラー

#define SWORD_SKILL_SIZE_X		(90.0f)		// サイズ
#define SWORD_SKILL_SIZE_Y		(90.0f)		// サイズ
#define SWORD_SKILL_DISTANCE	(400)		// 距離
#define SWORD_SKILL_SPEED		(5)			// 速度
#define SWORD_SKILL_LIFE		(70)		// ライフ
#define SWORD_SKILL_NUM			(10)		// 数

#define SWORD_SKILL_SIZE		(D3DXVECTOR3(SWORD_SKILL_SIZE_X, SWORD_SKILL_SIZE_Y, 0.0f))	// サイズ
#define SWORD_SKILL_COLOR		(D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f))							// カラー

//=====================================================
// 前方宣言
//=====================================================

//=====================================================
// ビルボードクラス
//=====================================================
class CParticle : public CBillboard
{
public:
	CParticle(PRIORITY Priority = PRIORITY_1);		// コンストラクタ
	~CParticle();									// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CParticle*Create(D3DXVECTOR3 pos,			// インスタンス生成
		D3DXVECTOR3 size, D3DXCOLOR color,
		D3DXVECTOR3 Distance, D3DXVECTOR3 move, int nLife);

private:
};

#endif