//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bg.h"
#include "billboard.h"
#include "fade.h"
#include "fire.h"
#include "game.h"
#include "input.h"
#include "joypad.h"
#include "keyboard.h"
#include "manager.h"
#include "meshfield.h"
#include "model.h"
#include "particle_factory.h"
#include "player.h"
#include "renderer.h"
#include "result.h"
#include "scene3D.h"
#include "sound.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "xfile.h"

//=============================================================================
//�ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
CRenderer *CManager::m_pRenderer = NULL;	//�����_���[�N���X�̃|�C���^�ϐ�
CInputKeyboard *CManager::m_pInput = NULL;//���͏����N���X�̃|�C���^�ϐ�
CConection *CManager::m_pConection = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CInputJoypad *CManager::m_pJoypad = NULL;
CSound *CManager::m_pSound = NULL;			//�T�E���h�N���X�̃|�C���^
CScene *CManager::m_pScene = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_���[�N���X�̃C���X�^���X����
	m_pRenderer = new CRenderer;

	//���������m�ۂł�����
	if (m_pRenderer != NULL)
	{
		// ����������
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//���͏����N���X�̃C���X�^���X����
	m_pInput = new CInputKeyboard;

	//���������m�ۂł�����
	if (m_pInput != NULL)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//���͏����N���X�̃C���X�^���X����
	m_pJoypad = new CInputJoypad;

	//���������m�ۂł�����
	if (m_pJoypad != NULL)
	{
		if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//�T�E���h�̃C���X�^���X����
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	//���C�u��������
	if (FAILED(InitImgui(hWnd)))
	{
		return E_FAIL;
	}

	//�t�F�[�h�N���X�̃N���G�C�g
	m_pFade = CFade::Create();

	//�S�e�N�X�`���̓ǂݍ���
	LoadAll();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�S�e�N�X�`���̔j��
	UnLoadAll();
	
	if (m_pFade != NULL)
	{
		//�t�F�[�h�N���X�̏I�������Ăяo��
		m_pFade->Uninit();

		//�������̔j��
		delete m_pFade;

		//�������̃N���A
		m_pFade = NULL;
	}

	if (m_pInput != NULL)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pInput->Uninit();

		//�������̍폜
		delete m_pInput;

		//�������̃N���A
		m_pInput = NULL;
	}

	if (m_pJoypad != NULL)
	{
		//���͏����N���X�̏I�������Ăяo��
		m_pJoypad->Uninit();

		//�������̍폜
		delete m_pInput;

		//�������̃N���A
		m_pJoypad = NULL;
	}

	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̏I�������Ăяo��
		m_pRenderer->Uninit();

		//�������̍폜
		delete m_pRenderer;

		//�������̃N���A
		m_pRenderer = NULL;
	}

	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pInput != NULL)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pInput->Update();
	}

	if (m_pJoypad != NULL)
	{
		//���͏����N���X�̍X�V�����Ăяo��
		m_pJoypad->Update();
	}

	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̍X�V�����Ăяo��
		m_pRenderer->Update();
	}

	if (m_pFade != NULL)
	{
		//�t�F�[�h�N���X�̍X�V�����Ăяo��
		m_pFade->Update();
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//�����_���[�N���X�̕`�揈���Ăяo��
		m_pRenderer->Draw();
	}
}

//=============================================================================
//�e�N�X�`���̑S���[�h����
//=============================================================================
void CManager::LoadAll(void)
{
	CResult::Load();
	CMeshField::Load();
	CTutorial::Load();
	CTexture::Load();
	CXfile::ModelLoad();
	CParticleFactory::ReadFile();
}

//=============================================================================
//�e�N�X�`���̑S�A�����[�h����
//=============================================================================
void CManager::UnLoadAll(void)
{
	CMeshField::UnLoad();
	CTexture::UnLoad();
	CXfile::ModelUnLoad();
}

//=============================================================================
//�Q�[�����[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	CSound *pSound = CManager::GetSound();

	//���݃��[�h�̏I��
	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			m_pTitle = NULL;
		}
		break;

	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);
			m_pTutorial = NULL;
		}
		break;

	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
			m_pGame = NULL;
		}
		break;

	case MODE_TYPE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	}

	CScene::ReleaseAll();

	//���[�h��ݒ�
	m_mode = mode;

	//�ݒ肳�ꂽ���[�h���N���G�C�g
	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		
		break;

	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
		}

		break;

	case MODE_TYPE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}

		break;

	case MODE_TYPE_RESULT:
		if (m_pGame == NULL)
		{
			m_pResult = CResult::Create();
		}

	default:
		break;
	}
}

//------------------------------------------------------------------------------
//Imgui������
//------------------------------------------------------------------------------
HRESULT CManager::InitImgui(HWND hWnd)
{
	//�Q�[���p�b�h�ƃL�[�{�[�h�̏��擾
	m_pInput = CManager::GetKeyboard();

	//NULL�`�F�b�N
	if (!m_pInput)
	{
		return E_FAIL;
	}

	//create
	IMGUI_CHECKVERSION();

	//����
	ImGui::CreateContext();

	//�f�t�H���g�J���[�ݒ�
	ImGui::StyleColorsDark();

	//������
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());


//	ImGui::Begin("config 1");
//
//	ImGui::End();

	return S_OK;
}

//------------------------------------------------------------------------------
//Imgui�I��
//------------------------------------------------------------------------------
void CManager::UninitImgui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
//------------------------------------------------------------------------------
//Imgui �f�o�b�O���\��
//------------------------------------------------------------------------------
void CManager::ShowDebugInfo()
{
#ifdef _DEBUG




	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	////�J�n
	//if (ImGui::CollapsingHeader("Debug"))
	//{
	//	//FPS���
	//	if (ImGui::TreeNode("FPS"))
	//	{
	//		//FPS
	//		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//		ImGui::TreePop();
	//	}


	//	//���
	//	if (ImGui::TreeNode("DebugCommand"))
	//	{
	//		//���C�e�B���O
	//		if (ImGui::Checkbox("Lighting", &m_Lighting))
	//		{
	//			pDevice->SetRenderState(D3DRS_LIGHTING, m_Lighting);		// ���C�e�B���O���[�h�؂�ւ�
	//		}

	//		//�J�����O
	//		if (ImGui::TreeNode("tree1", "CULLING"))
	//		{
	//			if (ImGui::RadioButton("D3DCULL_CCW", &m_Culling, 0))
	//			{
	//				//���ʃJ�����O
	//				CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);
	//			}
	//			ImGui::SameLine();
	//			if (ImGui::RadioButton("D3DCULL_CW", &m_Culling, 1))
	//			{
	//				//�\�ʃJ�����O
	//				CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CW);
	//			}
	//			ImGui::SameLine();
	//			if (ImGui::RadioButton("D3DCULL_NONE", &m_Culling, 2))
	//			{
	//				//�J�����O���Ȃ�
	//				CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);
	//			}
	//			ImGui::TreePop();
	//		}
	//		//�v���C���[�f�o�b�O
	//		if (ImGui::Checkbox("DebugPlayer", &m_bDebugPlayer))
	//		{

	//		}
	//		ImGui::TreePop();
	//	}
	//}

#endif //DEBUG
}

//=============================================================================
//�Q�[�����[�h���̎擾
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//�����_���[���擾
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}


//=============================================================================
//�L�[�{�[�h���擾
//=============================================================================
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

CConection *CManager::GetConection(void)
{
	return m_pConection;
}

//=============================================================================
//�t�F�[�h���擾
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
//�W���C�p�b�h���擾
//=============================================================================
CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad;
}

//=============================================================================
//�W���C�p�b�h���擾
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}
