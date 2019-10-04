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

#define ENEMY_COUNT 20

class ObjList {
public:

	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();

	//オブジェクトリストへ追加
	void AddObjList(std::shared_ptr<ObjBase> _Chara) { ObjectList.push_back(_Chara); }
	//エネミーリストへ追加
	void AddEnemyList(std::shared_ptr<Enemy> _Enemy) {ObjList_Enemy.push_back(_Enemy); }
	//ステージリストへ追加
	void AddStageList(std::shared_ptr<Stage> _Stage) { ObjList_Stage.push_back(_Stage); }

	//ゲッター
	std::list<std::shared_ptr<ObjBase>> GetObjList() { return ObjectList; }
	std::list<std::shared_ptr<Enemy>> GetEnemyList() { return ObjList_Enemy; }
	std::list<std::shared_ptr<Stage>> GetStageList() { return ObjList_Stage; }


	//リスト
	std::list<std::shared_ptr<ObjBase>> ObjectList;	//全てのオブジェクトのポインタを格納
	std::list<std::shared_ptr<Enemy>> ObjList_Enemy;
	std::list<std::shared_ptr<Stage>> ObjList_Stage;

	//オブジェクトタイプ
	enum { PLAYER, ENEMY, STAGE, POT, OTHER };

private:
	//エネミーが削除された回数をカウントする
	int DelCnt = 0;

};

#endif