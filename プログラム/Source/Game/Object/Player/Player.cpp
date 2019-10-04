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
	//�������W�ݒ�
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);

	//���b�V���ǂݍ���
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Chara_Body.x");//�{�f�B�[
	LoadMesh(GAMEDATA.lpD3DDevice, &xLHand, "Resource/Chara/Chara_LHand.x");//����
	LoadMesh(GAMEDATA.lpD3DDevice, &xRHand, "Resource/Chara/Chara_RHand.x");//�E��
	LoadMesh(GAMEDATA.lpD3DDevice, &xLFoot, "Resource/Chara/Chara_LFoot.x");//����
	LoadMesh(GAMEDATA.lpD3DDevice, &xRFoot, "Resource/Chara/Chara_RFoot.x");//�E��

	//�I�u�W�F�N�g�^�C�v�ݒ�
	Set_ObjType(PLAYER);

	//GAMEDATA.p_player =this;

	//�t�H���g�֘A�ݒ�B�f�o�b�O�Ɏg�p
	D3DXCreateFont(GAMEDATA.lpD3DDevice, 0, 10, 500, 1, FALSE, SHIFTJIS_CHARSET, 0, 0, 0, NULL, &lpFont);
	lpFont->OnResetDevice();

}

void Player::Update()
{
	//�s��
	D3DXMATRIX mTrans;
	D3DXMATRIX mRot;
	D3DXMATRIX mPos;

	//======================================
	//���_�̐ݒ�
	//�v���C���[�̓����ɍ��킹�Ĉړ�������
	//======================================

	//��{�ʒu
	//�E�B���h�E�̐^��
	GAMEDATA.BasePt.x = 320; GAMEDATA.BasePt.y = 240;

	
	POINT Pt;
	GetCursorPos(&Pt);
	Crad += (Pt.x - GAMEDATA.BasePt.x) / 9.0f;


	Urad += (Pt.y - GAMEDATA.BasePt.y) / 9.0f;
	if (Urad >= 6.0f) { Urad = 6.0f; }
	if (Urad <= -3.0f) { Urad = -3.0f; }

	//�J�[�\���ݒ�
	SetCursorPos(GAMEDATA.BasePt.x, GAMEDATA.BasePt.y);


	D3DXMatrixRotationY(&mRot, D3DXToRadian(Crad));


	//�J�������_�i�[
	D3DXVec3TransformCoord(&GAMEDATA.CPos, &D3DXVECTOR3(-8.0f, 5.0f + Urad, 0.0f), &mRot);
	GAMEDATA.CPos = GAMEDATA.CPos + Pos;
	GAMEDATA.CLook = Pos;
	GAMEDATA.CLook.y += 2.0f;

	//��������
	Pos.y += Accel;

	//���W�s��ݒ�
	D3DXMatrixTranslation(&mPos, Pos.x, Pos.y, Pos.z);

	//�Q�[�����X�^�[�g���Ă��鎞�݂̂̏���
	if (GAMEDATA.p_game->Get_GameStartFlg() == true)
	{
		//===================
		//�L�[�ݒ�
		//===================
		float MoveValue_x = 0.0f;
		float MoveValue_z = 0.0f;

		//W�L�[�����őO�i
		if (GetAsyncKeyState('W')) {

			MoveValue_x = 1.0f;

		}

		//S�L�[�����Ō��
		if (GetAsyncKeyState('S')) {
			MoveValue_x = -1.0f;


		}

		//A�L�[�����ō��ֈړ�
		if (GetAsyncKeyState('A')) {
			 MoveValue_z = 1.0f;


		}

		//D�L�[�ŉE�ֈړ�
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


		//�ړ��L�[�̉��ꂩ������
		if (MOVEKEY == true)
		{
			MoveFlg = true;
		}
		else
		{
			MoveFlg = false;
		}

		//�X�y�[�X�L�[�ŃW�����v
		if (GetAsyncKeyState(VK_SPACE))
		{
			if (JFlg == false)
			{
				JFlg = true;
				Accel += 1.0f;

				SOUND.SE_Play("Jump");
			}

		}

		//���N���b�N�ŃA�^�b�N
		//�������ŗ���
		//�����ƃA�^�b�N
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (AttackFlg == false)
			{
				AttackFlg = true;
				Attack_LButtonFlg = true;

			}
		}


		//�E�N���b�N
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			HaveEnemy();
		}


	}
	//GameStartFlg == true �I��

	
	//0�L�[�����Ńf�o�b�O�����`��
	if (GetAsyncKeyState('0'))
	{
		b_DebugFlg = true;
	}



	//���N���b�N��ArttackFlg��true�̎��݂̂̏���
	if (AttackFlg == true)
	{
		//���N���b�N���������̏���
		if (Attack_LButtonFlg == true)
		{
			//���N���b�N�����������痣�������̏���
			if (GetAsyncKeyState(VK_LBUTTON) == false)
			{
				OnAttackFlg = true;
				AttackTime = timeGetTime();
				
				//�G�t�F�N�g�폜
				EFFECT.DeleateEffect();

				SOUND.SE_Play("Attack");

				Attack_LButtonFlg = false;
			}
			else
			{
				//�G�t�F�N�g�`��p�ϐ����Z
				Attack_ChargeCnt++;
				if (Attack_ChargeCnt >= 197)Attack_ChargeCnt = 194;

				//�G�t�F�N�g����
				EFFECT.CreateEffect();
			}
		}
		
		//���N���b�N�𗣂��A�A�^�b�N���J�n���ꂽ���̏���
		if (OnAttackFlg == true)
		{
			Attack(mRot);
			if (timeGetTime() - AttackTime >= 100)
			{
				OnAttackFlg = false;
				AttackCoolTime = timeGetTime();
			}
		}

		//�A�^�b�N���I���������̏���
		//���Ԍo�߂܂ōă`���[�W�s�\�ɂ���
		if (OnAttackFlg == false)
		{
			if (timeGetTime() - AttackCoolTime >= 500 && Attack_LButtonFlg==false)
			{
				AttackFlg = false;
			//	Attack_ChargeCnt = 0;
			}
		}

	}
	//AttackFlg == true �I��


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
	

	//�X�e�[�W�Ƃ̏Փˏ���
	StageColl(mRot, &Pos, D3DXVECTOR3(0, -1, 0), D3DXVECTOR3(0, -0.5, 0));


	//=====================
	//�f�o�b�O����
	//���ݍ��W��\��
	//=====================
	char Text[200];

	//0�L�[���������ăt���O�𗧂��������̏���
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
	//�v���C���[�̋�������
	//�葫�̓��쓙
	//=====================

	mLHand = mRHand = mLFoot = mRFoot = mMat;

	//�ړ����͎�Ƒ���O��ɐU��
	//�~�܂��Ă鎞�͓������Ȃ�
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
	//�x�N�g���ݒ�
	LHRFvec = D3DXVECTOR3(LimbValue, 0, 0);
	D3DXVec3TransformCoord(&LHRFvec, &LHRFvec, &mLHand);
	RHLFvec = D3DXVECTOR3(-LimbValue, 0, 0);
	D3DXVec3TransformCoord(&RHLFvec, &RHLFvec, &mRHand);

	//�s��ݒ�
	D3DXMatrixTranslation(&mLHand, LHRFvec.x, LHRFvec.y, LHRFvec.z);
	mLHand = mRot * mLHand;
	D3DXMatrixTranslation(&mRHand, RHLFvec.x, RHLFvec.y, RHLFvec.z);
	mRHand = mRot * mRHand;
	D3DXMatrixTranslation(&mLFoot, LHRFvec.x, LHRFvec.y, LHRFvec.z);
	mLFoot = mRot * mLFoot;
	D3DXMatrixTranslation(&mRFoot, RHLFvec.x, RHLFvec.y, RHLFvec.z);
	mRFoot = mRot * mRFoot;


	//�X�e�[�W���痎�����珉���̍��W�ɖ߂�
	if (Pos.y <= -45)
	{
		Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	}
}

void Player::Draw()
{

	//��
	//�s��
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	//�`��
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);

	//����
	//�s��
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mLHand);
	//�`��
	DrawMesh(GAMEDATA.lpD3DDevice, &xLHand, &mLHand);

	//�E��
	//�s��
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mRHand);
	//�`��
	DrawMesh(GAMEDATA.lpD3DDevice, &xRHand, &mRHand);

	//����
	//�s��
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mLFoot);
	//�`��
	DrawMesh(GAMEDATA.lpD3DDevice, &xLFoot, &mLFoot);

	//�E��
	//�s��
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mRFoot);
	//�`��
	DrawMesh(GAMEDATA.lpD3DDevice, &xRFoot, &mRFoot);

}

void Player::Release()
{
	//���b�V���J��
	ReleaseMesh(&xMesh);
	ReleaseMesh(&xLHand);
	ReleaseMesh(&xRHand);
	ReleaseMesh(&xLFoot);
	ReleaseMesh(&xRFoot);
}


void Player::Attack(D3DXMATRIX _mRot)
{
	//�v���C���[��O�i������
	D3DXVECTOR3 vec,Dvec;
	vec = D3DXVECTOR3(1.5f,0,0);
	D3DXVec3TransformCoord(&vec, &vec, &_mRot);
	//Pos += vec;

	//�v���C���[�̑O�i���Ă���������擾
	Dvec = D3DXVECTOR3(0.5f, 0, 0);
	D3DXVec3TransformCoord(&Dvec, &Dvec, &_mRot);

	//�G�l�~�[�Ƃ̏Փ˔���
	HitEnemy(_mRot, Dvec,D3DXVECTOR3(3.5f, 0.0f, 0.0f));


	//�X�e�[�W�Ƃ̏Փˏ���
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

		D3DXVec3TransformCoord(&LocalPos, &(*itr)->GetPos(), &mInv);//�v�Z��̃��C���ˈʒu,���ۂ̃��C���ˈʒu,&mInv
		D3DXVec3TransformNormal(&LocalVec, &_Normal, &mInv);//�v�Z��̃��C���˕���,���ۂ̃��C���s����,&mInv



		D3DXVec3TransformCoord(&LocalPos, _Pos, &mInv);//�v�Z��̃��C���ˈʒu,���ۂ̃��C���ˈʒu,&mInv

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


				D3DXVec3TransformCoord(&LocalPos, &(*itr)->GetStagePos(i, j), &mInv);//�v�Z��̃��C���ˈʒu,���ۂ̃��C���ˈʒu,&mInv
				D3DXVec3TransformNormal(&LocalVec, &_Normal, &mInv);//�v�Z��̃��C���˕���,���ۂ̃��C���s����,&mInv



				D3DXVec3TransformCoord(&LocalPos, _Pos, &mInv);//�v�Z��̃��C���ˈʒu,���ۂ̃��C���ˈʒu,&mInv

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
	//�I�u�W�F�N�g���X�g����Pot��T��
	for (auto itr = GAMEDATA.p_objectlist->ObjectList.begin(); itr != GAMEDATA.p_objectlist->ObjectList.end(); itr++) {
		if ((*itr)->Get_ObjType() != POT)
		{
			continue;
		}

		//�ΏۃG�l�~�[���߂��ɂ�����ΏۃG�l�~�[���ӂ��Ƃ΂�
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

	//�I�u�W�F�N�g���X�g����Enemy��T��
	for (auto itr = GAMEDATA.p_objectlist->ObjList_Enemy.begin(); itr != GAMEDATA.p_objectlist->ObjList_Enemy.end(); itr++) {

		//�ΏۃG�l�~�[���߂��ɂ�����ΏۃG�l�~�[���ӂ��Ƃ΂�
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

	//�I�u�W�F�N�g���X�g����Enemy��T��
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