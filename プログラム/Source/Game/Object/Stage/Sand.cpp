#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>

#include"../ObjBase.h"
#include"Sand.h"
#include"../../../GameData.h"

#define DefPos_x 0
#define DefPos_y -50
#define DefPos_z 0


void Sand::Init()
{
	//メッシュ読み込み
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Sand.x");

	//初期座標設定
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	//オブジェクトタイプ設定
	Set_ObjType(STAGE);
}

void Sand::Update()
{

	//行列
	D3DXMATRIX mPos;
	D3DXMATRIX mScal;

	//座標
	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);
	//拡大
	D3DXMatrixScaling(&mScal, 100.0f, 1.0f, 100.0f);

	mMat = mScal * mPos;

}

void Sand::Draw()
{
	//ライト設定を無視する
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//行列設定
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	//描画
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);

	//ライト設定を元に戻す
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Sand::Release()
{
	//メッシュ開放
	ReleaseMesh(&xMesh);
}