

#ifndef __Title_h__
#define __Title_h__

class Title {
public:
	void Init();
	void Update();
	void Draw();
	void Release();

	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);
	bool Get_GameMode_ChangeFlg() { return GameMode_ChangeFlg; }
	void Set_GameMode_ChangeFlg(bool _flg) { GameMode_ChangeFlg = _flg; }
private:
	LPD3DXSPRITE lpSprite;
	D3DXMATRIX mSprite;
	RECT rc;

	LPDIRECT3DTEXTURE9 lpTitle;
	
	Title_UI t_ui;

	bool GameMode_ChangeFlg = false;
};


#endif

