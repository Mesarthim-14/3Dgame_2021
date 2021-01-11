#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// �G�l�~�[�N���X�w�b�_�[ [player.h]
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
#define MAX_PARTS			(10)		// �p�[�c�̐�
#define MOTION_KEYSET_MAX	(32)		// �L�[�Z�b�g�ő吔
#define ENEMY_SIZE_X		(1)			// �T�C�Y
#define ENEMY_SIZE_Y		(1)			// �T�C�Y
#define ENEMY_SIZE_Z		(1)			// �T�C�Y
#define MAX_MODEL_PARTS		(21)		// ���f���̃p�[�c�̍ő吔
#define ENEMY_COLLISION_X	(200)		// �����蔻��
#define ENEMY_COLLISION_Y	(175)		// �����蔻��
#define ENEMY_COLLISION_Z	(200)		// �����蔻��
#define ENEMY_RADIUS		(150)		// ���a

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
//�@���[�V������Ԃ̗񋓌^
//=============================================================================
typedef enum
{
	ENEMY_MOTION_NONE = -1,
	ENEMY_MOTION_IDOL,		//�A�C�h�����[�V����
	ENEMY_MOTION_WALK,		//���s���[�V����
	ENEMY_MOTION_ATTACK,		//�U�����[�V����
	ENEMY_MOTION_JUMP,		//�W�����v���[�V����
	ENEMY_MOTION_LANDING,		//���n���[�V����
	ENEMY_MOTION_WIN,			//�������[�V����
	ENEMY_MOTION_RIGHTBOOST,	//�E�u�[�X�g
	ENEMY_MOTION_LEFTBOOST,	//���u�[�X�g
	ENEMY_MOTION_DAMAGE,		//����
	ENEMY_MOTION_BEAM,		//�r�[���U��
	ENEMY_MOTION_LOSE,		//�������[�V����
	ENEMY_MOTION_MAX,			//���[�V�����ő吔
}ENEMY_MOTION_STATE;

////=============================================================================
////�@���f���t�@�C�����̍\����
////=============================================================================
//typedef struct
//{
//	char xFileName[1024];	//�t�@�C���l�[��
//	D3DXVECTOR3 offsetPos;	//�ʒu�̃I�t�Z�b�g���
//	D3DXVECTOR3 offsetRot;	//�����̃I�t�Z�b�g���
//	int nParent;	//�e���
//}ENEMY_MODELFILLE;
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
//}ENEMY_KEY;
//
////=============================================================================
////	�L�[���̍\����
////=============================================================================
//typedef struct
//{
//	int nFrame;	//�t���[����
//	ENEMY_KEY aKey[MAX_MODEL_PARTS];	//�e�p�[�c�̃L�[���
//}ENEMY_KEY_INFO;
//
////=============================================================================
////�@���[�V�������̍\����
////=============================================================================
//typedef struct
//{
//	bool bLoop;	//���[�v���邩�ǂ���
//	int nNumKey;	//�L�[��
//	ENEMY_KEY_INFO aKeyInfo[20];	//�L�[���
//}ENEMY_Motion_Info;

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy : public CCharacter
{
public:
	typedef enum
	{
		ENEMY_STATE_NONE = 0,		// �����u
		ENEMY_STATE_NORMAL,		// �ʏ���
		ENEMY_STATE_DAMAGE,		// �_���[�W
		ENEMY_STATE_EXPLOSION,		// ����
		ENEMY_STATE_DRAW,			// ��������
		ENEMY_STATE_MAX			// �ő吔
	}ENEMY_STATE;

	CEnemy(int nPriority = PRIORITY_ENEMY);	// �R���X�g���N�^
	~CEnemy();								// �f�X�g���N�^

	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �N���G�C�g

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void UpdateMotion(void);										// ���[�V�����X�V����
	void Draw(void);												// �`�揈��
	void UpdateState(void);											// �v���C���[�̏��
	void UpdateMotionState(void);											// ���[�V�������
	void GroundLimit(void);											// �n�ʂ̐���
	HRESULT ReadFile(void);											// �t�@�C���̓ǂݍ���

	// Set�֐�
	void SetMotion(ENEMY_MOTION_STATE motion);							// ���[�V�����̐ݒ�
	void SetPos(D3DXVECTOR3 pos);									// ���W�̐ݒ�
	void SetState(ENEMY_STATE state);								// �v���C���[���̐ݒ�
	void SetMove(D3DXVECTOR3 move);									// �ړ��ʂ̐ݒ�

	// Get�֐�
	bool GetJump(void);												// �W�����v�̏��
	D3DXVECTOR3 GetPos(void);										// ���݂̍��W���
	D3DXVECTOR3 GetOldPos(void);									// �Â����W���
	D3DXVECTOR3 GetRot(void);										// �p�x���
	D3DXVECTOR3 GetMove(void);										// �ړ��ʂ̏��
private:
	MODELFILLE m_modelfile[MAX_MODEL_PARTS];	//���f���t�@�C�����

	D3DXVECTOR3 m_pos;								// ���W
	D3DXVECTOR3 m_OldPos;							// 1�t���[���O�̍��W
	D3DXVECTOR3 m_rot;								// ��](���ݒn)
	D3DXVECTOR3 m_rotDest;							// ��](�ڕW�l)
	D3DXVECTOR3 m_move;								// �ړ�
	ENEMY_STATE m_state;							// �v���C���[���
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// ���f���p�[�c�p�̃|�C���^
	KEY_INFO *m_apKeyInfo;							// �L�[���̃|�C���^
	ENEMY_MOTION_STATE m_MotionState;						// ���[�V�����̏��
	Motion_Info m_Motion[ENEMY_MOTION_MAX];				// ���[�V�������
	int m_nNumKey;									// �L�[�̑���
	int m_nCountMotion;								// ���[�V�����J�E���^�[
	int m_nMotionInterval;							// ���[�V�����̃C���^�[�o��
	int m_nStateCounter;							// ��Ԃ̃J�E���^�[
	float m_fAngle;									// �p�x
	bool m_bMotionPlaing;
};
#endif