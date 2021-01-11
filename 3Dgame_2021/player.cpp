//=============================================================================
//
// プレイヤークラス [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include <stdio.h>
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "input.h"
#include "joypad.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED			(20.0f)						// プレイヤーの移動量
#define PLAYER_JUMP				(21.0f)						// ジャンプの処理
#define STICK_SENSITIVITY		(50.0f)						// スティック感度
#define PLAYER_ROT_SPEED		(0.1f)						// キャラクターの回転する速度
#define PLAYER_PARTS			(21)						// プレイヤーのパーツ数
#define LBX_XFAILE_NAME "data/Text/motion_LBX.txt"			// LBXのファイルパス
#define GANDAMU_XFAILE_NAME "data/Text/motion_gandamu.txt"	// ガンダムのファイルパス

//=============================================================================
// グローバル変数宣言
//=============================================================================
MODELFILLE g_modelfile[MAX_MODEL_PARTS];	//モデルパーツ情報

//=============================================================================
// static初期化
//=============================================================================

//=============================================================================
// クリエイト
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 初期化処理
	CPlayer *pPlayer = new CPlayer;

	// 初期化処理
	pPlayer->Init(pos, size);

	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority)
{
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MotionState = MOTION_IDOL;
	m_bArmor = false;
	m_bWalk = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 初期化処理
	CCharacter::SetCharacter(LBX_XFAILE_NAME, PLAYER_PARTS, MOTION_MAX);
	CCharacter::Init(pos, rot);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{	
	CCharacter::Uninit();

}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// 親クラスの更新処理
	CCharacter::Update();

	// 座標代入
	D3DXVECTOR3 pos = GetPos();		// 現在の座標取得
	SetPosOld(pos);					// 古い座標保存

	// プレイヤーの状態
	UpdateState();

	// モーション状態
	UpdateMotionState();

	// プレイヤーの制御
	PlayerControl();

	// 角度の取得
	D3DXVECTOR3 rot = GetRot();

	while (m_rotDest.y - rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	rot += (m_rotDest - rot)*PLAYER_ROT_SPEED;

	// 角度の設定
	SetRot(rot);
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}

//=============================================================================
// プレイヤーの状態
//=============================================================================
void CPlayer::UpdateState(void)
{
	STATE state = GetState();

	switch (state)
	{
	case STATE_NORMAL:
		// 通常状態

		break;

	case STATE_DAMAGE:

		//// ダメージを受けたら
		//m_nStateCounter++;

		//// 一定以上で
		//if (m_MotionState == MOTION_DAMAGE && m_bMotionPlaing == false)
		//{
		//	m_nStateCounter = 0;
		//	SetState(PLAYER_STATE_NORMAL);
		//	m_bArmor = true;
		//}
		break;
	default:
		break;
	}
}

//=============================================================================
// モーション状態
//=============================================================================
void CPlayer::UpdateMotionState(void)
{
	MOTION_STATE MotionState = (MOTION_STATE)GetMotionState();

	int nKey = GetKey();

	switch (MotionState)
	{
	case MOTION_IDOL:
		//	m_MotionState = MOTION_ATTACK;
		break;
	case MOTION_ATTACK:
		// 攻撃モーション
		if (nKey >= 1 && nKey <= 3)
		{

		}
		break;
	case MOTION_DAMAGE:
		
		break;
	case MOTION_JUMP:
		// 着地しているとき
		if (GetLanding() == true)
		{
				// 通常に戻す
				SetMotion(MOTION_IDOL);
		}
		break;
	}


}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer::PlayerControl()
{
	if (m_MotionState != MOTION_DAMAGE)
	{
		// プレイヤーの移動処理
		Walk();

		// ジャンプの処理
		Jump();
	}
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボード更新
	DIJOYSTATE js = CInputJoypad::GetStick(0);				// ジョイパッドの取得
	CSound *pSound = CManager::GetSound();					// サウンドの情報

	//カメラ角度取得
//	m_fAngle = CGame::GetCamera()->Getφ();
	float fAngle = CGame::GetCamera()->Getφ();
	D3DXVECTOR3 pos = GetPos();

	if (pKeyboard->GetTrigger(DIK_I) ||
		CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_L_TRIGGER, 0))
	{
		//攻撃モーションを再生
		SetMotion(MOTION_ATTACK);
		pSound->Play(CSound::SOUND_LABEL_SE_SLASH);
	}
	//入力が存在する
	if ((js.lX != 0.0f || js.lY != 0.0f ))
	{
		//ダメージを受けていないときのみ移動する
		if (m_MotionState != MOTION_DAMAGE)
		{
			bool bJump = GetJump();
			//ジャンプしていないとき
			if (bJump == false && m_bWalk == false)
			{
				// 歩き状態にする
				m_bWalk = true;

				//歩行モーションの再生
				SetMotion(MOTION_WALK);
			}

			//スティックXの入力が感度超えている
			if (js.lX < -STICK_SENSITIVITY)
			{
				m_rotDest.y = fAngle + D3DXToRadian(270.0f);

				pos.x += cosf(fAngle)* PLAYER_SPEED;
				pos.z -= sinf(fAngle)* PLAYER_SPEED;
			}
			else if (js.lX > STICK_SENSITIVITY)
			{
				m_rotDest.y = fAngle + D3DXToRadian(90.0f);

				pos.x -= cosf(fAngle)* PLAYER_SPEED;
				pos.z += sinf(fAngle)* PLAYER_SPEED;
			}
			else
			{
			}
			//スティックYの入力が感度を超えている
			if (js.lY < -STICK_SENSITIVITY)
			{
				m_rotDest.y = fAngle;

				pos.x -= sinf(fAngle)* PLAYER_SPEED;
				pos.z -= cosf(fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(315.0f);
				}
				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(45.0f);
				}
			}

			else if (js.lY > STICK_SENSITIVITY)
			{
				m_rotDest.y = fAngle + D3DXToRadian(180.0f);
				pos.x += sinf(fAngle)* PLAYER_SPEED;
				pos.z += cosf(fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(225.0f);
				}

				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(135.0f);
				}
			}
		}
		// Wキーを押したとき
		if (pKeyboard->GetPress(DIK_W))
		{
			m_rotDest.y = D3DXToDegree(fAngle);
			pos.z += cosf(0)*PLAYER_SPEED;
		}
		// Sキーを押したとき
		if (pKeyboard->GetPress(DIK_S))
		{
			m_rotDest.y = sin(fAngle);
			pos.z += cosf(D3DX_PI)*PLAYER_SPEED;
		}
		// Aキーを押したとき
		if (pKeyboard->GetPress(DIK_A))
		{
			pos.x += sinf(-D3DX_PI / 2)*PLAYER_SPEED;
		}
		// Dキーを押したとき
		if (pKeyboard->GetPress(DIK_D))
		{
			pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
		}
	}
	else
	{
		if (m_bWalk == true)
		{
			//待機モーションを再生
			SetMotion(MOTION_IDOL);
			m_bWalk = false;
		}
	}

	SetPos(pos);
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::Jump(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	bool bJump = GetJump();
	// SPACEキーを押したとき・コントローラのYを押したとき
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && bJump == false
			|| pKeyboard->GetTrigger(DIK_SPACE) && bJump == false)
	{
		D3DXVECTOR3 move = GetMove();
		move.y = PLAYER_JUMP;
		SetMove(move);
		SetJump(true);
		m_bWalk = false;

		//ジャンプモーションの再生
		SetMotion(MOTION_JUMP);
		SetLanding(false);
	}
}