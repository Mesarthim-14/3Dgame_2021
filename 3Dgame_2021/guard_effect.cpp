//=============================================================================
//
// ガードエフェクトのクラス [guard_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "guard_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGuardEffect::CGuardEffect(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGuardEffect::~CGuardEffect()
{

}

//=============================================================================
// クリエイト処理
//=============================================================================
CGuardEffect * CGuardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//3Dポリゴンクラスのポインタ変数
	CGuardEffect *pGuardEffect = new CGuardEffect;

	//メモリが確保できていたら
	if (pGuardEffect != NULL)
	{
		//初期化処理呼び出し
		pGuardEffect->Init(pos, size);
	}

	return pGuardEffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGuardEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CModel::Init(pos, size);

	BindModel(CXfile::GetXfile(CXfile::XFILE_NUM_GUARD_EFFECT));
	BindTexture(CXfile::GetXfileTexture(CXfile::XFILE_NUM_GUARD_EFFECT));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGuardEffect::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGuardEffect::Update(void)
{
	// 更新処理
	CModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CGuardEffect::Draw(void)
{
	D3DXMATERIAL *pMat;		//マテリアルデータへのポインタ

	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// 透明度戻す
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
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