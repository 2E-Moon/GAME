//==================================================
//
//�I�u�W�F�N�g���Ǘ�����List�p�̃N���X
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
	//�����̃I�u�W�F�N�g����
	//�錾�����X�g�ǉ����K�v�ł���΃|�C���^�i�[
	//�̏��Ԃōs��
	//===========================

	//�v���C���[
	std::shared_ptr<Player> p_player = std::make_shared<Player>();
	AddObjList(p_player);
	GAMEDATA.p_player = p_player;

	//�G�l�~�[
	//ENEMY_COUNT �̐��l����������
	//�G�l�~�[�̓I�u�W�F�N�g�i�[���X�g�Ƃ͕ʂɃG�l�~�[���X�g�ɒǉ�����
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		std::shared_ptr<Enemy> p_enemy = std::make_shared<Enemy>();
		AddEnemyList(p_enemy);
	}

	//�X�e�[�W
	std::shared_ptr<Stage> p_stage = std::make_shared<Stage>();
	AddStageList(p_stage);

	//�w�i
	std::shared_ptr<Background> p_background = std::make_shared<Background>();
	AddObjList(p_background);

	//�X�e�[�W���̒n��
	std::shared_ptr<Sand> p_sand = std::make_shared<Sand>();
	AddObjList(p_sand);

	//�|�b�g
	std::shared_ptr<Pot> p_pot = std::make_shared<Pot>();
	AddObjList(p_pot);
	GAMEDATA.p_pot = p_pot;

	//���X�g�Ɋi�[�����I�u�W�F�N�g��S�ď�����
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Init();
	}

	//���X�g�Ɋi�[�����I�u�W�F�N�g��S�ď�����
	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++) {
		(*itr)->Init();
	}

	//���X�g�Ɋi�[�����I�u�W�F�N�g��S�ď�����
	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++) {
		(*itr)->Init();
	}

}

void ObjList::Update()
{
	//���X�g���̃I�u�W�F�N�g���X�V
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		//DeleteFlg��true�̏ꍇ��Release�����s�����X�g����폜����
		if ((*itr)->Get_DeleteFlg() == true)
		{
			(*itr)->Release();
			itr = GAMEDATA.p_objectlist->ObjectList.erase(itr);
			continue;
		}
		(*itr)->Update();
	}

	//���X�g���̃G�l�~�[���X�V
	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++)
	{
		//DeleteFlg�������Ă���ꍇ�̓��X�g����폜���AEnemy��V������������
		if ((*itr)->Get_DeleteFlg() == true)
		{
			(*itr)->Release();
			itr = ObjList_Enemy.erase(itr);
			//�폜�J�E���g�𑝂₷
			DelCnt++;

			itr = ObjList_Enemy.begin();
		}
		(*itr)->Update();
	}

	//�폜�J�E���g���������炻�̐������G�l�~�[�̐�������
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

	//���X�g���̃X�e�[�W���X�V
	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++)
	{
		(*itr)->Update();
	}

}

void ObjList::Draw()
{
	//���X�g���̃I�u�W�F�N�g��`��
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Draw();
	}

	//���X�g���̃G�l�~�[��`��
	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++)
	{
		(*itr)->Draw();
	}

	//���X�g���̃X�e�[�W��`��
	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++)
	{
		(*itr)->Draw();
	}
}

void ObjList::Release()
{
	//���X�g���̃I�u�W�F�N�g�����
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); itr++) {
		(*itr)->Release();
	}

	//���X�g���̃G�l�~�[�����
	for (auto itr = ObjList_Enemy.begin(); itr != ObjList_Enemy.end(); itr++)
	{
		(*itr)->Release();
	}

	//���X�g���̃X�e�[�W�����
	for (auto itr = ObjList_Stage.begin(); itr != ObjList_Stage.end(); itr++)
	{
		(*itr)->Release();
	}

}
