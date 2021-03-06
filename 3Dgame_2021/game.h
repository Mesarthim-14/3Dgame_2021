#ifndef _GAME_H_
#define _GAME_H_
//=============================================================================
//
// ゲームの処理 [game.h]
// Author : Konishi Yuuto
//
//=============================================================================

//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// マクロ定義
//***************************************************************************************
#define MAX_PLAYER (1)			// プレイヤーの数

//***************************************************************************************
// 前方宣言
//***************************************************************************************
class CCamera;
class CLight;
class CMeshField;
class CBg;
class CPlayer;
class CPause;
class CSea;

//***************************************************************************************
// ゲームクラス
//***************************************************************************************
class CGame : public CScene
{
public:
	CGame(PRIORITY Priority = PRIORITY_0);				// コンストラクタ
	~CGame();											// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);									// 終了処理
	void Update(void);									// 更新処理
	void Draw(void);									// 描画処理
	void SetGame(void);									// ゲームの設定

	static CGame* Create();								// ゲーム生成情報
	static CCamera *GetCamera(void);					// カメラのポインタ情報
	static CLight *GetLight(void);						// ライトのポインタ情報
	static CPlayer *GetPlayer(void);					// プレイヤーのポインタ情報
	static CPause *GetPause(void);						// ポーズ画面のポインタ情報
private:	
	static CCamera *m_pCamera;			// カメラのポインタ	
	static CLight *m_pLight;			// ライトのポインタ
	static CMeshField *m_pMeshField;	// メッシュフィールドのポインタ
	static CBg *m_pBg;					// 背景のポインタ
	static CPlayer *m_pPlayer;			// プレイヤーのポインタ
	static CSea *m_pSea;				// 海のポインタ
	static CPause *m_pPause;			// ポーズのポインタ
	LPD3DXFONT m_pFont;					// デバック用フォント
	int m_nTimeCounter;					// ゲームのカウンター
	bool m_bGameEnd;					// ゲームのエンドフラグ
};
#endif