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
	//初期座標設定
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);

	//メッシュ読み込み
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Chara_Body.x");//ボディー
	LoadMesh(GAMEDATA.lpD3DDevice, &xLHand, "Resource/Chara/Chara_LHand.x");//左手
	LoadMesh(GAMEDATA.lpD3DDevice, &xRHand, "Resource/Chara/Chara_RHand.x");//右手
	LoadMesh(GAMEDATA.lpD3DDevice, &xLFoot, "Resource/Chara/Chara_LFoot.x");//左足
	LoadMesh(GAMEDATA.lpD3DDevice, &xRFoot, "Resource/Chara/Chara_RFoot.x");//右足

	//オブジェクトタイプ設定
	Set_ObjType(PLAYER);

	//GAMEDATA.p_player =this;

	//フォント関連設定。デバッグに使用
	D3DXCreateFont(GAMEDATA.lpD3DDevice, 0, 10, 500, 1, FALSE, SHIFTJIS_CHARSET, 0, 0, 0, NULL, &lpFont);
	lpFont->OnResetDevice();

}

void Player::Update()
{
	//行列
	D3DXMATRIX mTrans;
	D3DXMATRIX mRot;
	D3DXMATRIX mPos;

	//======================================
	//視点の設定
	//プレイヤーの動きに合わせて移動させる
	//======================================

	//基本位置
	//ウィンドウの真ん中
	GAMEDATA.BasePt.x = 320; GAMEDATA.BasePt.y = 240;

	
	POINT Pt;
	GetCursorPos(&Pt);
	Crad += (Pt.x - GAMEDATA.BasePt.x) / 9.0f;


	Urad += (Pt.y - GAMEDATA.BasePt.y) / 9.0f;
	if (Urad >= 6.0f) { Urad = 6.0f; }
	if (Urad <= -3.0f) { Urad = -3.0f; }

	//カーソル設定
	SetCursorPos(GAMEDATA.BasePt.x, GAMEDATA.BasePt.y);


	D3DXMatrixRotationY(&mRot, D3DXToRadian(Crad));


	//カメラ視点格納
	D3DXVec3TransformCoord(&GAMEDATA.CPos, &D3DXVECTOR3(-8.0f, 5.0f + Urad, 0.0f), &mRot);
	GAMEDATA.CPos = GAMEDATA.CPos + Pos;
	GAMEDATA.CLook = Pos;
	GAMEDATA.CLook.y += 2.0f;

	//落下処理
	Pos.y += Accel;

	//座標行列設定
	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);

	//ゲームがスタートしている時のみの処理
	if (GAMEDATA.p_game->Get_GameStartFlg() == true)
	{
		//===================
		//キー設定
		//===================
		float MoveValue_x = 0.0f;
		float MoveValue_z = 0.0f;

		//Wキー押下で前進
		if (GetAsyncKeyState('W')) {

			MoveValue_x = 1.0f;

		}

		//Sキー押下で後退
		if (GetAsyncKeyState('S')) {
			MoveValue_x = -1.0f;


		}

		//Aキー押下で左へ移動
		if (GetAsyncKeyState('A')) {
			 MoveValue_z = 1.0f;


		}

		//Dキーで右へ移動
		if (GetAsyncKeyState('D')) {
			MoveValue_z = -1.0f;


		}


		if (MoveValue_x != 0.0f || MoveValue_z != 0.0f)
		{
			float Length  = sqrt(MoveValue_x * MoveValue_x + MoveValue_z * MoveValue_z);

			float Normal_x = MoveValue_x / Length;
			float Normal_z = MoveValue_z / Length;

			D3DXVECTOR3 vec;
			vec = D3DXVECTOR3(Normal_x, 0.0f, Normal_z);

			D3DXVec3TransformCoord(&vec, &vec, &mRot);


			StageColl(mRot, &Pos, vec, D3DXVECTOR3(Normal_x*0.25f, 0, Normal_z*0.25f));
		}


		//移動キーの何れかを押下
		if (MOVEKEY == true)
		{
			MoveFlg = true;
		}
		else
		{
			MoveFlg = false;
		}

		//スペースキーでジャンプ
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (JFlg == false)
			{
				JFlg = true;
				Accel += 1.0f;

				SOUND.SE_Play("Jump");
			}

		}

		//左クリックでアタック
		//長押しで溜め
		//離すとアタック
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (AttackFlg == false)
			{
				AttackFlg = true;
				Attack_LButtonFlg = true;

			}
		}


		//右クリック
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			HaveEnemy();
		}


	}
	//GameStartFlg == true 終了

	
	//0キー押下でデバッグ文字描画
	if (GetAsyncKeyState('0'))
	{
		b_DebugFlg = true;
	}



	//左クリックでArttackFlgがtrueの時のみの処理
	if (AttackFlg == true)
	{
		//左クリック長押し中の処理
		if (Attack_LButtonFlg == true)
		{
			//左クリック長押し中から離した時の処理
			if (GetAsyncKeyState(VK_LBUTTON) == false)
			{
				OnAttackFlg = true;
				AttackTime = timeGetTime();
				
				//エフェクト削除
				EFFECT.DeleateEffect();

				SOUND.SE_Play("Attack");

				Attack_LButtonFlg = false;
			}
			else
			{
				//エフェクト描画用変数加算
				Attack_ChargeCnt++;
				if (Attack_ChargeCnt >= 197)Attack_ChargeCnt = 194;

				//エフェクト生成
				EFFECT.CreateEffect();
			}
		}
		
		//左クリックを離し、アタックが開始された時の処理
		if (OnAttackFlg == true)
		{
			Attack(mRot);
			if (timeGetTime() - AttackTime >= 100)
			{
				OnAttackFlg = false;
				AttackCoolTime = timeGetTime();
			}
		}

		//アタックが終了した時の処理
		//時間経過まで再チャージ不可能にする
		if (OnAttackFlg == false)
		{
			if (timeGetTime() - AttackCoolTime >= 500 && Attack_LButtonFlg==false)
			{
				AttackFlg = false;
			//	Attack_ChargeCnt = 0;
			}
		}

	}
	//AttackFlg == true 終了


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


	mTrans = mRot * mPos;
	mMat = mTrans;
	

	//ステージとの衝突処理
	StageColl(mRot, &Pos, D3DXVECTOR3(0, -1, 0), D3DXVECTOR3(0, -0.5, 0));


	//=====================
	//デバッグ処理
	//現在座標を表示
	//=====================
	char Text[200];

	//0キーを押下してフラグを立たせた時の処理
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



	//=====================
	//プレイヤーの挙動処理
	//手足の動作等
	//=====================

	mLHand = mRHand = mLFoot = mRFoot = mMat;

	//移動中は手と足を前後に振る
	//止まってる時は動かさない
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
	//ベクトル設定
	LHRFvec = D3DXVECTOR3(LimbValue, 0, 0);
	D3DXVec3TransformCoord(&LHRFvec, &LHRFvec, &mLHand);
	RHLFvec = D3DXVECTOR3(-LimbValue, 0, 0);
	D3DXVec3TransformCoord(&RHLFvec, &RHLFvec, &mRHand);

	//行列設定
	D3DXMatrixTranslation(&mLHand, LHRFvec.x, LHRFvec.y, LHRFvec.z);
	mLHand = mRot * mLHand;
	D3DXMatrixTranslation(&mRHand, RHLFvec.x, RHLFvec.y, RHLFvec.z);
	mRHand = mRot * mRHand;
	D3DXMatrixTranslation(&mLFoot, LHRFvec.x, LHRFvec.y, LHRFvec.z);
	mLFoot = mRot * mLFoot;
	D3DXMatrixTranslation(&mRFoot, RHLFvec.x, RHLFvec.y, RHLFvec.z);
	mRFoot = mRot * mRFoot;


	//ステージから落ちたら初期の座標に戻る
	if (Pos.y <= -45)
	{
		Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	}
}

void Player::Draw()
{

	//体
	//行列
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	//描画
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);

	//左手
	//行列
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mLHand);
	//描画
	DrawMesh(GAMEDATA.lpD3DDevice, &xLHand, &mLHand);

	//右手
	//行列
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mRHand);
	//描画
	DrawMesh(GAMEDATA.lpD3DDevice, &xRHand, &mRHand);

	//左足
	//行列
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mLFoot);
	//描画
	DrawMesh(GAMEDATA.lpD3DDevice, &xLFoot, &mLFoot);

	//右足
	//行列
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mRFoot);
	//描画
	DrawMesh(GAMEDATA.lpD3DDevice, &xRFoot, &mRFoot);

}

void Player::Release()
{
	//メッシュ開放
	ReleaseMesh(&xMesh);
	ReleaseMesh(&xLHand);
	ReleaseMesh(&xRHand);
	ReleaseMesh(&xLFoot);
	ReleaseMesh(&xRFoot);
}


void Player::Attack(D3DXMATRIX _mRot)
{
	//プレイヤーを前進させる
	D3DXVECTOR3 vec,Dvec;
	vec = D3DXVECTOR3(1.5f,0,0);
	D3DXVec3TransformCoord(&vec, &vec, &_mRot);
	//Pos += vec;

	//プレイヤーの前進している方向を取得
	Dvec = D3DXVECTOR3(0.5f, 0, 0);
	D3DXVec3TransformCoord(&Dvec, &Dvec, &_mRot);

	//エネミーとの衝突判定
	HitEnemy(_mRot, Dvec,D3DXVECTOR3(3.5f, 0.0f, 0.0f));


	//ステージとの衝突処理
	StageColl(_mRot, &Pos,vec, D3DXVECTOR3(1, 0, 0));

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

void Player::StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push)
{
	float StageDis;
	BOOL Hit = false;
	for (auto itr = GAMEDATA.p_objectlist->ObjList_Stage.begin(); itr != GAMEDATA.p_objectlist->ObjList_Stage.end(); itr++) {


		for (int i = 0; i < STAGEVALUE; i++)
		{
			for (int j = 0; j < STAGEVALUE; j++)
			{
				
				if (GetLength(Pos, (*itr)->GetStagePos(i, j)) > 5.0f)
				{
					(*itr)->SetHitFlg(false, i, j);
					continue;
				}


				D3DXMATRIX mInv;
				D3DXVECTOR3 LocalPos, LocalVec;

				D3DXMatrixInverse(&mInv, NULL, &(*itr)->GetStageMat(i,j));


				D3DXVec3TransformCoord(&LocalPos, &(*itr)->GetStagePos(i, j), &mInv);//計算上のレイ発射位置,実際のレイ発射位置,&mInv
				D3DXVec3TransformNormal(&LocalVec, &_Normal, &mInv);//計算上のレイ発射方向,実際のレイ実行方向,&mInv



				D3DXVec3TransformCoord(&LocalPos, _Pos, &mInv);//計算上のレイ発射位置,実際のレイ発射位置,&mInv

				D3DXIntersect((*itr)->GetMesh().lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &StageDis, NULL, NULL);
				if (Hit) {
					(*itr)->SetHitFlg(true, i, j);
					break;
				}
				else {
					(*itr)->SetHitFlg(false, i, j);
				}
			}
			if (Hit)break;
		}
		

	}

	if (!Hit || (Hit&&StageDis>1.0f)) {
		D3DXVECTOR3 vec;
		vec = _Push;
		D3DXVec3TransformCoord(&vec, &vec, &_mMat);
		*_Pos += vec;
		MoveVec = vec;
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
	//オブジェクトリストからPotを探す
	for (auto itr = GAMEDATA.p_objectlist->ObjectList.begin(); itr != GAMEDATA.p_objectlist->ObjectList.end(); itr++) {
		if ((*itr)->Get_ObjType() != POT)
		{
			continue;
		}

		//対象エネミーが近くにいたら対象エネミーをふっとばす
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

	//オブジェクトリストからEnemyを探す
	for (auto itr = GAMEDATA.p_objectlist->ObjList_Enemy.begin(); itr != GAMEDATA.p_objectlist->ObjList_Enemy.end(); itr++) {

		//対象エネミーが近くにいたら対象エネミーをふっとばす
		if (GetLength(Pos, (*itr)->GetPos()) < 3.0f)
		{
			D3DXVECTOR3 vec;
			vec = _Normal;
			//	D3DXVec3TransformCoord(&vec, &vec, &_mRot);
			(*itr)->SetDamage(true, vec, 1.0f);

			SOUND.SE_Play("Hit");

			return true;

		}
		//	}

	}
	
	return false;


}

void Player::HaveEnemy()
{
	if (timeGetTime() - HaveTime <= 500)
	{
		return;
	}

	//オブジェクトリストからEnemyを探す
	for (auto itr = GAMEDATA.p_objectlist->ObjList_Enemy.begin(); itr != GAMEDATA.p_objectlist->ObjList_Enemy.end(); itr++) {

		if ((*itr)->GetCarryToPlayerFlg() == true)
		{
			(*itr)->SetCarryToPlayerFlg(false);
			HaveEnemyFlg = false;
			HaveTime = timeGetTime();
			break;
		}

		if (GetLength(Pos, (*itr)->GetPos()) < 3.0f && HaveEnemyFlg==false)
		{
			(*itr)->SetCarryToPlayerFlg(true);
			HaveEnemyFlg = true;
			HaveTime = timeGetTime();
			break;
		}

	}

}