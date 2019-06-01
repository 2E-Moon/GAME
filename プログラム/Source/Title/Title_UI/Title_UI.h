#ifndef __Title_UI_h__
#define __Title_UI_h__


class Title_UI : public UIBase {
public:
	void Init();
	void Update();
	void Draw();
	void Release();

	bool Get_GameMode_ChangeFlg() { return GameMode_ChangeFlg; }
private:

	LPDIRECT3DTEXTURE9 lpButton;
	LPDIRECT3DTEXTURE9 lpButton_s;

	bool Button_SelectFlg;
	bool GameMode_ChangeFlg = false;

};

#endif