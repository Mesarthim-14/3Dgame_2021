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
#define GRAVITY_POWAR			(0.6f)						// 重力の強さ
#define GROUND_RIMIT			(0.0f)						// 地面の制限
#define STICK_SENSITIVITY		(50.0f)						// スティック感度
#define PLAYER_ROT_SPEED		(0.1f)						// キャラクターの回転する速度
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
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = PLAYER_STATE_NONE;
	memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	m_apKeyInfo = NULL;
	memset(&m_Motion, 0, sizeof(m_Motion));
	m_MotionState = MOTION_IDOL;
	m_nNumKey = 0;									//キーの総数
	m_nKey = 0;										//現在キーのNo
	m_nCountMotion = 0;								//モーションカウンター
	m_nMotionInterval = 0;							//モーションのインターバル
	m_bMotionPlaing = false;
	m_bJump = false;
	m_bArmor = false;
	m_nStateCounter = 0;
	m_bWalk = false;
	m_fAngle = 0.0f;
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
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_OldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//memset(m_apModelAnime, 0, sizeof(m_apModelAnime));
	//m_apKeyInfo = NULL;
	//memset(&m_Motion, 0, sizeof(m_Motion));
	//m_MotionState = MOTION_IDOL;
	//m_fAngle = 0.0f;

	////位置の設定
	//m_pos = pos;

	////ファイル読み込み
	//if (FAILED(ReadFile()))
	//{
	//	return E_FAIL;
	//}

	////モデルパーツ数分繰り返す
	//for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
	//{
	//	if (m_apModelAnime[nCntModel] == NULL)
	//	{
	//		//モデルの生成
	//		m_apModelAnime[nCntModel] = CModelAnime::Create(g_modelfile[nCntModel].xFileName,
	//			g_modelfile[nCntModel].offsetPos, g_modelfile[nCntModel].offsetRot);
	//	}
	//	//親子構造の設定
	//	if (m_apModelAnime[nCntModel] != NULL)
	//	{
	//		//親モデルの場合
	//		if (nCntModel == 0)
	//		{
	//			m_apModelAnime[nCntModel]->SetParent(NULL);
	//		}
	//		//子モデルの場合
	//		else
	//		{
	//			//自分の親情報を設定する
	//			m_apModelAnime[nCntModel]->SetParent(m_apModelAnime[g_modelfile[nCntModel].nParent]);
	//		}
	//	}
	//}

	////待機モーションの再生
	//SetMotion(MOTION_IDOL);

	////オブジェクトタイプの設定
	//SetObjType(CScene::OBJTYPE_PLAYER);

	CCharacter::SetCharacter(LBX_XFAILE_NAME, MAX_PARTS, MOTION_MAX);
	CCharacter::Init(pos, rot);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//for (int nCntModelNum = 0; nCntModelNum < MAX_MODEL_PARTS; nCntModelNum++)
	//{
	//	if (m_apModelAnime[nCntModelNum] != NULL)
	//	{
	//		//終了処理
	//		m_apModelAnime[nCntModelNum]->Uninit();

	//		//メモリの削除
	//		delete m_apModelAnime[nCntModelNum];

	//		//メモリのクリア
	//		m_apModelAnime[nCntModelNum] = NULL;
	//	}
	//}

	////オブジェクトの破棄
	//SetDeathFlag();

	
	CCharacter::Uninit();

}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボード更新
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	CCharacter::Update();

	// 古い座標取得
	m_OldPos = m_pos;

	// プレイヤーの状態
	PlayerState();

	// 重力をかける
	m_move.y -= GRAVITY_POWAR;
	m_pos.y += m_move.y;		// 落下

	// 地面の制限
	GroundLimit();

	// モーション状態
	MotionState();

	//アニメーションの更新処理
	UpdateMotion();

	// プレイヤーの制御
	PlayerControl();

	//位置へ移動量を加算
	m_pos += m_move;

	while (m_rotDest.y - m_rot.y > D3DXToRadian(180))
	{
		m_rotDest.y -= D3DXToRadian(360);
	}

	while (m_rotDest.y - m_rot.y < D3DXToRadian(-180))
	{
		m_rotDest.y += D3DXToRadian(360);
	}

	// キャラクター回転の速度
	m_rot += (m_rotDest - m_rot)*PLAYER_ROT_SPEED;
}

//=============================================================================
// アニメーションの更新処理
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	KEY *pKey[MAX_MODEL_PARTS];
	D3DXVECTOR3 diffPos, diffRot, startPos, startRot, setPos, setRot;

	//現在キーが最大キー数未満の場合
	if (m_nKey < m_Motion[m_MotionState].nNumKey)
	{
		for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
		{
			m_apKeyInfo = &m_Motion[m_MotionState].aKeyInfo[m_nKey];

			pKey[nCntModel] = &m_apKeyInfo->aKey[nCntModel];
		}

		for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
		{
			if (m_apModelAnime[nCntModel] != NULL)
			{
				D3DXVECTOR3 startPos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 startRot = m_apModelAnime[nCntModel]->GetRotAnime();

				//1フレーム当たりの更新値 = (終点位置-開始位置) / フレーム数
				diffPos.x = (pKey[nCntModel]->fPosX - startPos.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.y = (pKey[nCntModel]->fPosY - startPos.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffPos.z = (pKey[nCntModel]->fPosZ - startPos.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

				//1フレーム当たりの更新値 = (終点向き-開始向き) / フレーム数
				diffRot.x = (pKey[nCntModel]->fRotX - startRot.x) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.y = (pKey[nCntModel]->fRotY - startRot.y) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;
				diffRot.z = (pKey[nCntModel]->fRotZ - startRot.z) / (float)m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame;

				setPos.x = diffPos.x * m_nCountMotion + startPos.x;
				setPos.y = diffPos.y * m_nCountMotion + startPos.y;
				setPos.z = diffPos.z * m_nCountMotion + startPos.z;

				setRot.x = diffRot.x * m_nCountMotion + startRot.x;
				setRot.y = diffRot.y * m_nCountMotion + startRot.y;
				setRot.z = diffRot.z * m_nCountMotion + startRot.z;

				D3DXVECTOR3 pos = m_apModelAnime[nCntModel]->GetPosAnime();
				D3DXVECTOR3 rot = m_apModelAnime[nCntModel]->GetRotAnime();

				//位置に更新用の位置を加算
				pos += setPos;

				//向きに更新用の向きを加算
				rot += setRot;

				//位置の設定
				m_apModelAnime[nCntModel]->SetPosAnime(setPos);

				//向きの設定
				m_apModelAnime[nCntModel]->SetRotAnime(setRot);
			}
		}

		//モーションカウンターの加算
		m_nCountMotion++;

		//現在キーの再生フレームに達したら
		if (m_nCountMotion == m_Motion[m_MotionState].aKeyInfo[m_nKey].nFrame)
		{
			//キーを１つ進める
			m_nKey++;
			m_nCountMotion = 0;
		}
	}
	else
	{
		//ループするなら
		if (m_Motion[m_MotionState].bLoop == true)
		{
			m_nKey = 0;
		}
		else
		{
			m_nMotionInterval++;

			if (m_nMotionInterval == 10)
			{
				m_bMotionPlaing = false;

				if (m_MotionState != MOTION_WIN && m_MotionState != MOTION_LOSE)
				{
					//着地・攻撃・左右ブースト・ビームモーションの時かつ入力がtrue・ジャンプがfalse
					if ((m_MotionState == MOTION_LANDING || m_MotionState == MOTION_ATTACK ||
						m_MotionState == MOTION_LEFTBOOST || m_MotionState == MOTION_RIGHTBOOST ||
						m_MotionState == MOTION_BEAM)
						&& m_bJump == false)
					{
						SetMotion(MOTION_WALK);
					}
					else if (m_bJump == false)
					{
						SetMotion(MOTION_IDOL);
					}
				}
				else
				{
					return;
				}
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	//// 描画処理
	////デバイス情報の取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//D3DXMATRIX mtxRot, mtxTrans, mtxScale;

	////ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&m_mtxWorld);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);					// 裏面を（左回り）をカリング

	//for (int nCntModelNum = 0; nCntModelNum < MAX_MODEL_PARTS; nCntModelNum++)
	//{
	//	if (m_apModelAnime[nCntModelNum] != NULL)
	//	{
	//		//階層モデルクラスの描画処理
	//		m_apModelAnime[nCntModelNum]->Draw();
	//	}
	//}

	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);					// 裏面を（左回り）をカリング
	CCharacter::Draw();

}

//=============================================================================
// モーションセット処理
//=============================================================================
void CPlayer::SetMotion(MOTION_STATE motion)
{
	if (motion != MOTION_WIN && motion != MOTION_LOSE)
	{
		if (m_Motion[m_MotionState].bLoop == false &&
			m_bMotionPlaing == true && m_MotionState != MOTION_LANDING)
		{
			return;
		}
	}

	// 値の初期化
	m_nKey = 0;
	m_nCountMotion = 0;
	m_nMotionInterval = 0;
	D3DXVECTOR3 pos, rot;
	m_MotionState = motion;
	m_bMotionPlaing = true;

	for (int nCntModel = 0; nCntModel < MAX_MODEL_PARTS; nCntModel++)
	{
		if (m_apModelAnime[nCntModel] != NULL)
		{
			//開始位置
			pos.x = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			pos.y = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			pos.z = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;

			//開始向き
			rot.x = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
			rot.y = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
			rot.z = m_Motion[m_MotionState].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

			//位置の設定
			m_apModelAnime[nCntModel]->SetPosAnime(pos);

			//向きの設定
			m_apModelAnime[nCntModel]->SetRotAnime(rot);
		}
	}

	switch (m_MotionState)
	{
	case MOTION_IDOL:
		break;

	case MOTION_DAMAGE:

		// 無敵フラグ
		m_bArmor = true;
		break;
	default:
		break;
	}
}

//=============================================================================
// プレイヤーの状態
//=============================================================================
void CPlayer::PlayerState(void)
{
	CSound *pSound = CManager::GetSound();

	switch (m_state)
	{
	case PLAYER_STATE_NORMAL:
		// 通常状態

		break;

	case PLAYER_STATE_DAMAGE:

		// ダメージを受けたら
		m_nStateCounter++;

		// 一定以上で
		if (m_MotionState == MOTION_DAMAGE && m_bMotionPlaing == false)
		{
			m_nStateCounter = 0;
			m_state = PLAYER_STATE_NORMAL;
			m_bArmor = true;
		}
		break;
	default:
		break;
	}
}

//=============================================================================
// モーション状態
//=============================================================================
void CPlayer::MotionState(void)
{
	switch (m_MotionState)
	{
	case MOTION_IDOL:
		//	m_MotionState = MOTION_ATTACK;
		break;
	case MOTION_ATTACK:
		// 攻撃モーション
		if (m_nKey >= 1 && m_nKey <= 3)
		{

		}
		break;
	case MOTION_DAMAGE:
		
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
	m_fAngle = CGame::GetCamera()->Getφ();

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
			//ジャンプしていないとき
			if (m_bJump == false && m_bWalk == false)
			{
				// 歩き状態にする
				m_bWalk = true;

				//歩行モーションの再生
				SetMotion(MOTION_WALK);
			}

			//スティックXの入力が感度超えている
			if (js.lX < -STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(270.0f);

				m_pos.x += cosf(m_fAngle)* PLAYER_SPEED;
				m_pos.z -= sinf(m_fAngle)* PLAYER_SPEED;
			}
			else if (js.lX > STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(90.0f);

				m_pos.x -= cosf(m_fAngle)* PLAYER_SPEED;
				m_pos.z += sinf(m_fAngle)* PLAYER_SPEED;
			}
			else
			{
			}
			//スティックYの入力が感度を超えている
			if (js.lY < -STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle;

				m_pos.x -= sinf(m_fAngle)* PLAYER_SPEED;
				m_pos.z -= cosf(m_fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(315.0f);
				}
				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(45.0f);
				}
			}

			else if (js.lY > STICK_SENSITIVITY)
			{
				m_rotDest.y = m_fAngle + D3DXToRadian(180.0f);
				m_pos.x += sinf(m_fAngle)* PLAYER_SPEED;
				m_pos.z += cosf(m_fAngle)* PLAYER_SPEED;

				if (js.lX < -STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(225.0f);
				}

				else if (js.lX > STICK_SENSITIVITY)
				{
					m_rotDest.y = m_fAngle + D3DXToRadian(135.0f);
				}
			}
		}
		// Wキーを押したとき
		if (pKeyboard->GetPress(DIK_W))
		{
			m_rotDest.y = D3DXToDegree(m_fAngle);
			m_pos.z += cosf(0)*PLAYER_SPEED;
		}
		// Sキーを押したとき
		if (pKeyboard->GetPress(DIK_S))
		{
			m_rotDest.y = sin(m_fAngle);
			m_pos.z += cosf(D3DX_PI)*PLAYER_SPEED;
		}
		// Aキーを押したとき
		if (pKeyboard->GetPress(DIK_A))
		{
			m_pos.x += sinf(-D3DX_PI / 2)*PLAYER_SPEED;
		}
		// Dキーを押したとき
		if (pKeyboard->GetPress(DIK_D))
		{
			m_pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
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
}

//=============================================================================
// ジャンプ処理
//=============================================================================
void CPlayer::Jump(void)
{
	// サウンド情報
	CSound *pSound = CManager::GetSound();

	// キーボード情報
	CInputKeyboard *pKeyboard = CManager::GetKeyboard();

	// SPACEキーを押したとき・コントローラのYを押したとき
		if (CManager::GetJoypad()->GetJoystickTrigger(CInputJoypad::JOY_BUTTON_A, 0) && m_bJump == false	
			|| pKeyboard->GetTrigger(DIK_SPACE) && m_bJump == false)
	{
		// ジャンプの処理
		m_move.y = 0.0f;
		m_move.y = PLAYER_JUMP;
		m_bJump = true;
		m_bWalk = false;

		//ジャンプモーションの再生
		SetMotion(MOTION_JUMP);
		pSound->Play(CSound::SOUND_LABEL_SE_JUMP);
	}
}

//=============================================================================
// 地面の制限
//=============================================================================
void CPlayer::GroundLimit(void)
{
	// サウンド情報
	CSound *pSound = CManager::GetSound();

	// 着地の処理
	if (m_pos.y <= GROUND_RIMIT)
	{
		if (m_bJump == true)
		{
			SetMotion(MOTION_LANDING);
		}

		// 値代入
		m_move.y = 0.0f;
		m_pos.y = GROUND_RIMIT;
		m_bJump = false;
	}
}

//=============================================================================
// ファイル読み込み処理
//=============================================================================
//HRESULT CPlayer::ReadFile(void)
//{
//	//FILE *pFile = NULL;		//FILEポインタ
//	//char aHeadData[1024];
//	//char aModeName[1024];
//	//int nModelIndex = 0;	//モデルのインデックス
//	//int nMotionType = 0;	//モーションのタイプ
//	//int nKeyNum = 0;		//キー番号
//	//int nMotionNum = 0;		//モーション番号
//
//	//	//ファイルオープン
//	//	pFile = fopen(LBX_XFAILE_NAME, "r");
//
//	//if (pFile != NULL)
//	//{
//	//	do
//	//	{
//	//		//一列読み込んでモード情報を抽出
//	//		fgets(aHeadData, sizeof(aHeadData), pFile);
//	//		sscanf(aHeadData, "%s", aModeName);
//
//	//		if (strcmp(aModeName, "MODEL_FILENAME") == 0)
//	//		{
//	//			//Xファイルの名前
//	//			sscanf(aHeadData, "%*s %*s %s %*s %*s", g_modelfile[nModelIndex].xFileName);
//
//	//			//インデックスを１つ進める
//	//			nModelIndex++;
//	//		}
//
//	//		if (strcmp(aModeName, "CHARACTERSET") == 0)
//	//		{
//	//			//インデックスを最初に戻す
//	//			nModelIndex = 0;
//
//	//			//END_MOTIONSETを読み込むまで繰り返す
//	//			while (strcmp(aModeName, "END_CHARACTERSET") != 0)
//	//			{
//	//				//一列読み込んでモード情報を抽出
//	//				fgets(aHeadData, sizeof(aHeadData), pFile);
//	//				sscanf(aHeadData, "%s", aModeName);
//
//	//				if (strcmp(aModeName, "PARTSSET") == 0)
//	//				{
//	//					//END_PARTSSETを読み込むまで繰り返す
//	//					while (strcmp(aModeName, "END_PARTSSET") != 0)
//	//					{
//	//						//一列読み込んでモード情報を抽出
//	//						fgets(aHeadData, sizeof(aHeadData), pFile);
//	//						sscanf(aHeadData, "%s", aModeName);
//
//	//						if (strcmp(aModeName, "PARENT") == 0)
//	//						{
//	//							//親子情報の設定
//	//							sscanf(aHeadData, "%*s %*s %d", &g_modelfile[nModelIndex].nParent);
//	//						}
//	//						if (strcmp(aModeName, "POS") == 0)
//	//						{
//	//							//位置の設定
//	//							sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetPos.x,
//	//								&g_modelfile[nModelIndex].offsetPos.y, &g_modelfile[nModelIndex].offsetPos.z);
//	//						}
//	//						if (strcmp(aModeName, "ROT") == 0)
//	//						{
//	//							//向きの設定
//	//							sscanf(aHeadData, "%*s %*s %f %f %f", &g_modelfile[nModelIndex].offsetRot.x,
//	//								&g_modelfile[nModelIndex].offsetRot.y, &g_modelfile[nModelIndex].offsetRot.z);
//	//						}
//	//					}
//	//					//インデックスを１つ進める
//	//					nModelIndex++;
//	//				}
//	//			}
//	//		}
//
//	//		//モーションセット
//	//		if (strcmp(aModeName, "MOTIONSET") == 0)
//	//		{
//	//			//END_MOTIONSETを読み込むまで繰り返す
//	//			while (strcmp(aModeName, "END_MOTIONSET") != 0)
//	//			{
//	//				//一列読み込んでモード情報を抽出
//	//				fgets(aHeadData, sizeof(aHeadData), pFile);
//	//				sscanf(aHeadData, "%s", aModeName);
//
//	//				//ループ情報の取得
//	//				if (strcmp(aModeName, "LOOP") == 0)
//	//				{
//	//					sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].bLoop);
//	//				}
//
//	//				//キー情報の取得
//	//				if (strcmp(aModeName, "NUM_KEY") == 0)
//	//				{
//	//					sscanf(aHeadData, "%*s %*s %d", (int*)&m_Motion[nMotionType].nNumKey);
//	//				}
//
//	//				if (strcmp(aModeName, "KEYSET") == 0)
//	//				{
//	//					//END_KEYSETになるまで繰り返す
//	//					while (strcmp(aModeName, "END_KEYSET") != 0)
//	//					{
//	//						//一列読み込んでモード情報を抽出
//	//						fgets(aHeadData, sizeof(aHeadData), pFile);
//	//						sscanf(aHeadData, "%s", aModeName);
//
//	//						//フレーム数の取得
//	//						if (strcmp(aModeName, "FRAME") == 0)
//	//						{
//	//							sscanf(aHeadData, "%*s %*s %d", &m_Motion[nMotionType].aKeyInfo[nMotionNum].nFrame);
//	//						}
//
//	//						//各キーのオフセット情報の取得
//	//						if (strcmp(aModeName, "KEY") == 0)
//	//						{
//	//							//END_KEYになるまで繰り返す
//	//							while (strcmp(aModeName, "END_KEY") != 0)
//	//							{
//	//								//一列読み込んでモード情報を抽出
//	//								fgets(aHeadData, sizeof(aHeadData), pFile);
//	//								sscanf(aHeadData, "%s", aModeName);
//
//	//								//位置の取得
//	//								if (strcmp(aModeName, "POS") == 0)
//	//								{
//	//									sscanf(aHeadData, "%*s %*s %f %f %f",
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosX,
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosY,
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fPosZ);
//	//								}
//
//	//								//向きの取得
//	//								if (strcmp(aModeName, "ROT") == 0)
//	//								{
//	//									sscanf(aHeadData, "%*s %*s %f %f %f",
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotX,
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotY,
//	//										&m_Motion[nMotionType].aKeyInfo[nMotionNum].aKey[nKeyNum].fRotZ);
//	//								}
//	//							}
//	//							//読み終わったらカウントを1つ進める
//	//							nKeyNum++;
//	//						}
//	//					}
//	//					nKeyNum = 0;
//	//					nMotionNum++;
//	//				}
//	//			}
//	//			nMotionNum = 0;
//	//			nMotionType++;
//	//		}
//	//	} while (strcmp(aModeName, "END_SCRIPT") != 0);
//
//	//	//ファイルクローズ
//	//	fclose(pFile);
//
//	//	return S_OK;
//	//}
//	//else
//	//{
//	//	//失敗した場合メッセージボックスを表示
//	//	MessageBox(NULL, "モーションファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);
//
//	//	return	E_FAIL;
//	//}
//}

//=============================================================================
// ポジションの設定
//=============================================================================
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 状態の設定
//=============================================================================
void CPlayer::SetState(PLAYER_STATE state)
{
	m_state = state;
}

//=============================================================================
// 座標の情報
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 古い座標情報
//=============================================================================
D3DXVECTOR3 CPlayer::GetOldPos(void)
{
	return m_OldPos;
}

//=============================================================================
// 移動量の設定
//=============================================================================
void CPlayer::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//=============================================================================
// 移動量の情報
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//=============================================================================
// 回転量の情報
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// プレイヤー状態の情報
//=============================================================================
CPlayer::PLAYER_STATE CPlayer::GetState(void)
{
	return m_state;
}

//=============================================================================
// ジャンプフラグの情報
//=============================================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}