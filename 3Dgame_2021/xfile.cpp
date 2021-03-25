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
#define XFILE_NAME_BG						("data/model/bg_dome001.x")					// �w�i
#define XFILE_NAME_SWORD_EFFECT				("data/model/Effect/Sword__Effect003.x")	// �w�i
#define XFILE_NAME_SWORD_LOCUS_EFFECT		("data/model/Effect/Locus_Effect.x")		// �O�Ղ̃G�t�F�N�g
#define XFILE_NAME_GUARD_EFFECT				("data/model/Effect/guard_Effect000.x")		// �K�[�h�̃G�t�F�N�g
#define XFILE_NAME_STONE_000				("data/model/Effect/stone000.x")			// ��000
#define XFILE_NAME_STONE_001				("data/model/Effect/stone001.x")			// ��001
#define XFILE_NAME_STONE_002				("data/model/Effect/stone002.x")			// ��002

// �K�w�\�����f���̃t�@�C��
#define HIERARCHY_FILENAME_PLAYER			("data/Text/motion_LBX.txt")				// �v���C���[�̃t�@�C���l�[��
#define HIERARCHY_FILENAME_KOBOLD			("data/Text/motion_Kobold.txt")				// �v���C���[�̃t�@�C���l�[��

// �e�N�X�`���l�[��
#define XFILE_TEXTURE_NAME_EFFECT			("data/Texture/sword_effect001.jpg")		// �G�t�F�N�g
#define XFILE_TEXTURE_SWORD_LOCUS_EFFECT	("data/model/Texture/Sword_Effect001.png")	// �O�Ղ̃e�N�X�`��
#define XFILE_TEXTURE_GUARD_EFFECT			("data/model/Texture/guard_Effect000.png")	// �O�Ղ̃e�N�X�`��


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXfile::CXfile()
{
	memset(m_aXfile, 0, sizeof(m_aXfile));
	memset(m_aModelFile, 0, sizeof(m_aModelFile));
	memset(m_pFileName, 0, sizeof(m_pFileName));
	memset(m_nMaxParts, 0, sizeof(m_nMaxParts));
//	memset(m_aHierarchyModel, 0, sizeof(m_aHierarchyModel));

	for (int nCount = 0; nCount < HIERARCHY_XFILE_NUM_MAX; nCount++)
	{
		// ����������
		m_apHierarchyModel[nCount].clear();
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXfile::~CXfile()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CXfile * CXfile::Create(void)
{
	// �������m��
	CXfile *pXfile = new CXfile;

	return pXfile;
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
		nullptr,
		&m_aXfile[XFILE_NUM_BG].pBuffMat,
		nullptr,
		&m_aXfile[XFILE_NUM_BG].dwNumMat,
		&m_aXfile[XFILE_NUM_BG].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_SWORD_EFFECT,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].pBuffMat,
		nullptr,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].dwNumMat,
		&m_aXfile[XFILE_NUM_SWORD_EFFECT].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_SWORD_LOCUS_EFFECT,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].pBuffMat,
		nullptr,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].dwNumMat,
		&m_aXfile[XFILE_NUM_SWORD_LOCUS_EFFECT].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_GUARD_EFFECT,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_aXfile[XFILE_NUM_GUARD_EFFECT].pBuffMat,
		nullptr,
		&m_aXfile[XFILE_NUM_GUARD_EFFECT].dwNumMat,
		&m_aXfile[XFILE_NUM_GUARD_EFFECT].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_STONE_000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_aXfile[XFILE_NUM_STONE_000].pBuffMat,
		nullptr,
		&m_aXfile[XFILE_NUM_STONE_000].dwNumMat,
		&m_aXfile[XFILE_NUM_STONE_000].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_STONE_001,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_aXfile[XFILE_NUM_STONE_001].pBuffMat,
		nullptr,
		&m_aXfile[XFILE_NUM_STONE_001].dwNumMat,
		&m_aXfile[XFILE_NUM_STONE_001].pMesh);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(XFILE_NAME_STONE_002,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		nullptr,
		&m_aXfile[XFILE_NUM_STONE_002].pBuffMat,
		nullptr,
		&m_aXfile[XFILE_NUM_STONE_002].dwNumMat,
		&m_aXfile[XFILE_NUM_STONE_002].pMesh);


	for (int nCount = 0; nCount < XFILE_NUM_MAX; nCount++)
	{
		//�}�e���A�����̉��
		D3DXMATERIAL *materials = (D3DXMATERIAL*)m_aXfile[nCount].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aXfile[nCount].dwNumMat; nCntMat++)
		{
			// �t�@�C���l�[���̎擾
			char cData[128] = {};

			sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

			// �e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice, cData, &m_aXfile[nCount].apTexture[nCntMat]);
		}
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
		if (m_aXfile[nCount].pMesh != nullptr)
		{
			m_aXfile[nCount].pMesh->Release();
			m_aXfile[nCount].pMesh = nullptr;
		}
		//�}�e���A���̔j��
		if (m_aXfile[nCount].pBuffMat != nullptr)
		{
			m_aXfile[nCount].pBuffMat->Release();
			m_aXfile[nCount].pBuffMat = nullptr;
		}

		// �e�N�X�`���̔j��
		for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
		{
			if (m_aXfile[nCount].apTexture[nCntTexture] != nullptr)
			{
				m_aXfile[nCount].apTexture[nCntTexture]->Release();
				m_aXfile[nCount].apTexture[nCntTexture] = nullptr;
			}
		}
	}
}

//=============================================================================
// �K�w�\���̃��f���t�@�C���ǂݍ���
//=============================================================================
HRESULT CXfile::HierarchyReadFile(void)
{
	FILE *pFile = nullptr;		//FILE�|�C���^

	// �t�@�C���̖��O��ݒ�
	SetHierarchyFileName();

	for (int nModelCnt = 0; nModelCnt < HIERARCHY_XFILE_NUM_MAX; nModelCnt++)
	{
		// �t�@�C���I�[�v��
		pFile = fopen(m_pFileName[nModelCnt], "r");

		char aHeadData[1024];
		char aModeName[1024];
		int nModelIndex = 0;	// ���f���̃C���f�b�N�X
		int nMotionType = 0;	// ���[�V�����̃^�C�v
		int nKeyNum = 0;		// �L�[�ԍ�
		int nMotionNum = 0;		// ���[�V�����ԍ�

		if (pFile != nullptr)
		{
			do
			{
				//���ǂݍ���Ń��[�h���𒊏o
				fgets(aHeadData, sizeof(aHeadData), pFile);
				sscanf(aHeadData, "%s", aModeName);

				if (strcmp(aModeName, "MODEL_FILENAME") == 0)
				{
					//X�t�@�C���̖��O
					sscanf(aHeadData, "%*s %*s %s %*s %*s", m_aModelFile[nModelIndex][nModelCnt].xFileName);

					//�C���f�b�N�X���P�i�߂�
					nModelIndex++;
				}

				if (strcmp(aModeName, "CHARACTERSET") == 0)
				{
					//�C���f�b�N�X���ŏ��ɖ߂�
					nModelIndex = 0;

					//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
					while (strcmp(aModeName, "END_CHARACTERSET") != 0)
					{
						//���ǂݍ���Ń��[�h���𒊏o
						fgets(aHeadData, sizeof(aHeadData), pFile);
						sscanf(aHeadData, "%s", aModeName);

						if (strcmp(aModeName, "PARTSSET") == 0)
						{
							//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
							while (strcmp(aModeName, "END_PARTSSET") != 0)
							{
								//���ǂݍ���Ń��[�h���𒊏o
								fgets(aHeadData, sizeof(aHeadData), pFile);
								sscanf(aHeadData, "%s", aModeName);

								if (strcmp(aModeName, "PARENT") == 0)
								{
									//�e�q���̐ݒ�
									sscanf(aHeadData, "%*s %*s %d", &m_aModelFile[nModelIndex][nModelCnt].nParent);
								}
								if (strcmp(aModeName, "POS") == 0)
								{
									//�ʒu�̐ݒ�
									sscanf(aHeadData, "%*s %*s %f %f %f", &m_aModelFile[nModelIndex][nModelCnt].offsetPos.x,
										&m_aModelFile[nModelIndex][nModelCnt].offsetPos.y, &m_aModelFile[nModelIndex][nModelCnt].offsetPos.z);
								}
								if (strcmp(aModeName, "ROT") == 0)
								{
									//�����̐ݒ�
									sscanf(aHeadData, "%*s %*s %f %f %f", &m_aModelFile[nModelIndex][nModelCnt].offsetRot.x,
										&m_aModelFile[nModelIndex][nModelCnt].offsetRot.y, &m_aModelFile[nModelIndex][nModelCnt].offsetRot.z);
								}
							}

							//�C���f�b�N�X���P�i�߂�
							nModelIndex++;

							// �p�[�c���𐔂���
							m_nMaxParts[nModelCnt]++;

						}
					}
				}

			} while (strcmp(aModeName, "END_SCRIPT") != 0);

			//�t�@�C���N���[�Y
			fclose(pFile);
		}
		else
		{
			//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
			MessageBox(nullptr, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

			return	E_FAIL;
		}
	}

	return S_OK;
}

//=============================================================================
// �K�w�\���̃��f�����[�h
//=============================================================================
HRESULT CXfile::HierarchyModelLoad(void)
{
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (int nCount = 0; nCount < m_nMaxParts[nXFileNumCnt]; nCount++)
		{
			MODEL Hierarchy = {nullptr, nullptr, 0, nullptr};

			//���f���̓ǂݍ���
			D3DXLoadMeshFromX(m_aModelFile[nCount][nXFileNumCnt].xFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				nullptr,
				&Hierarchy.pBuffMat,
				nullptr,
				&Hierarchy.dwNumMat,
				&Hierarchy.pMesh);

			//�}�e���A�����̉��
			D3DXMATERIAL *materials = (D3DXMATERIAL*)Hierarchy.pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)Hierarchy.dwNumMat; nCntMat++)
			{
				if (materials[nCntMat].pTextureFilename != nullptr)
				{
					// �t�@�C���l�[���̎擾
					char cData[256] = {};

					sprintf(cData, "data/model/Texture/%s", materials[nCntMat].pTextureFilename);

					// �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice, cData, &Hierarchy.apTexture[nCntMat]);
				}
			}

			// ���f�������擾
			m_apHierarchyModel[nXFileNumCnt].push_back(Hierarchy);
		}
	}

	return S_OK;
}

//=============================================================================
// �K�w�\���̃A�����f�����[�h
//=============================================================================
void CXfile::HierarchyModelUnLoad(void)
{
	for (int nXFileNumCnt = 0; nXFileNumCnt < HIERARCHY_XFILE_NUM_MAX; nXFileNumCnt++)
	{
		for (unsigned nCount = 0; nCount < m_apHierarchyModel[nXFileNumCnt].size(); nCount++)
		{
			//�}�e���A�����̔j��
			if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat != nullptr)
			{
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat->Release();
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pBuffMat = nullptr;
			}

			//���b�V�����̔j��
			if (m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh != nullptr)
			{
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh->Release();
				m_apHierarchyModel[nXFileNumCnt].at(nCount).pMesh = nullptr;
			}

			// �e�N�X�`���̊J��
			for (int nCntTexture = 0; nCntTexture < MAX_XFILE_TEXTURE; nCntTexture++)
			{
				if (m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture[nCntTexture] != nullptr)
				{
					m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture[nCntTexture]->Release();
					m_apHierarchyModel[nXFileNumCnt].at(nCount).apTexture[nCntTexture] = nullptr;
				}
			}
		}

		m_apHierarchyModel[nXFileNumCnt].clear();
	}
}

//=============================================================================
// �t�@�C���̖��O��ݒ�
//=============================================================================
void CXfile::SetHierarchyFileName(void)
{
	m_pFileName[HIERARCHY_XFILE_NUM_PLAYER] = HIERARCHY_FILENAME_PLAYER;
	m_pFileName[HIERARCHY_XFILE_NUM_KOBOLD] = HIERARCHY_FILENAME_KOBOLD;
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
	if (TexNum < XFILE_NUM_MAX)
	{
		if (m_aXfile[TexNum].apTexture != nullptr)
		{
			return m_aXfile[TexNum].apTexture;
		}
	}

	return nullptr;
}
