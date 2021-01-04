//=======================================================================================
// 
// 2D�|���S���`�揈�� [scene2d.h]
// Author : Konishi Yuuto
//
//=======================================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// �N���X��`
//***************************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = PRIORITY_0);
	~CScene2D();
	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);			// �A�j���[�V������񏉊���
	void InitScroll(int nSpeed, float fDivision);								// �摜�X�N���[���̐ݒ�
	void UpdateAnimation(void);													// �A�j���[�V�����̍X�V
	void UpdateScroll(void);													// �摜�X�N���[���̍X�V
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetPolygonSize(const D3DXVECTOR3 nSize) { m_size = nSize; }
	void SetCol(D3DXCOLOR col);
	void SetRotation(float rotasion);
	D3DXVECTOR3 GetPos(void)const { return m_pos; }
	D3DXVECTOR3 GetSize(void)const { return m_size; }
	D3DXCOLOR   GetCol(void) { return m_col; }
private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 // ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �|���S���̈ʒu
	D3DXVECTOR3 m_size;				// �|���S���̃T�C�Y
	D3DXCOLOR   m_col;						// �|���S���̃J���[	
	D3DXVECTOR2 m_tex;						// �e�N�X�`���[�ݒ�
	int m_nCountAnim;						// �A�j���[�V�����e�N�X�`��
	int m_nCountAnimPattern;				// �A�j���[�V�����̃p�^�[��
	int m_nCounterAnim;						// �A�j���[�V�����̃J�E���^�[
	int m_nPatternAnim;						// �A�j���[�V�����̃p�^�[����
	int m_nSpeedTexture;					// �e�N�X�`���̈ړ����x
	int m_nLoop;							// ���[�v���邩�ǂ���
	float m_fDivisionCounter;				// �X�N���[���̃J�E���^�[
	float m_fDivisionBaseNum;				// �X�N���[���̈ړ���
	float m_fRotasion;
};

#endif // !_SCENE2D_H_
