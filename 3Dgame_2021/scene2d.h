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
	CScene2D(int nPriority = PRIORITY_0);
	~CScene2D();
	static CScene2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }
	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);			// アニメーション情報初期化
	void InitScroll(int nSpeed, float fDivision);								// 画像スクロールの設定
	void UpdateAnimation(void);													// アニメーションの更新
	void UpdateScroll(void);													// 画像スクロールの更新
	void SetPos(const D3DXVECTOR3 pos) { m_pos = pos; }
	void SetPolygonSize(const D3DXVECTOR3 nSize) { m_size = nSize; }
	void SetCol(D3DXCOLOR col);
	void SetRotation(float rotasion);
	D3DXVECTOR3 GetPos(void)const { return m_pos; }
	D3DXVECTOR3 GetSize(void)const { return m_size; }
	D3DXCOLOR   GetCol(void) { return m_col; }
private:
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 // 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						// ポリゴンの位置
	D3DXVECTOR3 m_size;				// ポリゴンのサイズ
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
	float m_fRotasion;
};

#endif // !_SCENE2D_H_
