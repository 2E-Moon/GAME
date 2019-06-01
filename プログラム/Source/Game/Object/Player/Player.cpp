#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<memory>
#include<iostream>


#include"../ObjBase.h"
#include"Player.h"
#include"../Enemy/Enemy.h"
#include"../../../GameData.h"
#include"../../../Sound/Sound.h"

#include"../../Effect/Effect.h"

#define DefPos_x -15.0
#define DefPos_y 10.0f
#define DefPos_z -0.0

#define MOVEKEY GetAsyncKeyState('W')  || GetAsyncKeyState('A')  || GetAsyncKeyState('S')  || GetAsyncKeyState('D') || GetAsyncKeyState('D') 


void Player::Init()
{
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Chara_Body.x");//ボディー
	LoadMesh(GAMEDATA.lpD3DDevice, &xLHand, "Resource/Chara/Chara_LHand.x");//左手
	LoadMesh(GAMEDATA.lpD3DDevice, &xRHand, "Resource/Chara/Chara_RHand.x");//右手
	LoadMesh(GAMEDATA.lpD3DDevice, &xLFoot, "Resource/Chara/Chara_LFoot.x");//左足
	LoadMesh(GAMEDATA.lpD3DDevice, &xRFoot, "Resource/Chara/Chara_RFoot.x");//右足
	Set_ObjType(PLAYER);

	//GAMEDATA.p_player =this;


	D3DXCreateFont(GAMEDATA.lpD3DDevice, 0, 10, 500, 1, FALSE, SHIFTJIS_CHARSET, 0, 0, 0, NULL, &lpFont);
	lpFont->OnResetDevice();

}

void Player::Update()
{
	D3DXMATRIX mTrans;
	D3DXMATRIX mRot;
	D3DXMATRIX mPos;


	GAMEDATA.BasePt.x = 320; GAMEDATA.BasePt.y = 240;

	POINT Pt;
	GetCursorPos(&Pt);
	Crad += (Pt.x - GAMEDATA.BasePt.x) / 9.0f;


	Urad += (Pt.y - GAMEDATA.BasePt.y) / 9.0f;
	if (Urad >= 6.0f) { Urad = 6.0f; }
	if (Urad <= -3.0f) { Urad = -3.0f; }

	SetCursorPos(GAMEDATA.BasePt.x, GAMEDATA.BasePt.y);


	D3DXMatrixRotationY(&mRot, D3DXToRadian(Crad));


	//カメラ視点格納
	D3DXVec3TransformCoord(&GAMEDATA.CPos, &D3DXVECTOR3(-8.0f, 5.0f + Urad, 0.0f), &mRot);
	GAMEDATA.CPos = GAMEDATA.CPos + Pos;
	GAMEDATA.CLook = Pos;
	GAMEDATA.CLook.y += 2.0f;

	Pos.y += Accel;


	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);

	if (GAMEDATA.p_game->Get_GameStartFlg() == true)
	{

		if (GetAsyncKeyState('W')) {
			D3DXVECTOR3 vec;
			vec = D3DXVECTOR3(1, 0, 0);

			ObjColl(STAGE, mRot, &Pos, vec, D3DXVECTOR3(0.25f, 0, 0));
			//		D3DXVec3TransformCoord(&vec, &vec, &mRot);
			//		Pos += vec;


		}

		if (GetAsyncKeyState('S')) {
			D3DXVECTOR3 vec;
			vec = D3DXVECTOR3(-1, 0, 0);

			ObjColl(STAGE, mRot, &Pos, vec, D3DXVECTOR3(-0.25f, 0, 0));

		}

		if (GetAsyncKeyState('A')) {
			D3DXVECTOR3 vec;
			vec = D3DXVECTOR3(0, 0, 1);

			ObjColl(STAGE, mRot, &Pos, vec, D3DXVECTOR3(0, 0, 0.25f));

		}

		if (GetAsyncKeyState('D')) {
			D3DXVECTOR3 vec;
			vec = D3DXVECTOR3(0, 0, -1);

			ObjColl(STAGE, mRot, &Pos, vec, D3DXVECTOR3(0, 0, -0.25f));

		}

		if (MOVEKEY == true)
		{
			MoveFlg = true;
		}
		else
		{
			MoveFlg = false;
		}


		if (GetAsyncKeyState(VK_SPACE))
		{
			if (JFlg == false)
			{
				JFlg = true;
				Accel += 1.0f;

				SOUND.SE_Play("Jump");
			}

		}

		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (AttackFlg == false)
			{
				AttackFlg = true;
				Attack_LButtonFlg = true;

			}
		}


	}

	if (GetAsyncKeyState('0'))
	{
		b_DebugFlg = true;
	}




	if (AttackFlg == true)
	{
		if (Attack_LButtonFlg == true)
		{
			if (GetAsyncKeyState(VK_LBUTTON) == false)
			{
				OnAttackFlg = true;
				AttackTime = timeGetTime();

				EFFECT.DeleateEffect();

				SOUND.SE_Play("Attack");

				Attack_LButtonFlg = false;
			}
			else
			{
				Attack_ChargeCnt++;
				if (Attack_ChargeCnt >= 197)Attack_ChargeCnt = 194;

				EFFECT.CreateEffect();
			}
		}
		

		if (OnAttackFlg == true)
		{
			Attack(mRot);
			if (timeGetTime() - AttackTime >= 100)
			{
				OnAttackFlg = false;
				AttackCoolTime = timeGetTime();
			}
		}

		if (OnAttackFlg == false)
		{
			if (timeGetTime() - AttackCoolTime >= 500 && Attack_LButtonFlg==false)
			{
				AttackFlg = false;
			//	Attack_ChargeCnt = 0;
			}
		}

	}

	if(AttackFlg == false || (AttackFlg == true && Attack_LButtonFlg == false))
	{
		Attack_ChargeCnt -= 5;
		if (Attack_ChargeCnt <= 0)Attack_ChargeCnt = 0;
	}

	Accel -= 0.05f;
	if (Accel <= 0)
	{
		Accel = 0;
		JFlg = false;
	}



//	D3DXVec3TransformCoord(CPos, &D3DXVECTOR3(-5.0f, 3.0f, 0.0f), &mRot);
//	*CPos = *CPos + Pos;
//	*CLook = Pos;
//	CLook->y += 1.0f;

	mTrans = mRot * mPos;
	mMat = mTrans;
	

	ObjColl(STAGE, mRot, &Pos, D3DXVECTOR3(0, -1, 0), D3DXVECTOR3(0, -0.5, 0));

	char Text[200];

	if (b_DebugFlg==true)
	{
		sprintf_s(Text, sizeof(Text), "X:%f", Pos.x);
		RECT rc = { 0, 0, 200, 200 };
		lpFont->DrawText(NULL, Text, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		sprintf_s(Text, sizeof(Text), "Y:%f", Pos.y);
		rc = { 0, 50, 200, 400 };
		lpFont->DrawText(NULL, Text, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		sprintf_s(Text, sizeof(Text), "Z:%f", Pos.z);
		rc = { 0, 100, 200, 600 };
		lpFont->DrawText(NULL, Text, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		sprintf_s(Text, sizeof(Text), "Crad:%d", Crad);
		rc = { 0, 200, 200, 600 };
		lpFont->DrawText(NULL, Text, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	mLHand = mRHand = mLFoot = mRFoot = mMat;

	//移動中は手と足を振る
	if (MoveFlg == true)
	{
		switch (Change_LimbShakeFlg)
		{
		case true:
			LimbValue += 0.1f;
			if (LimbValue >= 1.0f)Change_LimbShakeFlg = false;
			break;
		case false:
			LimbValue -= 0.1f;
			if (LimbValue <= -1.0f)Change_LimbShakeFlg = true;
			break;
		}
	}
	else
	{
		LimbValue = 0.0f;
	}

	D3DXVECTOR3 LHRFvec, RHLFvec;
	LHRFvec = D3DXVECTOR3(LimbValue, 0, 0);
	D3DXVec3TransformCoord(&LHRFvec, &LHRFvec, &mLHand);
	RHLFvec = D3DXVECTOR3(-LimbValue, 0, 0);
	D3DXVec3TransformCoord(&RHLFvec, &RHLFvec, &mRHand);

	D3DXMatrixTranslation(&mLHand, LHRFvec.x, LHRFvec.y, LHRFvec.z);
	mLHand = mRot * mLHand;
	D3DXMatrixTranslation(&mRHand, RHLFvec.x, RHLFvec.y, RHLFvec.z);
	mRHand = mRot * mRHand;
	D3DXMatrixTranslation(&mLFoot, LHRFvec.x, LHRFvec.y, LHRFvec.z);
	mLFoot = mRot * mLFoot;
	D3DXMatrixTranslation(&mRFoot, RHLFvec.x, RHLFvec.y, RHLFvec.z);
	mRFoot = mRot * mRFoot;



	if (Pos.y <= -45)
	{
		Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	}
}

void Player::Draw()
{

	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);

	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mLHand);
	DrawMesh(GAMEDATA.lpD3DDevice, &xLHand, &mLHand);

	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mRHand);
	DrawMesh(GAMEDATA.lpD3DDevice, &xRHand, &mRHand);

	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mLFoot);
	DrawMesh(GAMEDATA.lpD3DDevice, &xLFoot, &mLFoot);

	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mRFoot);
	DrawMesh(GAMEDATA.lpD3DDevice, &xRFoot, &mRFoot);

	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void Player::Release()
{
	ReleaseMesh(&xMesh);
	ReleaseMesh(&xLHand);
	ReleaseMesh(&xRHand);
	ReleaseMesh(&xLFoot);
	ReleaseMesh(&xRFoot);
}


void Player::Attack(D3DXMATRIX _mRot)
{
	D3DXVECTOR3 vec,Dvec;
	vec = D3DXVECTOR3(1.5f,0,0);
	D3DXVec3TransformCoord(&vec, &vec, &_mRot);
	Pos += vec;

	Dvec = D3DXVECTOR3(0.5f, 0, 0);
	D3DXVec3TransformCoord(&Dvec, &Dvec, &_mRot);
	HitEnemy(_mRot, Dvec,D3DXVECTOR3(3.5f, 0.0f, 0.0f));
}


void Player::ObjColl(int ObjType,D3DXMATRIX _mMat,D3DXVECTOR3* _Pos,D3DXVECTOR3 _Normal,D3DXVECTOR3 _Push)
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
	}
}

bool Player::HitEnemy(D3DXMATRIX _mRot,D3DXVECTOR3 _Normal,D3DXVECTOR3 _Push)
{
	BOOL Hit;
	float Dis;
	for (auto itr = GAMEDATA.p_objectlist->ObjectList.begin(); itr != GAMEDATA.p_objectlist->ObjectList.end(); itr++) {
		if ((*itr)->Get_ObjType() != ENEMY && (*itr)->Get_ObjType() != POT)
		{
			continue;
		}

	/*	D3DXMATRIX mInv;
		D3DXMatrixInverse(&mInv, NULL, &(*itr)->GetMat());
		D3DXVECTOR3 LocalPos, LocalVec;

		D3DXVec3TransformCoord(&LocalPos, &(*itr)->GetPos(), &mInv);//計算上のレイ発射位置,実際のレイ発射位置,&mInv
		D3DXVec3TransformNormal(&LocalVec, &_Normal, &mInv);//計算上のレイ発射方向,実際のレイ実行方向,&mInv



		D3DXVec3TransformCoord(&LocalPos, &Pos, &mInv);//計算上のレイ発射位置,実際のレイ発射位置,&mInv

		D3DXIntersect((*itr)->GetMesh().lpMesh, &LocalPos, &LocalVec,&Hit, NULL, NULL, NULL, &Dis, NULL, NULL);
		//メッシュの形状,レイ発射位置,レイの発射方向,当たったかどうか,NULL,NULL,NULL,当たった場所までの距離,NULL,NULL
		//		LPD3DXFONT lpFont;
		//		char Text[200];
		//		D3DXCreateFont(lpD3DDevice, 0, 10, 500, 1, FALSE, SHIFTJIS_CHARSET, 0, 0, 0, NULL, &lpFont);
		//		lpFont->OnResetDevice();
		//		sprintf_s(Text, sizeof(Text), "StageDis:%f", StageDis);
		//		RECT rc = { 0, 0, 200, 200 };
		//		lpFont->DrawText(NULL, Text, -1, &rc, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (Hit) {*/

			if (GetLength(Pos, (*itr)->GetPos()) < 3.0f)
			{
				D3DXVECTOR3 vec;
					vec = _Normal;
				//	D3DXVec3TransformCoord(&vec, &vec, &_mRot);
					(*itr)->SetDamage(true, vec,1.0f);

					SOUND.SE_Play("Hit");

				return true;

			}
	//	}
		
	}
	
	return false;


}