//=======================================================================================
//
// 2D�|���S���`�揈�� [scene2d.cpp]
// Author : Konishi Yuuto
//
//=======================================================================================

//=======================================================================================
// �C���N���[�h�t�@�C��
//=======================================================================================
#include "keyboard.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"

//=======================================================================================
// �R���X�g���N�^
//=======================================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	m_pTexture = NULL;								// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;								// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �|���S���̈ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �|���S���̃T�C�Y
	m_col = D3DCOLOR_RGBA(0, 0, 0, 0);				// �|���S���̃J���[	
	m_tex = D3DXVECTOR2(0.0f, 0.0f);				// �e�N�X�`���[�ݒ�
	m_nCountAnim = 0;								// �A�j���[�V�����e�N�X�`��
	m_nCountAnimPattern = 0;						// �A�j���[�V�����̃p�^�[��
	m_nCounterAnim= 0;								// �A�j���[�V�����̃J�E���^�[
	m_nPatternAnim= 0;								// �A�j���[�V�����̃p�^�[����
	m_nSpeedTexture = 0;							// �e�N�X�`���̈ړ����x
	m_nLoop = -1;									// ���[�v���邩�ǂ���
	m_fDivisionCounter = 0.0f;						// �X�N���[���̃J�E���^�[
	m_fDivisionBaseNum = 0.0f;						// �X�N���[���̈ړ���
	m_fRotasion = 0.0f;
}

//=======================================================================================
// �f�X�g���N�^
//=======================================================================================
CScene2D::~CScene2D()
{

}

//=======================================================================================
// �|���S���̏�����
//=======================================================================================
HRESULT CScene2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=======================================================================================
// �|���S���̏I������
//=======================================================================================
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �폜�t���O����������
	CScene::SetDeathFlag();
}

//=======================================================================================
// �|���S���̍X�V����
//=======================================================================================
void CScene2D::Update(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�f�[�^�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=======================================================================================
// �|���S���̕`�揈��
//=======================================================================================
void CScene2D::Draw(void)
{
	// Renderer�N���X����f�o�C�X���擾
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�A���t�@�e�X�g��L����
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//�A���t�@�e�X�g��l�̐ݒ�
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//�A���t�@�e�X�g�̔�r���@�̐ݒ�(GREATER�͊�l���傫���ꍇ)
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		NUM_POLYGON);

	//�A���t�@�e�X�g�𖳌���
	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// �e�N�X�`���̐ݒ�
	pD3DDevice->SetTexture(0, NULL);

}

//=======================================================================================
// Scene�N���X�̐���
//=======================================================================================
CScene2D* CScene2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �I�u�W�F�N�g�𐶐�
	CScene2D* pScene = new CScene2D();

	// ����������
	pScene->Init(pos ,size);

	return pScene;
}

//======================================================
//�F�̎擾
//======================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	m_col = col;

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�(0~255�̐��l�Őݒ�)
	pVtx[0].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r,g,b,a��0~255�͈̔͂Ō��߂邱��
	pVtx[1].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //r:���b�h g:�O���[���@b:�u���[
	pVtx[2].col = D3DXCOLOR(col.r, col.g, col.b, col.a); //a�́A�����x��\���Ă���
	pVtx[3].col = D3DXCOLOR(col.r, col.g, col.b, col.a);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================
// �A�j���[�V�������擾
//=============================================
void CScene2D::InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop)
{
	m_nCounterAnim = nCounterAnim;
	m_nPatternAnim = nPatternAnim;
	m_nLoop = nLoop;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W���X�V
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//=============================================
// �A�j���[�V�����X�V�֐�
//=============================================
void CScene2D::UpdateAnimation(void)
{
	// �����̃A�j���[�V�����J�E���g��i�߂āA�p�^�[����؂�ւ���
	m_nCountAnim++;
	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCountAnim >= m_nCounterAnim)	// �����̑���
	{
		// �A�j���[�V�����̃J�E���g��0�ɂ���
		m_nCountAnim = 0;

		// �A�j���[�V�����̃p�^�[�����J�E���g������
		m_nCountAnimPattern++;
	}

	// �A�j���[�V�������I�������
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// ���l��߂��Ă���
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// �I������
			Uninit();
		}
	}
	else
	{
		// ���_����ݒ�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

//======================================================
//���[�e�[�V�����̎擾
//======================================================
void CScene2D::SetRotation(float rotasion)
{
	rotasion += m_fRotasion;
	float r = sqrtf(powf(m_size.x / 2, 2.0) + powf(m_size.x / 2, 2.0));	//���a
	float fTheta = atan2(m_size.x / 2, m_size.x / 2);					//�V�[�^

	float XAngle = r*cos(fTheta + rotasion);	//X�̊p�x
	float YAngle = r*sin(fTheta + rotasion);	//Y�̊p�x

	VERTEX_2D*pVtx;	//���_���ւ̃|�C���^

	//���_�f�[�^�͈͂����b�N���A���_�o�b�t�@�ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x + XAngle, m_pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(90) + rotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(90) + rotasion);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + XAngle, m_pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(-90) + rotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(-90) + rotasion);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + XAngle, m_pos.y + YAngle, 0.0f);
	XAngle = r*cos(fTheta + D3DXToRadian(180) + rotasion);
	YAngle = r*sin(fTheta + D3DXToRadian(180) + rotasion);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + XAngle, m_pos.y + YAngle, 0.0f);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	// ��]��
	m_fRotasion += 0.01f;
}

//=============================================
// �e�N�X�`���̃X�N���[�������擾
//=============================================
void CScene2D::InitScroll(int nSpeed, float fDivision)
{
	m_nSpeedTexture = nSpeed;
	m_fDivisionBaseNum = fDivision;
}

//=============================================
// �e�N�X�`���̃X�N���[�������X�V
//=============================================
void CScene2D::UpdateScroll(void)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// �J�E���^�[��i�߂�
	m_nCounterAnim++;
	// ���_���(�e�N�X�`�����W)�̍X�V
	if (m_nCounterAnim >= m_nSpeedTexture)		// �����̑���
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W���X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - m_fDivisionCounter);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - m_fDivisionCounter);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - m_fDivisionCounter);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - m_fDivisionCounter);

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		// �A�j���[�V�����̃p�^�[�����J�E���g������
		m_fDivisionCounter += m_fDivisionBaseNum;
		m_nCounterAnim = 0;
	}
}