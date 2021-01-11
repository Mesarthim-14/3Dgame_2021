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
// �}�N����`
//=============================================================================
#define GRAVITY_POWAR			(0.6f)						// �d�͂̋���
#define GROUND_RIMIT			(0.0f)						// �n�ʂ̐���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacter::CCharacter(int nPriority) : CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = STATE_NONE;
	m_nLife = 0;	
	m_nAttack = 0;	
	m_nSpeed = 0;	
	m_nPart = 0;	
	m_fAngle = 0.0f;
	m_bJump = false;
	// ���f���p�ϐ�
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	memset(m_modelfile, 0, sizeof(m_modelfile));
	m_pFileName = NULL;
	memset(m_Motion, 0, sizeof(m_Motion));
	m_apKeyInfo = NULL;
	m_nMotionState = 0;				// ���[�V�����̏��
	m_nNumKey = 0;					// �L�[�̑���
	m_nCountMotion = 0;				// ���[�V�����J�E���^�[
	m_nMotionInterval = 0;			// ���[�V�����̃C���^�[�o��
	m_nStateCounter = 0;			// ��Ԃ̃J�E���^�[
	m_nKey = 0;						// ���݃L�[��No
	m_bMotionPlaing = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacter::~CCharacter()
{

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
	//�A�j���[�V�����̍X�V����
	UpdateMotion();

	// �d��
	if (Gravity() == true)
	{
		if (m_bLanding == false)
		{
			m_bLanding = true;
		}
	}

	m_pos += m_move;
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

void CCharacter::UpdateMotion(void)
{
	KEY *pKey[MAX_CHARACTER_PARTS];
	D3DXVECTOR3 diffPos, diffRot, startPos, startRot, setPos, setRot;

	//���݃L�[���ő�L�[�������̏ꍇ
	if (m_nKey < m_Motion[m_nMotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < m_nPart; nCntModel++)
		{
			m_apKeyInfo = &m_Motion[m_nMotionState].aKeyInfo[m_nKey];

			pKey[nCntModel] = &m_apKeyInfo->aKey[nCntModel];
		}

		for (int nCntModel = 0; nCntModel < m_nPart; nCntModel++)
		{
			if (m_apModelAnime[nCntModel] != NULL)
			{
				D3DXVECTOR3 startPos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 startRot = m_apModelAnime[nCntModel]->GetRotAnime();

				//1�t���[��������̍X�V�l = (�I�_�ʒu-�J�n�ʒu) / �t���[����
				diffPos.x = (pKey[nCntModel]->fPosX - startPos.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.y = (pKey[nCntModel]->fPosY - startPos.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.z = (pKey[nCntModel]->fPosZ - startPos.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

				//1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
				diffRot.x = (pKey[nCntModel]->fRotX - startRot.x) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.y = (pKey[nCntModel]->fRotY - startRot.y) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.z = (pKey[nCntModel]->fRotZ - startRot.z) / (float)m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame;

				setPos.x = diffPos.x * m_nCountMotion + startPos.x;
				setPos.y = diffPos.y * m_nCountMotion + startPos.y;
				setPos.z = diffPos.z * m_nCountMotion + startPos.z;

				setRot.x = diffRot.x * m_nCountMotion + startRot.x;
				setRot.y = diffRot.y * m_nCountMotion + startRot.y;
				setRot.z = diffRot.z * m_nCountMotion + startRot.z;

				D3DXVECTOR3 pos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 rot = m_apModelAnime[nCntModel]->GetRotAnime();

				//�ʒu�ɍX�V�p�̈ʒu�����Z
				pos += setPos;

				//�����ɍX�V�p�̌��������Z
				rot += setRot;

				//�ʒu�̐ݒ�
				m_apModelAnime[nCntModel]->SetPosAnime(setPos);

				//�����̐ݒ�
				m_apModelAnime[nCntModel]->SetRotAnime(setRot);
			}
		}

		//���[�V�����J�E���^�[�̉��Z
		m_nCountMotion++;

		//���݃L�[�̍Đ��t���[���ɒB������
		if (m_nCountMotion == m_Motion[m_nMotionState].aKeyInfo[m_nKey].nFrame)
		{
			//�L�[���P�i�߂�
			m_nKey++;
			m_nCountMotion = 0;
		}
	}
	else
	{
		//���[�v����Ȃ�
		if (m_Motion[m_nMotionState].bLoop == true)
		{
			m_nKey = 0;
		}
		else
		{
			m_nMotionInterval++;

			if (m_nMotionInterval == 10)
			{
				m_bMotionPlaing = false;

//				if (m_MotionState != MOTION_WIN && m_MotionState != MOTION_LOSE)
//				{
//					//���n�E�U���E���E�u�[�X�g�E�r�[�����[�V�����̎������͂�true�E�W�����v��false
//					if ((m_MotionState == MOTION_LANDING || m_MotionState == MOTION_ATTACK ||
//						m_MotionState == MOTION_LEFTBOOST || m_MotionState == MOTION_RIGHTBOOST ||
//						m_MotionState == MOTION_BEAM)
//						&& m_bJump == false)
//					{
//						SetMotion(MOTION_WALK);
//					}
//					else if (m_bJump == false)
//					{
//						SetMotion(MOTION_IDOL);
//					}
//				}
//				else
//				{
//					return;
//				}
			}
		}
	}

}

bool CCharacter::Gravity(void)
{
	// �d�͂�������
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// ����

	// ���n�̏���
	if (m_pos.y <= GROUND_RIMIT)
	{
		m_move.y = 0.0f;
		m_pos.y = GROUND_RIMIT;
		m_bJump = false;

		return true;
	}

	return false;
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

void CCharacter::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

void CCharacter::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

void CCharacter::SetState(STATE state)
{
	m_state = state;
}

void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

void CCharacter::SetLife(int nLife)
{
	m_nLife = nLife;
}

void CCharacter::SetCountMotion(int CountMotion)
{
	m_nCountMotion = CountMotion;
}

void CCharacter::SetMotionState(int nMotionState)
{
	m_nMotionState = nMotionState;
}

void CCharacter::SetMotion(int nMotion)
{
	// �l�̏�����
	m_nKey = 0;
	m_nCountMotion = 0;
	m_nMotionInterval = 0;
	D3DXVECTOR3 pos, rot;
	m_nMotionState = nMotion;
	m_bMotionPlaing = true;

	for (int nCntModel = 0; nCntModel < m_nPart; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//�J�n�ʒu
			pos.x = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			pos.y = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			pos.z = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;

			//�J�n����
			rot.x = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			rot.y = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			rot.z = m_Motion[m_nMotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			//�ʒu�̐ݒ�
			m_apModelAnime[nCntModel]->SetPosAnime(pos);

			//�����̐ݒ�
			m_apModelAnime[nCntModel]->SetRotAnime(rot);
		}
	}
}

void CCharacter::SetKey(int nKey)
{
	m_nKey = nKey;
}

void CCharacter::SetJump(bool bJump)
{
	m_bJump = bJump;
}

void CCharacter::SetLanding(bool bLanding)
{
	m_bLanding = bLanding;
}