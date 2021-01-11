#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// エネミークラスヘッダー [player.h]
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
#define MAX_PARTS			(10)		// パーツの数
#define MOTION_KEYSET_MAX	(32)		// キーセット最大数
#define ENEMY_SIZE_X		(1)			// サイズ
#define ENEMY_SIZE_Y		(1)			// サイズ
#define ENEMY_SIZE_Z		(1)			// サイズ
#define MAX_MODEL_PARTS		(21)		// モデルのパーツの最大数
#define ENEMY_COLLISION_X	(200)		// 当たり判定
#define ENEMY_COLLISION_Y	(175)		// 当たり判定
#define ENEMY_COLLISION_Z	(200)		// 当たり判定
#define ENEMY_RADIUS		(150)		// 半径

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
//　モーション状態の列挙型
//=============================================================================
typedef enum
{
	ENEMY_MOTION_NONE = -1,
	ENEMY_MOTION_IDOL,		//アイドルモーション
	ENEMY_MOTION_WALK,		//歩行モーション
	ENEMY_MOTION_ATTACK,		//攻撃モーション
	ENEMY_MOTION_JUMP,		//ジャンプモーション
	ENEMY_MOTION_LANDING,		//着地モーション
	ENEMY_MOTION_WIN,			//勝利モーション
	ENEMY_MOTION_RIGHTBOOST,	//右ブースト
	ENEMY_MOTION_LEFTBOOST,	//左ブースト
	ENEMY_MOTION_DAMAGE,		//やられ
	ENEMY_MOTION_BEAM,		//ビーム攻撃
	ENEMY_MOTION_LOSE,		//負けモーション
	ENEMY_MOTION_MAX,			//モーション最大数
}ENEMY_MOTION_STATE;

////=============================================================================
////　モデルファイル情報の構造体
////=============================================================================
//typedef struct
//{
//	char xFileName[1024];	//ファイルネーム
//	D3DXVECTOR3 offsetPos;	//位置のオフセット情報
//	D3DXVECTOR3 offsetRot;	//向きのオフセット情報
//	int nParent;	//親情報
//}ENEMY_MODELFILLE;
//
////=============================================================================
////　各要素のキー情報
////=============================================================================
//typedef struct
//{
//	float fPosX;
//	float fPosY;
//	float fPosZ;
//	float fRotX;
//	float fRotY;
//	float fRotZ;
//}ENEMY_KEY;
//
////=============================================================================
////	キー情報の構造体
////=============================================================================
//typedef struct
//{
//	int nFrame;	//フレーム数
//	ENEMY_KEY aKey[MAX_MODEL_PARTS];	//各パーツのキー情報
//}ENEMY_KEY_INFO;
//
////=============================================================================
////　モーション情報の構造体
////=============================================================================
//typedef struct
//{
//	bool bLoop;	//ループするかどうか
//	int nNumKey;	//キー数
//	ENEMY_KEY_INFO aKeyInfo[20];	//キー情報
//}ENEMY_Motion_Info;

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy : public CCharacter
{
public:
	typedef enum
	{
		ENEMY_STATE_NONE = 0,		// 初期置
		ENEMY_STATE_NORMAL,		// 通常状態
		ENEMY_STATE_DAMAGE,		// ダメージ
		ENEMY_STATE_EXPLOSION,		// 爆発
		ENEMY_STATE_DRAW,			// 引き分け
		ENEMY_STATE_MAX			// 最大数
	}ENEMY_STATE;

	CEnemy(int nPriority = PRIORITY_ENEMY);	// コンストラクタ
	~CEnemy();								// デストラクタ

	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// クリエイト

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void UpdateMotion(void);										// モーション更新処理
	void Draw(void);												// 描画処理
	void UpdateState(void);											// プレイヤーの状態
	void UpdateMotionState(void);											// モーション状態
	void GroundLimit(void);											// 地面の制限
	HRESULT ReadFile(void);											// ファイルの読み込み

	// Set関数
	void SetMotion(ENEMY_MOTION_STATE motion);							// モーションの設定
	void SetPos(D3DXVECTOR3 pos);									// 座標の設定
	void SetState(ENEMY_STATE state);								// プレイヤー情報の設定
	void SetMove(D3DXVECTOR3 move);									// 移動量の設定

	// Get関数
	bool GetJump(void);												// ジャンプの情報
	D3DXVECTOR3 GetPos(void);										// 現在の座標情報
	D3DXVECTOR3 GetOldPos(void);									// 古い座標情報
	D3DXVECTOR3 GetRot(void);										// 角度情報
	D3DXVECTOR3 GetMove(void);										// 移動量の情報
private:
	MODELFILLE m_modelfile[MAX_MODEL_PARTS];	//モデルファイル情報

	D3DXVECTOR3 m_pos;								// 座標
	D3DXVECTOR3 m_OldPos;							// 1フレーム前の座標
	D3DXVECTOR3 m_rot;								// 回転(現在地)
	D3DXVECTOR3 m_rotDest;							// 回転(目標値)
	D3DXVECTOR3 m_move;								// 移動
	ENEMY_STATE m_state;							// プレイヤー状態
	D3DXMATRIX m_mtxWorld;							// ワールドマトリックス
	CModelAnime *m_apModelAnime[MAX_MODEL_PARTS];	// モデルパーツ用のポインタ
	KEY_INFO *m_apKeyInfo;							// キー情報のポインタ
	ENEMY_MOTION_STATE m_MotionState;						// モーションの状態
	Motion_Info m_Motion[ENEMY_MOTION_MAX];				// モーション情報
	int m_nNumKey;									// キーの総数
	int m_nCountMotion;								// モーションカウンター
	int m_nMotionInterval;							// モーションのインターバル
	int m_nStateCounter;							// 状態のカウンター
	float m_fAngle;									// 角度
	bool m_bMotionPlaing;
};
#endif