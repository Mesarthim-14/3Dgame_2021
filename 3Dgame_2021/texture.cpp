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
#define TEXTURE_NAME_FIRE	("data/Texture/fire111.png")	// ��
#define TEXTURE_NAME_BG		("data/Texture/sky.jpg")		// �Q�[���w�i

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEXTURE] = {};				// �e�N�X�`���̃|�C���^
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_apTextureList = {};

// �e�N�X�`�����̐ݒ�
FILENAME_LIST CTexture::m_aTexFileName =
{
	{ "data/Texture/fire111.png" },						// ��
	{ "data/Texture/sky.jpg" },							// �Q�[���w�i
};

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
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG, &m_apTexture[TEXTURE_NUM_BG]);

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
	return m_apTexture[Tex_Num];
}
