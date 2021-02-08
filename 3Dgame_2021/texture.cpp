//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NAME_FIRE			("data/Texture/fire111.jpg")				// ��
#define TEXTURE_NAME_LIFEBAR		("data/Texture/LifeBar.png")				// ���C�t�̘g
#define TEXTURE_NAME_LIFEGAGE		("data/Texture/LifeBar000.png")				// ���C�t�o�[(��)
#define TEXTURE_NAME_TITLE_BG		("data/Texture/title.png")					// �^�C�g����ʂ̔w�i
#define TEXTURE_NAME_PARTICLE		("data/Texture/effect003.png")				// �p�[�e�B�N��
#define TEXTURE_NAME_SKILL_UI		("data/Texture/skill_ui.png")				// �X�L����UI
#define TEXTURE_NAME_SWORD_LOCUS	("data/Texture/SwordLocus003.png")			// ���̋O��
#define TEXTURE_NAME_SLASH_EFFECT	("data/Texture/magic24.jpg")				// �a���̃G�t�F�N�g
#define TEXTURE_NAME_SKILL_START	("data/Texture/Sword_Skill_Start001.png")	// �X�L���̑ҋ@��
#define TEXTURE_NAME_QUEST_START	("data/Texture/QuestStart_Logo.png")		// �N�G�X�g�̊J�n

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[TEXTURE_NUM_MAX] = {};				// �e�N�X�`���̃|�C���^
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTextureList = {};

//// �e�N�X�`�����̐ݒ�
//FILENAME_LIST CTexture::m_aTexFileName =
//{
//	{ "data/Texture/fire111.png" },						// ��
//	{ "data/Texture/sky.jpg" },							// �Q�[���w�i
//};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_FIRE, &m_apTexture[TEXTURE_NUM_FIRE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LIFEBAR, &m_apTexture[TEXTURE_NUM_GAGEFLAME]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LIFEGAGE, &m_apTexture[TEXTURE_NUM_GAGEBAR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_TITLE_BG, &m_apTexture[TEXTURE_NUM_TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_PARTICLE, &m_apTexture[TEXTURE_NUM_PARTICLE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SKILL_UI, &m_apTexture[TEXTURE_NUM_SKILL_UI]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SWORD_LOCUS, &m_apTexture[TEXTURE_NUM_SWORD_LOCUS]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SLASH_EFFECT, &m_apTexture[TEXTURE_NUM_SLASH_EFFECT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SKILL_START, &m_apTexture[TEXTURE_NUM_SKILL_START]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_QUEST_START, &m_apTexture[TEXTURE_NUM_QUEST_START]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != NULL)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}