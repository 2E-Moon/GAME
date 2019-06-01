#ifndef __UIBase_h__
#define __UIBase_h__


class UIBase {
public:
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);
private:

protected:
	LPD3DXSPRITE lpSprite;
	D3DXMATRIX mSprite;
	RECT rc;
};

#endif