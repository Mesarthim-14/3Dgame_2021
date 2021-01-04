#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define LIFE_NUM			(2)			// �\�����郉�C�t�̐�
#define MAX_PARTS			(10)		// �p�[�c�̐�
#define MOTION_KEYSET_MAX	(32)		// �L�[�Z�b�g�ő吔
#define PLAYER2_POS_X		(0.0f)		// ���W
#define PLAYER2_POS_Y		(171.0f)	// ���W
#define PLAYER2_POS_Z		(500)		// ���W
#define PLAYER_SIZE_X		(1)			// �T�C�Y
#define PLAYER_SIZE_Y		(1)			// �T�C�Y
#define PLAYER_SIZE_Z		(1)			// �T�C�Y
#define MAX_MODEL_PARTS		(21)		// ���f���̃p�[�c�̍ő吔
#define PLAYER_COLLISION_X	(200)		// �����蔻��
#define PLAYER_COLLISION_Y	(175)		// �����蔻��
#define PLAYER_COLLISION_Z	(200)		// �����蔻��
#define WEAPON_COLLISION_X	(150)		// ����̓����蔻��
#define WEAPON_COLLISION_Y	(150)		// ����̓����蔻��
#define WEAPON_COLLISION_Z	(150)		// ����̓����蔻��
#define PLAYER_RADIUS		(150)		// ���a

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
//�@���[�V������Ԃ̗񋓌^
//=============================================================================
typedef enum
{
	MOTION_NONE = -1,
	MOTION_IDOL,	//�A�C�h�����[�V����
	MOTION_WALK,	//���s���[�V����
	MOTION_ATTACK,	//�U�����[�V����
	MOTION_JUMP,	//�W�����v���[�V����
	MOTION_LANDING,	//���n���[�V����
	MOTION_WIN,		//�������[�V����
	MOTION_RIGHTBOOST,	//�E�u�[�X�g
	MOTION_LEFTBOOST,	//���u�[�X�g
	MOTION_DAMAGE,	//����
	MOTION_BEAM,	//�r�[���U��
	MOTION_LOSE,	//�������[�V����
	MOTION_MAX,		//���[�V�����ő吔
}MOTION_STATE;

////=============================================================================
////�@���f���t�@�C�����̍\����
////=============================================================================
//typedef struct
//{
//	char xFileName[1024];	//�t�@�C���l�[��
//	D3DXVECTOR3 offsetPos;	//�ʒu�̃I�t�Z�b�g���
//	D3DXVECTOR3 offsetRot;	//�����̃I�t�Z�b�g���
//	int nParent;	//�e���
//}MODELFILLE;
//
////=============================================================================
////�@�e�v�f�̃L�[���
////=============================================================================
//typedef struct
//{
//	float fPosX;
//	float fPosY;
//	float fPosZ;
//	float fRotX;
//	float fRotY;
//	float fRotZ;
//}KEY;
//
////=============================================================================
////	�L�[���̍\����
////=============================================================================
//typedef struct
//{
//	int nFrame;	//�t���[����
//	KEY aKey[MAX_MODEL_PARTS];	//�e�p�[�c�̃L�[���
//}KEY_INFO;
//
////=============================================================================
////�@���[�V�������̍\����
////=============================================================================
//typedef struct
//{
//	bool bLoop;	//���[�v���邩�ǂ���
//	int nNumKey;	//�L�[��
//	KEY_INFO aKeyInfo[20];	//�L�[���
//}Motion_Info;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{
public:

	typedef enum
	{
		PLAYER_STATE_NONE = 0,		// �����u
		PLAYER_STATE_NORMAL,		// �ʏ���
		PLAYER_STATE_DAMAGE,		// �_���[�W
		PLAYER_STATE_EXPLOSION,		// ����
		PLAYER_STATE_DRAW,			// ��������
		PLAYER_STATE_MAX			// �ő吔
	}PLAYER_STATE;

	CPlayer(int nPriority = PRIORITY_PLAYER);	// �R���X�g���N�^
	~CPlayer();									// �f�X�g���N�^

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �N���G�C�g

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void UpdateMotion(void);										// ���[�V�����X�V����
	void Draw(void);												// �`�揈��
	void PlayerState(void);											// �v���C���[�̏��
	void MotionState(void);											// ���[�V�������
	void PlayerControl(void);										// �v���C���[�̐���
	void Walk(void);												// �v���C���[�̕�������
	void Jump(void);												// �W�����v�̏���
	void GroundLimit(void);											// �n�ʂ̐���
	void SetMotion(MOTION_STATE motion);							// ���[�V�����̐ݒ�
	void SetPos(D3DXVECTOR3 pos);									// ���W�̐ݒ�
	void SetState(PLAYER_STATE state);								// �v���C���[���̐ݒ�
	void SetMove(D3DXVECTOR3 move);									// �ړ��ʂ̐ݒ�
	HRESULT ReadFile(void);											// �t�@�C���̓ǂݍ���
	PLAYER_STATE GetState(void);									// �v���C���[�̏��
	bool GetJump(void);												// �W�����v�̏��
	D3DXVECTOR3 GetPos(void);										// ���݂̍��W���
	D3DXVECTOR3 GetOldPos(void);									// �Â����W���
	D3DXVECTOR3 GetRot(void);										// �p�x���
	D3DXVECTOR3 GetMove(void);										// �ړ��ʂ̏��
private:
	D3DXVECTOR3 m_pos;								// ���W
	D3DXVECTOR3 m_OldPos;							// 1�t���[���O�̍��W
	D3DXVECTOR3 m_rot;								// ��](���ݒn)
	D3DXVECTOR3 m_rotDest;							// ��](�ڕW�l)
	D3DXVECTOR3 m_move;								// �ړ�
	PLAYER_STATE m_state;							// �v���C���[���
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// ���f���p�[�c�p�̃|�C���^
	KEY_INFO *m_apKeyInfo;							// �L�[���̃|�C���^
	MOTION_STATE m_MotionState;						// ���[�V�����̏��
	Motion_Info m_Motion[MOTION_MAX];				// ���[�V�������
	int m_nNumKey;									// �L�[�̑���
	int m_nKey;										// ���݃L�[��No
	int m_nCountMotion;								// ���[�V�����J�E���^�[
	int m_nMotionInterval;							// ���[�V�����̃C���^�[�o��
	int m_nStateCounter;							// ��Ԃ̃J�E���^�[
	float m_fAngle;									// �p�x
	bool m_bMotionPlaing;
	bool m_bJump;									// �W�����v�̃t���O
	bool m_bArmor;									// ���G����
	bool m_bWalk;									// �����Ă���t���O
};
#endif