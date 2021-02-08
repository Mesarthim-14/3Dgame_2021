#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//=====================================================
//
// ビルボードクラスヘッダー [billboard.h]
// Author : 小西優斗
//
//=====================================================

//=====================================================
// インクルード
//=====================================================
#include "scene.h"
//=====================================================
// マクロ定義
//=====================================================
#define BILLBOARD_SIZE_X	(25)	// 大きさ
#define BILLBOARD_SIZE_Y	(25)	// 大きさ

//=====================================================
// ビルボードクラス
//=====================================================
class CBillboard : public CScene
{
public:
	CBillboard(PRIORITY Priority = PRIORITY_0);		// コンストラクタ
	~CBillboard();								// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// 初期化処理
	virtual void Uninit(void);													// 終了処理
	virtual void Update(void);													// 更新処理
	virtual void Draw(void);													// 描画処理
	
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// テクスチャの設定
	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);	// アニメーション情報初期化
	void UpdateAnimation(void);											// アニメーションの更新
	
	// Set関数
	void SetPos(D3DXVECTOR3 pos);										// 座標の設定
	void SetMove(D3DXVECTOR3 move);										// 移動量設定
	void SetSize(D3DXVECTOR3 size);										// サイズ設定
	void SetSizeBase(D3DXVECTOR3 sizeBase);								// サイズのベース
	void SetColor(D3DXCOLOR color);										// 色の設定
	void SetLife(int nLife);											// 体力の設定
	void SetAlpha(bool bAlpha);											// アルファテストの設定
	
	// Get関数
	D3DXVECTOR3 GetPos(void);											// 座標情報
	D3DXVECTOR3 GetMove(void);											// 移動量情報
	D3DXVECTOR3 GetSize(void);											// サイズ情報
	int GetLIfe(void);													// 体力の情報
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void);								// バッファの情報

private:
	D3DXVECTOR3 m_pos;									// 位置情報
	D3DXVECTOR3 m_move;									// 移動量
	D3DXVECTOR3 m_size;									// サイズ
	D3DXVECTOR3 m_Dir;									// 方向7
	D3DXVECTOR3 m_sizeBase;								// サイズのベース
	D3DXCOLOR m_color;									// カラーの設定
	D3DXMATRIX m_mtxWorld;								// 行列計算用
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;						// ポリゴンのテクスチャ
	int m_nLife;										// 寿命
	int m_nCountAnim;									// アニメーションテクスチャ
	int m_nCountAnimPattern;							// アニメーションのパターン
	int m_nCounterAnim;									// アニメーションのカウンター
	int m_nPatternAnim;									// アニメーションのパターン数
	int m_nLoop;										// ループするか
	bool m_bUse;										// 使用判定
	bool m_bAlpha;										// アルファテストを使用するか
};

#endif