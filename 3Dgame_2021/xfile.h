#ifndef _XFILE_H_
#define _XFILE_H_
//=============================================================================
//
// Xファイル管理ヘッダー [xfile.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_XFILE_TEXTURE	(256)		// テクスチャの最大
#define MAX_NAME_NUM		(1024)		// 名前の最大

//=============================================================================
//クラス宣言
//=============================================================================
class CXfile
{
public:
	// テクスチャの番号の列挙型
	typedef enum
	{
		XFILE_NUM_NONE = -1,			// 初期値
		XFILE_NUM_BG,					// 背景
		XFILE_NUM_SWORD_EFFECT,			// 剣のエフェクト
		XFILE_NUM_SWORD_LOCUS_EFFECT,	// 剣の軌跡エフェクト
		XFILE_NUM_GUARD_EFFECT,			// ガードのエフェクト
		XFILE_NUM_MAX
	}XFILE_NUM;

	typedef struct
	{
		char xFileName[1024];								// ファイルネーム
		LPD3DXMESH pMesh;									// メッシュ情報へのポインタ
		LPD3DXBUFFER pBuffMat;								// マテリアル情報へのポインタ
		DWORD dwNumMat;										// マテリアル情報の数
		LPDIRECT3DTEXTURE9 apTexture[MAX_XFILE_TEXTURE];	// テクスチャの数
	}MODEL;

	CXfile();		// コンストラクタ
	~CXfile();		// デストラクタ

	static HRESULT ModelLoad(void);				// モデルロード
	static void ModelUnLoad(void);				// モデルアンロード

	// Get関数
	static MODEL GetXfile(XFILE_NUM Tex_Num);		// モデルの情報
	static LPDIRECT3DTEXTURE9 *GetXfileTexture(XFILE_NUM TexNum);	// モデルに使用するテクスチャ情報
private:
	static MODEL m_aXfile[XFILE_NUM_MAX];			// Xファイル情報の構造体
};
#endif
