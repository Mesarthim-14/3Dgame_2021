//=====================================================
//
// ビルボードクラス [billboard.cpp]
// Author : 小西優斗
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "billboard.h"
#include "manager.h"
#include "renderer.h"

//=====================================================
// コンストラクタ
//=====================================================
CBillboard::CBillboard(PRIORITY Priority) : CScene(Priority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置情報
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動量
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// サイズ
	m_sizeBase = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ベースのサイズ
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// カラーの設定
	m_Dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 方向7
	m_pVtxBuff = NULL;								// 頂点バッファへのポインタ
	m_pTexture = NULL;								// ポリゴンのテクスチャ
	m_nLife = 0;									// 寿命
	m_bUse = false;									// 使用判定
	m_nCountAnim = 0;;								// アニメーションテクスチャ
	m_nCountAnimPattern = 0;						// アニメーションのパターン
	m_nCounterAnim = 0;								// アニメーションのカウンター
	m_nPatternAnim = 0;								// アニメーションのパターン数
	m_nLoop = -1;									// ループするか
	m_bAlpha = false;								// アルファテストのフラグ
}

//=====================================================
// デストラクタ
//=====================================================
CBillboard::~CBillboard()
{

}

//=====================================================
// 初期化処理
//=====================================================
HRESULT CBillboard::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	// 情報の代入
	m_pos = pos;
	m_size = size;
	m_sizeBase = size;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(- m_size.x / 2, + m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x / 2, + m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x / 2, - m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x / 2, - m_size.y / 2, 0.0f);

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの設定（0～255の数値で設定）
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャの設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=====================================================
// 終了処理
//=====================================================
void CBillboard::Uninit(void)
{	
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクト破棄
	Release();
}

//=====================================================
// 更新処理
//=====================================================
void CBillboard::Update(void)
{
	// 移動量加算
	m_pos += m_move;

	// アニメーションの設定がされたとき
	if (m_nPatternAnim != 0)
	{
		// アニメーションを更新する
		UpdateAnimation();
	}

	// 体力を減らしていく
	m_nLife--;

	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();
	}
}

//=====================================================
// 描画処理
//=====================================================
void CBillboard::Draw(void)
{
	// デバイス情報取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成を行う
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// aデスティネーションカラー

	D3DMATERIAL9 material, OldMaterial;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Ambient = m_color;
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pDevice->GetMaterial(&OldMaterial);
	pDevice->SetMaterial(&material);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0x44444444);

	// 光の影響を無くす
	DWORD ambient;
	pDevice->GetRenderState(D3DRS_AMBIENT, &ambient);
	pDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	pDevice->LightEnable(0, FALSE);

	// アルファテストを有力化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// アルファテストが有効なら
	if (m_bAlpha == true)
	{
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0xC0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}
	else
	{
		// アルファテスト基準値の設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, 45);
	}

	//計算用のマトリクス
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// サイズを反映
	D3DXMatrixScaling(&mtxScale,
		m_size.x / m_sizeBase.x,
		m_size.y / m_sizeBase.y,
		0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 回転の逆行列の生成
	pDevice->GetTransform(D3DTS_VIEW, &mtxRot);
	D3DXMatrixInverse(&m_mtxWorld, NULL,
		&mtxRot);

	m_mtxWorld._41 = 0;
	m_mtxWorld._42 = 0;
	m_mtxWorld._43 = 0;

	// 位置を反映、ワールドマトリクス設定、ポリゴン描画
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリクスの設定 初期化、向き、位置
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, NULL);

	// アルファテストが有効でなかったら
	if (m_bAlpha != true)
	{
		// アルファテスト基準値の設定
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	}

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// aデスティネーションカラー

	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);

	pDevice->SetMaterial(&OldMaterial);					// マテリアルを元に戻す

//	pDevice->SetRenderState(D3DRS_AMBIENT, ambient);
	pDevice->LightEnable(0, TRUE);
}

//=============================================
// アニメーション情報取得
//=============================================
void CBillboard::InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop)
{
	// 値の代入
	m_nCounterAnim = nCounterAnim;
	m_nPatternAnim = nPatternAnim;
	m_nLoop = nLoop;

	// 頂点情報を設定
	VERTEX_3D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標を更新
	pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================
// アニメーション更新関数
//=============================================
void CBillboard::UpdateAnimation(void)
{
	// 爆発のアニメーションカウントを進めて、パターンを切り替える
	m_nCountAnim++;

	// 頂点情報(テクスチャ座標)の更新
	if (m_nCountAnim >= m_nCounterAnim)	// 爆発の速さ
	{
		// アニメーションのカウントを0にする
		m_nCountAnim = 0;

		// アニメーションのパターンをカウントさせる
		m_nCountAnimPattern++;
	}

	// アニメーションが終わったら
	if (m_nCountAnimPattern >= m_nPatternAnim)
	{
		// 数値を戻しておく
		m_nCountAnimPattern = 0;

		if (m_nLoop == 0)
		{
			// 終了処理
			Uninit();
		}
	}
	else
	{
		// 頂点情報を設定
		VERTEX_3D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標を更新
		pVtx[0].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 0.0f);
		pVtx[2].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((float)(1.0f / m_nPatternAnim)*(float)m_nCountAnimPattern + (float)(1.0f / m_nPatternAnim), 1.0f);

		// 頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=====================================================
// 位置の設定
//=====================================================
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定の設定
	pVtx[0].pos = D3DXVECTOR3(- m_size.x / 2, + m_size.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x / 2, + m_size.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x / 2, - m_size.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x / 2, - m_size.y / 2, 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//=====================================================
// 移動量設定
//=====================================================
void CBillboard::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=====================================================
// サイズ設定
//=====================================================
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=====================================================
// ベースサイズ設定
//=====================================================
void CBillboard::SetSizeBase(D3DXVECTOR3 sizeBase)
{
	m_sizeBase = sizeBase;
}

//=====================================================
// 色の設定
//=====================================================
void CBillboard::SetColor(D3DXCOLOR color)
{
	// カラーの設定
	m_color = color;
}

//=====================================================
// 体力の設定
//=====================================================
void CBillboard::SetLife(int nLife)
{
	m_nLife = nLife;
}

//=====================================================
// アルファテストの設定
//=====================================================
void CBillboard::SetAlpha(bool bAlpha)
{
	m_bAlpha = bAlpha;
}

//=====================================================
// 位置の取得
//=====================================================
D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}

//=====================================================
// 移動量情報
//=====================================================
D3DXVECTOR3 CBillboard::GetMove(void)
{
	return m_move;
}

//=====================================================
// サイズ情報
//=====================================================
D3DXVECTOR3 CBillboard::GetSize(void)
{
	return m_size;
}

//=====================================================
// 体力の設定
//=====================================================
int CBillboard::GetLIfe(void)
{
	return m_nLife;
}

//=====================================================
// テクスチャの設定
//=====================================================
void CBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================
// バッファの情報
//=============================================
LPDIRECT3DVERTEXBUFFER9 CBillboard::GetBuff(void)
{
	return m_pVtxBuff;
}