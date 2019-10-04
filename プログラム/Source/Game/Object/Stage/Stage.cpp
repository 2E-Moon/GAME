#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<random>

#include"../ObjBase.h"
#include"Stage.h"
#include"../../../GameData.h"

#define DefPos_x -20
#define DefPos_y -10
#define DefPos_z -20


void Stage::Init()
{
	//���b�V���ǂݍ���
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/StageBlock.x");
	LoadMesh(GAMEDATA.lpD3DDevice, &xHitMesh, "Resource/Chara/StageBlock_h.x");

	//�������W�ݒ�
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);

	CreateStage();


	//�I�u�W�F�N�g�^�C�v�ݒ�
	Set_ObjType(STAGE);
}

void Stage::Update()
{


	for (int i = 0; i < STAGEVALUE; i++)
	{
		for (int j = 0; j < STAGEVALUE; j++)
		{
			D3DXMatrixTranslation(&mBMat[i][j], vBPos[i][j].x , vBPos[i][j].y, vBPos[i][j].z);
		}
	}

//	D3DXMatrixTranslation(&mMat, Pos.x,Pos.y,Pos.z);
//	mMat = mScal * mMat;


}

void Stage::Draw()
{
	//���C�g�ݒ�𖳎�����
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�s��ݒ�
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);

	
	for (int i = 0; i < STAGEVALUE; i++)
	{
		for (int j = 0; j < STAGEVALUE; j++)
		{
			switch (isHitFlg[i][j])
			{
			case false:
				//�`��
				DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mBMat[i][j]);
				break;
			default:
				DrawMesh(GAMEDATA.lpD3DDevice, &xHitMesh, &mBMat[i][j]);
			}

		}
	}
	//���C�g�ݒ�����ɖ߂�
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Stage::Release()
{
	//���b�V���̉��
	ReleaseMesh(&xMesh);
}

void Stage::CreateStage()
{

	for (int i = 0; i < STAGEVALUE; i++)
	{
		for (int j = 0; j < STAGEVALUE; j++)
		{
			//��������
			std::mt19937 mt{ std::random_device{}() };
			std::uniform_int_distribution<int> Ypos(1, 4); //Y���W
			iBHeight[i][j] = Ypos(mt);
			
			if (j != 0)
			{

				if (iBHeight[i][j-1] > iBHeight[i][j])
				{

					if (iBHeight[i][j - 1] - iBHeight[i][j] >= 2)
					{
						iBHeight[i][j] = iBHeight[i][j - 1] - 1;
					}

				}

				if (iBHeight[i][j - 1] < iBHeight[i][j])
				{
					if (iBHeight[i][j] - iBHeight[i][j - 1] <= 2)
					{
						iBHeight[i][j] = iBHeight[i][j - 1] + 1;
					}
				}

			}

			vBPos[i][j] = D3DXVECTOR3(Pos.x + j * 4, Pos.y + iBHeight[i][j] *3.0f, Pos.z + i * 4);
			isHitFlg[i][j] = false;
		}
	}

}