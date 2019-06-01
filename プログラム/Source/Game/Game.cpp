#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<dsound.h>//2D�T�E���h
#include<memory>
#include<iostream>

#include"../GameData.h"

#include"Object/ObjBase.h"
#include"Object/Player/Player.h"
#include"Object/Enemy/Enemy.h"
#include"Object/Stage/Stage.h"
#include"Object/Stage/BackGround.h"
#include"Object/Stage/Sand.h"
#include"Object/Gimmick/Pot.h"

#include"Object/ObjList.h"

#include"Effect/Effect.h"

#include"Result/Result.h"

#include"../UI/UIBase.h"
#include"../UI/GameUI/GameUI.h"


#include "Game.h"


#define DEFTIME 120

void Game::Init()
{
	ObjectList = std::make_shared<ObjList>();
	ObjectList->Init();
	GAMEDATA.p_objectlist = ObjectList;

	EFFECT.Init();
	g_ui.Init();

	result = std::make_shared<Result>();
	result->Init();
	GAMEDATA.p_result = result;

	iTime = DEFTIME;
	ST = timeGetTime();


	GAMEDATA.m_SampSh.Init();

	SOUND.BGM_Play("Battle");
}

void Game::Update()
{
	ShowCursor(FALSE);

	ObjectList->Update();

	EFFECT.Update();
	g_ui.Update();
	result->Update();

	//�Q�[���J�n�t���O��true�̏ꍇ
	if (bGame_StartFlg == true)
	{

		if (timeGetTime() - ST > 1000)
		{
			iTime--;
			ST = timeGetTime();
		}


		if (iTime < 0)
		{
			bGame_StartFlg = false;
			bGame_EndFlg = true;

			SOUND.SE_Play("Whistle");

			//���Ԑ؂ꂩ�烊�U���g�܂ł̎��ԂɎg��
			ST = timeGetTime();
		}


		if (GetAsyncKeyState('9'))
		{
			iTime--;
		}
	}

	//�Q�[���I���t���O��true�̏ꍇ
	if (bGame_EndFlg == true)
	{
		if (timeGetTime() - ST > 5000)
		{
			bResultFlg = true;
		}

	}


}

void Game::Draw()
{



	// �V�F�[�_�ɂ��ˉe�s����Z�b�g
	GAMEDATA.m_SampSh.SetTransformProj(&GAMEDATA.mProj);
	// �V�F�[�_�ɂ��J���������Z�b�g
	GAMEDATA.m_SampSh.SetTransformView(&GAMEDATA.mView);

	GAMEDATA.m_SampSh.SetCamPos(&D3DXVECTOR3(GAMEDATA.mView._41, GAMEDATA.mView._42, GAMEDATA.mView._43));	// �V�F�[�_�ɃJ�������W���Z�b�g

	ObjectList->Draw();

	EFFECT.Draw();
	g_ui.Draw();
}

void Game::Release()
{
	ObjectList->Release();

	EFFECT.Release();
	g_ui.Release();
	result->Release();

	GAMEDATA.m_SampSh.Release();

}