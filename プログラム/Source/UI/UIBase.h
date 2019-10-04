#ifndef __UIBase_h__
#define __UIBase_h__


class UIBase {
public:
	//‰Šú‰»
	virtual void Init();
	//XV
	virtual void Update();
	//•`‰æ
	virtual void Draw();
	//‰ğ•ú
	virtual void Release();

	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);
private:

protected:
	LPD3DXSPRITE lpSprite;
	D3DXMATRIX mSprite;
	RECT rc;
};

#endif