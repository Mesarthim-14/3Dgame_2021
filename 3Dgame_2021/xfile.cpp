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
// モデルネーム
#define XFILE_NAME_BG						("data/model/dome2.x")						// 背景
#define XFILE_NAME_SWORD_EFFECT				("data/model/Effect/Sword__Effect003.x")	// 背景
#define XFILE_NAME_SWORD_LOCUS_EFFECT		("data/model/Effect/Locus_Effect.x")		// 軌跡のエフェクト
#define XFILE_NAME_GUARD_EFFECT				("data/model/Effect/guard_Effect000.x")		// 軌跡のエフェクト

// テクスチャネーム
#define XFILE_TEXTURE_NAME_EFFECT			("data/Texture/sword_effect001.jpg")		// エフェクト
#define XFILE_TEXTURE_SWORD_LOCUS_EFFECT	("data/model/Texture/Sword_Effect001.png")	// 軌跡のテクスチャ
#define XFILE_TEXTURE_GUARD_EFFECT			("data/model/Texture/guard_Effect000.png")	// 軌跡のテクスチャ

//=============================================================================
// static初期化
//=============================================================================
CXfile::MODEL CXfile::m_aXfile[XFILE_NUM_MAX] = {};

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

	// Xファイルの読み込み
	D3DXLoadMeshFromX(XFILE_NAME_SWORD_EFFECT,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].dwNumMat,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].pMesh);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(XFILE_NAME_SWORD_LOCUS_EFFECT,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].dwNumMat,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].pMesh);

	// Xファイルの読み込み
	D3DXLoadMeshFromX(XFILE_NAME_GUARD_EFFECT,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_GUARD_EFFECT].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_GUARD_EFFECT].dwNumMat,
		&m_aXfile[XFILE_NUM_GUARD_EFFECT].pMesh);


	if (m_aXfile[XFILE_NUM_SWORD_EFFECT].dwNumMat != 0)
	{
		D3DXMATERIAL*pMat = (D3DXMATERIAL*)m_aXfile[XFILE_NUM_SWORD_EFFECT].pBuffMat->GetBufferPointer();

		for (int nCnt = 0; nCnt < (int)m_aXfile[XFILE_NUM_SWORD_EFFECT].dwNumMat; nCnt++)
		{
			if (pMat[nCnt].pTextureFilename != NULL)
			{
				// テクスチャの生成
				D3DXCreateTextureFromFile(pDevice, XFILE_TEXTURE_NAME_EFFECT,
					&m_aXfile[XFILE_NUM_SWORD_EFFECT].apTexture[nCnt]);
			}
		}
	}

	//マテリアル情報の解析
	D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].pBuffMat->GetBufferPointer();
	
	for (int nCntMat = 0; nCntMat < (int)m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].dwNumMat; nCntMat++)
	{
		// ファイルネームの取得
		char cData[64] = {};

		sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, cData, &m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].apTexture[nCntMat]);
	}

	//マテリアル情報の解析
	materials = (D3DXMATERIAL*)m_aXfile[XFILE_NUM_GUARD_EFFECT].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aXfile[XFILE_NUM_GUARD_EFFECT].dwNumMat; nCntMat++)
	{
		// ファイルネームの取得
		char cData[64] = {};

		sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, cData, &m_aXfile[XFILE_NUM_GUARD_EFFECT].apTexture[nCntMat]);
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
			if (m_aXfile[nCount].apTexture[nCntTexture] != NULL)
			{
				m_aXfile[nCount].apTexture[nCntTexture]->Release();
				m_aXfile[nCount].apTexture[nCntTexture] = NULL;
			}
		}
	}
}

//=============================================================================
// モデルの情報
//=============================================================================
CXfile::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}

//=============================================================================
// モデルに使用するテクスチャ情報
//=============================================================================
LPDIRECT3DTEXTURE9 *CXfile::GetXfileTexture(XFILE_NUM TexNum)
{
	return m_aXfile[TexNum].apTexture;
}
