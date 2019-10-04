#ifndef __ObjBase_h__
#define __ObjBase_h__



class ObjBase {
public:
	//メッシュ関連
	struct XFILE {
		LPD3DXMESH lpMesh;
		DWORD NumMaterial;
		D3DMATERIAL9 *Mat;
		LPDIRECT3DTEXTURE9 *Tex;
	};


	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();

	//=============
	//ゲッター
	//=============
	//メッシュ
	XFILE GetMesh() { return xMesh; }
	//座標
	D3DXVECTOR3 GetPos() { return Pos; }
	//行列
	D3DXMATRIX GetMat() { return mMat; }
	//対象との距離
	float GetLength(D3DXVECTOR3 _form,D3DXVECTOR3 _prev);
	//オブジェクトタイプ
	int Get_ObjType() { return ObjType; }
	//削除フラグ
	bool Get_DeleteFlg() { return DeleteFlg; }

	//=============
	//セッター
	//=============
	//ダメージ
	void SetDamage(bool _flg, D3DXVECTOR3 _PushVec, float _accel) { DamageFlg = _flg; DamageVec = _PushVec; Accel = _accel; }
	//オブジェクトタイプ
	void Set_ObjType(int _type) { ObjType = _type; }
	//削除フラグ
	void Set_DeleteFlg(bool _flg) { DeleteFlg = _flg; }

	//オブジェクトタイプ用
	enum { PLAYER, ENEMY, STAGE, POT, OTHER };

private:

	//オブジェクトタイプ格納変数
	int ObjType;



protected:
	//=============
	//メッシュ関連
	//=============
	//読み込み
	void LoadMesh(LPDIRECT3DDEVICE9 lpD3DDevice, XFILE *XFile, const char FName[]);
	//描画
	void DrawMesh(LPDIRECT3DDEVICE9 lpD3DDevice, struct XFILE *xFile, D3DXMATRIX* _Mat ,bool isShaderRender = true);
	//解放
	void ReleaseMesh(struct XFILE *XFile);
	//メッシュ変数
	struct XFILE xMesh;

	//行列
	D3DXMATRIX mMat;
	//座標
	D3DXVECTOR3 Pos;

	//落下速度用変数
	float Accel;

	//ダメージ被弾判定
	bool DamageFlg;
	//ダメージ被弾時の飛ぶ距離用
	D3DXVECTOR3 DamageVec;
	//ダメージ被弾時間
	float DamageTime;

	//削除フラグ
	//解放する際にtrueにする
	bool DeleteFlg = false;
};

#endif