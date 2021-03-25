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
// �e�N�X�`���̖��O
#define TEXTURE_NAME_FIRE			("data/Texture/fire111.jpg")				// ��
#define TEXTURE_NAME_LIFEBAR		("data/Texture/LifeBar.png")				// ���C�t�̘g
#define TEXTURE_NAME_LIFEGAGE		("data/Texture/LifeBar000.png")				// ���C�t�o�[(��)
#define TEXTURE_NAME_TITLE_BG		("data/Texture/bg001.png")					// �^�C�g����ʂ̔w�i
#define TEXTURE_NAME_PARTICLE		("data/Texture/effect003.png")				// �p�[�e�B�N��
#define TEXTURE_NAME_SKILL_UI		("data/Texture/skill_ui.png")				// �X�L����UI
#define TEXTURE_NAME_SWORD_LOCUS	("data/Texture/sword_locus000.png")			// ���̋O��
#define TEXTURE_NAME_SLASH_EFFECT	("data/Texture/magic24.jpg")				// �a���̃G�t�F�N�g
#define TEXTURE_NAME_SKILL_START	("data/Texture/Sword_Skill_Start001.png")	// �X�L���̑ҋ@��
#define TEXTURE_NAME_QUEST_START	("data/Texture/QuestStart_Logo.png")		// �N�G�X�g�̊J�n
#define TEXTURE_NAME_OPERATION		("data/Texture/button_ui.png")				// ����{�^����UI
#define TEXTURE_NAME_JUMP_IMPACT	("data/Texture/inpact.tga")					// �W�����v�̏Ռ�
#define TEXTURE_NAME_ROAR_IMPACT	("data/Texture/inpact_red.tga")				// ���K�̏Ռ�
#define TEXTURE_NAME_HIT_IMPACT_000	("data/Texture/Hit_Impact002.tga")			// �U�����̏Ռ�
#define TEXTURE_NAME_FLOOR			("data/Texture/floor.jpg")					// ���̃e�N�X�`��
#define TEXTURE_NAME_DUSH_IMPACT	("data/Texture/Hit_Impact003.tga")			// �_�b�V���̏Ռ�
#define TEXTURE_NAME_ENEMY_LOCUS	("data/Texture/sword_locus002.png")			// �{�X�̋O��
#define TEXTURE_NAME_HIT_UI			("data/Texture/hit_ui.png")					// HIT��UI
#define TEXTURE_NAME_DAMAGE_UI		("data/Texture/damage_ui.png")				// �_���[�W��UI

// �����e�N�X�`���̖��O
#define SEPARATE_TEX_NAME_SHARP				("data/Texture/sharp_effect.png")			// �s���G�t�F�N�g
#define SEPARATE_TEX_NAME_ELECTRICITY		("data/Texture/Electricity_Effect000.png")	// �d���G�t�F�N�g
#define SEPARATE_TEX_NAME_SMOKE				("data/Texture/smoke000.png")				// ���G�t�F�N�g
#define SEPARATE_TEX_NAME_HIT_EFFECT		("data/Texture/hit_effect000.png")			// �q�b�g�G�t�F�N�g
#define SEPARATE_TEX_NAME_HIT_IMPACT		("data/Texture/slash_impact.png")			// �q�b�g���̏Ռ�
#define SEPARATE_TEX_NAME_SAND_SMOKE		("data/Texture/sand_smoke.png")				// �q�b�g���̏Ռ�
#define SEPARATE_TEX_NAME_CIRCLE			("data/Texture/circle.png")					// �T�[�N���G�t�F�N�g
#define SEPARATE_TEX_NAME_ATTACK_LIGHT		("data/Texture/attack_light_001.png")		// �U�����̌�
#define SEPARATE_TEX_NAME_KOBOLD_SMOKE		("data/Texture/smoke_101.png")				// �R�{���g�̉�
#define SEPARATE_TEX_NAME_JUMP_SMOKE		("data/Texture/smoke_effect000.png")			// �W�����v�̉�
#define SEPARATE_TEX_NAME_ATTACK_CIRCLE		("data/Texture/attack_circle000.png")		// �U���̉~
#define SEPARATE_TEX_NAME_DAMAGE_NUMBER		("data/Texture/damage_number.png")			// �_���[�W�̐����e�N�X�`��
#define SEPARATE_TEX_NAME_ARM_LIGHT			("data/Texture/arm_light.png")				// ��̌�
#define SEPARATE_TEX_NAME_DAMAGE_EFFECT		("data/Texture/damage_impact100.tga")		// �_���[�W���̃G�t�F�N�g
#define SEPARATE_TEX_NAME_ROAR_FIRE			("data/Texture/roar_attack000.png")			// ���K���̃t�@�C�A
#define SEPARATE_TEX_NAME_ROAR_LIGHT		("data/Texture/roar_light000.png")			// ���K���̌�
#define SEPARATE_TEX_NAME_COMBO_NUMBER		("data/Texture/combo_damage.png")			// �R���{�̃i���o�[
#define SEPARATE_TEX_NAME_COMBO_NUMBER_000	("data/Texture/combo_damage000.png")		// �R���{�̃_���[�W�i���o�[

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
	memset(m_apTexture, 0, sizeof(m_apTexture));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CTexture * CTexture::Create(void)
{
	CTexture *pTexture = new CTexture;

	return pTexture;
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
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_OPERATION, &m_apTexture[TEXTURE_NUM_OPERATION]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_JUMP_IMPACT, &m_apTexture[TEXTURE_NUM_JUMP_IMPACT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ROAR_IMPACT, &m_apTexture[TEXTURE_NUM_ROAR_IMPACT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_HIT_IMPACT_000, &m_apTexture[TEXTURE_NUM_HIT_IMPACT_000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_FLOOR, &m_apTexture[TEXTURE_NUM_FLOOR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_DUSH_IMPACT, &m_apTexture[TEXTURE_NUM_DUSH_IMPACT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_LOCUS, &m_apTexture[TEXTURE_NUM_ENEMY_LOCUS]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_HIT_UI, &m_apTexture[TEXTURE_NUM_HIT_UI]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_DAMAGE_UI, &m_apTexture[TEXTURE_NUM_DAMAGE_UI]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != nullptr)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = nullptr;
		}
	}
}

//=============================================================================
// �����e�N�X�`���̃��[�h
//=============================================================================
HRESULT CTexture::SeparateTexLoad(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_SHARP, &m_apSeparateTexture[SEPARATE_TEX_SHARP].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ELECTRICITY, &m_apSeparateTexture[SEPARATE_TEX_ELECTRICITY].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_SMOKE, &m_apSeparateTexture[SEPARATE_TEX_SMOKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_HIT_EFFECT, &m_apSeparateTexture[SEPARATE_TEX_HIT_EFFECT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_HIT_IMPACT, &m_apSeparateTexture[SEPARATE_TEX_HIT_IMPACT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_SAND_SMOKE, &m_apSeparateTexture[SEPARATE_TEX_SAND_SMOKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_CIRCLE, &m_apSeparateTexture[SEPARATE_TEX_CIRCLE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ATTACK_LIGHT, &m_apSeparateTexture[SEPARATE_TEX_ATTACK_LIGHT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_KOBOLD_SMOKE, &m_apSeparateTexture[SEPARATE_TEX_KOBOLD_SMOKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_JUMP_SMOKE, &m_apSeparateTexture[SEPARATE_TEX_JUMP_SMOKE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ATTACK_CIRCLE, &m_apSeparateTexture[SEPARATE_TEX_ATTACK_CIRCLE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_DAMAGE_NUMBER, &m_apSeparateTexture[SEPARATE_TEX_DAMAGE_NUMBER].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ARM_LIGHT, &m_apSeparateTexture[SEPARATE_TEX_ARM_LIGHT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_DAMAGE_EFFECT, &m_apSeparateTexture[SEPARATE_TEX_DAMAGE_EFFECT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ROAR_FIRE, &m_apSeparateTexture[SEPARATE_TEX_ROAR_FIRE].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_ROAR_LIGHT, &m_apSeparateTexture[SEPARATE_TEX_ROAR_LIGHT].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_COMBO_NUMBER, &m_apSeparateTexture[SEPARATE_TEX_COMBO_NUMBER].pSeparateTexture);
	D3DXCreateTextureFromFile(pDevice, SEPARATE_TEX_NAME_COMBO_NUMBER_000, &m_apSeparateTexture[SEPARATE_TEX_COMBO_NUMBER_000].pSeparateTexture);

	return S_OK;
}

//=============================================================================
// �����e�N�X�`���̃A�����[�h
//=============================================================================
void CTexture::SeparateTexUnLoad(void)
{
	// �e�N�X�`���̉��
	for (int nCount = 0; nCount < SEPARATE_TEX_MAX; nCount++)
	{
		if (m_apSeparateTexture[nCount].pSeparateTexture != nullptr)
		{
			m_apSeparateTexture[nCount].pSeparateTexture->Release();
			m_apSeparateTexture[nCount].pSeparateTexture = nullptr;
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
		if (m_apTexture[Tex_Num] != nullptr)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetSeparateTexture(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// NULLcheck
		if (m_apSeparateTexture[SepaTex_Type].pSeparateTexture != nullptr)
		{
			// �e�N�X�`�����
			return m_apSeparateTexture[SepaTex_Type].pSeparateTexture;
		}
	}

	return nullptr;
}

//=============================================================================
// �����e�N�X�`���̏��
//=============================================================================
D3DXVECTOR2 CTexture::GetSparateTexInfo(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].m_TexInfo;
	}

	return D3DXVECTOR2(0.0f, 0.0f);
}

bool CTexture::GetSparateTexLoop(SEPARATE_TEX_TYPE SepaTex_Type)
{
	// �z���菬����������
	if (SepaTex_Type < SEPARATE_TEX_MAX)
	{
		// �e�N�X�`�����
		return m_apSeparateTexture[SepaTex_Type].bLoop;
	}

	return false;
}