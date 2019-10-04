#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<random>

#include"../ObjBase.h"
#include"Enemy.h"
#include"../../../GameData.h"



void Enemy::Init()
{
	//��������
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> Typedist(0, 7); //�H�ނ̎��
	std::uniform_int_distribution<int> Posdist_x(-20, 100); //x���W
	std::uniform_int_distribution<int> Posdist_z(-20, 100); //z���W
	std::uniform_int_distribution<int> Scadist(1, 4); //�T�C�Y

	//�H�ނ̎�ސݒ�
	iFoodType = Typedist(mt);


	//���b�V���ǂݍ���
	switch (iFoodType)
	{
	case BEEF:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Beef.x");
		break;
	case CACAO:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Cacao.x");
		break;
	case CARROT:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Carrot.x");
		break;
	case CHICKEN:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Chicken.x");
		break;
	case EGG:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Egg.x");
		break;
	case MILK:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Milk.x");
		break;
	case MUSH:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Mush.x");
		break;
	case POTATO:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Potato.x");
		break;
	default:
		LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Potato.x");
		break;

	}

	//�����ʒu�ݒ�
	Pos = D3DXVECTOR3(Posdist_x(mt), 15.0f, Posdist_z(mt));
	//�T�C�Y�ݒ�
	Size = Scadist(mt);
	//�I�u�W�F�N�g�^�C�v�ݒ�
	Set_ObjType(ENEMY);

}

void Enemy::Update()
{

	//�T�C�Y�p�s��
	D3DXMATRIX mScal;




	//����
	Pos.y += Accel;

	Accel -= 0.05f;
	if (Accel <= 0)
	{
		Accel = 0;
	}

	//�_���[�W�q�b�g��
	if (DamageFlg == true)
	{
		Pos += DamageVec;
	}
	else {

	}

	//�s��ݒ�
	if (CarryToPlayerFlg == true)
	{
		Pos = GAMEDATA.p_player->GetPos();
	}
		D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);


	D3DXMatrixScaling(&mScal, Size, Size, Size);
	SetMove();


		mMat = mScal*mRot*mPos;

		//�X�e�[�W�Ƃ̔���
	StageColl(mRot, &Pos, D3DXVECTOR3(0, -1, 0), D3DXVECTOR3(0, -0.5, 0));

	//�X�e�[�W���痎���Ă��܂����ꍇ�폜���V�����G�l�~�[�𐶐�����
	if (Pos.y <= -45)
	{
		DeleteFlg = true;

	}


}

void Enemy::Draw()
{
	//�s���ݒ�
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	//�`��
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);

}

void Enemy::Release()
{
	//���b�V���̉��
	ReleaseMesh(&xMesh);
}


void Enemy::SetStartPos(float _x, float _y, float _z)
{
	vStartPos = D3DXVECTOR3(_x, _y, _z);
}


void Enemy::ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push)
{
	//�ΏۃI�u�W�F�N�g�Ƃ̋���
	float ObjDis;

	//�q�b�g����
	BOOL Hit;

	//�I�u�W�F�N�g�̃��X�g���񂵁A�Ώۂ̃I�u�W�F�N�g�^�C�v�̂��̂�T��
	for (auto itr = GAMEDATA.p_objectlist->ObjectList.begin(); itr != GAMEDATA.p_objectlist->ObjectList.end(); itr++) {
		
		//�ΏۊO�̂��̂͑��߂�
		if ((*itr)->Get_ObjType() != ObjType)
		{
			continue;
		}

		D3DXMATRIX mInv;
		D3DXMatrixInverse(&mInv, NULL, &(*itr)->GetMat());
		D3DXVECTOR3 LocalPos, LocalVec;

		D3DXVec3TransformCoord(&LocalPos, &(*itr)->GetPos(), &mInv);//�v�Z��̃��C���ˈʒu,���ۂ̃��C���ˈʒu,&mInv
		D3DXVec3TransformNormal(&LocalVec, &_Normal, &mInv);//�v�Z��̃��C���˕���,���ۂ̃��C���s����,&mInv



		D3DXVec3TransformCoord(&LocalPos, _Pos, &mInv);//�v�Z��̃��C���ˈʒu,���ۂ̃��C���ˈʒu,&mInv

		D3DXIntersect((*itr)->GetMesh().lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &ObjDis, NULL, NULL);
		//���b�V���̌`��,���C���ˈʒu,���C�̔��˕���,�����������ǂ���,NULL,NULL,NULL,���������ꏊ�܂ł̋���,NULL,NULL
		//		LPD3DXFONT lpFont;
		//		char Text[200];
		//		D3DXCreateFont(lpD3DDevice, 0, 10, 500, 1, FALSE, SHIFTJIS_CHARSET, 0, 0, 0, NULL, &lpFont);
		//		lpFont->OnResetDevice();
		//		sprintf_s(Text, sizeof(Text), "StageDis:%f", StageDis);
		//		RECT rc = { 0, 0, 200, 200 };
		//		lpFont->DrawText(NULL, Text, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}

	//�Ώۂ̕����ɃI�u�W�F�N�g���������A�����Ă������������ꍇ�͋�����i�߂�
	//�����łȂ��ꍇ�͗��܂点��
	if (!Hit || (Hit&&ObjDis>1.0f)) {


		D3DXVECTOR3 vec;
		vec = _Push;
		D3DXVec3TransformCoord(&vec, &vec, &_mMat);
		*_Pos += vec;
	}
	else
	{
		ObjDis = -1;
		DamageFlg = false;
	}
}

void Enemy::StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push)
{
	float StageDis;
	BOOL Hit;
	for (auto itr = GAMEDATA.p_objectlist->ObjList_Stage.begin(); itr != GAMEDATA.p_objectlist->ObjList_Stage.end(); itr++) {


		for (int i = 0; i < STAGEVALUE; i++)
		{
			for (int j = 0; j < STAGEVALUE; j++)
			{
				D3DXMATRIX mInv;
				D3DXVECTOR3 LocalPos, LocalVec;

				D3DXMatrixInverse(&mInv, NULL, &(*itr)->GetStageMat(i, j));


				D3DXVec3TransformCoord(&LocalPos, &(*itr)->GetStagePos(i, j), &mInv);//�v�Z��̃��C���ˈʒu,���ۂ̃��C���ˈʒu,&mInv
				D3DXVec3TransformNormal(&LocalVec, &_Normal, &mInv);//�v�Z��̃��C���˕���,���ۂ̃��C���s����,&mInv



				D3DXVec3TransformCoord(&LocalPos, _Pos, &mInv);//�v�Z��̃��C���ˈʒu,���ۂ̃��C���ˈʒu,&mInv

				D3DXIntersect((*itr)->GetMesh().lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &StageDis, NULL, NULL);
				if (Hit)break;
			}
			if (Hit)break;
		}
		if (Hit)break;

	}
	if (!Hit || (Hit&&StageDis>1.0f)) {


		D3DXVECTOR3 vec;
		vec = _Push;
		D3DXVec3TransformCoord(&vec, &vec, &_mMat);
		*_Pos += vec;
	}
	else
	{
		StageDis = -1;
		DamageFlg = false;
	}

}

void Enemy::SetMove()
{
	//�I�u�W�F�N�g���X�g����v���C���[���o��܂ŉ�
	for (auto itr = GAMEDATA.p_objectlist->ObjectList.begin(); itr != GAMEDATA.p_objectlist->ObjectList.end(); itr++) {
		if ((*itr)->Get_ObjType() != PLAYER)
		{
			continue;
		}

		//�v���C���[�̍��W�i�[
		D3DXVECTOR3 P_Pos;
		P_Pos = D3DXVECTOR3((*itr)->GetPos().x, (*itr)->GetPos().y, (*itr)->GetPos().z);

		//���W�ϊ�
		D3DXMATRIX mInv;
		D3DXMatrixInverse(&mInv, NULL, &mMat);
		D3DXVECTOR3 TargetPos;
		D3DXVec3TransformCoord(&TargetPos, &P_Pos, &mInv);

		//�O��
		D3DXVECTOR3 FrontVec(1, 0, 0);
		D3DXVECTOR3 RotAxis;
		D3DXVec3Cross(&RotAxis, &FrontVec, &TargetPos);

		//���K��
		D3DXVec3Normalize(&TargetPos, &TargetPos);

		//
		float Dot;
		Dot = D3DXVec3Dot(&FrontVec, &TargetPos);
		if (Dot > 1)Dot = 1;
		if (Dot < -1)Dot = -1;
		float Ang;
		Ang = D3DXToDegree(acos(Dot));
		if (Ang > 45)Ang = 45;


	//	D3DXMatrixRotationAxis(&mRot, &RotAxis, D3DXToRadian(Ang));
		D3DXMatrixRotationY(&mRot, D3DXToRadian(0));
	//	mMat = mRot * mMat;

	/*	if (GetLength(Pos, (*itr)->GetPos()) < 5)
		{
			D3DXVECTOR3 vec = D3DXVECTOR3(0.25f, 0, 0);
			D3DXVec3TransformCoord(&vec, &vec, &mRot);
			Pos += vec;
		}*/
	}
}

