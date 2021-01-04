//=============================================================================
//
// Xファイルの管理クラス [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define XFILE_NAME_BG		("data/model/dome2.x")		// 背景

//=============================================================================
// static初期化
//=============================================================================
CModel::MODEL CXfile::m_aXfile[MAX_XFILE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CXfile::CXfile()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CXfile::~CXfile()
{
}

//=============================================================================
// Xファイルロード
//=============================================================================
HRESULT CXfile::ModelLoad(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(XFILE_NAME_BG,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_BG].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_BG].dwNumMat,
		&m_aXfile[XFILE_NUM_BG].pMesh);

	//マテリアル情報の解析
	D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[XFILE_NUM_BG].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aXfile[XFILE_NUM_BG].pBuffMat; nCntMat++)
	{
		//ファイルネームの取得
	//	char *aXfileName = materials[nCntMat].pTextureFilename;

			//テクスチャの読み込み
	//		D3DXCreateTextureFromFile(pDevice, aXfileName, &m_aXfile[XFILE_NUM_BG].m_apTexture[nCntMat]);
		
	}

	return S_OK;
}

//=============================================================================
// Xファイルアンロード
//=============================================================================
void CXfile::ModelUnLoad(void)
{
	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//メッシュの破棄
		if (m_aXfile[nCount].pMesh != NULL)
		{
			m_aXfile[nCount].pMesh->Release();
			m_aXfile[nCount].pMesh = NULL;
		}
		//マテリアルの破棄
		if (m_aXfile[nCount].pBuffMat != NULL)
		{
			m_aXfile[nCount].pBuffMat->Release();
			m_aXfile[nCount].pBuffMat = NULL;
		}

		for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
		{
			if (m_aXfile[nCount].m_apTexture[nCntTexture] != NULL)
			{
				m_aXfile[nCount].m_apTexture[nCntTexture]->Release();
				m_aXfile[nCount].m_apTexture[nCntTexture] = NULL;
			}
		}
	}
}

//=============================================================================
// モデルの情報
//=============================================================================
CModel::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}