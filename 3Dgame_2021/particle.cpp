//=====================================================
//
// �p�[�e�B�N���N���X [particle.cpp]
// Author : �����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=====================================================
// �}�N����`
//=====================================================
#define DEFAULT_POS_Y		(200.0f)		// ���E�̍����̕W��

//=====================================================
// �R���X�g���N�^
//=====================================================
CParticle::CParticle(PRIORITY Priority) : CBillboard(Priority)
{
	
}

//=====================================================
// �f�X�g���N�^
//=====================================================
CParticle::~CParticle()
{

}

//=====================================================
// �C���X�^���X����
//=====================================================
CParticle * CParticle::Create(D3DXVECTOR3 pos, CParticleFactory::PARTICLE Particle,
	LPDIRECT3DTEXTURE9 pTexture)
{
	// �������m��
	CParticle *pParticle = new CParticle;

	if (pParticle != NULL)
	{
		// �e�N�X�`���ݒ�
		pParticle->BindTexture(pTexture);

		// �����̐ݒ�
		D3DXVECTOR3 Distance;
		Distance = D3DXVECTOR3(
			(float)(rand() % (int)Particle.Distance.x + rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x - rand() % (int)Particle.Distance.x),
			(float)(rand() % (int)Particle.Distance.y + rand() % (int)Particle.Distance.y),
			(float)(rand() % (int)Particle.Distance.z + rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z - rand() % (int)Particle.Distance.z));

		// �����_���ŏo�������߂�
		D3DXVECTOR3 TargetPos = D3DXVECTOR3(
			pos.x + Distance.x,
			pos.y + Distance.y,
			pos.z + Distance.z);

		// ����������
		pParticle->Init(TargetPos, Particle.size);

		// �ړ��ʐݒ�
		D3DXVECTOR3 move;
		switch (Particle.bGravity)
		{
			// �d�͖���
		case false:
			// �ړ���
			move =
				D3DXVECTOR3(
				(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
					(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y),
					(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
			break;

			// �d�͂���
		case true:
			// �ړ���
			move =
				D3DXVECTOR3(
				(float)(rand() % (int)Particle.move.x - rand() % (int)Particle.move.x + rand() % (int)Particle.move.x),
					(float)(rand() % (int)Particle.move.y + rand() % (int)Particle.move.y - rand() % (int)Particle.move.y),
					(float)(rand() % (int)Particle.move.z - rand() % (int)Particle.move.z + rand() % (int)Particle.move.z));
			break;
		}

		// �ړ���
		pParticle->SetMove(move);

		// �F�̐ݒ�
		pParticle->SetColor(Particle.color);

		// �̗͂̐ݒ�
		pParticle->SetLife(Particle.nLife);

		// �A���t�@�e�X�g�̐ݒ�
		pParticle->SetAlpha(Particle.bAlpha);

	}

	return pParticle;
}

//=====================================================
// ����������
//=====================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CBillboard::Init(pos, size);

	return S_OK;
}

//=====================================================
// �I������
//=====================================================
void CParticle::Uninit(void)
{
	// �I������
	CBillboard::Uninit();

	//�I�u�W�F�N�g�j��
	Release();
}

//=====================================================
// �X�V����
//=====================================================
void CParticle::Update(void)
{
	// �X�V����
	CBillboard::Update();
}

//=====================================================
// �`�揈��
//=====================================================
void CParticle::Draw(void)
{
	// �`�揈��
	CBillboard::Draw();
}