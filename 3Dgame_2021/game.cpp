//=======================================================================================
//
// �Q�[������ [game.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h
//=======================================================================================
#include "game.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "meshfield.h"
#include "bg.h"
#include "joypad.h"
#include "time.h"
#include "sound.h"
#include "keyboard.h"
#include "fire.h"
#include "enemy.h"

//=======================================================================================
// �}�N����`
//=======================================================================================

//=======================================================================================
// static������
//=======================================================================================
CCamera *CGame::m_pCamera = NULL;
CLight *CGame::m_pLight = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CBg *CGame::m_pBg = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CTime *CGame::m_pTime = NULL;
CUi *CGame::m_pUi = NULL;
CUiStart *CGame::m_pUiStart = NULL;
CBill *CGame::m_pBill = NULL;
CUiEnd *CGame::m_pUiEnd = NULL;
CPause *CGame::m_pPause = NULL;
CSea *CGame::m_pSea = NULL;

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CGame::CGame(int nPriority) : CScene(nPriority)
{
	m_bGameEnd = false;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CGame::~CGame()
{
}

//=======================================================================================
// �N���G�C�g
//=======================================================================================
CGame* CGame::Create(void)
{
	// �������m��
	CGame* pGame = new CGame();

	// ����������
	pGame->Init(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return pGame;
}

//=======================================================================================
// ����������
//=======================================================================================
HRESULT CGame::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �L�[�{�[�h���
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// �J�����N���X�̃N���G�C�g
	m_pCamera = CCamera::Create();

	//���C�g�N���X�̐���
	m_pLight = new CLight;

	// ���C�g�̏���������
	if (m_pLight != NULL)
	{
		if (FAILED(m_pLight->Init()))
		{
			return -1;
		}
	}

	// �v���C���[�̐���
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z));	
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create();
	}

	// �w�i
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z));

	//BGM
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::SOUND_LABEL_BGM_GAME);

	//�f�o�C�X���̎擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�t�H���g�̐���
	D3DXCreateFont(pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	return S_OK;
}

//=======================================================================================
// �I������
//=======================================================================================
void CGame::Uninit(void)
{

	if (m_pCamera != NULL)
	{
		//�J�����N���X�̏I�������Ăяo��
		m_pCamera->Uninit();

		//�������̔j��
		delete m_pCamera;

		//�������̃N���A
		m_pCamera = NULL;
	}


	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}


	// �w�i
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}

	// ���C�g�̏I������
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �v���C���[�̏I������
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}


	// UI
	if (m_pUi != NULL)
	{
		m_pUi = NULL;
	}

	// �X�^�[�gUI
	if (m_pUiStart != NULL)
	{
		m_pUiStart = NULL;
	}

	// �r��
	if (m_pBill != NULL)
	{
		m_pBill = NULL;
	}

	//�T�E���h���擾
	CSound *pSound = CManager::GetSound();

	//�Q�[��BGM��~
	pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);

	//�I�u�W�F�N�g�̔j��
	SetDeathFlag();
}

//=======================================================================================
// �X�V����
//=======================================================================================
void CGame::Update(void)
{
	if (m_pCamera != NULL)
	{
		//�J�����N���X�̍X�V����
		m_pCamera->Update();
	}

	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Update();
	}

	for (int nCount = 0; nCount < FIRE_NUM; nCount++)
	{
		// ���̐���
		CFire::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(FIRE_SIZE_X, FIRE_SIZE_Y, 0.0f), FIRE_LIFE);
	}

	// �Q�[���̐ݒ�
	SetGame();
}

//=======================================================================================
// �`�揈��
//=======================================================================================
void CGame::Draw(void)
{
	// ���b�V���t�B�[���h
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Draw();
	}

	// �w�i
	if (m_pBg != NULL)
	{
		m_pBg->Draw();
	}

	if (m_pLight != NULL)
	{
		m_pLight->ShowLightInfo();
	}


}

//=======================================================================================
// �Q�[���̐ݒ�
//=======================================================================================
void CGame::SetGame(void)
{

}


//=======================================================================================
// �J�����̏��
//=======================================================================================
CCamera * CGame::GetCamera(void)
{
	return m_pCamera;
}

//=======================================================================================
// ���C�g�̏��
//=======================================================================================
CLight * CGame::GetLight(void)
{
	return m_pLight;
}

//=======================================================================================
// �v���C���[�̏��
//=======================================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=======================================================================================
// �^�C���̏��
//=======================================================================================
CTime * CGame::GetTime(void)
{
	return m_pTime;
}

//=======================================================================================
// ui�̏��
//=======================================================================================
CUi * CGame::GetUi(void)
{
	return m_pUi;
}


//=======================================================================================
// uistart�̏��
//=======================================================================================
CUiStart * CGame::GetUiStart(void)
{
	return m_pUiStart;
}

//=======================================================================================
// uiend�̏��
//=======================================================================================
CUiEnd *CGame::GetUiEnd(void)
{
	return m_pUiEnd;
}

//=======================================================================================
// �r���̏��
//=======================================================================================
CBill * CGame::GetBill(void)
{
	return m_pBill;
}

//=======================================================================================
// �R���e�j���[�̏��
//=======================================================================================
CPause * CGame::GetPause(void)
{
	return m_pPause;
}