#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//------------------------------------------------------------------------------
//
// �L�����N�^�[����  [character.h]
// Author : Konishi Yuuto
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//------------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------------
#define MAX_CHARACTER_PARTS (21)

//=============================================================================
//�@���f���t�@�C�����̍\����
//=============================================================================
typedef struct
{
	char xFileName[1024];	//�t�@�C���l�[��
	D3DXVECTOR3 offsetPos;	//�ʒu�̃I�t�Z�b�g���
	D3DXVECTOR3 offsetRot;	//�����̃I�t�Z�b�g���
	int nParent;	//�e���
}MODELFILLE;

//=============================================================================
//�@�e�v�f�̃L�[���
//=============================================================================
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//=============================================================================
//	�L�[���̍\����
//=============================================================================
typedef struct
{
	int nFrame;	//�t���[����
	KEY aKey[MAX_CHARACTER_PARTS];	//�e�p�[�c�̃L�[���
}KEY_INFO;

//=============================================================================
//�@���[�V�������̍\����
//=============================================================================
typedef struct
{
	bool bLoop;	//���[�v���邩�ǂ���
	int nNumKey;	//�L�[��
	KEY_INFO aKeyInfo[20];	//�L�[���
}Motion_Info;

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------

//�L�����N�^�[�̃N���X
class CCharacter : public CScene
{
public:
	typedef enum
	{
		STATE_NONE = 0,		// �����l
		STATE_APPEAR,		// �o��
		STATE_NO_ACTIVE,	// ��퓬���
		STATE_NORMAL,		// �ʏ���
		STATE_DAMAGE,		// �_���[�W���
	}STATE;

	CCharacter(int nPriority = PRIORITY_1);
	virtual ~CCharacter();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// ������
	virtual void Uninit();									// �I������
	virtual void Update();									// �X�V
	virtual void Draw();									// �`��

	virtual void UpdateMotion(void);							// ���[�V�����̍X�V�̏������z�֐�

																// �������z�֐�
	virtual void UpdateState(void) = 0;								// �L�����N�^�[���
	virtual void UpdateMotionState(void) = 0;					// ���[�V�����̏��

	bool Gravity(void);											// �n�ʂ̐���
	HRESULT ReadFile(void);											// �t�@�C���̓ǂݍ���

	// Set�֐�
	void SetCharacter(char *xfilename, int nPart, int nMotion);
	void SetPos(D3DXVECTOR3 pos);									// ���W�̐ݒ�
	void SetPosOld(D3DXVECTOR3 posOld);								// ���W�̐ݒ�
	void SetState(STATE state);										// �v���C���[���̐ݒ�
	void SetMove(D3DXVECTOR3 move);									// �ړ��ʂ̐ݒ�
	void SetRot(D3DXVECTOR3 rot);
	void SetAngle(float Angle);										// �p�x�̐ݒ�
	void SetLife(int nLife);										// ���C�t�̐ݒ�
	void SetCountMotion(int CountMotion);							// ���[�V�����̃J�E���g�ݒ�
	void SetMotionState(int nMotionState);
	void SetMotion(int nMotion);				// ���[�V�����̐ݒ�
	void SetKey(int nKey);
	void SetJump(bool bJump);										// �W�����v�̃t���O
	void SetLanding(bool bLanding);									// ���n�̐ݒ�
	// Get�֐�
	D3DXVECTOR3 GetPos(void) { return m_pos; }									// ���݂̍��W���
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }								// �Â����W���
	D3DXVECTOR3 GetRot(void) { return m_rot; }									// �p�x���
	D3DXVECTOR3 GetMove(void) { return m_move; }								// �ړ��ʂ̏��
	STATE GetState(void) { return m_state; }									// �v���C���[�̏�ԏ��
	KEY_INFO *GetKeyInfo(void) { return m_apKeyInfo; }							// �L�[���
	Motion_Info GetMotion(int nCount) { return m_Motion[nCount]; }				// ���[�V�������
	int GetLife(void) { return m_nLife; }										// ���C�t�̏��
	int GetCountMotion(void) { return m_nCountMotion; }							// ���[�V�����̃J�E���g
	int GetMotionState(void) { return m_nMotionState; }
	int GetKey(void) { return m_nKey; }
	float GetAngle(void) { return m_fAngle; }									// �p�x�̏��
	CModelAnime *GetModelAnime(int nCount) { return m_apModelAnime[nCount]; }	// ���[�V�����̃J�E���g���
	bool GetJump(void) { return m_bJump; }										// �W�����v
	bool GetLanding(void) { return m_bLanding; }								// ���n�̃t���O
private:
	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_posOld;					// �Â����W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ���݂̉�]
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	STATE m_state;							// �L�����N�^�[�̏��
	int m_nLife;							// �̗�
	int m_nAttack;							// �U����
	int m_nSpeed;							// �ړ���
	int m_nPart;							// �p�[�c
	float m_fAngle;							// �p�x
	bool m_bJump;							// �W�����v���Ă���t���O
	bool m_bLanding;						// ���n�̃t���O

	// ���f���p�ϐ�
	CModelAnime *m_apModelAnime[MAX_CHARACTER_PARTS];	// ���f���p�[�c�p�̃|�C���^
	MODELFILLE m_modelfile[MAX_CHARACTER_PARTS];		// ���f���p�[�c���
	char *m_pFileName;									// �t�@�C���̖��O

	// ���[�V�����p�ϐ�
	Motion_Info m_Motion[30];		//���[�V�������
	KEY_INFO *m_apKeyInfo;			// �L�[���̃|�C���^
	int m_nMotionState;				// ���[�V�����̏��
	int m_nNumKey;					// �L�[�̑���
	int m_nCountMotion;				// ���[�V�����J�E���^�[
	int m_nMotionInterval;			// ���[�V�����̃C���^�[�o��
	int m_nStateCounter;			// ��Ԃ̃J�E���^�[
	int m_nKey;						// ���݃L�[��No
	bool m_bMotionPlaing;
};
#endif