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
#define STICK_SENSITIVITY		(50.0f)						// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED		(0.1f)						// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_PARTS			(21)						// �v���C���[�̃p�[�c��
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
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MotionState = MOTION_IDOL;
	m_bArmor = false;
	m_bWalk = false;
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
	// ����������
	CCharacter::SetCharacter(LBX_XFAILE_NAME, PLAYER_PARTS, MOTION_MAX);
	CCharacter::Init(pos, rot);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{	
	CCharacter::Uninit();

}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�X�V
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �e�N���X�̍X�V����
	CCharacter::Update();

	// ���W���
	D3DXVECTOR3 pos = GetPos();		// ���݂̍��W�擾
	SetPosOld(pos);					// �Â����W�ۑ�

	// �v���C���[�̏��
	UpdateState();

	// ���[�V�������
	UpdateMotionState();

	// �v���C���[�̐���
	PlayerControl();

	// �p�x�̎擾
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// �L�����N�^�[��]�̑��x
	rot += (m_rotDest - rot)*PLAYER_ROT_SPEED;

	// �p�x�̐ݒ�
	SetRot(rot);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}

//=============================================================================
// �v���C���[�̏��
//=============================================================================
void CPlayer::UpdateState(void)
{
	STATE state = GetState();

	switch (state)
	{
	case STATE_NORMAL:
		// �ʏ���

		break;

	case STATE_DAMAGE:

		//// �_���[�W���󂯂���
		//m_nStateCounter++;

		//// ���ȏ��
		//if (m_MotionState == MOTION_DAMAGE && m_bMotionPlaing == false)
		//{
		//	m_nStateCounter = 0;
		//	SetState(PLAYER_STATE_NORMAL);
		//	m_bArmor = true;
		//}
		break;
	default:
		break;
	}
}

//=============================================================================
// ���[�V�������
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotionState();

	int nKey = GetKey();

	switch (MotionState)
	{
	case MOTION_IDOL:
		//	m_MotionState = MOTION_ATTACK;
		break;
	case MOTION_ATTACK:
		// �U�����[�V����
		if (nKey >= 1 && nKey <= 3)
		{

		}
		break;
	case MOTION_DAMAGE:
		
		break;
	case MOTION_JUMP:
		// ���n���Ă���Ƃ�
		if (GetLanding() == true)
		{
				// �ʏ�ɖ߂�
				SetMotion(MOTION_IDOL);
		}
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
//	m_fAngle = CGame::GetCamera()->Get��();
	float fAngle = CGame::GetCamera()->Get��();
	D3DXVECTOR3 pos = GetPos();

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
			bool bJump = GetJump();
			//�W�����v���Ă��Ȃ��Ƃ�
			if (bJump == false && m_bWalk == false)
			{
				// ������Ԃɂ���
				m_bWalk = true;

				//���s���[�V�����̍Đ�
				SetMotion(MOTION_WALK);
			}

			//�X�e�B�b�NX�̓��͂����x�����Ă���
			if (js.lX < -STICK_SENSITIVITY)
			{
				m_rotDest.y = fAngle + D3DXToRadian(270.0f);

				pos.x += cosf(fAngle)* PLAYER_SPEED;
				pos.z -= sinf(fAngle)* PLAYER_SPEED;
			}
			else if (js.lX > STICK_SENSITIVITY)
			{
				m_rotDest.y = fAngle + D3DXToRadian(90.0f);

				pos.x -= cosf(fAngle)* PLAYER_SPEED;
				pos.z += sinf(fAngle)* PLAYER_SPEED;
			}
			else
			{
			}
			//�X�e�B�b�NY�̓��͂����x�𒴂��Ă���
			if (js.lY < -STICK_SENSITIVITY)
			{
				m_rotDest.y = fAngle;

				pos.x -= sinf(fAngle)* PLAYER_SPEED;
				pos.z -= cosf(fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(315.0f);
				}
				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(45.0f);
				}
			}

			else if (js.lY > STICK_SENSITIVITY)
			{
				m_rotDest.y = fAngle + D3DXToRadian(180.0f);
				pos.x += sinf(fAngle)* PLAYER_SPEED;
				pos.z += cosf(fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(225.0f);
				}

				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(135.0f);
				}
			}
		}
		// W�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_W))
		{
			m_rotDest.y = D3DXToDegree(fAngle);
			pos.z += cosf(0)*PLAYER_SPEED;
		}
		// S�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_S))
		{
			m_rotDest.y = sin(fAngle);
			pos.z += cosf(D3DX_PI)*PLAYER_SPEED;
		}
		// A�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_A))
		{
			pos.x += sinf(-D3DX_PI / 2)*PLAYER_SPEED;
		}
		// D�L�[���������Ƃ�
		if (pKeyboard->GetPress(DIK_D))
		{
			pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
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

	SetPos(pos);
}

//=============================================================================
// �W�����v����
//=============================================================================
void CPlayer::Jump(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	bool bJump = GetJump();
	// SPACE�L�[���������Ƃ��E�R���g���[����Y���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && bJump == false
			|| pKeyboard->GetTrigger(DIK_SPACE) && bJump == false)
	{
		D3DXVECTOR3 move = GetMove();
		move.y = PLAYER_JUMP;
		SetMove(move);
		SetJump(true);
		m_bWalk = false;

		//�W�����v���[�V�����̍Đ�
		SetMotion(MOTION_JUMP);
		SetLanding(false);
	}
}