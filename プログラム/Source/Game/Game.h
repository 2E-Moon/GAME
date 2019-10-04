#ifndef __Game_h__
#define __Game_h__

#include"../UI/UIBase.h"
#include"../UI/GameUI/GameUI.h"

#include"Object/ObjBase.h"
#include"Object/Player/Player.h"
#include"Object/Enemy/Enemy.h"
#include"Object/Stage/Stage.h"
#include"Object/Stage/BackGround.h"
#include"Object/Stage/Sand.h"

#include"Result/Result.h"

#include"Object/Gimmick/Pot.h"

#include"Object/ObjList.h"

class Game {
public:
	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();


	//=============
	//ゲッター
	//=============
	//ゲームモード切替フラグ
	bool Get_GameMode_ChangeFlg() { return isGameMode_ChangeFlg; }
	//ゲームスタート判定フラグ
	bool Get_GameStartFlg() { return isGame_StartFlg; }
	//ゲーム終了判定フラグ
	bool Get_GameEndFlg() { return isGame_EndFlg; }
	//リザルト表示判定フラグ
	bool Get_ResultFlg() { return isResultFlg; }

	//現在のタイム
	int Get_Time() { return iTime; }



	//=============
	//セッター
	//=============
	//ゲームモード切替フラグ
	void Set_GameMode_ChangeFlg(bool _flg) { isGameMode_ChangeFlg = _flg; }
	//ゲームスタート判定フラグ
	void Set_GameStartFlg(bool _flg) { isGame_StartFlg = _flg; }
	//ゲーム終了判定フラグ
	void Set_GameEndFlg(bool _flg) { isGame_EndFlg = _flg; }
	//リザルト表示判定フラグ
	void Set_ResultFlg(bool _flg) { isResultFlg = _flg; }

	//現在のタイム
	void Set_Time(int _time) { iTime = _time; }
private:
	//オブジェクトリスト
	std::shared_ptr<ObjList> ObjectList;
	//リザルト
	std::shared_ptr<Result> result;
	//ゲームUI
	GameUI g_ui;

	//ゲームモード切替フラグ
	bool isGameMode_ChangeFlg = false;
	//ゲームスタート判定フラグ
	bool isGame_StartFlg = false;
	//ゲーム終了判定フラグ
	bool isGame_EndFlg = false;

	//リザルト表示判定フラグ
	bool isResultFlg = false;

	//ゲーム内タイム
	int iTime;
	DWORD ST;



	
};


#endif

