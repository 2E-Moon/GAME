#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<dsound.h>//2D�T�E���h
#include<memory>
#include<iostream>

#include"../Game/Game.h"




#include"../UI/UIBase.h"
#include"../Title/Title_UI/Title_UI.h"
#include"../Title/Title.h"

#include"../GameData.h"

#include"Scene.h"


void Scene::Init()
{
	title = std::make_shared<Title>();
	GAMEDATA.p_title = title;

	game = std::make_shared<Game>();
	GAMEDATA.p_game = game;


	//�n�߂����Q�[�����[�h��1�ɂ���i�f�o�b�O�p�j
	if (1)
	{
		title->Init();
		GameMode = MODE_TITLE;
		GAMEDATA.GameMode = MODE_TITLE;

	}

	if (0)
	{
		game->Init();
		GameMode = MODE_GAME;
		GAMEDATA.GameMode = MODE_GAME;
	}

}

void Scene::Update()
{
	switch (GameMode)
	{
	case MODE_TITLE:
		title->Update();
		if (title->Get_GameMode_ChangeFlg() == true)
		{
			ChangeScene(MODE_GAME);
			title->Set_GameMode_ChangeFlg(false);

		}
		break;

	case MODE_GAME:
		game->Update();
		if (game->Get_GameMode_ChangeFlg() == true)
		{
			ChangeScene(MODE_TITLE);
			game->Set_GameMode_ChangeFlg(false);
		}
		break;
	}
}

void Scene::Draw()
{
	switch (GameMode)
	{
	case MODE_TITLE:
		title->Draw();
		break;

	case MODE_GAME:
		game->Draw();
		break;
	}
}

void Scene::Release()
{
	switch (GameMode)
	{
	case MODE_TITLE:
		title->Release();
		break;

	case MODE_GAME:
		game->Release();
		break;
	}
}

void Scene::ChangeScene(int _Mode)
{
	//���݂̃Q�[�����[�h�̉������
	switch (GameMode)
	{
	case MODE_TITLE:
		title->Release();
		
		break;

	case MODE_GAME:
		game->Release();
		break;
	}

	//���̃Q�[�����[�h�̏���
	switch (_Mode)
	{
	case MODE_TITLE:
		title->Init();
		break;

	case MODE_GAME:
		game->Init();
		break;
	}
	GameMode = _Mode;
	GAMEDATA.GameMode = _Mode;
}