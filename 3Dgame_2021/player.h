#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"
#include "modelanime.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LIFE_NUM			(2)			// 表示するライフの数
#define MAX_PARTS			(10)		// パーツの数
#define MOTION_KEYSET_MAX	(32)		// キーセット最大数
#define PLAYER2_POS_X		(0.0f)		// 座標
#define PLAYER2_POS_Y		(171.0f)	// 座標
#define PLAYER2_POS_Z		(500)		// 座標
#define PLAYER_SIZE_X		(1)			// サイズ
#define PLAYER_SIZE_Y		(1)			// サイズ
#define PLAYER_SIZE_Z		(1)			// サイズ
#define MAX_MODEL_PARTS		(21)		// モデルのパーツの最大数
#define PLAYER_COLLISION_X	(200)		// 当たり判定
#define PLAYER_COLLISION_Y	(175)		// 当たり判定
#define PLAYER_COLLISION_Z	(200)		// 当たり判定
#define WEAPON_COLLISION_X	(150)		// 武器の当たり判定
#define WEAPON_COLLISION_Y	(150)		// 武器の当たり判定
#define WEAPON_COLLISION_Z	(150)		// 武器の当たり判定
#define PLAYER_RADIUS		(150)		// 半径

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
//　モーション状態の列挙型
//=============================================================================
typedef enum
{
	MOTION_NONE = -1,
	MOTION_IDOL,		//アイドルモーション
	MOTION_WALK,		//歩行モーション
	MOTION_ATTACK,		//攻撃モーション
	MOTION_JUMP,		//ジャンプモーション
	MOTION_LANDING,		//着地モーション
	MOTION_WIN,			//勝利モーション
	MOTION_RIGHTBOOST,	//右ブースト
	MOTION_LEFTBOOST,	//左ブースト
	MOTION_DAMAGE,		//やられ
	MOTION_BEAM,		//ビーム攻撃
	MOTION_LOSE,		//負けモーション
	MOTION_MAX,			//モーション最大数
}MOTION_STATE;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter
{
public:

	typedef enum
	{
		PLAYER_STATE_NONE = 0,		// 初期置
		PLAYER_STATE_NORMAL,		// 通常状態
		PLAYER_STATE_DAMAGE,		// ダメージ
		PLAYER_STATE_EXPLOSION,		// 爆発
		PLAYER_STATE_DRAW,			// 引き分け
		PLAYER_STATE_MAX			// 最大数
	}PLAYER_STATE;

	CPlayer(int nPriority = PRIORITY_PLAYER);	// コンストラクタ
	~CPlayer();									// デストラクタ

	static CPlayer*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// クリエイト

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void UpdateState(void);											// プレイヤーの状態
	void UpdateMotionState(void);											// モーション状態
	void PlayerControl(void);										// プレイヤーの制御
	void Walk(void);												// プレイヤーの歩く処理
	void Jump(void);												// ジャンプの処理

private:
	D3DXVECTOR3 m_rotDest;							// 回転(目標値)
	MOTION_STATE m_MotionState;						// モーションの状態
	bool m_bArmor;									// 無敵時間
	bool m_bWalk;									// 歩いているフラグ
};
#endif