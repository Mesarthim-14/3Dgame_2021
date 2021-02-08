//=============================================================================
//
// �I�G�l�~�[�N���X [crab.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "crab.h"
#include "manager.h"
#include "renderer.h"
#include "life_frame.h"
#include "life_bar.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CRAB_XFAILE_NAME "data/Text/crab_motion.txt"		// LBX�̃t�@�C���p�X
#define CRAB_LIFE				(120)						// �I�̗̑�
#define CRAB_RADIUS				(200.0f)					// �I�̑傫��
#define CRAB_SPEED				(15.0f)						// �I�̑���
#define CRAB_ATTACK_INTER		(300)						// �U���̊Ԋu
#define CRAB_ATTACK_PARTS_NUM	(7)							// �U���̃p�[�c�ԍ�
#define CRAB_WEAPON_RADIUS		(200.0f)					// ����̔��a
#define CRAB_ARMOR_FLAME		(50)						// ���G���Ԃ̃t���[��
#define CRAB_ATTACK_POWAR		(20)						// �U����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCrab::CCrab(int nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCrab::~CCrab()
{
}

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
CCrab * CCrab::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �������m��
	CCrab *pCrab = new CCrab;

	// ����������
	pCrab->Init(pos, rot);

	return pCrab;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCrab::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// ����������
	SetCharaModel(CRAB_XFAILE_NAME, MAX_CRAB_PARTS, ENEMY_MOTION_MAX);	// ���f���̏���
	CEnemy::Init(pos, rot);												// ����������
	SetLife(CRAB_LIFE);													// ���C�t�̐���
	SetRadius(CRAB_RADIUS);												// ���a�̐ݒ�
	SetSpeed(CRAB_SPEED);												// �����̐ݒ�
	SetActive(true);													// �G�����邩�̐ݒ�
	SetAttackInter(CRAB_ATTACK_INTER);									// �U���̊Ԋu��ݒ�
	SetWeaponTipNum(CRAB_ATTACK_PARTS_NUM);								// �U���p�[�c�̔ԍ���ݒ�
	SetWeaponRadius(CRAB_WEAPON_RADIUS);								// ����̔��a
	SetArmorFlame(CRAB_ARMOR_FLAME);									// ���G���Ԃ̐ݒ�
	SetAttackPower(CRAB_ATTACK_POWAR);									// �U���͂̐ݒ�
	LifeBarCreate(ENEMY_LIFE_FRAME_POS, ENEMY_LIFE_FRAME_SIZE, 
	ENEMY_LIFE_BAR_POS, ENEMY_LIFE_BAR_SIZE,
	ENEMY_LIFE_BAR_COLOR, CRAB_LIFE);									// ���C�t�o�[�̐���
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCrab::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CCrab::Update(void)
{
	// �X�V����
	CEnemy::Update();

	// ���W���
	D3DXVECTOR3 pos = GetPos();		// ���݂̍��W�擾
	SetPosOld(pos);					// �Â����W�ۑ�

	// ��ԍX�V
	UpdateState();

	// ���[�V�������
	UpdateMotionState();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCrab::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}