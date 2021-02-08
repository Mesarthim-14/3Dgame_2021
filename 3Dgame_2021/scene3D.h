#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
// 3D�|���S���N���X�w�b�_�[ [scene3D.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// �C���N���[�h
//=========================================================================
#include "scene.h"

//=========================================================================
// �}�N����`
//=========================================================================

//=========================================================================
// 3D�|���S���N���X
//=========================================================================
class CScene3D :public CScene
{
public:
	CScene3D(PRIORITY Priority = PRIORITY_0);	// �R���X�g���N�^
	virtual ~CScene3D();						// �f�X�g���N�^
	
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	virtual void Uninit(void);									// �I������
	virtual void Update(void);									// �X�V����
	virtual void Draw(void);									// �`�揈��

	void SetPos(D3DXVECTOR3 pos);								// ���W�̐ݒ�
	void SetPosision(D3DXVECTOR3 pos);							// ���W�̍X�V
	void SetColor(D3DXCOLOR col);								// �J���[�̐ݒ�
	void SetRot(D3DXVECTOR3 rot);								// �p�x�̐ݒ�
	void Alpha(void);											// �����x
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// �e�N�X�`���̐ݒ�

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);					// �o�b�t�@���
	D3DXVECTOR3 GetPos(void);									// ���W
private:
	LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�|�C���^
	D3DXMATRIX	m_mtxWorld;						// ���[���h�}�g���N�X
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_size;							// �T�C�Y
	D3DXVECTOR3 m_rot;							// ����
};
#endif