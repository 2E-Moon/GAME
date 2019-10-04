//==================================================
//
//オブジェクトを管理するList用のクラス
//
//==================================================


#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<memory>
#include<iostream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include"../../GameData.h"

#include"ObjBase.h"

#include"Player/Player.h"
#include"Enemy/Enemy.h"
#include"Stage/Stage.h"
#include"Stage/BackGround.h"
#include"Stage/Sand.h"
#include"Gimmick/Pot.h"

#include"ObjList.h"

void ObjList::Init()
{
	//===========================
	//初期のオブジェクト生成
	//宣言→リスト追加→必要であればポインタ格納
	//の順番で行う
	//===========================

	//プレイヤー
	std::shared_ptr<Player> p_player = std::make_shared<Player>();
	AddObjList(p_player);
	GAMEDATA.p_player = p_player;

	//エネミー
	//ENEMY_COUNT の数値分生成する
	//エネミーはオブジェクト格納リストとは別にエネミーリストに追加する
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		std::shared_ptr<Enemy> p_enemy = std::make_shared<Enemy>();
		AddEnemyList(p_enemy);
	}

	//ステージ
	std::shared_ptr<Stage> p_stage = std::make_shared<Stage>();
	AddStageList(p_stage);

	//背景
	std::shared_ptr<Background> p_background = std::make_shared<Background>();
	AddObjList(p_background);

	//ステージ下の地面
	std::shared_ptr<Sand> p_sand = std::make_shared<Sand>();
	AddObjList(p_sand);

	//ポット
	std::shared_ptr<Pot> p_pot = std::make_shared<Pot>();
	AddObjList(p_pot);
	GAMEDATA.p_pot = p_pot;

	//リストに格納したオブジェクトを全て初期化
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Init();
	}

	//リストに格納したオブジェクトを全て初期化
	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++) {
		(*itr)->Init();
	}

	//リストに格納したオブジェクトを全て初期化
	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++) {
		(*itr)->Init();
	}

}

void ObjList::Update()
{
	//リスト内のオブジェクトを更新
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		//DeleteFlgがtrueの場合はReleaseを実行しリストから削除する
		if ((*itr)->Get_DeleteFlg() == true)
		{
			(*itr)->Release();
			itr = GAMEDATA.p_objectlist->ObjectList.erase(itr);
			continue;
		}
		(*itr)->Update();
	}

	//リスト内のエネミーを更新
	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++)
	{
		//DeleteFlgが立っている場合はリストから削除し、Enemyを新しく生成する
		if ((*itr)->Get_DeleteFlg() == true)
		{
			(*itr)->Release();
			itr = ObjList_Enemy.erase(itr);
			//削除カウントを増やす
			DelCnt++;

			itr = ObjList_Enemy.begin();
		}
		(*itr)->Update();
	}

	//削除カウントが増えたらその数だけエネミーの生成する
	if (DelCnt > 0)
	{
		for (int i = 0; i < DelCnt; i++)
		{
						std::shared_ptr<Enemy> p_enemy = std::make_shared<Enemy>();
						p_enemy->Init();

						AddEnemyList(p_enemy);
		}
		DelCnt = 0;
	}

	//リスト内のステージを更新
	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++)
	{
		(*itr)->Update();
	}

}

void ObjList::Draw()
{
	//リスト内のオブジェクトを描画
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Draw();
	}

	//リスト内のエネミーを描画
	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++)
	{
		(*itr)->Draw();
	}

	//リスト内のステージを描画
	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++)
	{
		(*itr)->Draw();
	}
}

void ObjList::Release()
{
	//リスト内のオブジェクトを解放
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Release();
	}

	//リスト内のエネミーを解放
	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++)
	{
		(*itr)->Release();
	}

	//リスト内のステージを解放
	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++)
	{
		(*itr)->Release();
	}

}
