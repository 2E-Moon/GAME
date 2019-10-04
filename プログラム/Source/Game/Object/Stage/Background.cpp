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
	//���b�V���ǂݍ���
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Background_f.x");

	//�������W�ݒ�
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	//�I�u�W�F�N�g�^�C�v�ݒ�
	Set_ObjType(OTHER);
}

void Background::Update()
{
	//�s��
	D3DXMATRIX mPos;
	D3DXMATRIX mScal;
	D3DXMATRIX mRot;

	//���W
	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);
	//��]
	D3DXMatrixRotationY(&mRot, D3DXToRadian(rad));
	//�g��
	D3DXMatrixScaling(&mScal, 100.0f, 100.0f, 100.0f);

	mMat = mRot * mScal * mPos;

	//��ɉ�]������
	rad+=0.05f;
	if (rad >= 360)rad = 0;

}

void Background::Draw()
{
	//���C�g�ݒ�𖳎�����
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�s��
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	//�`��(�V�F�[�_�Ȃ�)
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh,&mMat, false);

	//���C�g�ݒ��߂�
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Background::Release()
{
	//���b�V���J��
	ReleaseMesh(&xMesh);
}