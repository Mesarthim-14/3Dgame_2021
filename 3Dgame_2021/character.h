#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//------------------------------------------------------------------------------
//
// キャラクター処理  [character.h]
// Author:Yoshiki Hosoya
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

	static CCharacter *Create(char *xfilename, D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPart);
	HRESULT ReadFile(void);											// ファイルの読み込み

	void SetCharacter(char *xfilename, int nPart, int nMotion);

private:
	CModelAnime *m_apModelAnime[MAX_CHARACTER_PARTS];	// モデルパーツ用のポインタ
	MODELFILLE m_modelfile[MAX_CHARACTER_PARTS];		// モデルパーツ情報

	D3DXVECTOR3 m_pos;						// 座標
	D3DXVECTOR3 m_posOld;					// 古い座標
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_rot;						// 現在の回転
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	STATE m_State;							// キャラクターの状態
	int m_nLife;							// 体力
	int m_nAttack;							// 攻撃力
	int m_nSpeed;							// 移動量
	int m_nPart;							// パーツ
	char *m_pFileName;							// ファイルの名前
	Motion_Info m_Motion[30];		//モーション情報
};
#endif