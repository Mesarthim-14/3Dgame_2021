//=============================================================================
//
// ライトエフェクトのクラス [light_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "light_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CLightEffect::CLightEffect(PRIORITY Priority) : CModel(Priority)
{
	m_nLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLightEffect::~CLightEffect()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CLightEffect * CLightEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nLife)
{
	//3Dポリゴンクラスのポインタ変数
	CLightEffect *pLightEffect = new CLightEffect;

	//メモリが確保できていたら
	if (pLightEffect != NULL)
	{
		//初期化処理呼び出し
		pLightEffect->Init(pos, size);
		pLightEffect->m_nLife = nLife;
	}

	return pLightEffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLightEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CModel::Init(pos, size);
	BindModel(CXfile::GetXfile(CXfile::XFILE_NUM_SWORD_EFFECT));

	BindTexture(&CXfile::GetXfile(CXfile::XFILE_NUM_SWORD_EFFECT).apTexture[0]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLightEffect::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLightEffect::Update(void)
{
	// 更新処理
	CModel::Update();
	
	m_nLife--;

	// もしライフが指定されたフレーム以下になったら
	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLightEffect::Draw(void)
{
	D3DXMATERIAL *pMat;		//マテリアルデータへのポインタ

	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f);
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.3f, 1.0f, 0.3f, 0.2f);

	//	pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
		pMat[nCntMat].MatD3D.Ambient.a = 1.0f;
	}

	// 描画処理
	CModel::Draw();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}
}