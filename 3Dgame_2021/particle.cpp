//=====================================================
//
// パーティクルクラス [particle.cpp]
// Author : 小西優斗
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=====================================================
// マクロ定義
//=====================================================
#define DEFAULT_POS_Y		(200.0f)		// 世界の高さの標準

//=====================================================
// コンストラクタ
//=====================================================
CParticle::CParticle(PRIORITY Priority) : CBillboard(Priority)
{
	
}

//=====================================================
// デストラクタ
//=====================================================
CParticle::~CParticle()
{

}

//=====================================================
// インスタンス生成
//=====================================================
CParticle * CParticle::Create(D3DXVECTOR3 pos, CParticleFactory::PARTICLE Particle,
	LPDIRECT3DTEXTURE9 pTexture)
{
	// メモリ確保
	CParticle *pParticle = new CParticle;

	if (pParticle != NULL)
	{
		// テクスチャ設定
		pParticle->BindTexture(pTexture);

		// 距離の設定
		D3DXVECTOR3 Distance;
		Distance = D3DXVECTOR3(
			(float)(rand() % (int)Particle.Distance.x + rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x),
			(float)(rand() % (int)Particle.Distance.y + rand() % (int)Particle.Distance.y),
			(float)(rand() % (int)Particle.Distance.z + rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z));

		// ランダムで出現を決める
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y,
			pos.z + Distance.z);

		// 初期化処理
		pParticle->Init(TargetPos, Particle.size);

		// 移動量設定
		D3DXVECTOR3 move;
		switch (Particle.bGravity)
		{
			// 重力無し
		case false:
			// 移動量
			move =
				D3DXVECTOR3(
				(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
					(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y),
					(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
			break;

			// 重力あり
		case true:
			// 移動量
			move =
				D3DXVECTOR3(
				(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
					(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y - rand() % (int)Particle.move.y),
					(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
			break;
		}

		// 移動量
		pParticle->SetMove(move);

		// 色の設定
		pParticle->SetColor(Particle.color);

		// 体力の設定
		pParticle->SetLife(Particle.nLife);

		// アルファテストの設定
		pParticle->SetAlpha(Particle.bAlpha);

	}

	return pParticle;
}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CBillboard::Init(pos, size);

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CParticle::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();

	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CParticle::Update(void)
{
	// 更新処理
	CBillboard::Update();
}

//=====================================================
// 描画処理
//=====================================================
void CParticle::Draw(void)
{
	// 描画処理
	CBillboard::Draw();
}