//=============================================================================
//
// �K�[�h�G�t�F�N�g�̃N���X [guard_effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "guard_effect.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGuardEffect::CGuardEffect(PRIORITY Priority) : CModel(Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGuardEffect::~CGuardEffect()
{

}

//=============================================================================
// �N���G�C�g����
//=============================================================================
CGuardEffect * CGuardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//3D�|���S���N���X�̃|�C���^�ϐ�
	CGuardEffect *pGuardEffect = new CGuardEffect;

	//���������m�ۂł��Ă�����
	if (pGuardEffect != NULL)
	{
		//�����������Ăяo��
		pGuardEffect->Init(pos, size);
	}

	return pGuardEffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGuardEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CModel::Init(pos, size);

	BindModel(CXfile::GetXfile(CXfile::XFILE_NUM_GUARD_EFFECT));
	BindTexture(CXfile::GetXfileTexture(CXfile::XFILE_NUM_GUARD_EFFECT));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGuardEffect::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGuardEffect::Update(void)
{
	// �X�V����
	CModel::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGuardEffect::Draw(void)
{
	D3DXMATERIAL *pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	pMat = (D3DXMATERIAL*)GetBuffMat()->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// �����x�߂�
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f);
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.3f, 1.0f, 0.3f, 0.2f);

		//	pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
		pMat[nCntMat].MatD3D.Ambient.a = 1.0f;
	}

	// �`�揈��
	CModel::Draw();

	for (int nCntMat = 0; nCntMat < (int)GetNumMat(); nCntMat++)
	{
		// �����x�߂�
		pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
	}
}