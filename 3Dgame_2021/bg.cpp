//=================================================================================
//
// �w�i�N���X [bg.cpp]
// Author : Konishi Yuuto
//
//=================================================================================

//=================================================================================
// �C���N���[�h
//=================================================================================
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "xfile.h"

//=================================================================================
// �C���X�^���X����
//=================================================================================
CBg * CBg::Create(void)
{
	CBg *pBg = new CBg;

	if (pBg != NULL)
	{
		// ����������
		pBg->Init();
	}

	return pBg;
}

//=================================================================================
// �R���X�g���N�^
//=================================================================================
CBg::CBg()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=================================================================================
// �f�X�g���N�^
//=================================================================================
CBg::~CBg()
{
}

//=================================================================================
// ����������
//=================================================================================
HRESULT CBg::Init(void)
{

//	model.dwNumMat = m_nNumMat;
//	model.pBuffMat = m_pBuffMat;
//	model.pMesh = m_pMesh;

	//���f������ݒ�
	CModel::BindModel(CXfile::GetXfile(CXfile::XFILE_NUM_BG));

	m_pos = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(BG_SIZE_X, BG_SIZE_Y, BG_SIZE_Z);

	// ���W����^����
	CModel::SetPos(m_pos);

	return S_OK;
}

//=================================================================================
// �I������
//=================================================================================
void CBg::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=================================================================================
// �X�V����
//=================================================================================
void CBg::Update(void)
{
}

//=================================================================================
// �`�揈��
//=================================================================================
void CBg::Draw(void)
{
//	// Renderer�N���X����f�o�C�X���擾
//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	
//	D3DMATERIAL9 matDef;					// ���݂̃}�e���A���ێ��p
//	D3DXMATERIAL* pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
//	DWORD ambient;
//
//	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
//	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
//
//	pDevice->LightEnable(0, FALSE);
//
//	// ���[���h�}�g���b�N�X�̏�����
//	D3DXMatrixIdentity(&m_mtxWorld);
//
//	//// �X�P�[���𔽉f
//	D3DXMatrixScaling(&mtxScale,
//		m_size.x,
//		m_size.y,
//		m_size.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);
//
//	// �����𔽉f
//	D3DXMatrixRotationYawPitchRoll(&mtxRot,
//		m_rot.y,
//		m_rot.x,
//		m_rot.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
//
//	// �ʒu�𔽉f
//	D3DXMatrixTranslation(&mtxTrans,
//		m_pos.x,
//		m_pos.y,
//		m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
//
//	// ���[���h�}�g���b�N�X�̐ݒ�
//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, m_apTexture[0]);
//
//	// ���݂̃}�e���A�����擾����
//	pDevice->GetMaterial(&matDef);
//
//	// �}�e���A���f�[�^�ւ̃|�C���^���擾
//	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
//	{
//		pMat[nCntMat].MatD3D.Ambient.r = 1.0f;
//		pMat[nCntMat].MatD3D.Ambient.g = 1.0f;
//		pMat[nCntMat].MatD3D.Ambient.b = 1.0f;
//		pMat[nCntMat].MatD3D.Ambient.a = 1.0f;
//
//		// �e�N�X�`���̐ݒ�
//		pDevice->SetTexture(0, m_apTexture[0]);
//
//		// �}�e���A���̐ݒ�
//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//
//		// ���f���p�[�c
//		m_pMesh->DrawSubset(nCntMat);
//	}
//
//	// �ێ����Ă����}�e���A����߂�
//	pDevice->SetMaterial(&matDef);
//
//	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
//	pDevice->LightEnable(0, TRUE);
//
//	// �e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, NULL);

	// �`�揈��
	CModel::Draw();
}