//=============================================================================
//
// �p�[�e�B�N�������N���X [particle_factory.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "particle_factory.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PARTICLE_TEXTURE_NAME	("data/Text/particle.txt")

//=============================================================================
// static������
//=============================================================================
CParticleFactory::PARTICLE CParticleFactory::m_Particle[PARTICLE_NUM_MAX] = {};			// �p�[�e�B�N��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticleFactory::CParticleFactory()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticleFactory::~CParticleFactory()
{
}

//=============================================================================
// �p�[�e�B�N���̐���
//=============================================================================
void CParticleFactory::CreateParticle(D3DXVECTOR3 pos, PARTICLE_TYPE type)
{
	switch (type)
	{
	case PARTICLE_NUM_EXPLOSION:
		// �����������̃p�[�e�B�N������
		for (int nCount = 0; nCount < m_Particle[PARTICLE_NUM_EXPLOSION].nNum; nCount++)
		{
			CParticle::Create(pos, m_Particle[PARTICLE_NUM_EXPLOSION],
				CTexture::GetTexture(CTexture::TEXTURE_NUM_PARTICLE));
		}
		break;

	case PARTICLE_NUM_SWORD_SKILL:
		for (int nCount = 0; nCount < m_Particle[PARTICLE_NUM_SWORD_SKILL].nNum; nCount++)
		{
			// �\�[�h�X�L���������̃p�[�e�B�N������
			CParticle::Create(pos, m_Particle[PARTICLE_NUM_SWORD_SKILL],
				CTexture::GetTexture(CTexture::TEXTURE_NUM_SKILL_START));
		}
		break;

	case PARTICLE_NUM_SKILL_BLADE:
		for (int nCount = 0; nCount < m_Particle[PARTICLE_NUM_SKILL_BLADE].nNum; nCount++)
		{
			// �\�[�h�X�L�����̃p�[�e�B�N������
			CParticle::Create(pos, m_Particle[PARTICLE_NUM_SKILL_BLADE],
				CTexture::GetTexture(CTexture::TEXTURE_NUM_SKILL_START));
		}
		break;
	}
}

//=============================================================================
// �t�@�C���̓ǂݍ���
//=============================================================================
HRESULT CParticleFactory::ReadFile(void)
{
	FILE *pFile = NULL;		//FILE�|�C���^
	char aHeadData[1024];
	char aParticleName[1024];
	int nParticleIndex = 0;	// ���f���̃C���f�b�N�X

	// �t�@�C���I�[�v��
	pFile = fopen(PARTICLE_TEXTURE_NAME, "r");

	if (pFile != NULL)
	{
		do
		{
			//���ǂݍ���Ń��[�h���𒊏o
			fgets(aHeadData, sizeof(aHeadData), pFile);
			sscanf(aHeadData, "%s", aParticleName);

			if (strcmp(aParticleName, "PARTICLESET") == 0)
			{
				//�C���f�b�N�X���ŏ��ɖ߂�
				nParticleIndex = 0;

				//END_MOTIONSET��ǂݍ��ނ܂ŌJ��Ԃ�
				while (strcmp(aParticleName, "END_PARTICLESET") != 0)
				{
					//���ǂݍ���Ń��[�h���𒊏o
					fgets(aHeadData, sizeof(aHeadData), pFile);
					sscanf(aHeadData, "%s", aParticleName);

					if (strcmp(aParticleName, "EFFECTSET") == 0)
					{
						//END_PARTSSET��ǂݍ��ނ܂ŌJ��Ԃ�
						while (strcmp(aParticleName, "END_EFFECTSET") != 0)
						{
							//���ǂݍ���Ń��[�h���𒊏o
							fgets(aHeadData, sizeof(aHeadData), pFile);
							sscanf(aHeadData, "%s", aParticleName);

							if (strcmp(aParticleName, "SIZE") == 0)
							{
								// �T�C�Y�̐ݒ�
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Particle[nParticleIndex].size.x,
									&m_Particle[nParticleIndex].size.y,
									&m_Particle[nParticleIndex].size.z);
							}
							if (strcmp(aParticleName, "MOVE") == 0)
							{
								// �ړ���
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Particle[nParticleIndex].move.x,
									&m_Particle[nParticleIndex].move.y,
									&m_Particle[nParticleIndex].move.z);
							}
							if (strcmp(aParticleName, "DISTANCE") == 0)
							{
								// ����
								sscanf(aHeadData, "%*s %*s %f %f %f", 
									&m_Particle[nParticleIndex].Distance.x,
									&m_Particle[nParticleIndex].Distance.y, 
									&m_Particle[nParticleIndex].Distance.z);
							}
							if (strcmp(aParticleName, "LIFE") == 0)
							{
								// �̗�
								sscanf(aHeadData, "%*s %*s %d", &m_Particle[nParticleIndex].nLife);
							}
							if (strcmp(aParticleName, "NUM") == 0)
							{
								// ��
								sscanf(aHeadData, "%*s %*s %d", &m_Particle[nParticleIndex].nNum);
							}
							if (strcmp(aParticleName, "COLOR") == 0)
							{
								// �F
								sscanf(aHeadData, "%*s %*s %f %f %f %f", 
									&m_Particle[nParticleIndex].color.r,
									&m_Particle[nParticleIndex].color.g, 
									&m_Particle[nParticleIndex].color.b,
									&m_Particle[nParticleIndex].color.a);
							}
							if (strcmp(aParticleName, "GRAVITY") == 0)
							{
								// ��
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Particle[nParticleIndex].bGravity);
							}
							if (strcmp(aParticleName, "ALPHA") == 0)
							{
								// ��
								sscanf(aHeadData, "%*s %*s %d", (int*)&m_Particle[nParticleIndex].bAlpha);
							}
						}

						//�C���f�b�N�X���P�i�߂�
						nParticleIndex++;
					}
				}
			}

		} while (strcmp(aParticleName, "END_SCRIPT") != 0);

		//�t�@�C���N���[�Y
		fclose(pFile);

		return S_OK;
	}
	else
	{
		//���s�����ꍇ���b�Z�[�W�{�b�N�X��\��
		MessageBox(NULL, "���[�V�����t�@�C�����J���̂Ɏ��s���܂���", "�x��", MB_OK | MB_ICONEXCLAMATION);

		return	E_FAIL;
	}
}
