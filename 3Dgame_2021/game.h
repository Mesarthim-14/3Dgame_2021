#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// �}�N����`
//***************************************************************************************
#ifdef VIIEW_PORT_TEST
#endif // VIIEW_PORT_TEST
#define MAX_PLAYER (1)			// �v���C���[�̐�

//***************************************************************************************
// �O���錾
//***************************************************************************************
class CCamera;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CTime;
class CUi;
class CUiStart;
class CBill;
class CUiEnd;
class CPause;
class CSea;

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame(int nPriority = PRIORITY_0);	// �R���X�g���N�^
	~CGame();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	void SetGame(void);												// �Q�[���̐ݒ�

	static CGame* Create();											// �Q�[���������
	static CCamera *GetCamera(void);								// �J�����̃|�C���^���
	static CLight *GetLight(void);									// ���C�g�̃|�C���^���
	static CPlayer *GetPlayer(void);								// �v���C���[�̃|�C���^���
	static CTime *GetTime(void);									// �^�C���̃|�C���^���
	static CUi *GetUi(void);										// UI�̃|�C���^���
	static CUiStart *GetUiStart(void);								// �X�^�[�g��UI�̃|�C���^���
	static CUiEnd *GetUiEnd(void);									// �I�����̃|�C���^���
	static CBill *GetBill(void);									// �r���̃|�C���^���
	static CPause *GetPause(void);									// �|�[�Y��ʂ̃|�C���^���

private:	
	static CCamera *m_pCamera;					// �J�����̃|�C���^	
	static CLight *m_pLight;					// ���C�g�̃|�C���^
	static CMeshField *m_pMeshField;			// ���b�V���t�B�[���h�̃|�C���^
	static CBg *m_pBg;							// �w�i�̃|�C���^
	static CPlayer *m_pPlayer;					// �v���C���[�̃|�C���^
	static CTime *m_pTime;						// �^�C���̃|�C���^
	static CUi *m_pUi;							// ui�̃|�C���^
	static CUiStart *m_pUiStart;				// uistart�̃|�C���^
	static CUiEnd *m_pUiEnd;					// uiend�̃|�C���^
	static CBill *m_pBill;						// �r���̃|�C���^
	static CSea *m_pSea;						// �C�̃|�C���^
	static CPause *m_pPause;					// �|�[�Y�̃|�C���^
	LPD3DXFONT m_pFont;							// �f�o�b�N�p�t�H���g
	bool m_bGameEnd;							// �Q�[���̃G���h�t���O
};
#endif