#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// テクスチャの管理ヘッダー [texture.h]
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
#define MAX_TEXTURE (256)

using FILENAME_LIST = std::vector<std::string>;		//ファイル名のリスト

//=============================================================================
//クラス宣言
//=============================================================================
class CTexture
{
public:

	// テクスチャの番号の列挙型
	typedef enum
	{
		TEXTURE_NUM_NONE = -1,		// 初期値
		TEXTURE_NUM_FIRE,			// 炎
		TEXTURE_NUM_BG,				// 背景
		TEXTURE_NUM_LIFEBAR,		// ライフの枠
		TEXTURE_NUM_LIFEGAGE,		// ライフのゲージ
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	static HRESULT Load(void);										// テクスチャロード
	static void UnLoad(void);										// テクスチャアンロード
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);		// テクスチャの情報
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];				// テクスチャのポインタ
	static std::vector<LPDIRECT3DTEXTURE9> m_apTextureList;			// 通常テクスチャへのポインタのリスト
	static std::vector<std::string> m_aTexFileName;					// 通常テクスチャのファイル名
};
#endif
