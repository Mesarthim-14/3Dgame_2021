//=============================================================================
//
//  [title.h]
// Author : 佐藤颯紀
//
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_
//***************************************************************************************
// インクルードファイル
//***************************************************************************************
#include "scene.h"

class CScene2D;
class CTitlelogo;

//***************************************************************************************
// マクロ定義
//***************************************************************************************
#define MAX_TITLE (3)

//***************************************************************************************
// タイトルクラス
//***************************************************************************************
class CTitle : public CScene
{
public:
	CTitle(int nPriority = PRIORITY_0);
	~CTitle();
	static CTitle* Create(void);
	static HRESULT Load(void);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CTitlelogo *GetLogo(int nCount) { return m_apTitlelogo[nCount]; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[1];	//テクスチャへのポインタ
	CScene2D* m_pScene;	//ポインタ
	bool m_bModechenge;
	static CTitlelogo *m_apTitlelogo[MAX_TITLE];			//タイトルロゴのポインタ
};

#endif // !_TITEL_H_