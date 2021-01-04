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
#define XFILE_NAME_BG		("data/model/dome2.x")		// �w�i

//=============================================================================
// static������
//=============================================================================
CModel::MODEL CXfile::m_aXfile[MAX_XFILE] = {};

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

	//�}�e���A�����̉��
	D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[XFILE_NUM_BG].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aXfile[XFILE_NUM_BG].pBuffMat; nCntMat++)
	{
		//�t�@�C���l�[���̎擾
	//	char *aXfileName = materials[nCntMat].pTextureFilename;

			//�e�N�X�`���̓ǂݍ���
	//		D3DXCreateTextureFromFile(pDevice, aXfileName, &m_aXfile[XFILE_NUM_BG].m_apTexture[nCntMat]);
		
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
			if (m_aXfile[nCount].m_apTexture[nCntTexture] != NULL)
			{
				m_aXfile[nCount].m_apTexture[nCntTexture]->Release();
				m_aXfile[nCount].m_apTexture[nCntTexture] = NULL;
			}
		}
	}
}

//=============================================================================
// ���f���̏��
//=============================================================================
CModel::MODEL CXfile::GetXfile(XFILE_NUM Tex_Num)
{
	return m_aXfile[Tex_Num];
}