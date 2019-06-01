#ifndef __ObjBase_h__
#define __ObjBase_h__



class ObjBase {
public:
	struct XFILE {
		LPD3DXMESH lpMesh;
		DWORD NumMaterial;
		D3DMATERIAL9 *Mat;
		LPDIRECT3DTEXTURE9 *Tex;
	};

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	XFILE GetMesh() { return xMesh; }
	D3DXVECTOR3 GetPos() { return Pos; }
	D3DXMATRIX GetMat() { return mMat; }

	float GetLength(D3DXVECTOR3 _form,D3DXVECTOR3 _prev);
	void SetDamage(bool _flg, D3DXVECTOR3 _PushVec, float _accel) { DamageFlg = _flg; DamageVec = _PushVec; Accel = _accel; }

	void Set_ObjType(int _type) { ObjType = _type; }
	int Get_ObjType() { return ObjType; }

	bool Get_DeleteFlg() { return DeleteFlg; }
	void Set_DeleteFlg(bool _flg) { DeleteFlg = _flg; }


	enum { PLAYER, ENEMY, STAGE, POT, OTHER };

private:

	LPD3DXMESH lpTeapot;
	int ObjType;



protected:

	void LoadMesh(LPDIRECT3DDEVICE9 lpD3DDevice, XFILE *XFile, const char FName[]);
	void DrawMesh(LPDIRECT3DDEVICE9 lpD3DDevice, struct XFILE *xFile, D3DXMATRIX* _Mat ,bool isShaderRender = true);
	void ReleaseMesh(struct XFILE *XFile);

	D3DXVECTOR3 Pos;
	struct XFILE xMesh;

	D3DXMATRIX mMat;
	
	float Accel;

	bool DamageFlg;
	D3DXVECTOR3 DamageVec;
	float DamageTime;

	//âï˙Ç∑ÇÈç€Ç…trueÇ…Ç∑ÇÈ
	bool DeleteFlg = false;
};

#endif