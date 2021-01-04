//=================================================================================
//
// 背景クラス [bg.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// インクルード
//=================================================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"

//=================================================================================
// インスタンス生成
//=================================================================================
CBg * CBg::Create(void)
{
	CBg *pBg = new CBg;

	if (pBg != NULL)
	{
		// 初期化処理
		pBg->Init();
	}

	return pBg;
}

//=================================================================================
// コンストラクタ
//=================================================================================
CBg::CBg()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=================================================================================
// デストラクタ
//=================================================================================
CBg::~CBg()
{
}

//=================================================================================
// 初期化処理
//=================================================================================
HRESULT CBg::Init(void)
{

//	model.dwNumMat = m_nNumMat;
//	model.pBuffMat = m_pBuffMat;
//	model.pMesh = m_pMesh;

	//モデル情報を設定
	CModel::BindModel(CXfile::GetXfile(CXfile::XFILE_NUM_BG));

	m_pos = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(BG_SIZE_X, BG_SIZE_Y, BG_SIZE_Z);

	// 座標情報を与える
	CModel::SetPos(m_pos);

	return S_OK;
}

//=================================================================================
// 終了処理
//=================================================================================
void CBg::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=================================================================================
// 更新処理
//=================================================================================
void CBg::Update(void)
{
}

//=================================================================================
// 描画処理
//=================================================================================
void CBg::Draw(void)
{
//	// Rendererクラスからデバイスを取得
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	
//	D3DMATERIAL9 matDef;					// 現在のマテリアル保持用
//	D3DXMATERIAL* pMat;						// マテリアルデータへのポインタ
//	DWORD ambient;
//
//	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
//	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
//
//	pDevice->LightEnable(0, FALSE);
//
//	// ワールドマトリックスの初期化
//	D3DXMatrixIdentity(&m_mtxWorld);
//
//	//// スケールを反映
//	D3DXMatrixScaling(&mtxScale,
//		m_size.x,
//		m_size.y,
//		m_size.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);
//
//	// 向きを反映
//	D3DXMatrixRotationYawPitchRoll(&mtxRot,
//		m_rot.y,
//		m_rot.x,
//		m_rot.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
//
//	// 位置を反映
//	D3DXMatrixTranslation(&mtxTrans,
//		m_pos.x,
//		m_pos.y,
//		m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
//
//	// ワールドマトリックスの設定
//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
//
//	// テクスチャの設定
//	pDevice->SetTexture(0, m_apTexture[0]);
//
//	// 現在のマテリアルを取得する
//	pDevice->GetMaterial(&matDef);
//
//	// マテリアルデータへのポインタを取得
//	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
//	{
//		pMat[nCntMat].MatD3D.Ambient.r = 1.0f;
//		pMat[nCntMat].MatD3D.Ambient.g = 1.0f;
//		pMat[nCntMat].MatD3D.Ambient.b = 1.0f;
//		pMat[nCntMat].MatD3D.Ambient.a = 1.0f;
//
//		// テクスチャの設定
//		pDevice->SetTexture(0, m_apTexture[0]);
//
//		// マテリアルの設定
//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//		// モデルパーツ
//		m_pMesh->DrawSubset(nCntMat);
//	}
//
//	// 保持していたマテリアルを戻す
//	pDevice->SetMaterial(&matDef);
//
//	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
//	pDevice->LightEnable(0, TRUE);
//
//	// テクスチャの設定
//	pDevice->SetTexture(0, NULL);

	// 描画処理
	CModel::Draw();
}