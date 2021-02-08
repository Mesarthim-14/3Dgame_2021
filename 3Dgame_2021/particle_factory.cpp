//=============================================================================
//
// パーティクル生成クラス [particle_factory.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "particle_factory.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PARTICLE_TEXTURE_NAME	("data/Text/particle.txt")

//=============================================================================
// static初期化
//=============================================================================
CParticleFactory::PARTICLE CParticleFactory::m_Particle[PARTICLE_NUM_MAX] = {};			// パーティクル

//=============================================================================
// コンストラクタ
//=============================================================================
CParticleFactory::CParticleFactory()
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CParticleFactory::~CParticleFactory()
{
}

//=============================================================================
// パーティクルの生成
//=============================================================================
void CParticleFactory::CreateParticle(D3DXVECTOR3 pos, PARTICLE_TYPE type)
{
	switch (type)
	{
	case PARTICLE_NUM_EXPLOSION:
		// 爆発生成時のパーティクル生成
		for (int nCount = 0; nCount < m_Particle[PARTICLE_NUM_EXPLOSION].nNum; nCount++)
		{
			CParticle::Create(pos, m_Particle[PARTICLE_NUM_EXPLOSION],
				CTexture::GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
		}
		break;

	case PARTICLE_NUM_SWORD_SKILL:
		for (int nCount = 0; nCount < m_Particle[PARTICLE_NUM_SWORD_SKILL].nNum; nCount++)
		{
			// ソードスキル発生時のパーティクル生成
			CParticle::Create(pos, m_Particle[PARTICLE_NUM_SWORD_SKILL],
				CTexture::GetTexture(CTexture::TEXTURE_NUM_SKILL_START));
		}
		break;

	case PARTICLE_NUM_SKILL_BLADE:
		for (int nCount = 0; nCount < m_Particle[PARTICLE_NUM_SKILL_BLADE].nNum; nCount++)
		{
			// ソードスキル時のパーティクル生成
			CParticle::Create(pos, m_Particle[PARTICLE_NUM_SKILL_BLADE],
				CTexture::GetTexture(CTexture::TEXTURE_NUM_SKILL_START));
		}
		break;
	}
}

//=============================================================================
// ファイルの読み込み
//=============================================================================
HRESULT CParticleFactory::ReadFile(void)
{
	FILE *pFile = NULL;		//FILEポインタ
	char aHeadData[1024];
	char aParticleName[1024];
	int nParticleIndex = 0;	// モデルのインデックス

	// ファイルオープン
	pFile = fopen(PARTICLE_TEXTURE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//一列読み込んでモード情報を抽出
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aParticleName);

			if (strcmp(aParticleName, "PARTICLESET") == 0)
			{
				//インデックスを最初に戻す
				nParticleIndex = 0;

				//END_MOTIONSETを読み込むまで繰り返す
				while (strcmp(aParticleName, "END_PARTICLESET") != 0)
				{
					//一列読み込んでモード情報を抽出
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aParticleName);

					if (strcmp(aParticleName, "EFFECTSET") == 0)
					{
						//END_PARTSSETを読み込むまで繰り返す
						while (strcmp(aParticleName, "END_EFFECTSET") != 0)
						{
							//一列読み込んでモード情報を抽出
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aParticleName);

							if (strcmp(aParticleName, "SIZE") == 0)
							{
								// サイズの設定
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Particle[nParticleIndex].size.x,
									&m_Particle[nParticleIndex].size.y,
									&m_Particle[nParticleIndex].size.z);
							}
							if (strcmp(aParticleName, "MOVE") == 0)
							{
								// 移動量
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Particle[nParticleIndex].move.x,
									&m_Particle[nParticleIndex].move.y,
									&m_Particle[nParticleIndex].move.z);
							}
							if (strcmp(aParticleName, "DISTANCE") == 0)
							{
								// 距離
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Particle[nParticleIndex].Distance.x,
									&m_Particle[nParticleIndex].Distance.y, 
									&m_Particle[nParticleIndex].Distance.z);
							}
							if (strcmp(aParticleName, "LIFE") == 0)
							{
								// 体力
								sscanf(aHeadData, "%*s %*s %d", &m_Particle[nParticleIndex].nLife);
							}
							if (strcmp(aParticleName, "NUM") == 0)
							{
								// 数
								sscanf(aHeadData, "%*s %*s %d", &m_Particle[nParticleIndex].nNum);
							}
							if (strcmp(aParticleName, "COLOR") == 0)
							{
								// 色
								sscanf(aHeadData, "%*s %*s %f %f %f %f", 
									&m_Particle[nParticleIndex].color.r,
									&m_Particle[nParticleIndex].color.g, 
									&m_Particle[nParticleIndex].color.b,
									&m_Particle[nParticleIndex].color.a);
							}
							if (strcmp(aParticleName, "GRAVITY") == 0)
							{
								// 数
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Particle[nParticleIndex].bGravity);
							}
							if (strcmp(aParticleName, "ALPHA") == 0)
							{
								// 数
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Particle[nParticleIndex].bAlpha);
							}
						}

						//インデックスを１つ進める
						nParticleIndex++;
					}
				}
			}

		} while (strcmp(aParticleName, "END_SCRIPT") != 0);

		//ファイルクローズ
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//失敗した場合メッセージボックスを表示
		MessageBox(NULL, "モーションファイルを開くのに失敗しました", "警告", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}
