//=============================================================================
//
// モデル処理 [model.h]
// Author : 山田陵太
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"
#include "xfile.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_MODEL_TEXTURE	(256)		// テクスチャの最大数

//=============================================================================
// モデルクラス
//=============================================================================
class CModel : public CScene
{
public:
	typedef enum
	{
		MODEL_TYPE_NONE = 0,	// 初期値
		MODEL_TYPE_PLAYER1,		// プレイヤー
		MODEL_TYPE_PLAYER2,		// プレイヤー
		MODEL_TYPE_BEAM,		// ビーム
		MODEL_TYPE_OBJECT,		// 建物
		MODEL_TYPE_MAX
	}MODEL_TYPE;

	//=========================================================================
	//メンバ関数宣言
	//=========================================================================
	CModel(PRIORITY Priority = PRIORITY_EFFECT);
	~CModel();

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindModel(CXfile::MODEL model);
	void BindTexture(LPDIRECT3DTEXTURE9 *pTexture);
	void BindTexturePointer(LPDIRECT3DTEXTURE9 *ppTexture);

	// Set関数
	void SetPos(const D3DXVECTOR3 pos);
	void SetRot(const D3DXVECTOR3 rot);		// 座標の情報
	D3DXVECTOR3 GetRot(void);
	void SetType(MODEL_TYPE Mtype);
	void SetSize(D3DXVECTOR3 size);
	void SetTexPattern(int TexPattern);		// テクスチャのパターン

	// Get関数
	D3DXVECTOR3 GetPos(void)const;
	D3DXVECTOR3 GetSize(void);
	MODEL_TYPE GetType(void);
	D3DXMATRIX GetMtxWorld(void);
	LPD3DXMESH GetMesh(void)const;
	LPD3DXBUFFER GetBuffMat(void);
	DWORD GetNumMat(void);
	int GetTexPattern(void);
private:
	//=========================================================================
	//メンバ変数宣言
	//=========================================================================
//	LPDIRECT3DTEXTURE9 m_apTexture[MAX_MODEL_TEXTURE];
	LPDIRECT3DTEXTURE9 *m_apTexture;
	D3DXVECTOR3 m_pos;					// 位置
	D3DXVECTOR3 m_rot;					// 向き
	D3DXVECTOR3 m_size;					// サイズ
	D3DXMATRIX m_mtxWorld;				// ワールドマトリックス
	MODEL_TYPE m_type;					// 種類
	CXfile::MODEL m_Model;				// モデルの構造体
	int m_nTexPattern;						// テクスチャのパターン数
};
#endif 