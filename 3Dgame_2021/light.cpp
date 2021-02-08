//=============================================================================
//
// メイン処理 [light.cpp]
// Author : 山田陵太
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//ライトクラスのコンストラクタ
//=============================================================================
CLight::CLight()
{
	//メモリの0クリア
	SecureZeroMemory(&m_Light, sizeof(D3DLIGHT9));
}

//=============================================================================
//ライトクラスのデストラクタ
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
//ライトクラスの初期化処理
//=============================================================================
HRESULT CLight::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ライトをクリアする
	SecureZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	//ライトタイプの指定
	m_Light.Type = D3DLIGHT_DIRECTIONAL;

	//光の拡散の指定
	m_Light.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	//m_Light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	//ライト方向の指定
	m_vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//正規化する（大きさ1のベクトルにする必要がある）
	D3DXVec3Normalize(&m_vecDir, &m_vecDir);

	m_Light.Direction = m_vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &m_Light);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	return S_OK;
}

//=============================================================================
//ライトクラスの終了処理
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
//ライトクラスの更新処理
//=============================================================================
void CLight::Update(void)
{
}

//-----------------------------------------------------------------------------
// ライトの情報
//-----------------------------------------------------------------------------
void CLight::ShowLightInfo()
{
	//if (ImGui::CollapsingHeader("LightInfo"))
	//{
	//	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	//	if (ImGui::TreeNode("Light0"))
	//	{
	//		ImGui::SliderFloat3("direction", m_vecDir, -1.0f, 1.0f);

	//		D3DXVec3Normalize(&m_vecDir, &m_vecDir);		//正規化
	//		m_Light.Direction = m_vecDir;

	//		pDevice->SetLight(0, &m_Light);
	//		ImGui::TreePop();
	//	}
	//}
}