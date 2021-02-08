#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=====================================================
//
// �r���{�[�h�N���X�w�b�_�[ [billboard.h]
// Author : �����D�l
//
//=====================================================

//=====================================================
// �C���N���[�h
//=====================================================
#include "scene.h"
//=====================================================
// �}�N����`
//=====================================================
#define BILLBOARD_SIZE_X	(25)	// �傫��
#define BILLBOARD_SIZE_Y	(25)	// �傫��

//=====================================================
// �r���{�[�h�N���X
//=====================================================
class CBillboard : public CScene
{
public:
	CBillboard(PRIORITY Priority = PRIORITY_0);		// �R���X�g���N�^
	~CBillboard();								// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	virtual void Uninit(void);													// �I������
	virtual void Update(void);													// �X�V����
	virtual void Draw(void);													// �`�揈��
	
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// �e�N�X�`���̐ݒ�
	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);	// �A�j���[�V������񏉊���
	void UpdateAnimation(void);											// �A�j���[�V�����̍X�V
	
	// Set�֐�
	void SetPos(D3DXVECTOR3 pos);										// ���W�̐ݒ�
	void SetMove(D3DXVECTOR3 move);										// �ړ��ʐݒ�
	void SetSize(D3DXVECTOR3 size);										// �T�C�Y�ݒ�
	void SetSizeBase(D3DXVECTOR3 sizeBase);								// �T�C�Y�̃x�[�X
	void SetColor(D3DXCOLOR color);										// �F�̐ݒ�
	void SetLife(int nLife);											// �̗͂̐ݒ�
	void SetAlpha(bool bAlpha);											// �A���t�@�e�X�g�̐ݒ�
	
	// Get�֐�
	D3DXVECTOR3 GetPos(void);											// ���W���
	D3DXVECTOR3 GetMove(void);											// �ړ��ʏ��
	D3DXVECTOR3 GetSize(void);											// �T�C�Y���
	int GetLIfe(void);													// �̗͂̏��
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);								// �o�b�t�@�̏��

private:
	D3DXVECTOR3 m_pos;									// �ʒu���
	D3DXVECTOR3 m_move;									// �ړ���
	D3DXVECTOR3 m_size;									// �T�C�Y
	D3DXVECTOR3 m_Dir;									// ����7
	D3DXVECTOR3 m_sizeBase;								// �T�C�Y�̃x�[�X
	D3DXCOLOR m_color;									// �J���[�̐ݒ�
	D3DXMATRIX m_mtxWorld;								// �s��v�Z�p
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;						// �|���S���̃e�N�X�`��
	int m_nLife;										// ����
	int m_nCountAnim;									// �A�j���[�V�����e�N�X�`��
	int m_nCountAnimPattern;							// �A�j���[�V�����̃p�^�[��
	int m_nCounterAnim;									// �A�j���[�V�����̃J�E���^�[
	int m_nPatternAnim;									// �A�j���[�V�����̃p�^�[����
	int m_nLoop;										// ���[�v���邩
	bool m_bUse;										// �g�p����
	bool m_bAlpha;										// �A���t�@�e�X�g���g�p���邩
};

#endif