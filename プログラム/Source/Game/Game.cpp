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
	//�I�u�W�F�N�g���X�g����
	ObjectList = std::make_shared<ObjList>();
	ObjectList->Init();
	GAMEDATA.p_objectlist = ObjectList;

	//�G�t�F�N�g
	EFFECT.Init();
	//�Q�[��UI
	g_ui.Init();
	//���U���g
	result = std::make_shared<Result>();
	result->Init();
	GAMEDATA.p_result = result;
	//�V�F�[�_
	GAMEDATA.m_SampSh.Init();

	//�Q�[�����Ԑݒ�
	iTime = DEFTIME;
	ST = timeGetTime();


	//BGM�Đ�
	SOUND.BGM_Play("Battle");
}

void Game::Update()
{
	//�J�[�\���\����OFF
	ShowCursor(FALSE);

	//�I�u�W�F�N�g���X�g
	ObjectList->Update();
	//�G�t�F�N�g
	EFFECT.Update();
	//�Q�[��UI
	g_ui.Update();
	//���U���g
	result->Update();

	//�Q�[���J�n�t���O��true�̏ꍇ
	if (isGame_StartFlg == true)
	{
		//1�b���ƂɎ��Ԃ��������Ă����悤�ɂ���
		if (timeGetTime() - ST > 1000)
		{
			iTime--;
			ST = timeGetTime();
		}

		//�c��0�b�ɂȂ�����Q�[���I���̃t���O�𗧂�����
		if (iTime < 0)
		{
			isGame_StartFlg = false;
			isGame_EndFlg = true;

			//SE�Đ�
			SOUND.SE_Play("Whistle");

			//���Ԑ؂ꂩ�烊�U���g�܂ł̎��ԂɎg��
			ST = timeGetTime();
		}

		//�f�o�b�O�p
		//9�L�[�Ŏ��Ԃ𑁂߂�
		if (GetAsyncKeyState('9'))
		{
			iTime--;
		}
	}

	//�Q�[���I���t���O��true�̏ꍇ
	if (isGame_EndFlg == true)
	{
		if (timeGetTime() - ST > 5000)
		{
			isResultFlg = true;
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

	//�I�u�W�F�N�g���X�g
	ObjectList->Draw();
	//�G�t�F�N�g
	EFFECT.Draw();
	//�Q�[��UI
	g_ui.Draw();
}

void Game::Release()
{
	//�I�u�W�F�N�g���X�g
	ObjectList->Release();
	//�G�t�F�N�g
	EFFECT.Release();
	//�Q�[��UI
	g_ui.Release();
	//���U���g
	result->Release();
	//�V�F�[�_
	GAMEDATA.m_SampSh.Release();

}