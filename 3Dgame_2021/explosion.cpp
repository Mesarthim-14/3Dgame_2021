#ifndef _PARTICLE_H_
#define _PARTICLE_H_
//=====================================================
//
// �p�[�e�B�N���w�b�_�[ [particle.h]
// Author : Konishi Yuuto
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "billboard.h"

//=====================================================
// �}�N����`
//=====================================================
#define EXPLOSION_SIZE_X	(90.0f)		// �T�C�Y
#define EXPLOSION_SIZE_Y	(90.0f)		// �T�C�Y
#define EXPLOSION_DISTANCE	(150)		// ����
#define EXPLOSION_SPEED		(10)		// ���x
#define EXPLOSION_LIFE		(35)		// ���C�t
#define EXPLOSION_NUM		(40)		// ��

#define EXPLOSION_SIZE		(D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f))		// �T�C�Y
#define EXPLOSION_COLOR		(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))							// �J���[

#define SWORD_SKILL_SIZE_X		(90.0f)		// �T�C�Y
#define SWORD_SKILL_SIZE_Y		(90.0f)		// �T�C�Y
#define SWORD_SKILL_DISTANCE	(400)		// ����
#define SWORD_SKILL_SPEED		(5)			// ���x
#define SWORD_SKILL_LIFE		(70)		// ���C�t
#define SWORD_SKILL_NUM			(10)		// ��

#define SWORD_SKILL_SIZE		(D3DXVECTOR3(SWORD_SKILL_SIZE_X, SWORD_SKILL_SIZE_Y, 0.0f))	// �T�C�Y
#define SWORD_SKILL_COLOR		(D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f))							// �J���[

//=====================================================
// �O���錾
//=====================================================

//=====================================================
// �r���{�[�h�N���X
//=====================================================
class CParticle : public CBillboard
{
public:
	CParticle(PRIORITY Priority = PRIORITY_1);		// �R���X�g���N�^
	~CParticle();									// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CParticle*Create(D3DXVECTOR3 pos,			// �C���X�^���X����
		D3DXVECTOR3 size, D3DXCOLOR color,
		D3DXVECTOR3 Distance, D3DXVECTOR3 move, int nLife);

private:
};

#endif