//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bg.h"
#include "billboard.h"
#include "fade.h"
#include "fire.h"
#include "game.h"
#include "input.h"
#include "joypad.h"
#include "keyboard.h"
#include "manager.h"
#include "meshfield.h"
#include "model.h"
#include "particle_factory.h"
#include "player.h"
#include "renderer.h"
#include "result.h"
#include "scene3D.h"
#include "sound.h"
#include "texture.h"
#include "title.h"
#include "tutorial.h"
#include "xfile.h"

//=============================================================================
//静的メンバ変数宣言
//=============================================================================
CManager::MODE_TYPE CManager::m_mode = CManager::MODE_TYPE_TITLE;
CRenderer *CManager::m_pRenderer = NULL;	//レンダラークラスのポインタ変数
CInputKeyboard *CManager::m_pInput = NULL;//入力処理クラスのポインタ変数
CConection *CManager::m_pConection = NULL;
CFade *CManager::m_pFade = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CInputJoypad *CManager::m_pJoypad = NULL;
CSound *CManager::m_pSound = NULL;			//サウンドクラスのポインタ
CScene *CManager::m_pScene = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダラークラスのインスタンス生成
	m_pRenderer = new CRenderer;

	//メモリが確保できたら
	if (m_pRenderer != NULL)
	{
		// 初期化処理
		if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
		{
			return -1;
		}
	}

	//入力処理クラスのインスタンス生成
	m_pInput = new CInputKeyboard;

	//メモリが確保できたら
	if (m_pInput != NULL)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//入力処理クラスのインスタンス生成
	m_pJoypad = new CInputJoypad;

	//メモリが確保できたら
	if (m_pJoypad != NULL)
	{
		if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
		{
			return -1;
		}
	}

	//サウンドのインスタンス生成
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	//ライブラリ生成
	if (FAILED(InitImgui(hWnd)))
	{
		return E_FAIL;
	}

	//フェードクラスのクリエイト
	m_pFade = CFade::Create();

	//全テクスチャの読み込み
	LoadAll();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//全テクスチャの破棄
	UnLoadAll();
	
	if (m_pFade != NULL)
	{
		//フェードクラスの終了処理呼び出し
		m_pFade->Uninit();

		//メモリの破棄
		delete m_pFade;

		//メモリのクリア
		m_pFade = NULL;
	}

	if (m_pInput != NULL)
	{
		//入力処理クラスの終了処理呼び出し
		m_pInput->Uninit();

		//メモリの削除
		delete m_pInput;

		//メモリのクリア
		m_pInput = NULL;
	}

	if (m_pJoypad != NULL)
	{
		//入力処理クラスの終了処理呼び出し
		m_pJoypad->Uninit();

		//メモリの削除
		delete m_pInput;

		//メモリのクリア
		m_pJoypad = NULL;
	}

	if (m_pRenderer != NULL)
	{
		//レンダラークラスの終了処理呼び出し
		m_pRenderer->Uninit();

		//メモリの削除
		delete m_pRenderer;

		//メモリのクリア
		m_pRenderer = NULL;
	}

	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	if (m_pInput != NULL)
	{
		//入力処理クラスの更新処理呼び出し
		m_pInput->Update();
	}

	if (m_pJoypad != NULL)
	{
		//入力処理クラスの更新処理呼び出し
		m_pJoypad->Update();
	}

	if (m_pRenderer != NULL)
	{
		//レンダラークラスの更新処理呼び出し
		m_pRenderer->Update();
	}

	if (m_pFade != NULL)
	{
		//フェードクラスの更新処理呼び出し
		m_pFade->Update();
	}
}

//=============================================================================
//描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//レンダラークラスの描画処理呼び出し
		m_pRenderer->Draw();
	}
}

//=============================================================================
//テクスチャの全ロード処理
//=============================================================================
void CManager::LoadAll(void)
{
	CResult::Load();
	CMeshField::Load();
	CTutorial::Load();
	CTexture::Load();
	CXfile::ModelLoad();
	CParticleFactory::ReadFile();
}

//=============================================================================
//テクスチャの全アンロード処理
//=============================================================================
void CManager::UnLoadAll(void)
{
	CMeshField::UnLoad();
	CTexture::UnLoad();
	CXfile::ModelUnLoad();
}

//=============================================================================
//ゲームモードの設定処理
//=============================================================================
void CManager::SetMode(MODE_TYPE mode)
{
	CSound *pSound = CManager::GetSound();

	//現在モードの終了
	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			m_pTitle = NULL;
		}
		break;

	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			pSound->Stop(CSound::SOUND_LABEL_BGM_TITLE);
			m_pTutorial = NULL;
		}
		break;

	case MODE_TYPE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			pSound->Stop(CSound::SOUND_LABEL_BGM_GAME);
			m_pGame = NULL;
		}
		break;

	case MODE_TYPE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;

	}

	CScene::ReleaseAll();

	//モードを設定
	m_mode = mode;

	//設定されたモードをクリエイト
	switch (m_mode)
	{
	case MODE_TYPE_TITLE:
		if (m_pTitle == NULL)
		{
			m_pTitle = CTitle::Create();
		}
		
		break;

	case MODE_TYPE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = CTutorial::Create();
		}

		break;

	case MODE_TYPE_GAME:
		if (m_pGame == NULL)
		{
			m_pGame = CGame::Create();
		}

		break;

	case MODE_TYPE_RESULT:
		if (m_pGame == NULL)
		{
			m_pResult = CResult::Create();
		}

	default:
		break;
	}
}

//------------------------------------------------------------------------------
//Imgui初期化
//------------------------------------------------------------------------------
HRESULT CManager::InitImgui(HWND hWnd)
{
	//ゲームパッドとキーボードの情報取得
	m_pInput = CManager::GetKeyboard();

	//NULLチェック
	if (!m_pInput)
	{
		return E_FAIL;
	}

	//create
	IMGUI_CHECKVERSION();

	//生成
	ImGui::CreateContext();

	//デフォルトカラー設定
	ImGui::StyleColorsDark();

	//初期化
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(CManager::GetRenderer()->GetDevice());


//	ImGui::Begin("config 1");
//
//	ImGui::End();

	return S_OK;
}

//------------------------------------------------------------------------------
//Imgui終了
//------------------------------------------------------------------------------
void CManager::UninitImgui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
//------------------------------------------------------------------------------
//Imgui デバッグ情報表示
//------------------------------------------------------------------------------
void CManager::ShowDebugInfo()
{
#ifdef _DEBUG




	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	////開始
	//if (ImGui::CollapsingHeader("Debug"))
	//{
	//	//FPS情報
	//	if (ImGui::TreeNode("FPS"))
	//	{
	//		//FPS
	//		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//		ImGui::TreePop();
	//	}


	//	//情報
	//	if (ImGui::TreeNode("DebugCommand"))
	//	{
	//		//ライティング
	//		if (ImGui::Checkbox("Lighting", &m_Lighting))
	//		{
	//			pDevice->SetRenderState(D3DRS_LIGHTING, m_Lighting);		// ライティングモード切り替え
	//		}

	//		//カリング
	//		if (ImGui::TreeNode("tree1", "CULLING"))
	//		{
	//			if (ImGui::RadioButton("D3DCULL_CCW", &m_Culling, 0))
	//			{
	//				//裏面カリング
	//				CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);
	//			}
	//			ImGui::SameLine();
	//			if (ImGui::RadioButton("D3DCULL_CW", &m_Culling, 1))
	//			{
	//				//表面カリング
	//				CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CW);
	//			}
	//			ImGui::SameLine();
	//			if (ImGui::RadioButton("D3DCULL_NONE", &m_Culling, 2))
	//			{
	//				//カリングしない
	//				CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);
	//			}
	//			ImGui::TreePop();
	//		}
	//		//プレイヤーデバッグ
	//		if (ImGui::Checkbox("DebugPlayer", &m_bDebugPlayer))
	//		{

	//		}
	//		ImGui::TreePop();
	//	}
	//}

#endif //DEBUG
}

//=============================================================================
//ゲームモード情報の取得
//=============================================================================
CManager::MODE_TYPE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
//レンダラー情報取得
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}


//=============================================================================
//キーボード情報取得
//=============================================================================
CInputKeyboard * CManager::GetKeyboard(void)
{
	return m_pInput;
}

CConection *CManager::GetConection(void)
{
	return m_pConection;
}

//=============================================================================
//フェード情報取得
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
//ジョイパッド情報取得
//=============================================================================
CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad;
}

//=============================================================================
//ジョイパッド情報取得
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}
