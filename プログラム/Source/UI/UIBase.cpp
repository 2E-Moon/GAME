#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>

#include<dsound.h>//2Dサウンド



#include"../GameData.h"
#include "UIBase.h"



void UIBase::Init()
{

}

void UIBase::Update()
{

}

void UIBase::Draw()
{

}

void UIBase::Release()
{

}


//2D画像ロード
void UIBase::LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(GAMEDATA.lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
}