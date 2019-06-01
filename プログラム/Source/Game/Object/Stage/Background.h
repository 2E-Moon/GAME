#ifndef __Background_h__
#define __Background_h__

class Background : public ObjBase {
public:

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

private:
	float rad = 0;
	D3DXMATRIX mSpeed;



	LPDIRECT3DDEVICE9 D3DTmp;
};

#endif