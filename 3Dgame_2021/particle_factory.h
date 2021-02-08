#ifndef _PARTICLE_FACTORY_H_
#define _PARTICLE_FACTORY_H_
//=============================================================================
//
// �p�[�e�B�N�������N���X�w�b�_�[ [particle_factory.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
//�N���X�錾
//=============================================================================
class CParticleFactory
{
public:

	// �p�[�e�B�N���̍\����
	typedef struct
	{
		D3DXVECTOR3 size;		// �T�C�Y
		D3DXVECTOR3 move;		// �ړ���
		D3DXVECTOR3 Distance;	// ����
		int nLife;				// ���C�t
		int nNum;				// ��
		D3DXCOLOR color;		// �F
		bool bGravity;			// �d��
		bool bAlpha;			// �A���t�@�e�X�g
	}PARTICLE;

	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		PARTICLE_NUM_NONE = -1,		// �����l
		PARTICLE_NUM_EXPLOSION,		// �_���[�W���󂯂��Ƃ�
		PARTICLE_NUM_SWORD_SKILL,	// �X�L���̑ҋ@���Ԓ�
		PARTICLE_NUM_SKILL_BLADE,	// �X�L�����̓��g
		PARTICLE_NUM_MAX
	}PARTICLE_TYPE;

	CParticleFactory();													// �R���X�g���N�^
	~CParticleFactory();												// �f�X�g���N�^

	static HRESULT ReadFile(void);										// �t�@�C���̓ǂݍ���
	static void CreateParticle(D3DXVECTOR3 pos, PARTICLE_TYPE type);									// �p�[�e�B�N���̃N���X
private:
	static PARTICLE m_Particle[PARTICLE_NUM_MAX];			// �p�[�e�B�N��
};
#endif
