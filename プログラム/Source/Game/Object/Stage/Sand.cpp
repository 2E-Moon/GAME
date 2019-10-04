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
	//���b�V���ǂݍ���
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Sand.x");

	//�������W�ݒ�
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	//�I�u�W�F�N�g�^�C�v�ݒ�
	Set_ObjType(STAGE);
}

void Sand::Update()
{

	//�s��
	D3DXMATRIX mPos;
	D3DXMATRIX mScal;

	//���W
	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);
	//�g��
	D3DXMatrixScaling(&mScal, 100.0f, 1.0f, 100.0f);

	mMat = mScal * mPos;

}

void Sand::Draw()
{
	//���C�g�ݒ�𖳎�����
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�s��ݒ�
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	//�`��
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);

	//���C�g�ݒ�����ɖ߂�
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Sand::Release()
{
	//���b�V���J��
	ReleaseMesh(&xMesh);
}