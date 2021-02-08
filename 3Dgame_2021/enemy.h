#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// エネミークラスヘッダー [enemy.h]
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
	ENEMY_MOTION_IDOL,			// アイドルモーション
	ENEMY_MOTION_WALK,			// 歩行モーション
	ENEMY_MOTION_ATTACK,		// 攻撃モーション
	ENEMY_MOTION_DAMAGE,		// やられ
	ENEMY_MOTION_LOSE,			// 負けモーション
	ENEMY_MOTION_MAX,			// モーション最大数
}ENEMY_MOTION_STATE;

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy : public CCharacter
{
public:
	CEnemy(PRIORITY Priority = PRIORITY_CHARACTER);	// コンストラクタ
	~CEnemy();								// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void UpdateState(void);										// プレイヤーの状態
	void UpdateMotionState(void);								// モーション状態
	void Perception(void);										// プレイヤーを感知
	void Death(void);											// 死んだときの処理
	void Attack(void);											// 攻撃の処理
	static CEnemy*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);	// クリエイト

	// Set関数
	void SetActive(bool bActive);								// プレイヤー感知の設定
	void SetAttackInter(int nAttackInter);						// 攻撃の間隔設定
	void SetArmorFlame(int nArmorFlame);						// 無敵時間のフレーム

	// Get関数
	int GetAttackInter(void) { return m_nAttackInter; }			// 攻撃カウントの情報
	int ArmotFlame(void) { return m_nArmorFlame; }				// アーマーのフレーム
private:
	ENEMY_MOTION_STATE m_MotionState;	// モーションの状態
	int m_nAttackInter;					// 攻撃の間隔
	int m_nAttackFlameCnt;				// 攻撃のフレームカウント
	int m_nArmorFlame;					// 無敵時間の設定
	bool m_bActive;						// 敵がプレイヤーを感知するか
	bool m_bRange;						// 攻撃が届く範囲のフラグ
	bool m_bAttack;						// 攻撃の行うフラグ
};
#endif