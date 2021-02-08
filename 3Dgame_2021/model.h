//=============================================================================
//
// ���f������ [model.h]
// Author : �R�c�ˑ�
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_MODEL_TEXTURE	(256)		// �e�N�X�`���̍ő吔

//=============================================================================
// ���f���N���X
//=============================================================================
class CModel : public CScene
{
public:
	typedef enum
	{
		MODEL_TYPE_NONE = 0,	// �����l
		MODEL_TYPE_PLAYER1,		// �v���C���[
		MODEL_TYPE_PLAYER2,		// �v���C���[
		MODEL_TYPE_BEAM,		// �r�[��
		MODEL_TYPE_OBJECT,		// ����
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	//=========================================================================
	//�����o�֐��錾
	//=========================================================================
	CModel(PRIORITY Priority = PRIORITY_EFFECT);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindModel(CXfile::MODEL model);
	void BindTexture(LPDIRECT3DTEXTURE9 *pTexture);
	void BindTexturePointer(LPDIRECT3DTEXTURE9 *ppTexture);

	// Set�֐�
	void SetPos(const D3DXVECTOR3 pos);
	void SetRot(const D3DXVECTOR3 rot);		// ���W�̏��
	D3DXVECTOR3 GetRot(void);
	void SetType(MODEL_TYPE Mtype);
	void SetSize(D3DXVECTOR3 size);
	void SetTexPattern(int TexPattern);		// �e�N�X�`���̃p�^�[��

	// Get�֐�
	D3DXVECTOR3 GetPos(void)const;
	D3DXVECTOR3 GetSize(void);
	MODEL_TYPE GetType(void);
	D3DXMATRIX GetMtxWorld(void);
	LPD3DXMESH GetMesh(void)const;
	LPD3DXBUFFER GetBuffMat(void);
	DWORD GetNumMat(void);
	int GetTexPattern(void);
private:
	//=========================================================================
	//�����o�ϐ��錾
	//=========================================================================
//	LPDIRECT3DTEXTURE9 m_apTexture[MAX_MODEL_TEXTURE];
	LPDIRECT3DTEXTURE9 *m_apTexture;
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ����
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXMATRIX m_mtxWorld;				// ���[���h�}�g���b�N�X
	MODEL_TYPE m_type;					// ���
	CXfile::MODEL m_Model;				// ���f���̍\����
	int m_nTexPattern;						// �e�N�X�`���̃p�^�[����
};
#endif 