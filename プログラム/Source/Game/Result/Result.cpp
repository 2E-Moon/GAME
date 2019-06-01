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

	//ファイルが存在しない等で読み込めないとき
	if (ifsScore.fail())
	{

		std::ofstream ofsScore("Score.txt");
		ofsScore << std::to_string(FirstScore) <<"\n" << std::to_string(SecondScore) << "\n" << std::to_string(ThirdScore) << "\n" << std::to_string(FourthScore) << "\n" << std::to_string(FifthScore);
		ofsScore.close();

		return;
	}


	//1位スコア読み込み
	getline(ifsScore, stScore);
	FirstScore = atoi(stScore.c_str());

	//2位スコア読み込み
	getline(ifsScore, stScore);
	SecondScore = atoi(stScore.c_str());

	//3位スコア読み込み
	getline(ifsScore, stScore);
	ThirdScore = atoi(stScore.c_str());

	//4位スコア読み込み
	getline(ifsScore, stScore);
	FourthScore = atoi(stScore.c_str());

	//5位スコア読み込み
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


		//ランキング1位の場合
		if (NowScore >= FirstScore)
		{
			//ランキングを1つずつずらす
			FifthScore = FourthScore;
			FourthScore = ThirdScore;
			ThirdScore = SecondScore;
			SecondScore = FirstScore;

			//1位を今回のスコアにする
			FirstScore = NowScore;

			NowRank = FIRST;
			return;
		}

		//ランキング2位の場合
		if (NowScore >= SecondScore)
		{
			//ランキングを1つずつずらす
			FifthScore = FourthScore;
			FourthScore = ThirdScore;
			ThirdScore = SecondScore;

			//2位を今回のスコアにする
			SecondScore = NowScore;

			NowRank = SECOND;
			return;
		}

		//ランキング3位の場合
		if (NowScore >= ThirdScore)
		{
			//ランキングを1つずつずらす
			FifthScore = FourthScore;
			FourthScore = ThirdScore;

			//3位を今回のスコアにする
			ThirdScore = NowScore;

			NowRank = THIRD;
			return;
		}

		//ランキング4位の場合
		if (NowScore >= FourthScore)
		{
			//ランキングを1つずつずらす
			FifthScore = FourthScore;

			//4位を今回のスコアにする
			FourthScore = NowScore;

			NowRank = FOURTH;
			return;
		}

		//ランキング5位の場合
		if (NowScore >= FifthScore)
		{
			//5位を今回のスコアにする
			FifthScore = NowScore;

			NowRank = FIFTH;
			return;
		}

		//ランキング圏外の場合
		NowRank = RANKOUT;

	}

}

void Result::Draw()
{

}

void Result::Release()
{
	//スコアが更新された時のみ上書き
	if (ScoreCheckFlg == true)
	{
		//スコア上書き
		std::ofstream ofsScore("Score.txt");
		ofsScore << std::to_string(FirstScore) << "\n" << std::to_string(SecondScore) << "\n" << std::to_string(ThirdScore) << "\n" << std::to_string(FourthScore) << "\n" << std::to_string(FifthScore);
		ofsScore.close();
	}



}
