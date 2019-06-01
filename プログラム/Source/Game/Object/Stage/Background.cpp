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
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Background_f.x");

	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	Set_ObjType(OTHER);
}

void Background::Update()
{

	D3DXMATRIX mPos;
	D3DXMATRIX mScal;
	D3DXMATRIX mRot;

	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);
	D3DXMatrixRotationY(&mRot, D3DXToRadian(rad));
	D3DXMatrixScaling(&mScal, 100.0f, 100.0f, 100.0f);

	mMat = mRot * mScal * mPos;

	rad+=0.05f;
	if (rad >= 360)rad = 0;

}

void Background::Draw()
{
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh,&mMat, false);
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Background::Release()
{
	ReleaseMesh(&xMesh);
}