#ifndef _XFILE_H_
#define _XFILE_H_
//=============================================================================
//
// X�t�@�C���Ǘ��w�b�_�[ [xfile.h]
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
#define MAX_XFILE_TEXTURE	(256)		// �e�N�X�`���̍ő�
#define MAX_NAME_NUM		(1024)		// ���O�̍ő�

//=============================================================================
//�N���X�錾
//=============================================================================
class CXfile
{
public:
	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		XFILE_NUM_NONE = -1,			// �����l
		XFILE_NUM_BG,					// �w�i
		XFILE_NUM_SWORD_EFFECT,			// ���̃G�t�F�N�g
		XFILE_NUM_SWORD_LOCUS_EFFECT,	// ���̋O�ՃG�t�F�N�g
		XFILE_NUM_GUARD_EFFECT,			// �K�[�h�̃G�t�F�N�g
		XFILE_NUM_MAX
	}XFILE_NUM;

	typedef struct
	{
		char xFileName[1024];								// �t�@�C���l�[��
		LPD3DXMESH pMesh;									// ���b�V�����ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;								// �}�e���A�����ւ̃|�C���^
		DWORD dwNumMat;										// �}�e���A�����̐�
		LPDIRECT3DTEXTURE9 apTexture[MAX_XFILE_TEXTURE];	// �e�N�X�`���̐�
	}MODEL;

	CXfile();		// �R���X�g���N�^
	~CXfile();		// �f�X�g���N�^

	static HRESULT ModelLoad(void);				// ���f�����[�h
	static void ModelUnLoad(void);				// ���f���A�����[�h

	// Get�֐�
	static MODEL GetXfile(XFILE_NUM Tex_Num);		// ���f���̏��
	static LPDIRECT3DTEXTURE9 *GetXfileTexture(XFILE_NUM TexNum);	// ���f���Ɏg�p����e�N�X�`�����
private:
	static MODEL m_aXfile[XFILE_NUM_MAX];			// X�t�@�C�����̍\����
};
#endif
