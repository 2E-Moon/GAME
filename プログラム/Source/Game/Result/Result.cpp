#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<fstream>
#include<iostream>
#include<string>

#include"../../GameData.h"

#include"Result.h"



void Result::Init()
{
	std::ifstream ifsScore("Score.txt");
	std::string stScore;

	//�t�@�C�������݂��Ȃ����œǂݍ��߂Ȃ��Ƃ�
	if (ifsScore.fail())
	{

		std::ofstream ofsScore("Score.txt");
		ofsScore << std::to_string(FirstScore) <<"\n" << std::to_string(SecondScore) << "\n" << std::to_string(ThirdScore) << "\n" << std::to_string(FourthScore) << "\n" << std::to_string(FifthScore);
		ofsScore.close();

		return;
	}


	//1�ʃX�R�A�ǂݍ���
	getline(ifsScore, stScore);
	FirstScore = atoi(stScore.c_str());

	//2�ʃX�R�A�ǂݍ���
	getline(ifsScore, stScore);
	SecondScore = atoi(stScore.c_str());

	//3�ʃX�R�A�ǂݍ���
	getline(ifsScore, stScore);
	ThirdScore = atoi(stScore.c_str());

	//4�ʃX�R�A�ǂݍ���
	getline(ifsScore, stScore);
	FourthScore = atoi(stScore.c_str());

	//5�ʃX�R�A�ǂݍ���
	getline(ifsScore, stScore);
	FifthScore = atoi(stScore.c_str());

}

void Result::Update()
{
	if (ScoreCheckFlg == true)
	{
		return;
	}

	if (GAMEDATA.p_game->Get_GameEndFlg() == true)
	{
		NowScore = GAMEDATA.Score;
		ScoreCheckFlg = true;


		//�����L���O1�ʂ̏ꍇ
		if (NowScore >= FirstScore)
		{
			//�����L���O��1�����炷
			FifthScore = FourthScore;
			FourthScore = ThirdScore;
			ThirdScore = SecondScore;
			SecondScore = FirstScore;

			//1�ʂ�����̃X�R�A�ɂ���
			FirstScore = NowScore;

			NowRank = FIRST;
			return;
		}

		//�����L���O2�ʂ̏ꍇ
		if (NowScore >= SecondScore)
		{
			//�����L���O��1�����炷
			FifthScore = FourthScore;
			FourthScore = ThirdScore;
			ThirdScore = SecondScore;

			//2�ʂ�����̃X�R�A�ɂ���
			SecondScore = NowScore;

			NowRank = SECOND;
			return;
		}

		//�����L���O3�ʂ̏ꍇ
		if (NowScore >= ThirdScore)
		{
			//�����L���O��1�����炷
			FifthScore = FourthScore;
			FourthScore = ThirdScore;

			//3�ʂ�����̃X�R�A�ɂ���
			ThirdScore = NowScore;

			NowRank = THIRD;
			return;
		}

		//�����L���O4�ʂ̏ꍇ
		if (NowScore >= FourthScore)
		{
			//�����L���O��1�����炷
			FifthScore = FourthScore;

			//4�ʂ�����̃X�R�A�ɂ���
			FourthScore = NowScore;

			NowRank = FOURTH;
			return;
		}

		//�����L���O5�ʂ̏ꍇ
		if (NowScore >= FifthScore)
		{
			//5�ʂ�����̃X�R�A�ɂ���
			FifthScore = NowScore;

			NowRank = FIFTH;
			return;
		}

		//�����L���O���O�̏ꍇ
		NowRank = RANKOUT;

	}

}

void Result::Draw()
{

}

void Result::Release()
{
	//�X�R�A���X�V���ꂽ���̂ݏ㏑��
	if (ScoreCheckFlg == true)
	{
		//�X�R�A�㏑��
		std::ofstream ofsScore("Score.txt");
		ofsScore << std::to_string(FirstScore) << "\n" << std::to_string(SecondScore) << "\n" << std::to_string(ThirdScore) << "\n" << std::to_string(FourthScore) << "\n" << std::to_string(FifthScore);
		ofsScore.close();
	}



}
