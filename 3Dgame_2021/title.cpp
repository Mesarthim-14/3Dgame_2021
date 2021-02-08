//=======================================================================================
//
// �^�C�g���N���X�̏��� [title.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "title.h"
#include "scene2d.h"
#include "manager.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "title_bg.h"
#include "titlelogo.h"
#include "sound.h"
#include "joypad.h"

//=======================================================================================
//�ÓI�����o�ϐ��錾
//=======================================================================================
CTitleBg *CTitle::m_pTitleBg = NULL;
CTitlelogo *CTitle::m_pTitlelogo = NULL;

//=======================================================================================
// �^�C�g���N���X�̃R���X�g���N�^
//=======================================================================================
CTitle::CTitle(PRIORITY Priority) : CScene(Priority)
{
}

//=======================================================================================
// �^�C�g���N���X�̃f�X�g���N�^
//=======================================================================================
CTitle::~CTitle()
{

}

//=======================================================================================
// �^�C�g���N���X�̃N���G�C�g����
//=======================================================================================
CTitle* CTitle::Create(void)
{
	// �������m��
	CTitle* pTitle = new CTitle;

	if (pTitle != NULL)
	{
		// ����������
		pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
			D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
	}

	return pTitle;
}

//=======================================================================================
// �^�C�g���N���X�̏���������
//=======================================================================================
HRESULT CTitle::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �^�C�g���w�i�̏���
	if (m_pTitleBg == NULL)
	{
		// �I�u�W�F�N�g����
		m_pTitleBg = CTitleBg::Create(TITLE_BG_POS, TITLE_BG_SIZE);
	}

	//// �^�C�g�����S�̏���
	//if (m_pTitlelogo == NULL)
	//{
	//	// �I�u�W�F�N�g����
	//	m_pTitlelogo = CTitlelogo::Create(
	//		D3DXVECTOR3(TITLE_UI_POS_X, TITLE_UI_POS_Y, 0.0f), 
	//		D3DXVECTOR3(TITLE_UI_SIZE, TITLE_UI_SIZE, 0.0f));
	//}

	// �T�E���h�̏��
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//=======================================================================================
// �^�C�g���N���X�̏I������
//=======================================================================================
void CTitle::Uninit(void)
{
	// �^�C�g�����S�̏���
	if (m_pTitlelogo != NULL)
	{
		// �I������
		m_pTitlelogo = NULL;
	}

	// �^�C�g���w�i�̏���
	if (m_pTitleBg != NULL)
	{
		// �I�u�W�F�N�g����
		m_pTitleBg = NULL;
	}

	//BGM���~�߂鏈��
	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=======================================================================================
// �^�C�g���N���X�̍X�V����
//=======================================================================================
void CTitle::Update(void)
{
	CInputKeyboard* pKey = CManager::GetKeyboard();
	CFade::FADE_MODE mode = CManager::GetFade()->GetFade();
	CSound *pSound = CManager::GetSound();
	
	// �R���g���[����start���������Ƃ����A�G���^�[�L�[���������Ƃ�
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_START, 0) && mode == CFade::FADE_MODE_NONE 
		|| pKey->GetTrigger(DIK_RETURN) && mode == CFade::FADE_MODE_NONE)
	{
		CFade *pFade = CManager::GetFade();
		pFade->SetFade(CManager::MODE_TYPE_TUTORIAL);
		pSound->Play(CSound::SOUND_LABEL_SE_START);
	}
}

//=======================================================================================
// �^�C�g���N���X�̕`�揈��
//=======================================================================================
void CTitle::Draw(void)
{

}