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
#include "life_bar.h"
#include "life_frame.h"
#include "collision.h"
#include "fade.h"
#include "sp_bar.h"
#include "ui_skill.h"
#include "light_effect.h"
#include "locus.h"
#include "particle.h"
#include "particle_factory.h"
#include "slashing_effect.h"
#include "guard_effect.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_SPEED				(20.0f)						// プレイヤーの移動量
#define PLAYER_AVOID_SPEED			(30.0f)						// プレイヤーの回避量
#define PLAYER_JUMP					(21.0f)						// ジャンプの処理
#define STICK_SENSITIVITY			(50.0f)						// スティック感度
#define PLAYER_ROT_SPEED			(0.1f)						// キャラクターの回転する速度
#define PLAYER_RADIUS				(150.0f)					// 半径の大きさ
#define PLAYER_PARTS				(22)						// プレイヤーのパーツ数
#define PLAYER_ARMOR_TIME			(50)						// 無敵時間
#define GAME_END_FLAME				(100)						// ゲームが終わるフレーム
#define MAX_SP_NUM					(300)						// SPの最大数
#define SKILL_SP_NUM				(100)						// スキルの消費ゲージ
#define BLADE_PARTICLE_INTER		(170)						// 刀身のパーティクルの間隔
#define WEAPON_TIP_NUM				(20)						// 剣先のパーツ番号
#define WEAPON_ROOT_NUM				(21)						// 剣の根元のパーツ番号
#define PLAYER_AVOID_FLAME			(20)						// 回避時間

#define LBX_XFAILE_NAME		"data/Text/motion_LBX.txt"		// LBXのファイルパス
#define GANDAMU_XFAILE_NAME "data/Text/motion_gandamu.txt"	// ガンダムのファイルパス

//=============================================================================
// グローバル変数宣言
//=============================================================================
MODELFILE g_modelfile[PLAYER_PARTS];	//モデルパーツ情報

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
CPlayer::CPlayer(PRIORITY Priority)
{
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bWalk = false;
	m_bDraw = true;
	m_nEndCounter = 0;
	m_pSpBar = NULL;
	m_pUiSkill = NULL;
	m_bUseLocusEffect = false;
	m_bAvoid = false;
	m_bArmor = false;
	m_nAvoidCounter = 0;
	m_pGuardEffect = NULL;
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
	CCharacter::SetCharaModel(LBX_XFAILE_NAME, PLAYER_PARTS, MOTION_MAX);			// モデルパーツ
	CCharacter::Init(pos, rot);														// 座標　角度
	SetRadius(PLAYER_RADIUS);														// 半径の設定
	SetCType(CHARACTER_TYPE_PLAYER);												// キャラクターのタイプ
	SetSpeed(PLAYER_SPEED);															// 速度の設定
	SetWeaponTipNum(PARTS_NUM_COLLISION);											// 剣先のパーツ番号
	SetWeaponRootNum(PARTS_NUM_ROOT);												// 剣の根本のパーツ番号
	LifeBarCreate(PLAYER_LIFE_FRAME_POS, PLAYER_LIFE_FRAME_SIZE,
		PLAYER_LIFE_BAR_POS, PLAYER_LIFE_BAR_SIZE,
		PLAYER_LIFE_BAR_COLOR, PLAYER_LIFE_NUM);									// ライフバーの生成

	// SPバーの生成
	if (m_pSpBar == NULL)
	{
		m_pSpBar = CSpBar::Create(PLAYER_SP_BAR_POS, PLAYER_SP_BAR_SIZE, MAX_SP_NUM);
	}

	// スキルのUI
	if (m_pUiSkill == NULL)
	{
		m_pUiSkill = CUiSkill::Create(UI_SKILL_POS, UI_SKILL_SIZE);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{	
	// 終了処理
	CCharacter::Uninit();

	if (m_pSpBar != NULL)
	{
		// 終了処理
		m_pSpBar->Uninit();
		m_pSpBar = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	if (m_bDraw == true)
	{
		// キーボード更新
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();

		// 親クラスの更新処理
		CCharacter::Update();

		// 座標代入
		D3DXVECTOR3 pos = GetPos();	// 現在の座標取得
		SetPosOld(pos);				// 古い座標保存

		// 剣の軌跡
		//SwordLocus();

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

		// 体力が0になったら
		if (GetLife() <= 0)
		{
			// 死んだとき
			Death();
		}
	}
	else
	{
		m_nEndCounter++;

		// ゲーム終了のフレーム
		if (m_nEndCounter >= GAME_END_FLAME)
		{
			// リザルト画面へ
			CManager::GetFade()->SetFade(CManager::MODE_TYPE_RESULT);
			m_nEndCounter = 0;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	if (m_bDraw == true)
	{
		// 描画処理
		CCharacter::Draw();
	}
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
	{
		// 状態カウンター取得
		int nStateCounter = GetStateCounter();

		// 一定時間経過したら
		if (nStateCounter >= PLAYER_ARMOR_TIME)
		{
			SetState(STATE_NORMAL);		// 通常状態に戻す
			SetArmor(false);			// 無敵状態解除
			SetStateCounter(0);			// 状態カウンターリセット
		}
	}

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
		//	state = MOTION_ATTACK;
		break;
	case MOTION_ATTACK:
		
		// 剣のエフェクト
		SwordLight();

		// 攻撃モーション
		if (nKey == 3)
		{
			if (m_bUseLocusEffect == false)
			{
				// 剣先の現在座標
				D3DXVECTOR3 Top = D3DXVECTOR3(
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
					GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

				// 軌跡のエフェクト生成
				CSlashingEffect::Create(Top, SLASHING_EFFECT_SIZE);
				m_bUseLocusEffect = true;
			}


			// 攻撃時の当たり判定
			if (AttackCollision() == true)
			{

			}
		}
		break;
		
		break;
	case MOTION_JUMP:
		// 着地しているとき
		if (GetLanding() == true)
		{
			// 通常に戻す
			SetMotion(MOTION_IDOL);
		}
		break;

	case MOTION_GUARD:
		break;
	}
}

//=============================================================================
// プレイヤーの制御
//=============================================================================
void CPlayer::PlayerControl()
{
	MOTION_STATE state = (MOTION_STATE)GetState();

	// やられ状態じゃないとき
	if (state != MOTION_DAMAGE)
	{
		// プレイヤーの移動処理
		Walk();

		// スキルの処理
		if (UseSkill() == false)
		{
			// ジャンプの処理
			Jump();

			// 攻撃の処理
			Attack();

			// ガードの処理
			Guard();

			// 回避の処理
			Avoid();
		}
	}

#ifdef _DEBUG
	// デバッグコマンド
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボード更新

	// Lボタンの時
	if (pKeyboard->GetTrigger(DIK_L))
	{
		// ダメージを与える
		AddDamage(20);
	}

#endif
}

//=============================================================================
// プレイヤー移動処理
//=============================================================================
void CPlayer::Walk(void)
{
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();	// キーボード更新
	DIJOYSTATE js = CInputJoypad::GetStick(0);				// ジョイパッドの取得
	CSound *pSound = CManager::GetSound();					// サウンドの情報

	// カメラ角度取得
	float fAngle = CGame::GetCamera()->Getφ();
	D3DXVECTOR3 pos = GetPos();

	if (GetMotionState() != MOTION_ATTACK && GetMotionState() != MOTION_GUARD && GetMotionState() != MOTION_DAMAGE)
	{
		//入力が存在する
		if ((js.lX != 0.0f || js.lY != 0.0f))
		{
			//ダメージを受けていないときのみ移動する
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

					pos.x += cosf(fAngle)* GetSpeed();
					pos.z -= sinf(fAngle)* GetSpeed();
				}
				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle + D3DXToRadian(90.0f);

					pos.x -= cosf(fAngle)* GetSpeed();
					pos.z += sinf(fAngle)* GetSpeed();
				}
				else
				{
				}
				//スティックYの入力が感度を超えている
				if (js.lY < -STICK_SENSITIVITY)
				{
					m_rotDest.y = fAngle;

					pos.x -= sinf(fAngle)* GetSpeed();
					pos.z -= cosf(fAngle)* GetSpeed();

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
					pos.x += sinf(fAngle)* GetSpeed();
					pos.z += cosf(fAngle)* GetSpeed();

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
		else
		{
			// 歩いていたら
			if (m_bWalk == true)
			{
				//待機モーションを再生
				SetMotion(MOTION_IDOL);
				m_bWalk = false;
			}
		}
	}

	// 状態の保存
	MOTION_STATE Motionstate = (MOTION_STATE)GetMotionState();	// モーション状態
	STATE state = (STATE)GetState();							// 状態

	//ダメージを受けていないときのみ移動する
	if (Motionstate != MOTION_DAMAGE && Motionstate != MOTION_JUMP && Motionstate != MOTION_ATTACK)
	{
		// 前に移動
		if (pKeyboard->GetPress(DIK_W))
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);

			pos.x -= sinf((CGame::GetCamera()->Getφ()))*GetSpeed();
			pos.z -= cosf((CGame::GetCamera()->Getφ()))*GetSpeed();
			m_rotDest.y = CGame::GetCamera()->Getφ();
			SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera()->Getφ(), GetRot().z));
		}
		// 後ろに移動
		if (pKeyboard->GetPress(DIK_S))
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);

			pos.x += sinf((CGame::GetCamera()->Getφ()))*GetSpeed();
			pos.z += cosf((CGame::GetCamera()->Getφ()))*GetSpeed();
			m_rotDest.y = CGame::GetCamera()->Getφ();
			SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera()->Getφ() + D3DXToRadian(-180.0f), GetRot().z));

		}
		// 左に移動
		if (pKeyboard->GetPress(DIK_A))
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);

			pos.x += sinf((CGame::GetCamera()->Getφ() + D3DXToRadian(90.0f)))*GetSpeed();
			pos.z += cosf((CGame::GetCamera()->Getφ() + D3DXToRadian(90.0f)))*GetSpeed();
			m_rotDest.y = CGame::GetCamera()->Getφ();
			SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera()->Getφ() + D3DXToRadian(-90.0f), GetRot().z));

		}
		// 右に移動
		if (pKeyboard->GetPress(DIK_D))
		{
			// 歩きモーション
			SetMotion(MOTION_WALK);

			pos.x += sinf((CGame::GetCamera()->Getφ() + D3DXToRadian(-90.0f)))*GetSpeed();
			pos.z += cosf((CGame::GetCamera()->Getφ() + D3DXToRadian(-90.0f)))*GetSpeed();
			m_rotDest.y = CGame::GetCamera()->Getφ();
			SetRot(D3DXVECTOR3(GetRot().x, CGame::GetCamera()->Getφ() + D3DXToRadian(90.0f), GetRot().z));

		}

		// 座標設定
		SetPos(pos);

		// 古い座標取得
		D3DXVECTOR3 OldPos = GetOldPos();

		// 動いていなかったら
		if (OldPos == pos)
		{
			// 通常モーション
			SetMotion(MOTION_IDOL);
		}
	}
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

//=============================================================================
// 死んだときの処理
//=============================================================================
void CPlayer::Death(void)
{
	m_bDraw = false;
}

//=============================================================================
// 攻撃の処理
//=============================================================================
void CPlayer::Attack(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// ENTERキーを押したとき・コントローラのXを押したとき
	if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_X, 0) 
		|| pKeyboard->GetTrigger(DIK_RETURN))
	{
		// 攻撃モーション
		SetMotion(MOTION_ATTACK);
	}
}

//=============================================================================
// ガードの処理
//=============================================================================
void CPlayer::Guard(void)
{
		// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// ガードの処理
	if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_B, 0) 
		|| pKeyboard->GetPress(DIK_G))
	{
		// ガードモーション
		SetMotion(MOTION_GUARD);

		// ガードエフェクトが使われていなかったら
		if (m_pGuardEffect == NULL)
		{
			m_pGuardEffect = CGuardEffect::Create(D3DXVECTOR3(GetPos().x, GetPos().y+200.0f, GetPos().z), GUARD_EFFECT_SIZE);
		}
	}
	else
	{
		// ガードエフェクトが使われていたら
		if (m_pGuardEffect != NULL)
		{
			// 終了処理
			m_pGuardEffect->Uninit();
			m_pGuardEffect = NULL;
		}

	}
}

//=============================================================================
// 回避の処理
//=============================================================================
void CPlayer::Avoid(void)
{
	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();
	DIJOYSTATE js = CInputJoypad::GetStick(0);				// ジョイパッドの取得

	float fAngle2 = atan2f(-(float)js.lX, (float)js.lY);
	float fAngle = CGame::GetCamera()->Getφ();

	D3DXVECTOR3 pos = GetPos();

	if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_Y, 0)
		|| pKeyboard->GetPress(DIK_T))
	{
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		SetMove(D3DXVECTOR3(
			sinf(fAngle +(fAngle2))*PLAYER_AVOID_SPEED,
			0.0f,
			cosf(fAngle + (fAngle2))*PLAYER_AVOID_SPEED));

		m_bAvoid = true;	// 回避
		SetArmor(true);		// 無敵時間
	}

	// 回避が使われたとき
	if (m_bAvoid == true)
	{
		m_nAvoidCounter++;
	}

	// 回避の時間
	if (m_nAvoidCounter >= PLAYER_AVOID_FLAME)
	{
		m_nAvoidCounter = 0;
		m_bAvoid = false;
		SetMotion(MOTION_IDOL);
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	// 無敵時間解除
	if (m_nAvoidCounter == 5)
	{
		SetArmor(false);		// 無敵時間
	}
}

//=============================================================================
// 剣のエフェクトの処理
//=============================================================================
void CPlayer::SwordLight(void)
{
	// 剣の根本と剣先のワールド座標取得
	D3DXVECTOR3 Root = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._43);

	D3DXVECTOR3 Tip = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

	//==========================================================
	// ベクトル求める
	//==========================================================
	// 2点間のベクトルを求める（終点[目標地点] - 始点[自身の位置]）
	D3DXVECTOR3 Vector = Tip - Root;

	// ベクトルの大きさを求める(√c^2 = a^2 * b^2)	長さ
	float fVectorSize = D3DXVec3Length(&Vector);

	//Root + Vector / ((fVectorSize / LIGHT_EFFECT_RADIAN) * nCount);
	
	for (int nCount = 0; nCount < fVectorSize / LIGHT_EFFECT_RADIAN_INTER; nCount++)
	{
		// 根元からのベクトルをnCountで分ける
		D3DXVECTOR3 pos = Root + (Vector / (fVectorSize / LIGHT_EFFECT_RADIAN_INTER)) * (float)nCount;

		if (int nNum = rand() % BLADE_PARTICLE_INTER == 0)
		{
			// ソードスキル時の刀身パーティクル
			CParticleFactory::CreateParticle(pos,
				CParticleFactory::PARTICLE_NUM_SKILL_BLADE);
		}

		// ソードエフェクト
		CLightEffect::Create(pos, LIGHT_EFFECT_SIZE, LIGHT_EFFECT_LIFE);
	}

}

//=============================================================================
// 剣の軌跡
//=============================================================================
void CPlayer::SwordLocus(void)
{
	// 原点の古い座標取得
	D3DXVECTOR3 OldOrigin = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetOldMtxWorld()._43);

	// 剣先の古い座標
	D3DXVECTOR3 OldTop = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetOldMtxWorld()._43);

	// 原点の現在座標
	D3DXVECTOR3 Origin = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_ROOT)->GetMtxWorld()._43);

	// 剣先の現在座標
	D3DXVECTOR3 Top = D3DXVECTOR3(
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._41,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._42,
		GetModelAnime(PARTS_NUM_COLLISION)->GetMtxWorld()._43);

	// 軌跡の生成
	CLocus::Create(Origin, Top, OldOrigin, OldTop,
		GetRot(), D3DXVECTOR3(LOCUS_SIZE_X, LOCUS_SIZE_Y, LOCUS_SIZE_Z),
		LOCUS_LIFE);
}

//=============================================================================
// スキルの使用処理
//=============================================================================
bool CPlayer::UseSkill(void)
{
	MOTION_STATE Motionstate = (MOTION_STATE)GetMotionState();	// モーション状態

	if (Motionstate != MOTION_ATTACK)
	{
		// キーボード情報
		CInputKeyboard *pKeyboard = CManager::GetKeyboard();

		// Kキーを押したとき・コントローラのR1を押したとき
		if (CManager::GetJoypad()->GetJoystickPress(CInputJoypad::JOY_BUTTON_R_TRIGGER, 0)
			|| pKeyboard->GetPress(DIK_RSHIFT))
		{
				// ソードスキル発生時のパーティクル
				CParticleFactory::CreateParticle(GetPos(),
					CParticleFactory::PARTICLE_NUM_SWORD_SKILL);

			if (m_pUiSkill != NULL)
			{
				// 使われてなかったら
				if (m_pUiSkill->GetUse() == false)
				{
					// スキルのUIを描画する
					m_pUiSkill->SetUse(true);
				}
			}
		
			// Kキーを押したとき・コントローラのBを押したとき
			if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_B, 0)
				|| pKeyboard->GetTrigger(DIK_1))
			{
				// SPバーが使われていたら
				if (m_pSpBar != NULL)
				{
					// ゲージが一定量以上だったら
					if (m_pSpBar->GetGage() >= SKILL_SP_NUM)
					{
						// 攻撃モーション
						SetMotion(MOTION_ATTACK);

						// SPバーのゲージを減らす
						m_pSpBar->SubGage(SKILL_SP_NUM);
					}
				}
			}

			return true;
		}
		else
		{
			if (m_pUiSkill != NULL)
			{
				// 使われてなかったら
				if (m_pUiSkill->GetUse() == true)
				{
					// スキルのUIを描画する
					m_pUiSkill->SetUse(false);
				}
			}

		}
	}

	return false;
}