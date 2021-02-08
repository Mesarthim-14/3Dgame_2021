#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================

using FILENAME_LIST = std::vector<std::string>;		//�t�@�C�����̃��X�g

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:

	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		TEXTURE_NUM_NONE = -1,		// �����l
		TEXTURE_NUM_FIRE,			// ��
		TEXTURE_NUM_GAGEFLAME,		// ���C�t�̘g
		TEXTURE_NUM_GAGEBAR,		// ���C�t�̃Q�[�W
		TEXTURE_NUM_TITLE_BG,		// �^�C�g���̔w�i
		TEXTURE_NUM_PARTICLE,		// �p�[�e�B�N��
		TEXTURE_NUM_SKILL_UI,		// �X�L����UI
		TEXTURE_NUM_SWORD_LOCUS,	// ���̊��
		TEXTURE_NUM_SLASH_EFFECT,	// �a���̃G�t�F�N�g
		TEXTURE_NUM_SKILL_START,	// �X�L���̑ҋ@��
		TEXTURE_NUM_QUEST_START,	// �N�G�X�g�̎n�܂�
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);	// �e�N�X�`���̏��
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];				// �e�N�X�`���̃|�C���^
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;			// �ʏ�e�N�X�`���ւ̃|�C���^�̃��X�g
	static std::vector<std::string> m_aTexFileName;					// �ʏ�e�N�X�`���̃t�@�C����
};
#endif
