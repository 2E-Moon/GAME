#ifndef __Effect_h__
#define __Effect_h__

#define EFFECT Effect::GetInstance()

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
class Effect  {
public:


	//------------------
	//	シングルトン生成
	//------------------
	static Effect& GetInstance()
	{
		static Effect Instance;
		return Instance;

	}

	void Init();
	void Update();
	void Draw();
	void Release();

	//エフェクト生成フラグを立たせる用
	void CreateEffect();

	//エフェクト削除フラグを立たせる用
	void DeleateEffect();

private:


	//テクスチャ読み込み
	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);


	//テクスチャ
	LPDIRECT3DTEXTURE9 lpCharge;

	struct VERTEX
	{
		D3DXVECTOR3 Pos;
		D3DCOLOR Color;
		D3DXVECTOR2 Tex;
	};
	VERTEX v[4];

	//チャージ中フラグ
	bool Effect_ChargeFlg;
	//エフェクトを広げる用変数
	float CCnt = 100;
	//エフェクトのフェード用変数
	int FeadCnt = 255;

	//行列
	D3DXMATRIX mCharge;



};
#endif