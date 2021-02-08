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
#include "life_bar.h"
#include "life_frame.h"
#include "collision.h"
#include "fade.h"
#include "sp_bar.h"
#include "ui_skill.h"
#include "light_effect.h"
#include "locus.h"
#include "particle.h"
#include "particle_factory.h"
#include "slashing_effect.h"
#include "guard_effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SPEED				(20.0f)						// �v���C���[�̈ړ���
#define PLAYER_AVOID_SPEED			(30.0f)						// �v���C���[�̉���
#define PLAYER_JUMP					(21.0f)						// �W�����v�̏���
#define STICK_SENSITIVITY			(50.0f)						// �X�e�B�b�N���x
#define PLAYER_ROT_SPEED			(0.1f)						// �L�����N�^�[�̉�]���鑬�x
#define PLAYER_RADIUS				(150.0f)					// ���a�̑傫��
#define PLAYER_PARTS				(22)						// �v���C���[�̃p�[�c��
#define PLAYER_ARMOR_TIME			(50)						// ���G����
#define GAME_END_FLAME				(100)						// �Q�[�����I���t���[��
#define MAX_SP_NUM					(300)						// SP�̍ő吔
#define SKILL_SP_NUM				(100)						// �X�L���̏���Q�[�W
#define BLADE_PARTICLE_INTER		(170)						// ���g�̃p�[�e�B�N���̊Ԋu
#define WEAPON_TIP_NUM				(20)						// ����̃p�[�c�ԍ�
#define WEAPON_ROOT_NUM				(21)						// ���̍����̃p�[�c�ԍ�
#define PLAYER_AVOID_FLAME			(20)						// �������

#define LBX_XFAILE_NAME		"data/Text/motion_LBX.txt"		// LBX�̃t�@�C���p�X
#define GANDAMU_XFAILE_NAME "data/Text/motion_gandamu.txt"	// �K���_���̃t�@�C���p�X

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
MODELFILE g_modelfile[PLAYER_PARTS];	//���f���p�[�c���

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
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bWalk = false;
	m_bDraw = true;
	m_nEndCounter = 0;
	m_pSpBar = NULL;
	m_pUiSkill = NULL;
	m_bUseLocusEffect = false;
	m_bAvoid = false;
	m_bArmor = false;
	m_nAvoidCounter = 0;
	m_pGuardEffect = NULL;
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
	CCharacter::SetCharaModel(LBX_XFAILE_NAME, PLAYER_PARTS, MOTION_MAX);			// ���f���p�[�c
	CCharacter::Init(pos, rot);														// ���W�@�p�x
	SetRadius(PLAYER_RADIUS);														// ���a�̐ݒ�
	SetCType(CHARACTER_TYPE_PLAYER);												// �L�����N�^�[�̃^�C�v
	SetSpeed(PLAYER_SPEED);															// ���x�̐ݒ�
	SetWeaponTipNum(PARTS_NUM_COLLISION);											// ����̃p�[�c�ԍ�
	SetWeaponRootNum(PARTS_NUM_ROOT);												// ���̍��{�̃p�[�c�ԍ�
	LifeBarCreate(PLAYER_LIFE_FRAME_POS, PLAYER_LIFE_FRAME_SIZE,
		PLAYER_LIFE_BAR_POS, PLAYER_LIFE_BAR_SIZE,
		PLAYER_LIFE_BAR_COLOR, PLAYER_LIFE_NUM);									// ���C�t�o�[�̐���

	// SP�o�[�̐���
	if (m_pSpBar == NULL)
	{
		m_pSpBar = CSpBar::Create(PLAYER_SP_BAR_POS, PLAYER_SP_BAR_SIZE, MAX_SP_NUM);
	}

	// �X�L����UI
	if (m_pUiSkill == NULL)
	{
		m_pUiSkill = CUiSkill::Create(UI_SKILL_POS, UI_SKILL_SIZE);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{	
	// �I������
	CCharacter::Uninit();

	if (m_pSpBar != NULL)
	{
		// �I������
		m_pSpBar->Uninit();
		m_pSpBar = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	if (m_bDraw == true)
	{
		// �L�[�{�[�h�X�V
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();

		// �e�N���X�̍X�V����
		CCharacter::Update();

		// ���W���
		D3DXVECTOR3 pos = GetPos();	// ���݂̍��W�擾
		SetPosOld(pos);				// �Â����W�ۑ�

		// ���̋O��
		//SwordLocus();

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

		// �̗͂�0�ɂȂ�����
		if (GetLife() <= 0)
		{
			// ���񂾂Ƃ�
			Death();
		}
	}
	else
	{
		m_nEndCounter++;

		// �Q�[���I���̃t���[��
		if (m_nEndCounter >= GAME_END_FLAME)
		{
			// ���U���g��ʂ�
			CManager::GetFade()->SetFade(CManager::MODE_TYPE_RESULT);
			m_nEndCounter = 0;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	if (m_bDraw == true)
	{
		// �`�揈��
		CCharacter::Draw();
	}
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
	{
		// ��ԃJ�E���^�[�擾
		int nStateCounter = GetStateCounter();

		// ��莞�Ԍo�߂�����
		if (nStateCounter >= PLAYER_ARMOR_TIME)
		{
			SetState(STATE_NORMAL);		// �ʏ��Ԃɖ߂�
			SetArmor(false);			// ���G��ԉ���
			SetStateCounter(0);			// ��ԃJ�E���^�[���Z�b�g
		}
	}

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
		//	state = MOTION_ATTACK;
		break;
	case MOTION_ATTACK:
		
		// ���̃G�t�F�N�g
		SwordLight();

		// �U�����[�V����
		if (nKey == 3)
		{
			if (m_bUseLocusEffect == false)
			{
				// ����̌��ݍ��W
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// �O�Ղ̃G�t�F�N�g����
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}


			// �U�����̓����蔻��
			if (AttackCollision() == true)
			{

			}
		}
		break;
		
		break;
	case MOTION_JUMP:
		// ���n���Ă���Ƃ�
		if (GetLanding() == true)
		{
			// �ʏ�ɖ߂�
			SetMotion(MOTION_IDOL);
		}
		break;

	case MOTION_GUARD:
		break;
	}
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
void CPlayer::PlayerControl()
{
	MOTION_STATE state = (MOTION_STATE)GetState();

	// �����Ԃ���Ȃ��Ƃ�
	if (state != MOTION_DAMAGE)
	{
		// �v���C���[�̈ړ�����
		Walk();

		// �X�L���̏���
		if (UseSkill() == false)
		{
			// �W�����v�̏���
			Jump();

			// �U���̏���
			Attack();

			// �K�[�h�̏���
			Guard();

			// ����̏���
			Avoid();
		}
	}

#ifdef _DEBUG
	// �f�o�b�O�R�}���h
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// �L�[�{�[�h�X�V

	// L�{�^���̎�
	if (pKeyboard->GetTrigger(DIK_L))
	{
		// �_���[�W��^����
		AddDamage(20);
	}

#endif
}

//=============================================================================
// �v���C���[�ړ�����
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// �L�[�{�[�h�X�V
	DIJOYSTATE js = CInputJoypad::GetStick(0);				// �W���C�p�b�h�̎擾
	CSound *pSound = CManager::GetSound();					// �T�E���h�̏��

	// �J�����p�x�擾
	float fAngle = CGame::GetCamera()->Get��();
	D3DXVECTOR3 pos = GetPos();

	if (GetMotionState() != MOTION_ATTACK && GetMotionState() != MOTION_GUARD && GetMotionState() != MOTION_DAMAGE)
	{
		//���͂����݂���
		if ((js.lX != 0.0f || js.lY != 0.0f))
		{
			//�_���[�W���󂯂Ă��Ȃ��Ƃ��݈̂ړ�����
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

					pos.x += cosf(fAngle)* GetSpeed();
					pos.z -= sinf(fAngle)* GetSpeed();
				}
				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(90.0f);

					pos.x -= cosf(fAngle)* GetSpeed();
					pos.z += sinf(fAngle)* GetSpeed();
				}
				else
				{
				}
				//�X�e�B�b�NY�̓��͂����x�𒴂��Ă���
				if (js.lY < -STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle;

					pos.x -= sinf(fAngle)* GetSpeed();
					pos.z -= cosf(fAngle)* GetSpeed();

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
					pos.x += sinf(fAngle)* GetSpeed();
					pos.z += cosf(fAngle)* GetSpeed();

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
		else
		{
			// �����Ă�����
			if (m_bWalk == true)
			{
				//�ҋ@���[�V�������Đ�
				SetMotion(MOTION_IDOL);
				m_bWalk = false;
			}
		}
	}

	// ��Ԃ̕ۑ�
	MOTION_STATE Motionstate = (MOTION_STATE)GetMotionState();	// ���[�V�������
	STATE state = (STATE)GetState();							// ���

	//�_���[�W���󂯂Ă��Ȃ��Ƃ��݈̂ړ�����
	if (Motionstate != MOTION_DAMAGE && Motionstate != MOTION_JUMP && Motionstate != MOTION_ATTACK)
	{
		// �O�Ɉړ�
		if (pKeyboard->GetPress(DIK_W))
		{
			// �������[�V����
			SetMotion(MOTION_WALK);

			pos.x -= sinf((CGame::GetCamera()->Get��()))*GetSpeed();
			pos.z -= cosf((CGame::GetCamera()->Get��()))*GetSpeed();
			m_rotDest.y = CGame::GetCamera()->Get��();
			SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera()->Get��(), GetRot().z));
		}
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_S))
		{
			// �������[�V����
			SetMotion(MOTION_WALK);

			pos.x += sinf((CGame::GetCamera()->Get��()))*GetSpeed();
			pos.z += cosf((CGame::GetCamera()->Get��()))*GetSpeed();
			m_rotDest.y = CGame::GetCamera()->Get��();
			SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera()->Get��() + D3DXToRadian(-180.0f), GetRot().z));

		}
		// ���Ɉړ�
		if (pKeyboard->GetPress(DIK_A))
		{
			// �������[�V����
			SetMotion(MOTION_WALK);

			pos.x += sinf((CGame::GetCamera()->Get��() + D3DXToRadian(90.0f)))*GetSpeed();
			pos.z += cosf((CGame::GetCamera()->Get��() + D3DXToRadian(90.0f)))*GetSpeed();
			m_rotDest.y = CGame::GetCamera()->Get��();
			SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera()->Get��() + D3DXToRadian(-90.0f), GetRot().z));

		}
		// �E�Ɉړ�
		if (pKeyboard->GetPress(DIK_D))
		{
			// �������[�V����
			SetMotion(MOTION_WALK);

			pos.x += sinf((CGame::GetCamera()->Get��() + D3DXToRadian(-90.0f)))*GetSpeed();
			pos.z += cosf((CGame::GetCamera()->Get��() + D3DXToRadian(-90.0f)))*GetSpeed();
			m_rotDest.y = CGame::GetCamera()->Get��();
			SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera()->Get��() + D3DXToRadian(90.0f), GetRot().z));

		}

		// ���W�ݒ�
		SetPos(pos);

		// �Â����W�擾
		D3DXVECTOR3 OldPos = GetOldPos();

		// �����Ă��Ȃ�������
		if (OldPos == pos)
		{
			// �ʏ탂�[�V����
			SetMotion(MOTION_IDOL);
		}
	}
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

//=============================================================================
// ���񂾂Ƃ��̏���
//=============================================================================
void CPlayer::Death(void)
{
	m_bDraw = false;
}

//=============================================================================
// �U���̏���
//=============================================================================
void CPlayer::Attack(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// ENTER�L�[���������Ƃ��E�R���g���[����X���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0) 
		|| pKeyboard->GetTrigger(DIK_RETURN))
	{
		// �U�����[�V����
		SetMotion(MOTION_ATTACK);
	}
}

//=============================================================================
// �K�[�h�̏���
//=============================================================================
void CPlayer::Guard(void)
{
		// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �K�[�h�̏���
	if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_B, 0) 
		|| pKeyboard->GetPress(DIK_G))
	{
		// �K�[�h���[�V����
		SetMotion(MOTION_GUARD);

		// �K�[�h�G�t�F�N�g���g���Ă��Ȃ�������
		if (m_pGuardEffect == NULL)
		{
			m_pGuardEffect = CGuardEffect::Create(D3DXVECTOR3(GetPos().x, GetPos().y+200.0f, GetPos().z), GUARD_EFFECT_SIZE);
		}
	}
	else
	{
		// �K�[�h�G�t�F�N�g���g���Ă�����
		if (m_pGuardEffect != NULL)
		{
			// �I������
			m_pGuardEffect->Uninit();
			m_pGuardEffect = NULL;
		}

	}
}

//=============================================================================
// ����̏���
//=============================================================================
void CPlayer::Avoid(void)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	DIJOYSTATE js = CInputJoypad::GetStick(0);				// �W���C�p�b�h�̎擾

	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);
	float fAngle = CGame::GetCamera()->Get��();

	D3DXVECTOR3 pos = GetPos();

	if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_Y, 0)
		|| pKeyboard->GetPress(DIK_T))
	{
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		SetMove(D3DXVECTOR3(
			sinf(fAngle +(fAngle2))*PLAYER_AVOID_SPEED,
			0.0f,
			cosf(fAngle + (fAngle2))*PLAYER_AVOID_SPEED));

		m_bAvoid = true;	// ���
		SetArmor(true);		// ���G����
	}

	// ������g��ꂽ�Ƃ�
	if (m_bAvoid == true)
	{
		m_nAvoidCounter++;
	}

	// ����̎���
	if (m_nAvoidCounter >= PLAYER_AVOID_FLAME)
	{
		m_nAvoidCounter = 0;
		m_bAvoid = false;
		SetMotion(MOTION_IDOL);
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// ���G���ԉ���
	if (m_nAvoidCounter == 5)
	{
		SetArmor(false);		// ���G����
	}
}

//=============================================================================
// ���̃G�t�F�N�g�̏���
//=============================================================================
void CPlayer::SwordLight(void)
{
	// ���̍��{�ƌ���̃��[���h���W�擾
	D3DXVECTOR3 Root = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._43);

	D3DXVECTOR3 Tip = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

	//==========================================================
	// �x�N�g�����߂�
	//==========================================================
	// 2�_�Ԃ̃x�N�g�������߂�i�I�_[�ڕW�n�_] - �n�_[���g�̈ʒu]�j
	D3DXVECTOR3 Vector = Tip - Root;

	// �x�N�g���̑傫�������߂�(��c^2 = a^2 * b^2)	����
	float fVectorSize = D3DXVec3Length(&Vector);

	//Root + Vector / ((fVectorSize / LIGHT_EFFECT_RADIAN) * nCount);
	
	for (int nCount = 0; nCount < fVectorSize / LIGHT_EFFECT_RADIAN_INTER; nCount++)
	{
		// ��������̃x�N�g����nCount�ŕ�����
		D3DXVECTOR3 pos = Root + (Vector / (fVectorSize / LIGHT_EFFECT_RADIAN_INTER)) * (float)nCount;

		if (int nNum = rand() % BLADE_PARTICLE_INTER == 0)
		{
			// �\�[�h�X�L�����̓��g�p�[�e�B�N��
			CParticleFactory::CreateParticle(pos,
				CParticleFactory::PARTICLE_NUM_SKILL_BLADE);
		}

		// �\�[�h�G�t�F�N�g
		CLightEffect::Create(pos, LIGHT_EFFECT_SIZE, LIGHT_EFFECT_LIFE);
	}

}

//=============================================================================
// ���̋O��
//=============================================================================
void CPlayer::SwordLocus(void)
{
	// ���_�̌Â����W�擾
	D3DXVECTOR3 OldOrigin = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._43);

	// ����̌Â����W
	D3DXVECTOR3 OldTop = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._43);

	// ���_�̌��ݍ��W
	D3DXVECTOR3 Origin = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._43);

	// ����̌��ݍ��W
	D3DXVECTOR3 Top = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

	// �O�Ղ̐���
	CLocus::Create(Origin, Top, OldOrigin, OldTop,
		GetRot(), D3DXVECTOR3(LOCUS_SIZE_X, LOCUS_SIZE_Y, LOCUS_SIZE_Z),
		LOCUS_LIFE);
}

//=============================================================================
// �X�L���̎g�p����
//=============================================================================
bool CPlayer::UseSkill(void)
{
	MOTION_STATE Motionstate = (MOTION_STATE)GetMotionState();	// ���[�V�������

	if (Motionstate != MOTION_ATTACK)
	{
		// �L�[�{�[�h���
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();

		// K�L�[���������Ƃ��E�R���g���[����R1���������Ƃ�
		if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_R_TRIGGER, 0)
			|| pKeyboard->GetPress(DIK_RSHIFT))
		{
				// �\�[�h�X�L���������̃p�[�e�B�N��
				CParticleFactory::CreateParticle(GetPos(),
					CParticleFactory::PARTICLE_NUM_SWORD_SKILL);

			if (m_pUiSkill != NULL)
			{
				// �g���ĂȂ�������
				if (m_pUiSkill->GetUse() == false)
				{
					// �X�L����UI��`�悷��
					m_pUiSkill->SetUse(true);
				}
			}
		
			// K�L�[���������Ƃ��E�R���g���[����B���������Ƃ�
			if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0)
				|| pKeyboard->GetTrigger(DIK_1))
			{
				// SP�o�[���g���Ă�����
				if (m_pSpBar != NULL)
				{
					// �Q�[�W�����ʈȏゾ������
					if (m_pSpBar->GetGage() >= SKILL_SP_NUM)
					{
						// �U�����[�V����
						SetMotion(MOTION_ATTACK);

						// SP�o�[�̃Q�[�W�����炷
						m_pSpBar->SubGage(SKILL_SP_NUM);
					}
				}
			}

			return true;
		}
		else
		{
			if (m_pUiSkill != NULL)
			{
				// �g���ĂȂ�������
				if (m_pUiSkill->GetUse() == true)
				{
					// �X�L����UI��`�悷��
					m_pUiSkill->SetUse(false);
				}
			}

		}
	}

	return false;
}