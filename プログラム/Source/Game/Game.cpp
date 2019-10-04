#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<dsound.h>//2Dサウンド
#include<memory>
#include<iostream>

#include"../GameData.h"

#include"Object/ObjBase.h"
#include"Object/Player/Player.h"
#include"Object/Enemy/Enemy.h"
#include"Object/Stage/Stage.h"
#include"Object/Stage/BackGround.h"
#include"Object/Stage/Sand.h"
#include"Object/Gimmick/Pot.h"

#include"Object/ObjList.h"

#include"Effect/Effect.h"

#include"Result/Result.h"

#include"../UI/UIBase.h"
#include"../UI/GameUI/GameUI.h"


#include "Game.h"


#define DEFTIME 120

void Game::Init()
{
	//オブジェクトリスト生成
	ObjectList = std::make_shared<ObjList>();
	ObjectList->Init();
	GAMEDATA.p_objectlist = ObjectList;

	//エフェクト
	EFFECT.Init();
	//ゲームUI
	g_ui.Init();
	//リザルト
	result = std::make_shared<Result>();
	result->Init();
	GAMEDATA.p_result = result;
	//シェーダ
	GAMEDATA.m_SampSh.Init();

	//ゲーム時間設定
	iTime = DEFTIME;
	ST = timeGetTime();


	//BGM再生
	SOUND.BGM_Play("Battle");
}

void Game::Update()
{
	//カーソル表示をOFF
	ShowCursor(FALSE);

	//オブジェクトリスト
	ObjectList->Update();
	//エフェクト
	EFFECT.Update();
	//ゲームUI
	g_ui.Update();
	//リザルト
	result->Update();

	//ゲーム開始フラグがtrueの場合
	if (isGame_StartFlg == true)
	{
		//1秒ごとに時間が減少していくようにする
		if (timeGetTime() - ST > 1000)
		{
			iTime--;
			ST = timeGetTime();
		}

		//残り0秒になったらゲーム終了のフラグを立たせる
		if (iTime < 0)
		{
			isGame_StartFlg = false;
			isGame_EndFlg = true;

			//SE再生
			SOUND.SE_Play("Whistle");

			//時間切れからリザルトまでの時間に使う
			ST = timeGetTime();
		}

		//デバッグ用
		//9キーで時間を早める
		if (GetAsyncKeyState('9'))
		{
			iTime--;
		}
	}

	//ゲーム終了フラグがtrueの場合
	if (isGame_EndFlg == true)
	{
		if (timeGetTime() - ST > 5000)
		{
			isResultFlg = true;
		}

	}


}

void Game::Draw()
{



	// シェーダにも射影行列をセット
	GAMEDATA.m_SampSh.SetTransformProj(&GAMEDATA.mProj);
	// シェーダにもカメラ情報をセット
	GAMEDATA.m_SampSh.SetTransformView(&GAMEDATA.mView);

	GAMEDATA.m_SampSh.SetCamPos(&D3DXVECTOR3(GAMEDATA.mView._41, GAMEDATA.mView._42, GAMEDATA.mView._43));	// シェーダにカメラ座標をセット

	//オブジェクトリスト
	ObjectList->Draw();
	//エフェクト
	EFFECT.Draw();
	//ゲームUI
	g_ui.Draw();
}

void Game::Release()
{
	//オブジェクトリスト
	ObjectList->Release();
	//エフェクト
	EFFECT.Release();
	//ゲームUI
	g_ui.Release();
	//リザルト
	result->Release();
	//シェーダ
	GAMEDATA.m_SampSh.Release();

}