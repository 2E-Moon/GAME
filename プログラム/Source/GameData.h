#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<memory>
#include<iostream>

#include<dsound.h>//2D�T�E���h

#include"Game/Object/ObjBase.h"
#include"Game/Object/Player/Player.h"
#include"Game/Object/Enemy/Enemy.h"
#include"Game/Object/Stage/Stage.h"
#include"Game/Object/Stage/BackGround.h"
#include"Game/Object/Stage/Sand.h"
#include"Game/Object/ObjList.h"
#include"Game/Game.h"

#include"Shader/Shader.h"

#include<dsound.h>//2D�T�E���h
#include"Sound/wavread.h"
#include"Sound/Sound.h"

#include"UI/UIBase.h"
#include"Title/Title_UI/Title_UI.h"

#include"Title/Title.h"

#include"Game/Result/Result.h"

#include"Scene/Scene.h"


#ifndef __Game_Data_h__
#define __Game_Data_h__

//	�f�[�^�̃V���O���g����Ԃ��}�N��
#define GAMEDATA GameData::GetInstance()
#define MODE_TITLE 0
#define MODE_GAME 1


/*=============

Class�錾

=============*/

class GameData
{
public:

	//--------------------------
	//	�V���O���g���p�^�[������
	//--------------------------
	static GameData& GetInstance()
	{
		static GameData Instance;
		return Instance;
	}

	//==========
	//�|�C���^
	//==========
	//�V�[��
	std::shared_ptr<Scene> p_scene;

	//�v���C���[
	std::shared_ptr<Player> p_player;
	//����
	std::shared_ptr<Pot> p_pot;

	//�G�t�F�N�g
	ID3DXEffect* effect;

	//�^�C�g��
	std::shared_ptr<Title> p_title;
	//�Q�[��
	std::shared_ptr<Game> p_game;
	//���U���g
	std::shared_ptr<Result> p_result;

	//�I�u�W�F�N�g���X�g
	std::shared_ptr<ObjList> p_objectlist;


	// Direct3D�C���^�[�t�F�C�X
	LPDIRECT3D9				lpD3D;	
	// Direct3DDevice�C���^�[�t�F�C�X
	LPDIRECT3DDEVICE9	lpD3DDevice;

	//�r���[,�v���W�F�N�g
	D3DXMATRIX mView, mProj;

	//�V�F�[�_�N���X
	SimpleShader 	m_SampSh;


	//���݂̃Q�[�����[�h
	int GameMode;

	//���݂̃X�R�A
	int Score = 0;
	//�l���X�R�A
	int GetPoint=0;
	//������������
	int GetCook = 999;

	//�J�[�\���̃x�[�X
	//��{��ʂ̐^�񒆂��w��
	POINT BasePt;

	//�J�[�\���ړ�����
	//�ǂꂾ�������������}��p
	POINT NowPt;
	//�E�B���h�E���
	HWND T_hwnd;

	//���Ă������
	//�J�����̕���
	D3DXVECTOR3 CLook;
	//���Ă���ꏊ
	//�J�����ʒu
	D3DXVECTOR3 CPos;


private:




};

#endif