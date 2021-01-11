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
#define MAX_TEXTURE (256)

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
		TEXTURE_NUM_BG,				// �w�i
		TEXTURE_NUM_LIFEBAR,		// ���C�t�̘g
		TEXTURE_NUM_LIFEGAGE,		// ���C�t�̃Q�[�W
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);		// �e�N�X�`���̏��
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];				// �e�N�X�`���̃|�C���^
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;			// �ʏ�e�N�X�`���ւ̃|�C���^�̃��X�g
	static std::vector<std::string> m_aTexFileName;					// �ʏ�e�N�X�`���̃t�@�C����
};
#endif
