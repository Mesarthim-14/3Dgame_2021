//=======================================================================================
// 
// 2Dポリゴン描画処理 [scene2d.h]
// Author : Konishi Yuuto
//
//=======================================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// クラス定義
//***************************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(PRIORITY Priority = PRIORITY_0);	// コンストラクタ
	~CScene2D();								// デストラクタ

	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// インスタンス生成
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// テクスチャの設定
	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);	// アニメーション情報初期化
	void InitScroll(int nSpeed, float fDivision);						// 画像スクロールの設定
	void UpdateAnimation(void);											// アニメーションの更新
	void UpdateScroll(void);											// 画像スクロールの更新
	void ScaleUp(float fScaleUp);										// 拡大関数

	// Set関数
	void SetPos(D3DXVECTOR3 pos);										// 座標の設定
	void SetSize(D3DXVECTOR3 size);										// サイズの設定
	void SetCol(D3DXCOLOR col);											// 色の設定
	void SetRotation(float rotasion);									// 回転の設定
	void SetScale(const float &fScale);										// 拡大の値設定

	// Get関数
	D3DXVECTOR3 GetPos(void)const { return m_pos; }						// 座標の情報
	D3DXVECTOR3 GetSize(void)const { return m_size; }					// サイズの情報
	D3DXCOLOR   GetCol(void) { return m_col; }							// 色の情報
	float GetScale(void) { return m_fScaleNum; }												// 拡大の値情報
private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						// ポリゴンの位置
	D3DXVECTOR3 m_size;						// ポリゴンのサイズ
	D3DXCOLOR   m_col;						// ポリゴンのカラー	
	D3DXVECTOR2 m_tex;						// テクスチャー設定
	int m_nCountAnim;						// アニメーションテクスチャ
	int m_nCountAnimPattern;				// アニメーションのパターン
	int m_nCounterAnim;						// アニメーションのカウンター
	int m_nPatternAnim;						// アニメーションのパターン数
	int m_nSpeedTexture;					// テクスチャの移動速度
	int m_nLoop;							// ループするかどうか
	float m_fDivisionCounter;				// スクロールのカウンター
	float m_fDivisionBaseNum;				// スクロールの移動量
	float m_fRotasion;						// 回転用変数
	float m_fScaleNum;						// 拡大用変数
};

#endif // !_SCENE2D_H_
