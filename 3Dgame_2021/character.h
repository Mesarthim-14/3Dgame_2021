#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//------------------------------------------------------------------------------
//
// �L�����N�^�[����  [character.h]
// Author:Yoshiki Hosoya
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

	static CCharacter *Create(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPart);
	HRESULT ReadFile(void);											// �t�@�C���̓ǂݍ���

	void SetCharacter(char *xfilename, int nPart, int nMotion);

private:
	CModelAnime *m_apModelAnime[MAX_CHARACTER_PARTS];	// ���f���p�[�c�p�̃|�C���^
	MODELFILLE m_modelfile[MAX_CHARACTER_PARTS];		// ���f���p�[�c���

	D3DXVECTOR3 m_pos;						// ���W
	D3DXVECTOR3 m_posOld;					// �Â����W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_rot;						// ���݂̉�]
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X
	STATE m_State;							// �L�����N�^�[�̏��
	int m_nLife;							// �̗�
	int m_nAttack;							// �U����
	int m_nSpeed;							// �ړ���
	int m_nPart;							// �p�[�c
	char *m_pFileName;							// �t�@�C���̖��O
	Motion_Info m_Motion[30];		//���[�V�������
};
#endif