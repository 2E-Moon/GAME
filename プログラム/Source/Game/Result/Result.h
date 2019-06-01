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
	int NowScore; //����̃X�R�A
	int NowRank = RANKOUT; //����̃����L���O

	int FirstScore=2000;//1�ʂ̃X�R�A
	int SecondScore=1000;//2�ʂ̃X�R�A
	int ThirdScore=500;//3�ʂ̃X�R�A
	int FourthScore=300;//4�ʂ̃X�R�A
	int FifthScore=100;//5�ʂ̃X�R�A


	bool ScoreCheckFlg = false;

};

#endif