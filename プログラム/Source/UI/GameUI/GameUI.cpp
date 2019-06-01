#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>

#include"../../GameData.h"
#include "../UIBase.h"
#include "GameUI.h"


#define Gage_Orange 101
#define Gage_Red 180

#define SCORE GAMEDATA.Score

#define GETFIRST GAMEDATA.p_result->Get_FirstScore()
#define GETSECOND GAMEDATA.p_result->Get_SecondScore()
#define GETTHIRD GAMEDATA.p_result->Get_ThirdScore()
#define GETFOURTH GAMEDATA.p_result->Get_FourthScore()
#define GETFIFTH GAMEDATA.p_result->Get_FifthScore()

//現在の残り時間を持ってくる
#define GETTIME GAMEDATA.p_game->Get_Time()
//現在の残り時間を1秒減らす
#define TIMEDOWN GAMEDATA.p_game->Set_Time(GAMEDATA.p_game->Get_Time() - 1)


void GameUI::Init()
{
	D3DXCreateSprite(GAMEDATA.lpD3DDevice, &lpSprite);
	lpSprite->OnResetDevice();

	//===============================================
	//UI読み込み
	//===============================================
	//ゲージUI
	LoadText(&lpPowerGage_g, "Resource/UI/PowerUI_gg.png", 200, 29, NULL);
	LoadText(&lpPowerGage_f, "Resource/UI/PowerUI_ff.png", 200, 35, NULL);

	//食材格納UI
	LoadText(&lpHolder, "Resource/UI/Holder.png", 50, 250, NULL);

	//食材UI
	LoadText(&lpBeef, "Resource/UI/Beef.png", 40, 40, NULL);
	LoadText(&lpCacao, "Resource/UI/Cacao.png", 40, 40, NULL);
	LoadText(&lpCarrot, "Resource/UI/Carrot.png", 40, 40, NULL);
	LoadText(&lpChicken, "Resource/UI/Chicken.png", 40, 40, NULL);
	LoadText(&lpEgg, "Resource/UI/Egg.png", 40, 40, NULL);
	LoadText(&lpMilk, "Resource/UI/Milk.png", 40, 40, NULL);
	LoadText(&lpMush, "Resource/UI/Mush.png", 40, 40, NULL);
	LoadText(&lpPotato, "Resource/UI/Potato.png", 40, 40, NULL);

	//料理UI
	LoadText(&lpChickenFry, "Resource/UI/ChickenFry.png", 200, 200, NULL);
	LoadText(&lpChoko, "Resource/UI/Choko.png", 200, 200, NULL);
	LoadText(&lpCurry, "Resource/UI/Curry.png", 200, 200, NULL);
	LoadText(&lpPudding, "Resource/UI/Pudding.png", 200, 200, NULL);
	LoadText(&lpStew, "Resource/UI/Stew.png", 180, 182, NULL);

	//時間UI
	LoadText(&lpStart, "Resource/UI/Start.png", 335, 75, NULL);
	LoadText(&lpTimeUp, "Resource/UI/TimeUp.png", 300, 49, NULL);
	LoadText(&lpNumber, "Resource/UI/NumFont1.png", 600, 120, NULL);
	LoadText(&lpNumber_r, "Resource/UI/NumFont1_red.png", 600, 120, NULL);
	LoadText(&lpMark, "Resource/UI/Mark.png", 180, 60, NULL);
	LoadText(&lpMark_r, "Resource/UI/Mark_r.png", 180, 60, NULL);


	//リザルトUI
	LoadText(&lpDark, "Resource/UI/Dark.png", 640, 480, NULL);
	LoadText(&lpFirst, "Resource/UI/1st.png", 179, 124, NULL);
	LoadText(&lpSecond, "Resource/UI/2nd.png", 179, 124, NULL);
	LoadText(&lpThird, "Resource/UI/3rd.png", 179, 124, NULL);
	LoadText(&lpFourth, "Resource/UI/4th.png", 179, 124, NULL);
	LoadText(&lpFifth, "Resource/UI/5th.png", 179, 124, NULL);


	strNowScore = std::make_shared<UI_ScoreStr>();
	strFirstScore = std::make_shared<UI_ScoreStr>();
	strSecondScore = std::make_shared<UI_ScoreStr>();
	strThirdScore = std::make_shared<UI_ScoreStr>();
	strFourthScore = std::make_shared<UI_ScoreStr>();
	strFifthScore = std::make_shared<UI_ScoreStr>();

	ST = timeGetTime();
}

void GameUI::Update()
{

	//パワーゲージの枠
	rc = { 0, 0, 200, 35 };
	D3DXMatrixTranslation(&mSprite, 50, 420, 0);

	//パワーゲージ
	uiGage.rc = { 0, 0,GAMEDATA.p_player->GetChargeCnt() , 29 };
	D3DXMatrixTranslation(&uiGage.mMat, 53, 423, 0);


	//食材格納枠
	uiHolder.rc = { 0,0,50,250 };
	D3DXMatrixTranslation(&uiHolder.mMat, 580, 10, 0);

	//格納中の食材
	for (int i = 0; i < 5; i++)
	{
		//食材格納枠
		uiFood[i].rc = { 0,0,40,40 };
		D3DXMatrixTranslation(&uiFood[i].mMat, 585, 50*i+5, 0);
	}


	//累積スコア
	Update_ScoreInfo(strNowScore, SCORE, 330, 400);
	/*
	//一の位
	uiScore_one.rc = { (SCORE-(SCORE/(int)10*10)) * 60, 0,(SCORE - (SCORE / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&uiScore_one.mMat, 580, 400, 0);

	//十の位
	uiScore_ten.rc = { ((SCORE/10) - ((SCORE / 10) / (int)10 * 10)) * 60, 0,((SCORE / 10) - ((SCORE / 10) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&uiScore_ten.mMat, 530, 400, 0);

	//百の位
	uiScore_hun.rc = { ((SCORE / 100) - ((SCORE / 100) / (int)10 * 10)) * 60, 0,((SCORE / 100) - ((SCORE / 100) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&uiScore_hun.mMat, 480, 400, 0);

	//千の位
	uiScore_tho.rc = { ((SCORE / 1000) - ((SCORE / 1000) / (int)10 * 10)) * 60, 0,((SCORE / 1000) - ((SCORE / 1000) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&uiScore_tho.mMat, 430, 400, 0);

	//万の位
	uiScore_tth.rc = { ((SCORE / 10000) - ((SCORE / 10000) / (int)10 * 10)) * 60, 0,((SCORE / 10000) - ((SCORE / 10000) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&uiScore_tth.mMat, 380, 400, 0);

	//十万の位
	uiScore_hth.rc = { ((SCORE / 100000) - ((SCORE / 100000) / (int)10 * 10)) * 60, 0,((SCORE / 100000) - ((SCORE / 100000) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&uiScore_hth.mMat, 330, 400, 0);
	*/


	//料理
	uiCook.rc = { 0,0,200,200 };
	D3DXMatrixTranslation(&uiCook.mMat, 400, 300 - fUp_GetPoint, 0);

	//加算スコア
	uiPlusScore_one.rc = { 0, 0,60,60 };
	D3DXMatrixTranslation(&uiPlusScore_one.mMat, 580, 350 - fUp_GetPoint, 0);
	uiPlusScore_ten.rc = { 0,0,60,60 };
	D3DXMatrixTranslation(&uiPlusScore_ten.mMat, 530, 350 - fUp_GetPoint, 0);
	uiPlusScore_hun.rc = { ((PlusScore / 100) - ((PlusScore / 100) / (int)10 * 10)) * 60, 0,((PlusScore / 100) - ((PlusScore / 100) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&uiPlusScore_hun.mMat, 480, 350 - fUp_GetPoint, 0);
	uiPlusScore_tho.rc = { ((PlusScore / 1000) - ((PlusScore / 1000) / (int)10 * 10)) * 60, 0,((PlusScore / 1000) - ((PlusScore / 1000) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&uiPlusScore_tho.mMat, 430, 350 - fUp_GetPoint, 0);
	uiPlusScore_pls.rc = { 60,60,120,120 };
	D3DXMatrixTranslation(&uiPlusScore_pls.mMat, 380, 350 - fUp_GetPoint, 0);



	//ゲーム開始前に表示するUIの設定
	if (GAMEDATA.p_game->Get_GameStartFlg() == false && GAMEDATA.p_game->Get_GameEndFlg() == false)
	{
		
		uiStart.rc = { 0, 0, 335, 75 };
		D3DXMatrixTranslation(&uiStart.mMat, 160, 200, 0);
		 
		uiStartCount.rc = { iTimeCount * 60, 0, iTimeCount * 60 + 60, 60 };
		D3DXMatrixTranslation(&uiStartCount.mMat, 290, 200, 0);

		//1秒経過でカウント-1
		if (timeGetTime() - ST > 1000) {
			iTimeCount--;
			ST = timeGetTime();
			if (iTimeCount < 0)
			{
				GAMEDATA.p_game->Set_GameStartFlg(true);
				ST = timeGetTime();
			}
		}


	}

	//ゲーム開始中のUI設定
	if (GAMEDATA.p_game->Get_GameStartFlg() == true)
	{
		int DrawTime;

		//何分
		DrawTime = GETTIME / 60;
		uiNumMinute.rc = { DrawTime * 60, 0, DrawTime * 60 + 60, 60 };
		D3DXMatrixTranslation(&uiNumMinute.mMat, 240, 10, 0);


		//分と秒の区切り
		uiNumColon.rc = { 60, 0, 90, 60 };
		D3DXMatrixTranslation(&uiNumColon.mMat, 300, 10, 0);


		//何十秒
		DrawTime = (GETTIME - (GETTIME / 60 * 60)) / 10;
		uiNumSec_tens.rc = { DrawTime * 60, 0, DrawTime * 60 + 60, 60 };
		D3DXMatrixTranslation(&uiNumSec_tens.mMat, 330, 10, 0);


		//何秒
		DrawTime = (GETTIME - (GETTIME / 60 * 60)) - (DrawTime * 10);
		uiNumSec_ones.rc = { DrawTime * 60, 0, DrawTime * 60 + 60, 60 };
		D3DXMatrixTranslation(&uiNumSec_ones.mMat, 380, 10, 0);



	}

	//時間切れの時に表示するUIの行列設定
	if (GAMEDATA.p_game->Get_GameEndFlg() == true)
	{
		uiEnd.rc = { 0, 0, 335, 75 };
		D3DXMatrixTranslation(&uiEnd.mMat, 160, 200, 0);
	}


	//リザルト表示に使う行列設定
	if (GAMEDATA.p_game->Get_ResultFlg() == true)
	{
		uiDark.rc = { 0,0,640,480 };
		D3DXMatrixTranslation(&uiDark.mMat, 0, 0, 0);



		D3DXMATRIX mScal;
		D3DXMatrixScaling(&mScal, 0.5f, 0.5f, 1.0f);

		//====
		//1位
		//====

		//文字
		uiFirst.rc = {0, 0, 179, 124};
		D3DXMatrixTranslation(&uiFirst.mMat, 20, 50, 0);
		uiFirst.mMat = mScal * uiFirst.mMat;

		//スコア
		Update_ScoreInfo(strFirstScore, GAMEDATA.p_result->Get_FirstScore(), 120, 55);


		//====
		//2位
		//====

		//文字
		uiSecond.rc = { 0, 0, 179, 124 };
		D3DXMatrixTranslation(&uiSecond.mMat, 20, 120, 0);
		uiSecond.mMat = mScal * uiSecond.mMat;

		//スコア
		Update_ScoreInfo(strSecondScore, GAMEDATA.p_result->Get_SecondScore(), 120, 125);

		//====
		//3位
		//====

		//文字
		uiThird.rc = { 0, 0, 179, 124 };
		D3DXMatrixTranslation(&uiThird.mMat, 20, 190, 0);
		uiThird.mMat = mScal * uiThird.mMat;

		//スコア
		Update_ScoreInfo(strThirdScore, GAMEDATA.p_result->Get_ThirdScore(), 120, 195);


		//====
		//4位
		//====

		//文字
		uiFourth.rc = { 0, 0, 179, 124 };
		D3DXMatrixTranslation(&uiFourth.mMat, 20, 260, 0);
		uiFourth.mMat = mScal * uiFourth.mMat;

		//スコア
		Update_ScoreInfo(strFourthScore, GAMEDATA.p_result->Get_FourthScore(), 120, 265);


		//====
		//5位
		//====

		//文字
		uiFifth.rc = { 0, 0, 179, 124 };
		D3DXMatrixTranslation(&uiFifth.mMat, 20, 330, 0);
		uiFifth.mMat = mScal * uiFifth.mMat;

		//スコア
		Update_ScoreInfo(strFifthScore, GAMEDATA.p_result->Get_FifthScore(), 120, 335);



	}


	if (GAMEDATA.GetPoint > 0)
	{
		GetPoint();
	}

	if (PlusScoreFlg == true)
	{
		fUp_GetPoint += 0.1f;
		Alpha_DrawScore--;
		if (Alpha_DrawScore <= 0)
		{
			PlusScoreFlg = false;
			GAMEDATA.GetCook = 999;
		}
	}
}

void GameUI::Draw()
{
	lpSprite->Begin(D3DXSPRITE_ALPHABLEND);

	lpSprite->SetTransform(&mSprite);
	lpSprite->Draw(lpPowerGage_f, &rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	lpSprite->SetTransform(&uiGage.mMat);
	lpSprite->Draw(lpPowerGage_g, &uiGage.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//食材格納枠
	lpSprite->SetTransform(&uiHolder.mMat);
	lpSprite->Draw(lpHolder, &uiHolder.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//格納中の食材
	for (int i = 0; i < 5; i++)
	{

		lpSprite->SetTransform(&uiFood[i].mMat);
		switch (GAMEDATA.p_pot->Get_FoodHolder(i))
		{
		case BEEF:
			lpSprite->Draw(lpBeef, &uiFood[i].rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case CACAO:
			lpSprite->Draw(lpCacao, &uiFood[i].rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case CARROT:
			lpSprite->Draw(lpCarrot, &uiFood[i].rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case CHICKEN:
			lpSprite->Draw(lpChicken, &uiFood[i].rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case EGG:
			lpSprite->Draw(lpEgg, &uiFood[i].rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case MILK:
			lpSprite->Draw(lpMilk, &uiFood[i].rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case MUSH:
			lpSprite->Draw(lpMush, &uiFood[i].rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
		case POTATO:
			lpSprite->Draw(lpPotato, &uiFood[i].rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;

		default:
			break;
		}
		
	}

	//
	//累計スコア表示
	//

	Draw_ScoreInfo(strNowScore);

	/*
	//一の位
	lpSprite->SetTransform(&uiScore_one.mMat);
	lpSprite->Draw(lpNumber, &uiScore_one.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//十の位
	lpSprite->SetTransform(&uiScore_ten.mMat);
	lpSprite->Draw(lpNumber, &uiScore_ten.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//百の位
	lpSprite->SetTransform(&uiScore_hun.mMat);
	lpSprite->Draw(lpNumber, &uiScore_hun.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//千の位
	lpSprite->SetTransform(&uiScore_tho.mMat);
	lpSprite->Draw(lpNumber, &uiScore_tho.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//万の位
	lpSprite->SetTransform(&uiScore_tth.mMat);
	lpSprite->Draw(lpNumber, &uiScore_tth.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//十万の位
	lpSprite->SetTransform(&uiScore_hth.mMat);
	lpSprite->Draw(lpNumber, &uiScore_hth.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	*/



	//ゲーム開始前のUI表示
	if (GAMEDATA.p_game->Get_GameStartFlg() == false && GAMEDATA.p_game->Get_GameEndFlg() == false) {
	
		if (iTimeCount == 0) {
			D3DXMatrixTranslation(&mSprite, 160, 200, 0);
			lpSprite->SetTransform(&uiStart.mMat);
			lpSprite->Draw(lpStart, &uiStart.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else {
			lpSprite->SetTransform(&uiStartCount.mMat);
			lpSprite->Draw(lpNumber, &uiStartCount.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}



	//ゲーム中のUI表示
	if (GAMEDATA.p_game->Get_GameStartFlg() == true)
	{

		lpSprite->SetTransform(&uiNumMinute.mMat);
		if (GETTIME <= 30) { lpSprite->Draw(lpNumber_r, &uiNumMinute.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255)); }
		else { 
			lpSprite->Draw(lpNumber, &uiNumMinute.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		lpSprite->SetTransform(&uiNumColon.mMat);
		if (GETTIME <= 30) { lpSprite->Draw(lpMark_r, &uiNumColon.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255)); }
		else { 
			lpSprite->Draw(lpMark, &uiNumColon.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		lpSprite->SetTransform(&uiNumSec_tens.mMat);
		if (GETTIME <= 30) { lpSprite->Draw(lpNumber_r, &uiNumSec_tens.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255)); }
		else {
			lpSprite->Draw(lpNumber, &uiNumSec_tens.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		lpSprite->SetTransform(&uiNumSec_ones.mMat);
		if (GETTIME <= 30) { lpSprite->Draw(lpNumber_r, &uiNumSec_ones.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255)); }
		else {
			lpSprite->Draw(lpNumber, &uiNumSec_ones.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		}

	}

	//ゲーム終了後のUI表示
	if (GAMEDATA.p_game->Get_GameStartFlg() == false && GAMEDATA.p_game->Get_GameEndFlg() == true)
	{
		D3DXMatrixTranslation(&mSprite, 160, 200, 0);
		lpSprite->SetTransform(&uiEnd.mMat);
		lpSprite->Draw(lpTimeUp, &uiEnd.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}



	if (PlusScoreFlg == true)
	{

		//
		//獲得料理表示
		//
		lpSprite->SetTransform(&uiCook.mMat);
		switch (GAMEDATA.GetCook)
		{
		case CHIKENFRY:
			lpSprite->Draw(lpChickenFry, &uiCook.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));
			break;
		case CHOKO:
			lpSprite->Draw(lpChoko, &uiCook.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));
			break;
		case CURRY:
			lpSprite->Draw(lpCurry, &uiCook.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));
			break;
		case PUDDING:
			lpSprite->Draw(lpPudding, &uiCook.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));
			break;
		case STEW:
			lpSprite->Draw(lpStew, &uiCook.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));
			break;

		}
	}


	//
	//加算スコア表示
	//

	if (PlusScoreFlg == true)
	{
		//一の位
		lpSprite->SetTransform(&uiPlusScore_one.mMat);
		lpSprite->Draw(lpNumber, &uiPlusScore_one.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));

		//十の位
		lpSprite->SetTransform(&uiPlusScore_ten.mMat);
		lpSprite->Draw(lpNumber, &uiPlusScore_ten.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));

		//百の位
		lpSprite->SetTransform(&uiPlusScore_hun.mMat);
		lpSprite->Draw(lpNumber, &uiPlusScore_hun.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));


		if (PlusScore - 1000 >= 0)
		{
			//千の位
			lpSprite->SetTransform(&uiPlusScore_tho.mMat);
			lpSprite->Draw(lpNumber, &uiPlusScore_tho.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));
		}

		//＋
		lpSprite->SetTransform(&uiPlusScore_pls.mMat);
		lpSprite->Draw(lpNumber, &uiPlusScore_pls.rc, NULL, NULL, D3DCOLOR_ARGB(Alpha_DrawScore, 255, 255, 255));

	}

	//リザルト表示
	//ランクインしてたら点滅
	if (GAMEDATA.p_game->Get_ResultFlg() ==true)
	{
		//背景
		lpSprite->SetTransform(&uiDark.mMat);
		lpSprite->Draw(lpDark, &uiDark.rc, NULL, NULL, D3DCOLOR_ARGB(150, 255, 255, 255));

		//1位
		lpSprite->SetTransform(&uiFirst.mMat);
		lpSprite->Draw(lpFirst, &uiFirst.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (GAMEDATA.p_result->Get_NowRank() == FIRST)
		{
			if (Blink_ScoreFlg == true)
			{
				Draw_ScoreInfo(strFirstScore);
			}
		}
		else
		{
			Draw_ScoreInfo(strFirstScore);
		}


		//2位
		lpSprite->SetTransform(&uiSecond.mMat);
		lpSprite->Draw(lpSecond, &uiSecond.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (GAMEDATA.p_result->Get_NowRank() == SECOND)
		{
			if (Blink_ScoreFlg == true)
			{
				Draw_ScoreInfo(strSecondScore);
			}
		}
		else
		{
			Draw_ScoreInfo(strSecondScore);
		}

		//3位
		lpSprite->SetTransform(&uiThird.mMat);
		lpSprite->Draw(lpThird, &uiThird.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (GAMEDATA.p_result->Get_NowRank() == THIRD)
		{
			if (Blink_ScoreFlg == true)
			{
				Draw_ScoreInfo(strThirdScore);
			}
		}
		else
		{
			Draw_ScoreInfo(strThirdScore);
		}

		//4位
		lpSprite->SetTransform(&uiFourth.mMat);
		lpSprite->Draw(lpFourth, &uiFourth.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (GAMEDATA.p_result->Get_NowRank() == FOURTH)
		{
			if (Blink_ScoreFlg == true)
			{
				Draw_ScoreInfo(strFourthScore);
			}
		}
		else
		{
			Draw_ScoreInfo(strFourthScore);
		}

		//5位
		lpSprite->SetTransform(&uiFifth.mMat);
		lpSprite->Draw(lpFifth, &uiFifth.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
		if (GAMEDATA.p_result->Get_NowRank() == FIFTH)
		{
			if (Blink_ScoreFlg == true)
			{
				Draw_ScoreInfo(strFifthScore);
			}
		}
		else
		{
			Draw_ScoreInfo(strFifthScore);
		}


		//スコア点滅処理
		if (timeGetTime() - Time_BlinkScore >= 500)
		{
			Blink_ScoreFlg = !Blink_ScoreFlg;
			Time_BlinkScore = timeGetTime();
		}
	}


	lpSprite->End();

}

void GameUI::Release()
{

	lpPowerGage_g->Release();
	lpPowerGage_f->Release();

	lpHolder->Release();

	lpBeef->Release();
	lpCacao->Release();
	lpCarrot->Release();
	lpChicken->Release();
	lpEgg->Release();
	lpMilk->Release();
	lpMush->Release();
	lpPotato->Release();

	lpChickenFry->Release();
	lpChoko->Release();
	lpCurry->Release();
	lpPudding->Release();
	lpStew->Release();

	 lpStart->Release();
	 lpTimeUp->Release();
	 lpNumber->Release();
	 lpNumber_r->Release();
	 lpMark->Release();
	 lpMark_r->Release();

	 lpDark->Release();
	 lpFirst->Release();
	 lpSecond->Release();
	 lpThird->Release();
	 lpFourth->Release();
	 lpFifth->Release();



	lpSprite->Release();
}


void GameUI::GetPoint()
{
		PlusScoreFlg = true;
		GAMEDATA.Score += GAMEDATA.GetPoint;
		PlusScore = GAMEDATA.GetPoint;
		GAMEDATA.GetPoint = 0;

		fUp_GetPoint = 0;
		Time_DrawScore = timeGetTime();
		Alpha_DrawScore = 255;

}

void GameUI::Update_ScoreInfo(std::shared_ptr<UI_ScoreStr> _Scorestr, int _Score, float _x, float _y, float _scal)
{
	//一の位
	_Scorestr->one.rc = { (_Score - (_Score / (int)10 * 10)) * 60, 0,(_Score - (_Score / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&_Scorestr->one.mMat, _x+250, _y, 0);
	_Scorestr->one.mMat = _scal * _Scorestr->one.mMat;

	//十の位
	_Scorestr->ten.rc = { ((_Score / 10) - ((_Score / 10) / (int)10 * 10)) * 60, 0,((_Score / 10) - ((_Score / 10) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&_Scorestr->ten.mMat, _x+200, _y, 0);
	_Scorestr->ten.mMat = _scal * _Scorestr->ten.mMat;

	//百の位
	_Scorestr->hun.rc = { ((_Score / 100) - ((_Score / 100) / (int)10 * 10)) * 60, 0,((_Score / 100) - ((_Score / 100) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&_Scorestr->hun.mMat, _x+150, _y, 0);
	_Scorestr->hun.mMat = _scal * _Scorestr->hun.mMat;

	//千の位
	_Scorestr->tho.rc = { ((_Score / 1000) - ((_Score / 1000) / (int)10 * 10)) * 60, 0,((_Score / 1000) - ((_Score / 1000) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&_Scorestr->tho.mMat, _x+100, _y, 0);
	_Scorestr->tho.mMat = _scal * _Scorestr->tho.mMat;

	//万の位
	_Scorestr->tth.rc = { ((_Score / 10000) - ((_Score / 10000) / (int)10 * 10)) * 60, 0,((_Score / 10000) - ((_Score / 10000) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&_Scorestr->tth.mMat, _x+50, _y, 0);
	_Scorestr->tth.mMat = _scal * _Scorestr->tth.mMat;

	//十万の位
	_Scorestr->hth.rc = { ((_Score / 100000) - ((_Score / 100000) / (int)10 * 10)) * 60, 0,((_Score / 100000) - ((_Score / 100000) / (int)10 * 10)) * 60 + 60, 60 };
	D3DXMatrixTranslation(&_Scorestr->hth.mMat, _x, _y, 0);
	_Scorestr->hth.mMat = _scal * _Scorestr->hth.mMat;

	//D3DXMatrixTranslation(&_Scorestr->hth.mMat, 330, 400, 0);
}

void GameUI::Draw_ScoreInfo(std::shared_ptr<UI_ScoreStr> _Scorestr)
{
	//一の位
	lpSprite->SetTransform(&_Scorestr->one.mMat);
	lpSprite->Draw(lpNumber, &_Scorestr->one.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//十の位
	lpSprite->SetTransform(&_Scorestr->ten.mMat);
	lpSprite->Draw(lpNumber, &_Scorestr->ten.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//百の位
	lpSprite->SetTransform(&_Scorestr->hun.mMat);
	lpSprite->Draw(lpNumber, &_Scorestr->hun.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//千の位
	lpSprite->SetTransform(&_Scorestr->tho.mMat);
	lpSprite->Draw(lpNumber, &_Scorestr->tho.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//万の位
	lpSprite->SetTransform(&_Scorestr->tth.mMat);
	lpSprite->Draw(lpNumber, &_Scorestr->tth.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	//十万の位
	lpSprite->SetTransform(&_Scorestr->hth.mMat);
	lpSprite->Draw(lpNumber, &_Scorestr->hth.rc, NULL, NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}