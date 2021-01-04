//=============================================================================
//
// �L�����N�^�[�N���X [character.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(int nPriority) : CScene(nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{

}

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
CCharacter * CCharacter::Create(char * xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPart)
{
	// �������m��
	CCharacter *pCharacter = new CCharacter;

	pCharacter->m_pFileName = xfilename;
	pCharacter->m_nPart = nPart;
	pCharacter->Init(pos, rot);
	return pCharacter;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCharacter::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
//�t�@�C���ǂݍ���
if (FAILED(CCharacter::ReadFile()))
{
	return E_FAIL;
}

//���f���p�[�c�����J��Ԃ�
for (int nCntModel = 0; nCntModel < m_nPart; nCntModel++)
{
	if (m_apModelAnime[nCntModel] == NULL)
	{
		//���f���̐���
		m_apModelAnime[nCntModel] = CModelAnime::Create(m_modelfile[nCntModel].xFileName,
			m_modelfile[nCntModel].offsetPos, m_modelfile[nCntModel].offsetRot);
	}
	//�e�q�\���̐ݒ�
	if (m_apModelAnime[nCntModel] != NULL)
	{
		//�e���f���̏ꍇ
		if (nCntModel == 0)
		{
			m_apModelAnime[nCntModel]->SetParent(NULL);
		}
		//�q���f���̏ꍇ
		else
		{
			//�����̐e����ݒ肷��
			m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[m_modelfile[nCntModel].nParent]);
		}
	}
	}
	return E_NOTIMPL;
}

//=============================================================================
// �I������
//=============================================================================
void CCharacter::Uninit()
{
	for (int nCntModelNum = 0; nCntModelNum < m_nPart; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//�I������
			m_apModelAnime[nCntModelNum]->Uninit();

			//�������̍폜
			delete m_apModelAnime[nCntModelNum];

			//�������̃N���A
			m_apModelAnime[nCntModelNum] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	SetDeathFlag();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCharacter::Update()
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCharacter::Draw()
{
	// �`�揈��
	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// ���ʂ��i�����j���J�����O

	for (int nCntModelNum = 0; nCntModelNum < m_nPart; nCntModelNum++)
	{
		if (m_apModelAnime[nCntModelNum] != NULL)
		{
			//�K�w���f���N���X�̕`�揈��
			m_apModelAnime[nCntModelNum]->Draw();
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// ���ʂ��i�����j���J�����O
}

HRESULT CCharacter::ReadFile(void)
{
	FILE *pFile = NULL;		//FILE�|�C���^
	char aHeadData[1024];
	char aModeName[1024];
	int nModelIndex = 0;	// ���f���̃C���f�b�N�X
	int nMotionType = 0;	// ���[�V�����̃^�C�v
	int nKeyNum = 0;		// �L�[�ԍ�
	int nMotionNum = 0;		// ���[�V�����ԍ�

	// �t�@�C���I�[�v��
	pFile = fopen(m_pFileName, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aModeName);

			if (strcmp(aModeName, "MODEL_FILENAME") == 0)
			{
				//X�t�@�C���̖��O
				sscanf(aHeadData, "%*s %*s %s %*s %*s", m_modelfile[nModelIndex].xFileName);

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
								sscanf(aHeadData, "%*s %*s %d", &m_modelfile[nModelIndex].nParent);
							}
							if (strcmp(aModeName, "POS") == 0)
							{
								//�ʒu�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", &m_modelfile[nModelIndex].offsetPos.x,
									&m_modelfile[nModelIndex].offsetPos.y, &m_modelfile[nModelIndex].offsetPos.z);
							}
							if (strcmp(aModeName, "ROT") == 0)
							{
								//�����̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", &m_modelfile[nModelIndex].offsetRot.x,
									&m_modelfile[nModelIndex].offsetRot.y, &m_modelfile[nModelIndex].offsetRot.z);
							}
						}
						//�C���f�b�N�X���P�i�߂�
						nModelIndex++;
					}
				}
			}

			//���[�V�����Z�b�g
			if (strcmp(aModeName, "MOTIONSET") == 0)
			{
				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aModeName, "END_MOTIONSET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aModeName);

					//���[�v���̎擾
					if (strcmp(aModeName, "LOOP") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].bLoop);
					}

					//�L�[���̎擾
					if (strcmp(aModeName, "NUM_KEY") == 0)
					{
						sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].nNumKey);
					}

					if (strcmp(aModeName, "KEYSET") == 0)
					{
						//END_KEYSET�ɂȂ�܂ŌJ��Ԃ�
						while (strcmp(aModeName, "END_KEYSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aModeName);

							//�t���[�����̎擾
							if (strcmp(aModeName, "FRAME") == 0)
							{
								sscanf(aHeadData, "%*s %*s %d", &m_Motion[nMotionType].aKeyInfo[nMotionNum].nFrame);
							}

							//�e�L�[�̃I�t�Z�b�g���̎擾
							if (strcmp(aModeName, "KEY") == 0)
							{
								//END_KEY�ɂȂ�܂ŌJ��Ԃ�
								while (strcmp(aModeName, "END_KEY") != 0)
								{
									//���ǂݍ���Ń��[�h���𒊏o
									fgets(aHeadData, sizeof(aHeadData), pFile);
									sscanf(aHeadData, "%s", aModeName);

									//�ʒu�̎擾
									if (strcmp(aModeName, "POS") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosZ);
									}

									//�����̎擾
									if (strcmp(aModeName, "ROT") == 0)
									{
										sscanf(aHeadData, "%*s %*s %f %f %f",
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotX,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotY,
											&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotZ);
									}
								}
								//�ǂݏI�������J�E���g��1�i�߂�
								nKeyNum++;
							}
						}
						nKeyNum = 0;
						nMotionNum++;
					}
				}
				nMotionNum = 0;
				nMotionType++;
			}
		} while (strcmp(aModeName, "END_SCRIPT") != 0);

		//�t�@�C���N���[�Y
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}

void CCharacter::SetCharacter(char * xfilename, int nPart, int nMotion)
{
	m_pFileName = xfilename;
	m_nPart = nPart;
}