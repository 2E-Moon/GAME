#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>

#include"../ObjBase.h"
#include"Pot.h"
#include"../../../GameData.h"

#define DefPos_x 0
#define DefPos_y 10
#define DefPos_z 0

#define MAXSCORE 999999

void Pot::Init()
{
	//���b�V���ǂݍ���
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Pot_re.x");

	//�������W�ݒ�
	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	//�I�u�W�F�^�C�v�ݒ�
	Set_ObjType(POT);
	
	//�H�ފi�[�z���_�[�ϐ������ׂċ�ɂ���
	for (int i = 0; i < 5; i++) {
		iFoodHolder[i] = NONE;
	}
}

void Pot::Update()
{
	//�s��
	D3DXMATRIX mRot;
	D3DXMATRIX mScal;

	//�T�C�Y�ݒ�
	D3DXMatrixScaling(&mScal, 2.5f, 2.5f, 2.5f);

	//=========
	//��������
	//=========
	Pos.y += Accel;
	Accel -= 0.05f;
	if (Accel <= 0)
	{
		Accel = 0;
	}

	//�v���C���[�ɃA�^�b�N���ꂽ���̏���
	if (DamageFlg == true)
	{
		Pos += DamageVec;
	}
	else {

	}

	//�s��ݒ�
	D3DXMatrixTranslation(&mMat, Pos.x, Pos.y, Pos.z);
	mMat = mScal * *mScal*mMat;


	D3DXMatrixRotationY(&mRot, D3DXToRadian(0));

	//�H�ފl������
	//�߂��ɐH�ނ������iFoodHolder�Ɋi�[
	GetFood();

	//��������
	//�H�ނ������Ă���΂��̐H�ނ�����|�C���g���l������
	//UI�p��GetCook�ɑΏۂ̗������i�[
	switch (GetCook())
	{
		//���g��
	case CHIKENFRY:
		GAMEDATA.GetPoint += 500;
		GAMEDATA.GetCook = CHIKENFRY;
		break;
		//�`���R���[�g
	case CHOKO:
		GAMEDATA.GetPoint += 700;
		GAMEDATA.GetCook = CHOKO;
		break;
		//�J���[
	case CURRY:
		GAMEDATA.GetPoint += 1000;
		GAMEDATA.GetCook = CURRY;
		break;
		//�v����
	case PUDDING:
		GAMEDATA.GetPoint += 700;
		GAMEDATA.GetCook = PUDDING;
		break;
		//�V�`���[
	case STEW:
		GAMEDATA.GetPoint += 1500;
		GAMEDATA.GetCook = STEW;
		break;
	}

	//�H�ފi�[�z���_�[�̐���
	SortFood();

	//�X�e�[�W�Ƃ̏Փ˔���
	StageColl(mRot, &Pos, D3DXVECTOR3(0, -1, 0), D3DXVECTOR3(0, -0.5, 0));

	//�X�e�[�W���痎�����ꍇ�͏����ʒu�Ɉړ�������
	if (Pos.y <= -45)
	{
		Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	}

}

void Pot::Draw()
{
	//�s��ݒ�
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	//�`��
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);

}

void Pot::Release()
{
	//���b�V�����
	ReleaseMesh(&xMesh);
}

void Pot::ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push) {
	//�ΏۃI�u�W�F�N�g�Ƃ̋���
	float StageDis;

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

		D3DXIntersect((*itr)->GetMesh().lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &StageDis, NULL, NULL);
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

void Pot::StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push)
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


void Pot::GetFood()
{
	//���X�g����G�l�~�[�̏��������Ă���
	for (auto itr = GAMEDATA.p_objectlist->ObjList_Enemy.begin(); itr != GAMEDATA.p_objectlist->ObjList_Enemy.end(); itr++) {
		if ((*itr)->Get_DeleteFlg() == true)
		{
			continue;
		}

		if ((*itr)->GetCarryToPlayerFlg() == true)
		{
			continue;
		}

		//�G�l�~�[�̋������|�b�g�Ƌ߂��ꍇ
		if (GetLength(Pos, (*itr)->GetPos()) < 3.0f)
		{
			//���g�̐H�ނ�������ɂ��炵�A�擪�Ɋl�������A�C�e�����i�[
			for (int i = 4; i >= 0; i--) {
				iFoodHolder[i + 1] = iFoodHolder[i];
			}
			iFoodHolder[0] = (*itr)->iFoodType;

			//�|�C���g�����Z����B�ő�MAXSCORE�ŌŒ肷��
			GAMEDATA.GetPoint += 100;
			if (GAMEDATA.Score >= MAXSCORE)
			{
				GAMEDATA.Score = MAXSCORE;
			}

			(*itr)->Set_DeleteFlg(true);
			
			SOUND.SE_Play("Get");
			
		}
		//	}

	}
}

//�H�ޘg���\�[�g����(��ɂ߂�)
void Pot::SortFood()
{
	//�i�[�ϐ���6��(�\������Ȃ��g)�̒��g������
	iFoodHolder[5] = NONE;
	//�󔒂̘g������Ό��̂��̂������Ă���
	for (int i = 0; i < 4; i++)
	{
		if (iFoodHolder[i] == NONE)
		{
			iFoodHolder[i] = iFoodHolder[i + 1];
			iFoodHolder[i + 1] = NONE;
		}
	}

}



int Pot::GetCook()
{

	//�f�ނ̘g1�`4�ڂ��m�F����B5�ڂ͉��ɘg���Ȃ��̂Ŋm�F���Ȃ�
	for (int i = 0; i < 4; i++)
	{


		switch (iFoodHolder[i])
		{

			//����
		case BEEF:
			//�J���[
			//�f�ނ�3�Ȃ̂ŁA�Ώۑf�ނ�艺��2�g�����邩�m�F����
			if (i >= 3)
			{
				break;
			}
			break;
			//�J���[�̑f�ނ��ǂ���
			//����-���Ⴊ-�l�Q
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}
			//����-�l�Q-���Ⴊ
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}

			//�J�J�I
		case CACAO:
			//�`���R���[�g
			//�`���R-����
			if (iFoodHolder[i + 1] == MILK)//�v�����̑f�ވȊO�Ȃ��΂�
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return CHOKO;
			}


			break;


			//�l�Q
		case CARROT:
			//�J���[
			//�f�ނ�3�Ȃ̂ŁA�Ώۑf�ނ�艺��2�g�����邩�m�F����
			if (i >= 3)
			{
				break;
			}
			//�J���[�̑f�ނ��ǂ���
			//�l�Q-���Ⴊ-����
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == BEEF)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}
			//�l�Q-����-���Ⴊ
			if (iFoodHolder[i + 1] == BEEF)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}
			break;


			//�V�`���[
			//�f�ނ�4�Ȃ̂ŁA�Ώۑf�ނ�艺��3�g�����邩�m�F����
			if (i >= 2)
			{
				break;
			}
			//�V�`���[�̑f�ނ��ǂ���
			//�l�Q-����-�{��-���Ⴊ
			if (iFoodHolder[i + 1] == MILK)
			{
				if (iFoodHolder[i + 2] == CHICKEN)
				{
					if (iFoodHolder[i + 3] == POTATO)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�l�Q-����-���Ⴊ-�{��
			if (iFoodHolder[i + 1] == MILK)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					if (iFoodHolder[i + 3] == CHICKEN)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�l�Q-�{��-���Ⴊ-����
			if (iFoodHolder[i + 1] == CHICKEN)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					if (iFoodHolder[i + 3] == MILK)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�l�Q-�{��-����-���Ⴊ
			if (iFoodHolder[i + 1] == CHICKEN)
			{
				if (iFoodHolder[i + 2] == MILK)
				{
					if (iFoodHolder[i + 3] == POTATO)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�l�Q-���Ⴊ-����-�{��
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == MILK)
				{
					if (iFoodHolder[i + 3] == CHICKEN)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�l�Q-���Ⴊ-�{��-����
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == CHICKEN)
				{
					if (iFoodHolder[i + 3] == MILK)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			break;


			//�{��
		case CHICKEN:

			//���g��
			if (iFoodHolder[i + 1] == CHICKEN)
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return CHIKENFRY;
			}

			//�f�ނ�4�Ȃ̂ŁA�Ώۑf�ނ�艺��3�g�����邩�m�F����
			if (i >= 2)
			{
				break;
			}
			//�V�`���[�̑f�ނ��ǂ���
			//�{��-����-�l�Q-���Ⴊ
			if (iFoodHolder[i + 1] == MILK)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					if (iFoodHolder[i + 3] == POTATO)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�{��-����-���Ⴊ-�l�Q
			if (iFoodHolder[i + 1] == MILK)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					if (iFoodHolder[i + 3] == CARROT)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�{��-�l�Q-���Ⴊ-����
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					if (iFoodHolder[i + 3] == MILK)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�{��-�l�Q-����-���Ⴊ
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == MILK)
				{
					if (iFoodHolder[i + 3] == POTATO)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�{��-���Ⴊ-����-�l�Q
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == MILK)
				{
					if (iFoodHolder[i + 3] == CARROT)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//�{��-���Ⴊ-�l�Q-����
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					if (iFoodHolder[i + 3] == MILK)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}


			break;

			//���܂�
		case EGG:
			//�v����
			if (iFoodHolder[i + 1] == MILK)
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return PUDDING;
			}
			break;

			//����
		case MILK:
			//�v����
			if (iFoodHolder[i + 1] == EGG)
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return PUDDING;
			}

			//�v����
			if (iFoodHolder[i + 1] == CACAO)
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return CHOKO;
			}

			//�V�`���[
			//�f�ނ�4�Ȃ̂ŁA�Ώۑf�ނ�艺��3�g�����邩�m�F����
			if (i >= 2)
			{
				break;
			}
			//�V�`���[�̑f�ނ��ǂ���
			//����-�{��-�l�Q-���Ⴊ
			if (iFoodHolder[i + 1] == CHICKEN)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					if (iFoodHolder[i + 3] == POTATO)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//����-�{��-���Ⴊ-�l�Q
			if (iFoodHolder[i + 1] == CHICKEN)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					if (iFoodHolder[i + 3] == CARROT)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//����-�l�Q-���Ⴊ-�{��
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					if (iFoodHolder[i + 3] == CHICKEN)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//����-�l�Q-�{��-���Ⴊ
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == CHICKEN)
				{
					if (iFoodHolder[i + 3] == POTATO)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//����-���Ⴊ-�{��-�l�Q
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == CHICKEN)
				{
					if (iFoodHolder[i + 3] == CARROT)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//����-���Ⴊ-�l�Q-�{��
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					if (iFoodHolder[i + 3] == CHICKEN)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}

			break;

		case MUSH:

			break;
		case POTATO:
			//�J���[
			//�f�ނ�3�Ȃ̂ŁA�Ώۑf�ނ�艺��2�g�����邩�m�F����
			if (i >= 3)
			{
				break;
			}
			break;
			//�J���[�̑f�ނ��ǂ���
			//���Ⴊ-����-�l�Q
			if (iFoodHolder[i + 1] == BEEF)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}
			//���Ⴊ-�l�Q-����
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == BEEF)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}


			//�V�`���[
			//�f�ނ�4�Ȃ̂ŁA�Ώۑf�ނ�艺��3�g�����邩�m�F����
			if (i >= 2)
			{
				break;
			}
			//�V�`���[�̑f�ނ��ǂ���
			//���Ⴊ-�{��-�l�Q-����
			if (iFoodHolder[i + 1] == CHICKEN)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					if (iFoodHolder[i + 3] == MILK)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//���Ⴊ-�{��-����-�l�Q
			if (iFoodHolder[i + 1] == CHICKEN)
			{
				if (iFoodHolder[i + 2] == MILK)
				{
					if (iFoodHolder[i + 3] == CARROT)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//���Ⴊ-�l�Q-����-�{��
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == MILK)
				{
					if (iFoodHolder[i + 3] == CHICKEN)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//���Ⴊ-�l�Q-�{��-����
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == CHICKEN)
				{
					if (iFoodHolder[i + 3] == MILK)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//���Ⴊ-����-�{��-�l�Q
			if (iFoodHolder[i + 1] == MILK)
			{
				if (iFoodHolder[i + 2] == CHICKEN)
				{
					if (iFoodHolder[i + 3] == CARROT)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}
			//���Ⴊ-����-�l�Q-�{��
			if (iFoodHolder[i + 1] == MILK)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					if (iFoodHolder[i + 3] == CHICKEN)
					{
						iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = iFoodHolder[i + 3] = NONE;
						return STEW;
					}
				}
			}

			break;

		}

	}
	return NONE;

}