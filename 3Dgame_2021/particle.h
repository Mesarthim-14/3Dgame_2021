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
#include "particle_factory.h"

//=====================================================
// �}�N����`
//=====================================================

//=====================================================
// �O���錾
//=====================================================
CParticleFactory;

//=====================================================
// �r���{�[�h�N���X
//=====================================================
class CParticle : public CBillboard
{
public:
	CParticle(PRIORITY Priority = PRIORITY_PARTICLE);	// �R���X�g���N�^
	~CParticle();										// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CParticle*Create(D3DXVECTOR3 pos,			// �C���X�^���X����
		CParticleFactory::PARTICLE Particle,
		LPDIRECT3DTEXTURE9 pTexture);
private:
};

#endif