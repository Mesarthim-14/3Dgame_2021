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
#include "particle_factory.h"

//=====================================================
// マクロ定義
//=====================================================

//=====================================================
// 前方宣言
//=====================================================
CParticleFactory;

//=====================================================
// ビルボードクラス
//=====================================================
class CParticle : public CBillboard
{
public:
	CParticle(PRIORITY Priority = PRIORITY_PARTICLE);	// コンストラクタ
	~CParticle();										// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理

	static CParticle*Create(D3DXVECTOR3 pos,			// インスタンス生成
		CParticleFactory::PARTICLE Particle,
		LPDIRECT3DTEXTURE9 pTexture);
private:
};

#endif