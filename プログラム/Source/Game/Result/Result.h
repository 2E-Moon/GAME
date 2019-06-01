#ifndef __Result_h__
#define __Result_h__

enum Rank { FIRST, SECOND, THIRD, FOURTH, FIFTH, RANKOUT = 999 };

class Result {
public:

	void Init();
	void Update();
	void Draw();
	void Release();

	int Get_FirstScore() { return FirstScore; };
	int Get_SecondScore() { return SecondScore; };
	int Get_ThirdScore() { return ThirdScore; };
	int Get_FourthScore() { return FourthScore; };
	int Get_FifthScore() { return FifthScore; };

	int Get_NowRank() { return NowRank; }

private:
	int NowScore; //今回のスコア
	int NowRank = RANKOUT; //今回のランキング

	int FirstScore=2000;//1位のスコア
	int SecondScore=1000;//2位のスコア
	int ThirdScore=500;//3位のスコア
	int FourthScore=300;//4位のスコア
	int FifthScore=100;//5位のスコア


	bool ScoreCheckFlg = false;

};

#endif