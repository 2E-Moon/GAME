#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>

#include"../ObjBase.h"
#include"Stage.h"
#include"../../../GameData.h"

#define DefPos_x 0
#define DefPos_y 0
#define DefPos_z 0


void Stage::Init()
{
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Stage.x");

	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	Set_ObjType(STAGE);
}

void Stage::Update()
{

	D3DXMATRIX mScal;
	D3DXMatrixScaling(&mScal, 10.0, 1, 10.0);
	D3DXMatrixTranslation(&mMat, Pos.x,Pos.y,Pos.z);
	mMat = mScal * mMat;


}

void Stage::Draw()
{
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat,false);
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Stage::Release()
{
	ReleaseMesh(&xMesh);
}