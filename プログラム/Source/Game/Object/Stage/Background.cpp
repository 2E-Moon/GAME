#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>

#include"../ObjBase.h"
#include"Background.h"
#include"../../../GameData.h"

#define DefPos_x 0
#define DefPos_y -120
#define DefPos_z 0


void Background::Init()
{
	//メッシュ読み込み
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Background_f.x");

	//初期座標設定
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	//オブジェクトタイプ設定
	Set_ObjType(OTHER);
}

void Background::Update()
{
	//行列
	D3DXMATRIX mPos;
	D3DXMATRIX mScal;
	D3DXMATRIX mRot;

	//座標
	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);
	//回転
	D3DXMatrixRotationY(&mRot, D3DXToRadian(rad));
	//拡大
	D3DXMatrixScaling(&mScal, 100.0f, 100.0f, 100.0f);

	mMat = mRot * mScal * mPos;

	//常に回転させる
	rad+=0.05f;
	if (rad >= 360)rad = 0;

}

void Background::Draw()
{
	//ライト設定を無視する
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//行列
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	//描画(シェーダなし)
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh,&mMat, false);

	//ライト設定を戻す
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Background::Release()
{
	//メッシュ開放
	ReleaseMesh(&xMesh);
}