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

	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();

	//�I�u�W�F�N�g���X�g�֒ǉ�
	void AddObjList(std::shared_ptr<ObjBase> _Chara) { ObjectList.push_back(_Chara); }
	//�G�l�~�[���X�g�֒ǉ�
	void AddEnemyList(std::shared_ptr<Enemy> _Enemy) {ObjList_Enemy.push_back(_Enemy); }
	//�X�e�[�W���X�g�֒ǉ�
	void AddStageList(std::shared_ptr<Stage> _Stage) { ObjList_Stage.push_back(_Stage); }

	//�Q�b�^�[
	std::list<std::shared_ptr<ObjBase>> GetObjList() { return ObjectList; }
	std::list<std::shared_ptr<Enemy>> GetEnemyList() { return ObjList_Enemy; }
	std::list<std::shared_ptr<Stage>> GetStageList() { return ObjList_Stage; }


	//���X�g
	std::list<std::shared_ptr<ObjBase>> ObjectList;	//�S�ẴI�u�W�F�N�g�̃|�C���^���i�[
	std::list<std::shared_ptr<Enemy>> ObjList_Enemy;
	std::list<std::shared_ptr<Stage>> ObjList_Stage;

	//�I�u�W�F�N�g�^�C�v
	enum { PLAYER, ENEMY, STAGE, POT, OTHER };

private:
	//�G�l�~�[���폜���ꂽ�񐔂��J�E���g����
	int DelCnt = 0;

};

#endif