//=============================================================================
//
// X�t�@�C���̊Ǘ��N���X [xfile.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "xfile.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
// ���f���l�[��
#define XFILE_NAME_BG						("data/model/dome2.x")						// �w�i
#define XFILE_NAME_SWORD_EFFECT				("data/model/Effect/Sword__Effect003.x")	// �w�i
#define XFILE_NAME_SWORD_LOCUS_EFFECT		("data/model/Effect/Locus_Effect.x")		// �O�Ղ̃G�t�F�N�g
#define XFILE_NAME_GUARD_EFFECT				("data/model/Effect/guard_Effect000.x")		// �O�Ղ̃G�t�F�N�g

// �e�N�X�`���l�[��
#define XFILE_TEXTURE_NAME_EFFECT			("data/Texture/sword_effect001.jpg")		// �G�t�F�N�g
#define XFILE_TEXTURE_SWORD_LOCUS_EFFECT	("data/model/Texture/Sword_Effect001.png")	// �O�Ղ̃e�N�X�`��
#define XFILE_TEXTURE_GUARD_EFFECT			("data/model/Texture/guard_Effect000.png")	// �O�Ղ̃e�N�X�`��

//=============================================================================
// static������
//=============================================================================
CXfile::MODEL CXfile::m_aXfile[XFILE_NUM_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXfile::CXfile()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXfile::~CXfile()
{
}

//=============================================================================
// X�t�@�C�����[�h
//=============================================================================
HRESULT CXfile::ModelLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_BG,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_BG].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_BG].dwNumMat,
		&m_aXfile[XFILE_NUM_BG].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_SWORD_EFFECT,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].dwNumMat,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_SWORD_LOCUS_EFFECT,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].pBuffMat,
		NULL,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].dwNumMat,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].pMesh);

	// X�t�@�C���̓ǂݍ���
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
				// �e�N�X�`���̐���
				D3DXCreateTextureFromFile(pDevice, XFILE_TEXTURE_NAME_EFFECT,
					&m_aXfile[XFILE_NUM_SWORD_EFFECT].apTexture[nCnt]);
			}
		}
	}

	//�}�e���A�����̉��
	D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].pBuffMat->GetBufferPointer();
	
	for (int nCntMat = 0; nCntMat < (int)m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].dwNumMat; nCntMat++)
	{
		// �t�@�C���l�[���̎擾
		char cData[64] = {};

		sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, cData, &m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].apTexture[nCntMat]);
	}

	//�}�e���A�����̉��
	materials = (D3DXMATERIAL*)m_aXfile[XFILE_NUM_GUARD_EFFECT].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aXfile[XFILE_NUM_GUARD_EFFECT].dwNumMat; nCntMat++)
	{
		// �t�@�C���l�[���̎擾
		char cData[64] = {};

		sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, cData, &m_aXfile[XFILE_NUM_GUARD_EFFECT].apTexture[nCntMat]);
	}


	return S_OK;
}

//=============================================================================
// X�t�@�C���A�����[�h
//=============================================================================
void CXfile::ModelUnLoad(void)
{
	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//���b�V���̔j��
		if (m_aXfile[nCount].pMesh != NULL)
		{
			m_aXfile[nCount].pMesh->Release();
			m_aXfile[nCount].pMesh = NULL;
		}
		//�}�e���A���̔j��
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
// ���f���̏��
//=============================================================================
CXfile::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}

//=============================================================================
// ���f���Ɏg�p����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 *CXfile::GetXfileTexture(XFILE_NUM TexNum)
{
	return m_aXfile[TexNum].apTexture;
}
