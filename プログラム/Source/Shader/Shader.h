#ifndef __Shader_h__
#define __Shader_h__

//======================================================
// サンプルシェーダ
//	Sample.fxを動作させるためのクラス
//======================================================
class SimpleShader {
public:
	LPD3DXEFFECT	m_Effect;		// エフェクト
	LPDIRECT3DTEXTURE9 lpWhite;

									// 
	SimpleShader() {
		m_Effect = NULL;
	}
	~SimpleShader() {
		Release();
	}

	//======================================================
	// エフェクト読み込み＆解放など
	//======================================================
	// 初期設定
	void Init();

	// 解放
	void Release()
	{
		if (m_Effect) { m_Effect->Release(); m_Effect = NULL; }
		

	}

	//======================================================
	// パラメータ設定系
	//======================================================
	// シェーダに行列を設定
	// ワールド
	void SetTransformWorld(const D3DXMATRIX* mat) {
		if (m_Effect == NULL)return;
		m_Effect->SetMatrix("mW", mat);
	}
	// ビュー
	void SetTransformView(const D3DXMATRIX* mat) {
		if (m_Effect == NULL)return;
		m_Effect->SetMatrix("mV", mat);
	}
	// 射影
	void SetTransformProj(const D3DXMATRIX* mat) {
		if (m_Effect == NULL)return;
		m_Effect->SetMatrix("mP", mat);
	}
	// ライト情報
	void SetLightDir(const D3DXVECTOR3* vDir) {
		if (m_Effect == NULL)return;
		m_Effect->SetValue("LightDir", vDir, sizeof(D3DXVECTOR3));		// 方向
	}
	// カメラ位置設定
	void SetCamPos(const D3DXVECTOR3* lpvPos) {
		if (m_Effect == NULL)return;
		m_Effect->SetValue("CamPos", lpvPos, sizeof(D3DXVECTOR3));
	}

	//======================================================
	// 描画係
	//======================================================
	// メッシュ描画
	void DrawMesh(LPD3DXMESH _Mesh,
	DWORD _NumMaterial,
	D3DMATERIAL9* _Mat,
	LPDIRECT3DTEXTURE9 _Tex);


	//2D画像ロード
	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);


};

#endif
