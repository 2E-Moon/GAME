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


void Pot::Init()
{
	LoadMesh(GAMEDATA.lpD3DDevice, &xMesh, "Resource/Chara/Pot_re.x");

	Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	Set_ObjType(POT);

	for (int i = 0; i < 5; i++) {
		iFoodHolder[i] = NONE;
	}

//	GAMEDATA.p_pot = this;
}

void Pot::Update()
{

	D3DXMATRIX mScal;
		D3DXMatrixScaling(&mScal, 2.5f, 2.5f, 2.5f);

	Pos.y += Accel;

	Accel -= 0.05f;
	if (Accel <= 0)
	{
		Accel = 0;
	}

	if (DamageFlg == true)
	{
		Pos += DamageVec;
	}
	else {

	}

	D3DXMatrixTranslation(&mMat, Pos.x, Pos.y, Pos.z);
	mMat = mScal * *mScal*mMat;


	D3DXMatrixRotationY(&mRot, D3DXToRadian(0));

	GetFood();

	switch (GetCook())
	{
	case CHIKENFRY:
		GAMEDATA.GetPoint += 500;
		GAMEDATA.GetCook = CHIKENFRY;
		break;
	case CHOKO:
		GAMEDATA.GetPoint += 700;
		GAMEDATA.GetCook = CHOKO;
		break;
	case CURRY:
		GAMEDATA.GetPoint += 1000;
		GAMEDATA.GetCook = CURRY;
		break;
	case PUDDING:
		GAMEDATA.GetPoint += 700;
		GAMEDATA.GetCook = PUDDING;
		break;
	case STEW:
		GAMEDATA.GetPoint += 1500;
		GAMEDATA.GetCook = STEW;
		break;
	}

	SortFood();

	ObjColl(STAGE, mRot, &Pos, D3DXVECTOR3(0, -1, 0), D3DXVECTOR3(0, -0.5, 0));


	if (Pos.y <= -45)
	{
		Pos = D3DXVECTOR3(DefPos_x, DefPos_y, DefPos_z);
	}

}

void Pot::Draw()
{
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_WORLD, &mMat);
	DrawMesh(GAMEDATA.lpD3DDevice, &xMesh, &mMat);
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void Pot::Release()
{
	ReleaseMesh(&xMesh);
}

void Pot::ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push) {
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

void Pot::GetFood()
{
	//リストからエネミーの情報をもってくる
	for (auto itr = GAMEDATA.p_objectlist->ObjList_Enemy.begin(); itr != GAMEDATA.p_objectlist->ObjList_Enemy.end(); itr++) {
		if ((*itr)->Get_DeleteFlg() == true)
		{
			continue;
		}
		//エネミーの距離がポットと近い場合
		if (GetLength(Pos, (*itr)->GetPos()) < 3.0f)
		{
			for (int i = 4; i >= 0; i--) {
				iFoodHolder[i + 1] = iFoodHolder[i];
			}
			iFoodHolder[0] = (*itr)->iFoodType;

			GAMEDATA.GetPoint += 100;
			if (GAMEDATA.Score >= 999999)
			{
				GAMEDATA.Score = 999999;
			}

			(*itr)->Set_DeleteFlg(true);
			
			SOUND.SE_Play("Get");
			
		}
		//	}

	}
}

//食材枠をソートする(上につめる)
void Pot::SortFood()
{
	iFoodHolder[5] = NONE;
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

	//素材の枠1～4個目を確認する。5個目は下に枠がないので確認しない
	for (int i = 0; i < 4; i++)
	{


		switch (iFoodHolder[i])
		{

			//牛肉
		case BEEF:
			//カレー
			//素材が3つなので、対象素材より下に2つ枠があるか確認する
			if (i >= 3)
			{
				break;
			}
			break;
			//カレーの素材かどうか
			//牛肉-じゃが-人参
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}
			//牛肉-人参-じゃが
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}

			//カカオ
		case CACAO:
			//チョコレート
			//チョコ-牛乳
			if (iFoodHolder[i + 1] == MILK)//プリンの素材以外なら飛ばす
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return CHOKO;
			}


			break;


			//人参
		case CARROT:
			//カレー
			//素材が3つなので、対象素材より下に2つ枠があるか確認する
			if (i >= 3)
			{
				break;
			}
			//カレーの素材かどうか
			//人参-じゃが-牛肉
			if (iFoodHolder[i + 1] == POTATO)
			{
				if (iFoodHolder[i + 2] == BEEF)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}
			//人参-牛肉-じゃが
			if (iFoodHolder[i + 1] == BEEF)
			{
				if (iFoodHolder[i + 2] == POTATO)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}
			break;


			//シチュー
			//素材が4つなので、対象素材より下に3つ枠があるか確認する
			if (i >= 2)
			{
				break;
			}
			//シチューの素材かどうか
			//人参-牛乳-鶏肉-じゃが
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
			//人参-牛乳-じゃが-鶏肉
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
			//人参-鶏肉-じゃが-牛乳
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
			//人参-鶏肉-牛乳-じゃが
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
			//人参-じゃが-牛乳-鶏肉
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
			//人参-じゃが-鶏肉-牛乳
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


			//鶏肉
		case CHICKEN:

			//唐揚げ
			if (iFoodHolder[i + 1] == CHICKEN)
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return CHIKENFRY;
			}

			//素材が4つなので、対象素材より下に3つ枠があるか確認する
			if (i >= 2)
			{
				break;
			}
			//シチューの素材かどうか
			//鶏肉-牛乳-人参-じゃが
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
			//鶏肉-牛乳-じゃが-人参
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
			//鶏肉-人参-じゃが-牛乳
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
			//鶏肉-人参-牛乳-じゃが
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
			//鶏肉-じゃが-牛乳-人参
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
			//鶏肉-じゃが-人参-牛乳
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

			//たまご
		case EGG:
			//プリン
			if (iFoodHolder[i + 1] == MILK)
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return PUDDING;
			}
			break;

			//牛乳
		case MILK:
			//プリン
			if (iFoodHolder[i + 1] == EGG)
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return PUDDING;
			}

			//プリン
			if (iFoodHolder[i + 1] == CACAO)
			{
				iFoodHolder[i] = iFoodHolder[i + 1] = NONE;
				return CHOKO;
			}

			//シチュー
			//素材が4つなので、対象素材より下に3つ枠があるか確認する
			if (i >= 2)
			{
				break;
			}
			//シチューの素材かどうか
			//牛乳-鶏肉-人参-じゃが
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
			//牛乳-鶏肉-じゃが-人参
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
			//牛乳-人参-じゃが-鶏肉
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
			//牛乳-人参-鶏肉-じゃが
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
			//牛乳-じゃが-鶏肉-人参
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
			//牛乳-じゃが-人参-鶏肉
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
			//カレー
			//素材が3つなので、対象素材より下に2つ枠があるか確認する
			if (i >= 3)
			{
				break;
			}
			break;
			//カレーの素材かどうか
			//じゃが-牛肉-人参
			if (iFoodHolder[i + 1] == BEEF)
			{
				if (iFoodHolder[i + 2] == CARROT)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}
			//じゃが-人参-牛肉
			if (iFoodHolder[i + 1] == CARROT)
			{
				if (iFoodHolder[i + 2] == BEEF)
				{
					iFoodHolder[i] = iFoodHolder[i + 1] = iFoodHolder[i + 2] = NONE;
					return CURRY;
				}
			}


			//シチュー
			//素材が4つなので、対象素材より下に3つ枠があるか確認する
			if (i >= 2)
			{
				break;
			}
			//シチューの素材かどうか
			//じゃが-鶏肉-人参-牛乳
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
			//じゃが-鶏肉-牛乳-人参
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
			//じゃが-人参-牛乳-鶏肉
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
			//じゃが-人参-鶏肉-牛乳
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
			//じゃが-牛乳-鶏肉-人参
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
			//じゃが-牛乳-人参-鶏肉
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