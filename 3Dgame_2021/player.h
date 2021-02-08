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
#define PLAYER_LIFE_NUM			(100)		// �\�����郉�C�t�̐�
#define MOTION_KEYSET_MAX		(32)		// �L�[�Z�b�g�ő吔
#define PLAYER2_POS_X			(0.0f)		// ���W
#define PLAYER2_POS_Y			(171.0f)	// ���W
#define PLAYER2_POS_Z			(500)		// ���W
#define PLAYER_SIZE_X			(1)			// �T�C�Y
#define PLAYER_SIZE_Y			(1)			// �T�C�Y
#define PLAYER_SIZE_Z			(1)			// �T�C�Y

#define PLAYER_COLLISION_X		(200)		// �����蔻��
#define PLAYER_COLLISION_Y		(175)		// �����蔻��
#define PLAYER_COLLISION_Z		(200)		// �����蔻��
#define WEAPON_COLLISION_X		(150)		// ����̓����蔻��
#define WEAPON_COLLISION_Y		(150)		// ����̓����蔻��
#define WEAPON_COLLISION_Z		(150)		// ����̓����蔻��
#define PLAYER_ATTACK_DAMAGE	(40)		// �U����
#define PLAYER_GUARD_CUT_DAMAGE	(3)			// �_���[�W�J�b�g�̒l

//=============================================================================
//�@���[�V������Ԃ̗񋓌^
//=============================================================================
typedef enum
{
	PARTS_NUM_NONE = -1,
	PARTS_NUM_WAIST,			// [0]��
	PARTS_NUM_BODY,				// [1]��
	PARTS_NUM_HEAD,				// [2]��
	PARTS_NUM_RIGHT_SHOLDER,	// [3]�E��
	PARTS_NUM_RIGHT_UPPERARM,	// [4]�E��r
	PARTS_NUM_RIGHT_ARM,		// [5]�E�r
	PARTS_NUM_RIGHT_HAND,		// [6]�E��̂Ђ�
	PARTS_NUM_LEFT_SHOLDER,		// [7]����
	PARTS_NUM_LEFT_UPPERARM,	// [8]����r
	PARTS_NUM_LEFT_ARM,			// [9]���r
	PARTS_NUM_RIGHT_THIGHS,		// [10]�E��
	PARTS_NUM_RIGHT_SHIN,		// [11]�E��
	PARTS_NUM_RIGHT_SHOE,		// [12]�E��
	PARTS_NUM_LEFT_THIGHS,		// [13]����
	PARTS_NUM_LEFT_SHIN,		// [14]����
	PARTS_NUM_LEFT_SHOE,		// [15]����
	PARTS_NUM_BACKPACK,			// [16]�o�b�N�p�b�N
	PARTS_NUM_RIGHT_WING,		// [17]�E��
	PARTS_NUM_LEFT_WING,		// [18]����
	PARTS_NUM_WEAPON,			// [19]����
	PARTS_NUM_COLLISION,		// [20]�����蔻��
	PARTS_NUM_ROOT,				// [21]���̍��{
	PARTS_NUM_MAX,				// ���[�V�����ő吔
}PARTS_NUM;

//=============================================================================
//�@�O���錾
//=============================================================================
class CSpBar;
class CUiSkill;
class CGuardEffect;

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
		MOTION_GUARD,
		MOTION_DAMAGE,		//����
		MOTION_MAX,			//���[�V�����ő吔
	}MOTION_STATE;

	CPlayer(PRIORITY Priority = PRIORITY_CHARACTER);	// �R���X�g���N�^
	~CPlayer();											// �f�X�g���N�^

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// �N���G�C�g

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��
	void UpdateState(void);								// �v���C���[�̏��
	void UpdateMotionState(void);						// ���[�V�������
	void PlayerControl(void);							// �v���C���[�̐���
	void Walk(void);									// �v���C���[�̕�������
	void Jump(void);									// �W�����v�̏���
	void Death(void);									// ���񂾂Ƃ��̏���
	void Attack(void);									// �U���̏���
	void Guard(void);									// �K�[�h�̏���
	void Avoid(void);									// ����̏���
	void SwordLight(void);								// ���̃G�t�F�N�g�̏���
	void SwordLocus(void);								// ���̋O��
	bool UseSkill(void);								// �X�L���̎g�p
private:
	D3DXVECTOR3 m_rotDest;							// ��](�ڕW�l)
	bool m_bWalk;									// �����Ă���t���O
	bool m_bDraw;									// �`��̃t���O
	bool m_bUseLocusEffect;							// �G�t�F�N�g�̎g�p�t���O
	bool m_bAvoid;									// ����̃t���O
	bool m_bArmor;									// ���G���Ԃ̃t���O
	int m_nEndCounter;								// ���񂾌�̃J�E���^�[
	int m_nAvoidCounter;							// ����̃J�E���^�[
	CSpBar *m_pSpBar;								// SP�o�[
	CUiSkill *m_pUiSkill;							// �X�L����UI
	CGuardEffect *m_pGuardEffect;					// �K�[�h�G�t�F�N�g�̃|�C���^
};
#endif