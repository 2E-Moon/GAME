#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<dsound.h>


#include"../GameData.h"



#include "../UI/UIBase.h"
#include "Title_UI/Title_UI.h"

#include "Title.h"



void Title::Init()
{
	D3DXCreateSprite(GAMEDATA.lpD3DDevice, &lpSprite);
	lpSprite->OnResetDevice();
	LoadText(&lpTitle, "Resource/Title/Title.png", 640, 480, NULL);
	t_ui.Init();


}

void Title::Update()
{
	SOUND.BGM_Play("Title");

	//タイトル画像
	rc = { 0, 0, 640, 480 };
	D3DXMatrixTranslation(&mSprite, 0, 0, 1);

	t_ui.Update();

	if (t_ui.Get_GameMode_ChangeFlg() == true)
	{
		GameMode_ChangeFlg = true;
		SOUND.BGM_Stop();
	}
}

void Title::Draw()
{
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	lpSprite->SetTransform(&mSprite);
	lpSprite->Draw(lpTitle, &rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	lpSprite->End();

	t_ui.Draw();
}

void Title::Release()
{

	lpTitle->Release();
	lpSprite->Release();

	t_ui.Release();
}

//2D画像ロード
void Title::LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(GAMEDATA.lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
}

