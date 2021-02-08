#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//=============================================================================
//
// 3Dポリゴンクラスヘッダー [scene3D.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=========================================================================
// インクルード
//=========================================================================
#include "scene.h"

//=========================================================================
// マクロ定義
//=========================================================================

//=========================================================================
// 3Dポリゴンクラス
//=========================================================================
class CScene3D :public CScene
{
public:
	CScene3D(PRIORITY Priority = PRIORITY_0);	// コンストラクタ
	virtual ~CScene3D();						// デストラクタ
	
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	virtual void Uninit(void);									// 終了処理
	virtual void Update(void);									// 更新処理
	virtual void Draw(void);									// 描画処理

	void SetPos(D3DXVECTOR3 pos);								// 座標の設定
	void SetPosision(D3DXVECTOR3 pos);							// 座標の更新
	void SetColor(D3DXCOLOR col);								// カラーの設定
	void SetRot(D3DXVECTOR3 rot);								// 角度の設定
	void Alpha(void);											// 透明度
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// テクスチャの設定

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);					// バッファ情報
	D3DXVECTOR3 GetPos(void);									// 座標
private:
	LPDIRECT3DTEXTURE9 m_pTexture;				// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファポインタ
	D3DXMATRIX	m_mtxWorld;						// ワールドマトリクス
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_size;							// サイズ
	D3DXVECTOR3 m_rot;							// 向き
};
#endif