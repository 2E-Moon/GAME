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

	//==========
	//ポインタ
	//==========
	//シーン
	std::shared_ptr<Scene> p_scene;

	//プレイヤー
	std::shared_ptr<Player> p_player;
	//お鍋
	std::shared_ptr<Pot> p_pot;

	//エフェクト
	ID3DXEffect* effect;

	//タイトル
	std::shared_ptr<Title> p_title;
	//ゲーム
	std::shared_ptr<Game> p_game;
	//リザルト
	std::shared_ptr<Result> p_result;

	//オブジェクトリスト
	std::shared_ptr<ObjList> p_objectlist;


	// Direct3Dインターフェイス
	LPDIRECT3D9				lpD3D;	
	// Direct3DDeviceインターフェイス
	LPDIRECT3DDEVICE9	lpD3DDevice;

	//ビュー,プロジェクト
	D3DXMATRIX mView, mProj;

	//シェーダクラス
	SimpleShader 	m_SampSh;


	//現在のゲームモード
	int GameMode;

	//現在のスコア
	int Score = 0;
	//獲得スコア
	int GetPoint=0;
	//完成した料理
	int GetCook = 999;

	//カーソルのベース
	//基本画面の真ん中を指す
	POINT BasePt;

	//カーソル移動時に
	//どれだけ動かしたか図る用
	POINT NowPt;
	//ウィンドウ情報
	HWND T_hwnd;

	//見ている方向
	//カメラの方向
	D3DXVECTOR3 CLook;
	//見ている場所
	//カメラ位置
	D3DXVECTOR3 CPos;


private:




};

#endif