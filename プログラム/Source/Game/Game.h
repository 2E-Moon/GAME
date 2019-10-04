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
	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();


	//=============
	//�Q�b�^�[
	//=============
	//�Q�[�����[�h�ؑփt���O
	bool Get_GameMode_ChangeFlg() { return isGameMode_ChangeFlg; }
	//�Q�[���X�^�[�g����t���O
	bool Get_GameStartFlg() { return isGame_StartFlg; }
	//�Q�[���I������t���O
	bool Get_GameEndFlg() { return isGame_EndFlg; }
	//���U���g�\������t���O
	bool Get_ResultFlg() { return isResultFlg; }

	//���݂̃^�C��
	int Get_Time() { return iTime; }



	//=============
	//�Z�b�^�[
	//=============
	//�Q�[�����[�h�ؑփt���O
	void Set_GameMode_ChangeFlg(bool _flg) { isGameMode_ChangeFlg = _flg; }
	//�Q�[���X�^�[�g����t���O
	void Set_GameStartFlg(bool _flg) { isGame_StartFlg = _flg; }
	//�Q�[���I������t���O
	void Set_GameEndFlg(bool _flg) { isGame_EndFlg = _flg; }
	//���U���g�\������t���O
	void Set_ResultFlg(bool _flg) { isResultFlg = _flg; }

	//���݂̃^�C��
	void Set_Time(int _time) { iTime = _time; }
private:
	//�I�u�W�F�N�g���X�g
	std::shared_ptr<ObjList> ObjectList;
	//���U���g
	std::shared_ptr<Result> result;
	//�Q�[��UI
	GameUI g_ui;

	//�Q�[�����[�h�ؑփt���O
	bool isGameMode_ChangeFlg = false;
	//�Q�[���X�^�[�g����t���O
	bool isGame_StartFlg = false;
	//�Q�[���I������t���O
	bool isGame_EndFlg = false;

	//���U���g�\������t���O
	bool isResultFlg = false;

	//�Q�[�����^�C��
	int iTime;
	DWORD ST;



	
};


#endif

