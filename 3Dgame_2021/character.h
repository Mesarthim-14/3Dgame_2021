#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//------------------------------------------------------------------------------
//
// キャラクター処理  [character.h]
// Author : Konishi Yuuto
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "modelanime.h"

//------------------------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------------------------
#define MAX_CHARACTER_PARTS (21)

//=============================================================================
//　モデルファイル情報の構造体
//=============================================================================
typedef struct
{
	char xFileName[1024];	//ファイルネーム
	D3DXVECTOR3 offsetPos;	//位置のオフセット情報
	D3DXVECTOR3 offsetRot;	//向きのオフセット情報
	int nParent;	//親情報
}MODELFILLE;

//=============================================================================
//　各要素のキー情報
//=============================================================================
typedef struct
{
	float fPosX;
	float fPosY;
	float fPosZ;
	float fRotX;
	float fRotY;
	float fRotZ;
}KEY;

//=============================================================================
//	キー情報の構造体
//=============================================================================
typedef struct
{
	int nFrame;	//フレーム数
	KEY aKey[MAX_CHARACTER_PARTS];	//各パーツのキー情報
}KEY_INFO;

//=============================================================================
//　モーション情報の構造体
//=============================================================================
typedef struct
{
	bool bLoop;	//ループするかどうか
	int nNumKey;	//キー数
	KEY_INFO aKeyInfo[20];	//キー情報
}Motion_Info;

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------

//キャラクターのクラス
class CCharacter : public CScene
{
public:
	typedef enum
	{
		STATE_NONE = 0,		// 初期値
		STATE_APPEAR,		// 出現
		STATE_NO_ACTIVE,	// 非戦闘状態
		STATE_NORMAL,		// 通常状態
		STATE_DAMAGE,		// ダメージ状態
	}STATE;

	CCharacter(int nPriority = PRIORITY_1);
	virtual ~CCharacter();

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// 初期化
	virtual void Uninit();									// 終了処理
	virtual void Update();									// 更新
	virtual void Draw();									// 描画

	virtual void UpdateMotion(void);							// モーションの更新の純粋仮想関数

																// 純粋仮想関数
	virtual void UpdateState(void) = 0;								// キャラクター状態
	virtual void UpdateMotionState(void) = 0;					// モーションの状態

	bool Gravity(void);											// 地面の制限
	HRESULT ReadFile(void);											// ファイルの読み込み

	// Set関数
	void SetCharacter(char *xfilename, int nPart, int nMotion);
	void SetPos(D3DXVECTOR3 pos);									// 座標の設定
	void SetPosOld(D3DXVECTOR3 posOld);								// 座標の設定
	void SetState(STATE state);										// プレイヤー情報の設定
	void SetMove(D3DXVECTOR3 move);									// 移動量の設定
	void SetRot(D3DXVECTOR3 rot);
	void SetAngle(float Angle);										// 角度の設定
	void SetLife(int nLife);										// ライフの設定
	void SetCountMotion(int CountMotion);							// モーションのカウント設定
	void SetMotionState(int nMotionState);
	void SetMotion(int nMotion);				// モーションの設定
	void SetKey(int nKey);
	void SetJump(bool bJump);										// ジャンプのフラグ
	void SetLanding(bool bLanding);									// 着地の設定
	// Get関数
	D3DXVECTOR3 GetPos(void) { return m_pos; }									// 現在の座標情報
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }								// 古い座標情報
	D3DXVECTOR3 GetRot(void) { return m_rot; }									// 角度情報
	D3DXVECTOR3 GetMove(void) { return m_move; }								// 移動量の情報
	STATE GetState(void) { return m_state; }									// プレイヤーの状態情報
	KEY_INFO *GetKeyInfo(void) { return m_apKeyInfo; }							// キー情報
	Motion_Info GetMotion(int nCount) { return m_Motion[nCount]; }				// モーション情報
	int GetLife(void) { return m_nLife; }										// ライフの情報
	int GetCountMotion(void) { return m_nCountMotion; }							// モーションのカウント
	int GetMotionState(void) { return m_nMotionState; }
	int GetKey(void) { return m_nKey; }
	float GetAngle(void) { return m_fAngle; }									// 角度の情報
	CModelAnime *GetModelAnime(int nCount) { return m_apModelAnime[nCount]; }	// モーションのカウント情報
	bool GetJump(void) { return m_bJump; }										// ジャンプ
	bool GetLanding(void) { return m_bLanding; }								// 着地のフラグ
private:
	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_posOld;					// 古い座標
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_rot;						// 現在の回転
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	STATE m_state;							// キャラクターの状態
	int m_nLife;							// 体力
	int m_nAttack;							// 攻撃力
	int m_nSpeed;							// 移動量
	int m_nPart;							// パーツ
	float m_fAngle;							// 角度
	bool m_bJump;							// ジャンプしているフラグ
	bool m_bLanding;						// 着地のフラグ

	// モデル用変数
	CModelAnime *m_apModelAnime[MAX_CHARACTER_PARTS];	// モデルパーツ用のポインタ
	MODELFILLE m_modelfile[MAX_CHARACTER_PARTS];		// モデルパーツ情報
	char *m_pFileName;									// ファイルの名前

	// モーション用変数
	Motion_Info m_Motion[30];		//モーション情報
	KEY_INFO *m_apKeyInfo;			// キー情報のポインタ
	int m_nMotionState;				// モーションの状態
	int m_nNumKey;					// キーの総数
	int m_nCountMotion;				// モーションカウンター
	int m_nMotionInterval;			// モーションのインターバル
	int m_nStateCounter;			// 状態のカウンター
	int m_nKey;						// 現在キーのNo
	bool m_bMotionPlaing;
};
#endif