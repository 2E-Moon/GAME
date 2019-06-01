#ifndef __Sand_h__
#define __Sand_h__

class Sand : public ObjBase {
public:

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

private:
	D3DXMATRIX mTmp;
	LPD3DXMESH lpTeapot;

	long rad = 0;
	D3DXMATRIX mSpeed;



	LPDIRECT3DDEVICE9 D3DTmp;
};

#endif