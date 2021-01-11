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
	MOTION_IDOL,		//�A�C�h�����[�V����
	MOTION_WALK,		//���s���[�V����
	MOTION_ATTACK,		//�U�����[�V����
	MOTION_JUMP,		//�W�����v���[�V����
	MOTION_LANDING,		//���n���[�V����
	MOTION_WIN,			//�������[�V����
	MOTION_RIGHTBOOST,	//�E�u�[�X�g
	MOTION_LEFTBOOST,	//���u�[�X�g
	MOTION_DAMAGE,		//����
	MOTION_BEAM,		//�r�[���U��
	MOTION_LOSE,		//�������[�V����
	MOTION_MAX,			//���[�V�����ő吔
}MOTION_STATE;

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
	void Draw(void);												// �`�揈��
	void UpdateState(void);											// �v���C���[�̏��
	void UpdateMotionState(void);											// ���[�V�������
	void PlayerControl(void);										// �v���C���[�̐���
	void Walk(void);												// �v���C���[�̕�������
	void Jump(void);												// �W�����v�̏���

private:
	D3DXVECTOR3 m_rotDest;							// ��](�ڕW�l)
	MOTION_STATE m_MotionState;						// ���[�V�����̏��
	bool m_bArmor;									// ���G����
	bool m_bWalk;									// �����Ă���t���O
};
#endif