//=============================================================================
//
// �X�L����UI�N���X [ui_skill.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "ui_skill.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//=============================================================================
// �I�u�W�F�N�g����
//=============================================================================
CUiSkill* CUiSkill::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �I�u�W�F�N�g�𐶐�
	CUiSkill* pUiSkill = new CUiSkill;

	// ����������
	pUiSkill->Init(pos, size);

	return pUiSkill;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUiSkill::CUiSkill()
{
	m_bUse = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUiSkill::~CUiSkill()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUiSkill::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// ����������
	CUi::Init(pos, size);												// ���W�A�T�C�Y
	BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_SKILL_UI));	// �e�N�X�`�����f

	return S_OK;
}

//================================================
// �I������
//================================================
void CUiSkill::Uninit(void)
{
	// �I������
	CUi::Uninit();
}

//================================================
// �X�V����
//================================================
void CUiSkill::Update(void)
{
	// �X�V����
	CUi::Update();
}

//================================================
// �`�揈��
//================================================
void CUiSkill::Draw(void)
{
	// �t���O�������
	if (m_bUse == true)
	{
		// �`�揈��
		CUi::Draw();
	}
}

//================================================
// �t���O�̐ݒ�
//================================================
void CUiSkill::SetUse(bool bUse)
{
	m_bUse = bUse;
}