//=============================================================================
//
// �v���C���[�N���X [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "player.h"
#include <stdio.h>
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED			(20.0f)						// �v���C���[�̈ړ���
#define PLAYER_JUMP				(21.0f)						// �W�����v�̏���
#define GRAVITY_POWAR			(0.6f)						// �d�͂̋���
#define GROUND_RIMIT			(0.0f)						// �n�ʂ̐���
#define STICK_SENSITIVITY		(50.0f)						// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED		(0.1f)						// �L�����N�^�[�̉�]���鑬�x
#define LBX_XFAILE_NAME "data/Text/motion_LBX.txt"			// LBX�̃t�@�C���p�X
#define GANDAMU_XFAILE_NAME "data/Text/motion_gandamu.txt"	// �K���_���̃t�@�C���p�X

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
MODELFILLE g_modelfile[MAX_MODEL_PARTS];	//���f���p�[�c���

//=============================================================================
// static������
//=============================================================================

//=============================================================================
// �N���G�C�g
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CPlayer *pPlayer = new CPlayer;

	// ����������
	pPlayer->Init(pos, size);

	return pPlayer;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = PLAYER_STATE_NONE;
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	m_apKeyInfo = NULL;
	memset(&m_Motion, 0, sizeof(m_Motion));
	m_MotionState = MOTION_IDOL;
	m_nNumKey = 0;									//�L�[�̑���
	m_nKey = 0;										//���݃L�[��No
	m_nCountMotion = 0;								//���[�V�����J�E���^�[
	m_nMotionInterval = 0;							//���[�V�����̃C���^�[�o��
	m_bMotionPlaing = false;
	m_bJump = false;
	m_bArmor = false;
	m_nStateCounter = 0;
	m_bWalk = false;
	m_fAngle = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	//m_apKeyInfo = NULL;
	//memset(&m_Motion, 0, sizeof(m_Motion));
	//m_MotionState = MOTION_IDOL;
	//m_fAngle = 0.0f;

	////�ʒu�̐ݒ�
	//m_pos = pos;

	////�t�@�C���ǂݍ���
	//if (FAILED(ReadFile()))
	//{
	//	return E_FAIL;
	//}

	////���f���p�[�c�����J��Ԃ�
	//for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
	//{
	//	if (m_apModelAnime[nCntModel] == NULL)
	//	{
	//		//���f���̐���
	//		m_apModelAnime[nCntModel] = CModelAnime::Create(g_modelfile[nCntModel].xFileName,
	//			g_modelfile[nCntModel].offsetPos, g_modelfile[nCntModel].offsetRot);
	//	}
	//	//�e�q�\���̐ݒ�
	//	if (m_apModelAnime[nCntModel] != NULL)
	//	{
	//		//�e���f���̏ꍇ
	//		if (nCntModel == 0)
	//		{
	//			m_apModelAnime[nCntModel]->SetParent(NULL);
	//		}
	//		//�q���f���̏ꍇ
	//		else
	//		{
	//			//�����̐e����ݒ肷��
	//			m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[g_modelfile[nCntModel].nParent]);
	//		}
	//	}
	//}

	////�ҋ@���[�V�����̍Đ�
	//SetMotion(MOTION_IDOL);

	////�I�u�W�F�N�g�^�C�v�̐ݒ�
	//SetObjType(CScene::OBJTYPE_PLAYER);

	CCharacter::SetCharacter(LBX_XFAILE_NAME, MAX_PARTS, MOTION_MAX);
	CCharacter::Init(pos, rot);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//for (int nCntModelNum = 0; nCntModelNum < MAX_MODEL_PARTS; nCntModelNum++)
	//{
	//	if (m_apModelAnime[nCntModelNum] != NULL)
	//	{
	//		//�I������
	//		m_apModelAnime[nCntModelNum]->Uninit();

	//		//�������̍폜
	//		delete m_apModelAnime[nCntModelNum];

	//		//�������̃N���A
	//		m_apModelAnime[nCntModelNum] = NULL;
	//	}
	//}

	////�I�u�W�F�N�g�̔j��
	//SetDeathFlag();

	
	CCharacter::Uninit();

}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	CCharacter::Update();

	// �Â����W�擾
	m_OldPos = m_pos;

	// �v���C���[�̏��
	PlayerState();

	// �d�͂�������
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// ����

	// �n�ʂ̐���
	GroundLimit();

	// ���[�V�������
	MotionState();

	//�A�j���[�V�����̍X�V����
	UpdateMotion();

	// �v���C���[�̐���
	PlayerControl();

	//�ʒu�ֈړ��ʂ����Z
	m_pos += m_move;

	while (m_rotDest.y - m_rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - m_rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// �L�����N�^�[��]�̑��x
	m_rot += (m_rotDest - m_rot)*PLAYER_ROT_SPEED;
}

//=============================================================================
// �A�j���[�V�����̍X�V����
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	KEY *pKey[MAX_MODEL_PARTS];
	D3DXVECTOR3 diffPos, diffRot, startPos, startRot, setPos, setRot;

	//���݃L�[���ő�L�[�������̏ꍇ
	if (m_nKey < m_Motion[m_MotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
		{
			m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[m_nKey];

			pKey[nCntModel] = &m_apKeyInfo->aKey[nCntModel];
		}

		for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
		{
			if (m_apModelAnime[nCntModel] != NULL)
			{
				D3DXVECTOR3 startPos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 startRot = m_apModelAnime[nCntModel]->GetRotAnime();

				//1�t���[��������̍X�V�l = (�I�_�ʒu-�J�n�ʒu) / �t���[����
				diffPos.x = (pKey[nCntModel]->fPosX - startPos.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.y = (pKey[nCntModel]->fPosY - startPos.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.z = (pKey[nCntModel]->fPosZ - startPos.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

				//1�t���[��������̍X�V�l = (�I�_����-�J�n����) / �t���[����
				diffRot.x = (pKey[nCntModel]->fRotX - startRot.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.y = (pKey[nCntModel]->fRotY - startRot.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.z = (pKey[nCntModel]->fRotZ - startRot.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

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
		if (m_nCountMotion == m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame)
		{
			//�L�[���P�i�߂�
			m_nKey++;
			m_nCountMotion = 0;
		}
	}
	else
	{
		//���[�v����Ȃ�
		if (m_Motion[m_MotionState].bLoop == true)
		{
			m_nKey = 0;
		}
		else
		{
			m_nMotionInterval++;

			if (m_nMotionInterval == 10)
			{
				m_bMotionPlaing = false;

				if (m_MotionState != MOTION_WIN && m_MotionState != MOTION_LOSE)
				{
					//���n�E�U���E���E�u�[�X�g�E�r�[�����[�V�����̎������͂�true�E�W�����v��false
					if ((m_MotionState == MOTION_LANDING || m_MotionState == MOTION_ATTACK ||
						m_MotionState == MOTION_LEFTBOOST || m_MotionState == MOTION_RIGHTBOOST ||
						m_MotionState == MOTION_BEAM)
						&& m_bJump == false)
					{
						SetMotion(MOTION_WALK);
					}
					else if (m_bJump == false)
					{
						SetMotion(MOTION_IDOL);
					}
				}
				else
				{
					return;
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	//// �`�揈��
	////�f�o�C�X���̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	////���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&m_mtxWorld);

	////�����𔽉f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	////�ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	////���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// ���ʂ��i�����j���J�����O

	//for (int nCntModelNum = 0; nCntModelNum < MAX_MODEL_PARTS; nCntModelNum++)
	//{
	//	if (m_apModelAnime[nCntModelNum] != NULL)
	//	{
	//		//�K�w���f���N���X�̕`�揈��
	//		m_apModelAnime[nCntModelNum]->Draw();
	//	}
	//}

	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// ���ʂ��i�����j���J�����O
	CCharacter::Draw();

}

//=============================================================================
// ���[�V�����Z�b�g����
//=============================================================================
void CPlayer::SetMotion(MOTION_STATE motion)
{
	if (motion != MOTION_WIN && motion != MOTION_LOSE)
	{
		if (m_Motion[m_MotionState].bLoop == false &&
			m_bMotionPlaing == true && m_MotionState != MOTION_LANDING)
		{
			return;
		}
	}

	// �l�̏�����
	m_nKey = 0;
	m_nCountMotion = 0;
	m_nMotionInterval = 0;
	D3DXVECTOR3 pos, rot;
	m_MotionState = motion;
	m_bMotionPlaing = true;

	for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//�J�n�ʒu
			pos.x = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			pos.y = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			pos.z = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;

			//�J�n����
			rot.x = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			rot.y = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			rot.z = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			//�ʒu�̐ݒ�
			m_apModelAnime[nCntModel]->SetPosAnime(pos);

			//�����̐ݒ�
			m_apModelAnime[nCntModel]->SetRotAnime(rot);
		}
	}

	switch (m_MotionState)
	{
	case MOTION_IDOL:
		break;

	case MOTION_DAMAGE:

		// ���G�t���O
		m_bArmor = true;
		break;
	default:
		break;
	}
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer::PlayerState(void)
{
	CSound *pSound = CManager::GetSound();

	switch (m_state)
	{
	case PLAYER_STATE_NORMAL:
		// �ʏ���

		break;

	case PLAYER_STATE_DAMAGE:

		// �_���[�W���󂯂���
		m_nStateCounter++;

		// ���ȏ��
		if (m_MotionState == MOTION_DAMAGE && m_bMotionPlaing == false)
		{
			m_nStateCounter = 0;
			m_state = PLAYER_STATE_NORMAL;
			m_bArmor = true;
		}
		break;
	default:
		break;
	}
}

//=============================================================================
// ���[�V�������
//=============================================================================
void CPlayer::MotionState(void)
{
	switch (m_MotionState)
	{
	case MOTION_IDOL:
		//	m_MotionState = MOTION_ATTACK;
		break;
	case MOTION_ATTACK:
		// �U�����[�V����
		if (m_nKey >= 1 && m_nKey <= 3)
		{

		}
		break;
	case MOTION_DAMAGE:
		
		break;
	}
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	if (m_MotionState != MOTION_DAMAGE)
	{
		// �v���C���[�̈ړ�����
		Walk();

		// �W�����v�̏���
		Jump();
	}
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// �L�[�{�[�h�X�V
	DIJOYSTATE js = CInputJoypad::GetStick(0);				// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetSound();					// �T�E���h�̏��

	//�J�����p�x�擾
	m_fAngle = CGame::GetCamera()->Get��();

	if (pKeyboard->GetTrigger(DIK_I) ||
		CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, 0))
	{
		//�U�����[�V�������Đ�
		SetMotion(MOTION_ATTACK);
		pSound->Play(CSound::SOUND_LABEL_SE_SLASH);
	}
	//���͂����݂���
	if ((js.lX != 0.0f || js.lY != 0.0f ))
	{
		//�_���[�W���󂯂Ă��Ȃ��Ƃ��݈̂ړ�����
		if (m_MotionState != MOTION_DAMAGE)
		{
			//�W�����v���Ă��Ȃ��Ƃ�
			if (m_bJump == false && m_bWalk == false)
			{
				// ������Ԃɂ���
				m_bWalk = true;

				//���s���[�V�����̍Đ�
				SetMotion(MOTION_WALK);
			}

			//�X�e�B�b�NX�̓��͂����x�����Ă���
			if (js.lX < -STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(270.0f);

				m_pos.x += cosf(m_fAngle)* PLAYER_SPEED;
				m_pos.z -= sinf(m_fAngle)* PLAYER_SPEED;
			}
			else if (js.lX > STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(90.0f);

				m_pos.x -= cosf(m_fAngle)* PLAYER_SPEED;
				m_pos.z += sinf(m_fAngle)* PLAYER_SPEED;
			}
			else
			{
			}
			//�X�e�B�b�NY�̓��͂����x�𒴂��Ă���
			if (js.lY < -STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle;

				m_pos.x -= sinf(m_fAngle)* PLAYER_SPEED;
				m_pos.z -= cosf(m_fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(315.0f);
				}
				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(45.0f);
				}
			}

			else if (js.lY > STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(180.0f);
				m_pos.x += sinf(m_fAngle)* PLAYER_SPEED;
				m_pos.z += cosf(m_fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(225.0f);
				}

				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(135.0f);
				}
			}
		}
		// W�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_W))
		{
			m_rotDest.y = D3DXToDegree(m_fAngle);
			m_pos.z += cosf(0)*PLAYER_SPEED;
		}
		// S�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_S))
		{
			m_rotDest.y = sin(m_fAngle);
			m_pos.z += cosf(D3DX_PI)*PLAYER_SPEED;
		}
		// A�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_A))
		{
			m_pos.x += sinf(-D3DX_PI / 2)*PLAYER_SPEED;
		}
		// D�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_D))
		{
			m_pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
		}
	}
	else
	{
		if (m_bWalk == true)
		{
			//�ҋ@���[�V�������Đ�
			SetMotion(MOTION_IDOL);
			m_bWalk = false;
		}
	}
}

//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::Jump(void)
{
	// �T�E���h���
	CSound *pSound = CManager::GetSound();

	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && m_bJump == false	
			|| pKeyboard->GetTrigger(DIK_SPACE) && m_bJump == false)
	{
		// �W�����v�̏���
		m_move.y = 0.0f;
		m_move.y = PLAYER_JUMP;
		m_bJump = true;
		m_bWalk = false;

		//�W�����v���[�V�����̍Đ�
		SetMotion(MOTION_JUMP);
		pSound->Play(CSound::SOUND_LABEL_SE_JUMP);
	}
}

//=============================================================================
// �n�ʂ̐���
//=============================================================================
void CPlayer::GroundLimit(void)
{
	// �T�E���h���
	CSound *pSound = CManager::GetSound();

	// ���n�̏���
	if (m_pos.y <= GROUND_RIMIT)
	{
		if (m_bJump == true)
		{
			SetMotion(MOTION_LANDING);
		}

		// �l���
		m_move.y = 0.0f;
		m_pos.y = GROUND_RIMIT;
		m_bJump = false;
	}
}

//=============================================================================
// �t�@�C���ǂݍ��ݏ���
//=============================================================================
//HRESULT CPlayer::ReadFile(void)
//{
//	//FILE *pFile = NULL;		//FILE�|�C���^
//	//char aHeadData[1024];
//	//char aModeName[1024];
//	//int nModelIndex = 0;	//���f���̃C���f�b�N�X
//	//int nMotionType = 0;	//���[�V�����̃^�C�v
//	//int nKeyNum = 0;		//�L�[�ԍ�
//	//int nMotionNum = 0;		//���[�V�����ԍ�
//
//	//	//�t�@�C���I�[�v��
//	//	pFile = fopen(LBX_XFAILE_NAME, "r");
//
//	//if (pFile != NULL)
//	//{
//	//	do
//	//	{
//	//		//���ǂݍ���Ń��[�h���𒊏o
//	//		fgets(aHeadData, sizeof(aHeadData), pFile);
//	//		sscanf(aHeadData, "%s", aModeName);
//
//	//		if (strcmp(aModeName, "MODEL_FILENAME") == 0)
//	//		{
//	//			//X�t�@�C���̖��O
//	//			sscanf(aHeadData, "%*s %*s %s %*s %*s", g_modelfile[nModelIndex].xFileName);
//
//	//			//�C���f�b�N�X���P�i�߂�
//	//			nModelIndex++;
//	//		}
//
//	//		if (strcmp(aModeName, "CHARACTERSET") == 0)
//	//		{
//	//			//�C���f�b�N�X���ŏ��ɖ߂�
//	//			nModelIndex = 0;
//
//	//			//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
//	//			while (strcmp(aModeName, "END_CHARACTERSET") != 0)
//	//			{
//	//				//���ǂݍ���Ń��[�h���𒊏o
//	//				fgets(aHeadData, sizeof(aHeadData), pFile);
//	//				sscanf(aHeadData, "%s", aModeName);
//
//	//				if (strcmp(aModeName, "PARTSSET") == 0)
//	//				{
//	//					//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
//	//					while (strcmp(aModeName, "END_PARTSSET") != 0)
//	//					{
//	//						//���ǂݍ���Ń��[�h���𒊏o
//	//						fgets(aHeadData, sizeof(aHeadData), pFile);
//	//						sscanf(aHeadData, "%s", aModeName);
//
//	//						if (strcmp(aModeName, "PARENT") == 0)
//	//						{
//	//							//�e�q���̐ݒ�
//	//							sscanf(aHeadData, "%*s %*s %d", &g_modelfile[nModelIndex].nParent);
//	//						}
//	//						if (strcmp(aModeName, "POS") == 0)
//	//						{
//	//							//�ʒu�̐ݒ�
//	//							sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetPos.x,
//	//								&g_modelfile[nModelIndex].offsetPos.y, &g_modelfile[nModelIndex].offsetPos.z);
//	//						}
//	//						if (strcmp(aModeName, "ROT") == 0)
//	//						{
//	//							//�����̐ݒ�
//	//							sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetRot.x,
//	//								&g_modelfile[nModelIndex].offsetRot.y, &g_modelfile[nModelIndex].offsetRot.z);
//	//						}
//	//					}
//	//					//�C���f�b�N�X���P�i�߂�
//	//					nModelIndex++;
//	//				}
//	//			}
//	//		}
//
//	//		//���[�V�����Z�b�g
//	//		if (strcmp(aModeName, "MOTIONSET") == 0)
//	//		{
//	//			//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
//	//			while (strcmp(aModeName, "END_MOTIONSET") != 0)
//	//			{
//	//				//���ǂݍ���Ń��[�h���𒊏o
//	//				fgets(aHeadData, sizeof(aHeadData), pFile);
//	//				sscanf(aHeadData, "%s", aModeName);
//
//	//				//���[�v���̎擾
//	//				if (strcmp(aModeName, "LOOP") == 0)
//	//				{
//	//					sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].bLoop);
//	//				}
//
//	//				//�L�[���̎擾
//	//				if (strcmp(aModeName, "NUM_KEY") == 0)
//	//				{
//	//					sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].nNumKey);
//	//				}
//
//	//				if (strcmp(aModeName, "KEYSET") == 0)
//	//				{
//	//					//END_KEYSET�ɂȂ�܂ŌJ��Ԃ�
//	//					while (strcmp(aModeName, "END_KEYSET") != 0)
//	//					{
//	//						//���ǂݍ���Ń��[�h���𒊏o
//	//						fgets(aHeadData, sizeof(aHeadData), pFile);
//	//						sscanf(aHeadData, "%s", aModeName);
//
//	//						//�t���[�����̎擾
//	//						if (strcmp(aModeName, "FRAME") == 0)
//	//						{
//	//							sscanf(aHeadData, "%*s %*s %d", &m_Motion[nMotionType].aKeyInfo[nMotionNum].nFrame);
//	//						}
//
//	//						//�e�L�[�̃I�t�Z�b�g���̎擾
//	//						if (strcmp(aModeName, "KEY") == 0)
//	//						{
//	//							//END_KEY�ɂȂ�܂ŌJ��Ԃ�
//	//							while (strcmp(aModeName, "END_KEY") != 0)
//	//							{
//	//								//���ǂݍ���Ń��[�h���𒊏o
//	//								fgets(aHeadData, sizeof(aHeadData), pFile);
//	//								sscanf(aHeadData, "%s", aModeName);
//
//	//								//�ʒu�̎擾
//	//								if (strcmp(aModeName, "POS") == 0)
//	//								{
//	//									sscanf(aHeadData, "%*s %*s %f %f %f",
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosX,
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosY,
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosZ);
//	//								}
//
//	//								//�����̎擾
//	//								if (strcmp(aModeName, "ROT") == 0)
//	//								{
//	//									sscanf(aHeadData, "%*s %*s %f %f %f",
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotX,
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotY,
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotZ);
//	//								}
//	//							}
//	//							//�ǂݏI�������J�E���g��1�i�߂�
//	//							nKeyNum++;
//	//						}
//	//					}
//	//					nKeyNum = 0;
//	//					nMotionNum++;
//	//				}
//	//			}
//	//			nMotionNum = 0;
//	//			nMotionType++;
//	//		}
//	//	} while (strcmp(aModeName, "END_SCRIPT") != 0);
//
//	//	//�t�@�C���N���[�Y
//	//	fclose(pFile);
//
//	//	return S_OK;
//	//}
//	//else
//	//{
//	//	//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
//	//	MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);
//
//	//	return	E_FAIL;
//	//}
//}

//=============================================================================
// �|�W�V�����̐ݒ�
//=============================================================================
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
void CPlayer::SetState(PLAYER_STATE state)
{
	m_state = state;
}

//=============================================================================
// ���W�̏��
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �Â����W���
//=============================================================================
D3DXVECTOR3 CPlayer::GetOldPos(void)
{
	return m_OldPos;
}

//=============================================================================
// �ړ��ʂ̐ݒ�
//=============================================================================
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// �ړ��ʂ̏��
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//=============================================================================
// ��]�ʂ̏��
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �v���C���[��Ԃ̏��
//=============================================================================
CPlayer::PLAYER_STATE CPlayer::GetState(void)
{
	return m_state;
}

//=============================================================================
// �W�����v�t���O�̏��
//=============================================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}