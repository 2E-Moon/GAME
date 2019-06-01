#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<memory>
#include<iostream>

#include<dsound.h>//2Dサウンド

#include"Game/Object/ObjBase.h"
#include"Game/Object/Player/Player.h"
#include"Game/Object/Enemy/Enemy.h"
#include"Game/Object/Stage/Stage.h"
#include"Game/Object/Stage/BackGround.h"
#include"Game/Object/Stage/Sand.h"
#include"Game/Object/ObjList.h"
#include"Game/Game.h"

#include"Shader/Shader.h"

#include<dsound.h>//2Dサウンド
#include"Sound/wavread.h"
#include"Sound/Sound.h"

#include"UI/UIBase.h"
#include"Title/Title_UI/Title_UI.h"

#include"Title/Title.h"

#include"Game/Result/Result.h"

#include"Scene/Scene.h"


#ifndef __Game_Data_h__
#define __Game_Data_h__

//	データのシングルトンを返すマクロ
#define GAMEDATA GameData::GetInstance()
#define MODE_TITLE 0
#define MODE_GAME 1

/*=============

Class宣言

=============*/

class GameData
{
public:

	//--------------------------
	//	シングルトンパターン生成
	//--------------------------
	static GameData& GetInstance()
	{
		static GameData Instance;
		return Instance;
	}



	std::shared_ptr<Scene> p_scene;

	POINT BasePt;

	LPDIRECT3D9				lpD3D;		// Direct3Dインターフェイス
	LPDIRECT3DDEVICE9	lpD3DDevice;	// Direct3DDeviceインターフェイス

	D3DXMATRIX mView, mProj;

	ID3DXEffect* effect;
	UINT numPass;

	SimpleShader 	m_SampSh;

	std::shared_ptr<Player> p_player;
	std::shared_ptr<Pot> p_pot;

	std::shared_ptr<Title> p_title;
	std::shared_ptr<Game> p_game;
	std::shared_ptr<Result> p_result;

	std::shared_ptr<ObjList> p_objectlist;

	//ObjList* Get_ObjList() { return p_objectlist; }

	int GameMode;

	int Score = 0;
	int GetPoint=0;
	int GetCook = 999;

	POINT NowPt;
	HWND T_hwnd;

	D3DXVECTOR3 CLook;
	D3DXVECTOR3 CPos;


private:




};

#endif