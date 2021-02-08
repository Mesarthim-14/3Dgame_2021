//=============================================================================
//
// 蟹エネミークラス [crab.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "crab.h"
#include "manager.h"
#include "renderer.h"
#include "life_frame.h"
#include "life_bar.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CRAB_XFAILE_NAME "data/Text/crab_motion.txt"		// LBXのファイルパス
#define CRAB_LIFE				(120)						// 蟹の体力
#define CRAB_RADIUS				(200.0f)					// 蟹の大きさ
#define CRAB_SPEED				(15.0f)						// 蟹の速さ
#define CRAB_ATTACK_INTER		(300)						// 攻撃の間隔
#define CRAB_ATTACK_PARTS_NUM	(7)							// 攻撃のパーツ番号
#define CRAB_WEAPON_RADIUS		(200.0f)					// 武器の半径
#define CRAB_ARMOR_FLAME		(50)						// 無敵時間のフレーム
#define CRAB_ATTACK_POWAR		(20)						// 攻撃力

//=============================================================================
// コンストラクタ
//=============================================================================
CCrab::CCrab(int nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CCrab::~CCrab()
{
}

//=============================================================================
// オブジェクト生成
//=============================================================================
CCrab * CCrab::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// メモリ確保
	CCrab *pCrab = new CCrab;

	// 初期化処理
	pCrab->Init(pos, rot);

	return pCrab;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCrab::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	SetCharaModel(CRAB_XFAILE_NAME, MAX_CRAB_PARTS, ENEMY_MOTION_MAX);	// モデルの処理
	CEnemy::Init(pos, rot);												// 初期化処理
	SetLife(CRAB_LIFE);													// ライフの生成
	SetRadius(CRAB_RADIUS);												// 半径の設定
	SetSpeed(CRAB_SPEED);												// 速さの設定
	SetActive(true);													// 敵視するかの設定
	SetAttackInter(CRAB_ATTACK_INTER);									// 攻撃の間隔を設定
	SetWeaponTipNum(CRAB_ATTACK_PARTS_NUM);								// 攻撃パーツの番号を設定
	SetWeaponRadius(CRAB_WEAPON_RADIUS);								// 武器の半径
	SetArmorFlame(CRAB_ARMOR_FLAME);									// 無敵時間の設定
	SetAttackPower(CRAB_ATTACK_POWAR);									// 攻撃力の設定
	LifeBarCreate(ENEMY_LIFE_FRAME_POS, ENEMY_LIFE_FRAME_SIZE, 
	ENEMY_LIFE_BAR_POS, ENEMY_LIFE_BAR_SIZE,
	ENEMY_LIFE_BAR_COLOR, CRAB_LIFE);									// ライフバーの生成
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCrab::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCrab::Update(void)
{
	// 更新処理
	CEnemy::Update();

	// 座標代入
	D3DXVECTOR3 pos = GetPos();		// 現在の座標取得
	SetPosOld(pos);					// 古い座標保存

	// 状態更新
	UpdateState();

	// モーション状態
	UpdateMotionState();
}

//=============================================================================
// 描画処理
//=============================================================================
void CCrab::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}