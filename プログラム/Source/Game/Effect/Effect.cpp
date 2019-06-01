#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>

#include"../../GameData.h"
#include "Effect.h"



void Effect::Init()
{
	//エフェクト読み込み
	LoadText(&lpCharge, "Resource/Effect/Hit.png", 500, 500, NULL);

}

void Effect::Update()
{

	//チャージ中
	if (Effect_ChargeFlg==true)
	{


		//プレイヤーの座標からチャージエフェクトを出現させる
		{

			D3DXVECTOR3 TmpPos = GAMEDATA.p_player->GetPos();
			D3DXMatrixTranslation(&mCharge, TmpPos.x, TmpPos.y, TmpPos.z);
			D3DXMATRIX mRot;
			D3DXMatrixRotationY(&mRot, D3DXToRadian(90));
			mCharge = mRot * GAMEDATA.p_player->GetMat();

		}

		//エフェクト用の板。
		//CCnt:エフェクトを拡大するための変数
		v[0].Pos = D3DXVECTOR3(-CCnt, 0, -CCnt);
		v[1].Pos = D3DXVECTOR3(-CCnt, 0, CCnt);
		v[2].Pos = D3DXVECTOR3(CCnt, 0, CCnt);
		v[3].Pos = D3DXVECTOR3(CCnt, 0, -CCnt);

		v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
		v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
		v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
		v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

		v[0].Color = D3DCOLOR_ARGB(FeadCnt, 255, 255, 255);
		v[1].Color = D3DCOLOR_ARGB(FeadCnt, 255, 255, 255);
		v[2].Color = D3DCOLOR_ARGB(FeadCnt, 255, 255, 255);
		v[3].Color = D3DCOLOR_ARGB(FeadCnt, 255, 255, 255);


		

		//エフェクトが消えるまでカウントを進める
		CCnt += 2.5f;

		//フェードカウントを進める
		//0になったらそれ以下に下がらないよう調整
			FeadCnt -= 25;
			if (FeadCnt <= 0)
			{
				FeadCnt = 0;
			}

			//エフェクトが広ぎきったら縮小して再表示
		if (CCnt >= 100)
		{
			CCnt = 0;
			FeadCnt = 255;
		}
	}

}

void Effect::Draw()
{
	GAMEDATA.lpD3DDevice->SetFVF(FVF_VERTEX);

	//チャージ中
	if (Effect_ChargeFlg == true)
	{
		GAMEDATA.lpD3DDevice->SetTexture(0, lpCharge);

		GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mCharge);

		GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		GAMEDATA.lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
		GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	}


}

void Effect::Release()
{

	lpCharge->Release();
}


void Effect::LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(GAMEDATA.lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
}

void Effect::CreateEffect()
{
	Effect_ChargeFlg = true;
}

void Effect::DeleateEffect()
{
	Effect_ChargeFlg = false;
}