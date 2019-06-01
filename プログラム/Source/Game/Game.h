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
	void Init();
	void Update();
	void Draw();
	void Release();

	bool Get_GameMode_ChangeFlg() { return GameMode_ChangeFlg; }
	void Set_GameMode_ChangeFlg(bool _flg) { GameMode_ChangeFlg = _flg; }

	bool Get_GameStartFlg() { return bGame_StartFlg; }
	void Set_GameStartFlg(bool _flg) { bGame_StartFlg = _flg; }

	bool Get_GameEndFlg() { return bGame_EndFlg; }
	void Set_GameEndFlg(bool _flg) { bGame_EndFlg = _flg; }

	bool Get_ResultFlg() { return bResultFlg; }
	void Set_ResultFlg(bool _flg) { bResultFlg = _flg; }

	int Get_Time() { return iTime; }
	void Set_Time(int _time) { iTime = _time; }
private:

	std::shared_ptr<ObjList> ObjectList;
	GameUI g_ui;

	bool bGame_StartFlg = false;
	bool bGame_EndFlg = false;

	bool bResultFlg = false;

	int iTime;
	DWORD ST;

	std::shared_ptr<Result> result;

	bool GameMode_ChangeFlg = false;
};


#endif

