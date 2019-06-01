#ifndef __ObjList_h__
#define __ObjList_h__

#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<memory>
#include<iostream>


#include"ObjBase.h"
#include"Player/Player.h"
#include"Enemy/Enemy.h"
#include"Stage/Stage.h"
#include"Stage/BackGround.h"
#include"Stage/Sand.h"
#include"Gimmick/Pot.h"



class ObjList {
public:

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();


	void AddObjList(std::shared_ptr<ObjBase> _Chara) { ObjectList.push_back(_Chara); }
	void AddEnemyList(std::shared_ptr<Enemy> _Enemy) {ObjList_Enemy.push_back(_Enemy); }
	void AddStageList(std::shared_ptr<Stage> _Stage)  {ObjList_Stage.push_back(_Stage); }


	std::list<std::shared_ptr<ObjBase>> GetObjList() { return ObjectList; }
	std::list<std::shared_ptr<Enemy>> GetEnemyList() { return ObjList_Enemy; }
	std::list<std::shared_ptr<Stage>> GetStageList() { return ObjList_Stage; }

	std::list<std::shared_ptr<ObjBase>> ObjectList;	//全てのオブジェクトのポインタを格納
	std::list<std::shared_ptr<Enemy>> ObjList_Enemy;
	std::list<std::shared_ptr<Stage>> ObjList_Stage;

	enum { PLAYER, ENEMY, STAGE, POT, OTHER };

private:
	int DelCnt = 0;

};

#endif