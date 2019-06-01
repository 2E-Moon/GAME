#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<dsound.h>//2DƒTƒEƒ“ƒh



#include"../../GameData.h"
#include "../../UI/UIBase.h"
#include"Title_UI.h"


void Title_UI::Init()
{
	D3DXCreateSprite(GAMEDATA.lpD3DDevice, &lpSprite);
	lpSprite->OnResetDevice();
	LoadText(&lpButton, "Resource/Title/PlayGame.png", 327, 54, NULL);
	LoadText(&lpButton_s, "Resource/Title/PlayGame_Select.png", 327, 54, NULL);
}

void Title_UI::Update()
{


	rc = { 0, 0, 327, 54 };
	D3DXMatrixTranslation(&mSprite, 160, 270, 0);

	if (GAMEDATA.NowPt.x >= 160 && GAMEDATA.NowPt.x <= 486 && GAMEDATA.NowPt.y >= 270 && GAMEDATA.NowPt.y <= 323) {
		Button_SelectFlg = true;
	}
	else
	{
		Button_SelectFlg = false;
	}

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (Button_SelectFlg == true)
		{
			SOUND.SE_Play("Decision");
			GameMode_ChangeFlg = true;
		}
	}




}

void Title_UI::Draw()
{
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	lpSprite->SetTransform(&mSprite);
	switch (Button_SelectFlg)
	{
	case true:
		lpSprite->Draw(lpButton_s, &rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case false:
		lpSprite->Draw(lpButton, &rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}


	lpSprite->End();

}

void Title_UI::Release()
{

	lpButton->Release();
	lpButton_s->Release();
	lpSprite->Release();
}