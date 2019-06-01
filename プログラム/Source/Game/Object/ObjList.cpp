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



	std::shared_ptr<Player> p_player = std::make_shared<Player>();
	AddObjList(p_player);
	GAMEDATA.p_player = p_player;

	for (int i = 0; i < 20; i++)
	{
		std::shared_ptr<Enemy> p_enemy = std::make_shared<Enemy>();
		AddObjList(p_enemy);
		AddEnemyList(p_enemy);
	}

	std::shared_ptr<Stage> p_stage = std::make_shared<Stage>();
	std::shared_ptr<Background> p_background = std::make_shared<Background>();
	std::shared_ptr<Sand> p_sand = std::make_shared<Sand>();
	AddObjList(p_stage);
	AddObjList(p_background);
	AddObjList(p_sand);

	std::shared_ptr<Pot> p_pot = std::make_shared<Pot>();
	AddObjList(p_pot);
	GAMEDATA.p_pot = p_pot;


	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Init();
	}

}

void ObjList::Update()
{

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


	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++)
	{
		//DeleteFlgが立っている場合はリストから削除し、Enemyを新しく生成する
		if ((*itr)->Get_DeleteFlg() == true)
		{
			itr = GAMEDATA.p_objectlist->ObjList_Enemy.erase(itr);
			DelCnt++;

			continue;
		}
	}

	if (DelCnt > 0)
	{
		for (int i = 0; i < DelCnt; i++)
		{
						std::shared_ptr<Enemy> p_enemy = std::make_shared<Enemy>();
						p_enemy->Init();
						AddObjList(p_enemy);
						AddEnemyList(p_enemy);
		}
		DelCnt = 0;
	}

	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++)
	{
		itr = GAMEDATA.p_objectlist->ObjList_Stage.erase(itr);
		continue;
	}
}

void ObjList::Draw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Draw();
	}
}

void ObjList::Release()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Release();
	}
}
