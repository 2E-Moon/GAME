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
	//乱数生成
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> Typedist(0, 7); //食材の種類
	std::uniform_int_distribution<int> Posdist_x(-200,200); //x座標
	std::uniform_int_distribution<int> Posdist_z(-200, 200); //z座標
	std::uniform_int_distribution<int> Scadist(1, 4); //サイズ

	//食材の種類設定
	iFoodType = Typedist(mt);


	//メッシュ読み込み
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

	//初期位置設定
	Pos = D3DXVECTOR3(Posdist_x(mt), 5.0f, Posdist_z(mt));
	//サイズ設定
	Size = Scadist(mt);
	//オブジェクトタイプ設定
	Set_ObjType(ENEMY);

}

void Enemy::Update()
{

	//サイズ用行列
	D3DXMATRIX mScal;




	//落下
	Pos.y += Accel;

	Accel -= 0.05f;
	if (Accel <= 0)
	{
		Accel = 0;
	}

	//ダメージヒット中
	if (DamageFlg == true)
	{
		Pos += DamageVec;
	}
	else {

	}

	//行列設定
	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);
	D3DXMatrixScaling(&mScal, Size, Size, Size);
	SetMove();


		mMat = mScal*mRot*mPos;
	

		//ステージから落ちてしまった場合削除し新しいエネミーを生成する
		if (Pos.y <= -45) 
		{
			DeleteFlg = true;
		}




		//ステージとの判定
	ObjColl(STAGE, mRot, &Pos, D3DXVECTOR3(0, -1, 0), D3DXVECTOR3(0, -0.5, 0));



}

void Enemy::Draw()
{
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Enemy::Release()
{
	ReleaseMesh(&xMesh);
}


void Enemy::SetStartPos(float _x, float _y, float _z)
{
	vStartPos = D3DXVECTOR3(_x, _y, _z);
}


void Enemy::ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push)
{
	float StageDis;
	BOOL Hit;
	for (auto itr = GAMEDATA.p_objectlist->ObjectList.begin(); itr != GAMEDATA.p_objectlist->ObjectList.end(); itr++) {
		if ((*itr)->Get_ObjType() != ObjType)
		{
			continue;
		}

		D3DXMATRIX mInv;
		D3DXMatrixInverse(&mInv, NULL, &(*itr)->GetMat());
		D3DXVECTOR3 LocalPos, LocalVec;

		D3DXVec3TransformCoord(&LocalPos, &(*itr)->GetPos(), &mInv);//計算上のレイ発射位置,実際のレイ発射位置,&mInv
		D3DXVec3TransformNormal(&LocalVec, &_Normal, &mInv);//計算上のレイ発射方向,実際のレイ実行方向,&mInv



		D3DXVec3TransformCoord(&LocalPos, _Pos, &mInv);//計算上のレイ発射位置,実際のレイ発射位置,&mInv

		D3DXIntersect((*itr)->GetMesh().lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &StageDis, NULL, NULL);
		//メッシュの形状,レイ発射位置,レイの発射方向,当たったかどうか,NULL,NULL,NULL,当たった場所までの距離,NULL,NULL
		//		LPD3DXFONT lpFont;
		//		char Text[200];
		//		D3DXCreateFont(lpD3DDevice, 0, 10, 500, 1, FALSE, SHIFTJIS_CHARSET, 0, 0, 0, NULL, &lpFont);
		//		lpFont->OnResetDevice();
		//		sprintf_s(Text, sizeof(Text), "StageDis:%f", StageDis);
		//		RECT rc = { 0, 0, 200, 200 };
		//		lpFont->DrawText(NULL, Text, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
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
	for (auto itr = GAMEDATA.p_objectlist->ObjectList.begin(); itr != GAMEDATA.p_objectlist->ObjectList.end(); itr++) {
		if ((*itr)->Get_ObjType() != PLAYER)
		{
			continue;
		}

		D3DXMATRIX mTmp;
/*		D3DXMatrixTranslation(&mTmp, 0, 0, 1);
		mMat = mTmp * mMat;*/
		D3DXVECTOR3 P_Pos;
		P_Pos = D3DXVECTOR3((*itr)->GetPos().x, (*itr)->GetPos().y, (*itr)->GetPos().z);

		D3DXMATRIX mInv;
		D3DXMatrixInverse(&mInv, NULL, &mMat);
		D3DXVECTOR3 TargetPos;
		D3DXVec3TransformCoord(&TargetPos, &P_Pos, &mInv);

		D3DXVECTOR3 FrontVec(1, 0, 0);
		D3DXVECTOR3 RotAxis;
		D3DXVec3Cross(&RotAxis, &FrontVec, &TargetPos);

		D3DXVec3Normalize(&TargetPos, &TargetPos);
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

void Enemy::DamageProc()
{

}