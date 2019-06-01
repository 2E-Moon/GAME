#ifndef __GameUI_h__
#define __GameUI_h__
class GameUI :public UIBase {
public:
	void Init();
	void Update();
	void Draw();
	void Release();
private:
	void GetPoint();

	//==================================
	//UIテクスチャ
	//==================================

	//タックルのチャージUI
	LPDIRECT3DTEXTURE9 lpPowerGage_f;
	LPDIRECT3DTEXTURE9 lpPowerGage_g;

	//食材格納UI
	LPDIRECT3DTEXTURE9 lpHolder;

	//食材UI
	LPDIRECT3DTEXTURE9 lpBeef; //牛肉
	LPDIRECT3DTEXTURE9 lpCacao; //カカオ
	LPDIRECT3DTEXTURE9 lpCarrot; //人参
	LPDIRECT3DTEXTURE9 lpChicken; //鶏肉
	LPDIRECT3DTEXTURE9 lpEgg; //たまご
	LPDIRECT3DTEXTURE9 lpMilk; //牛乳
	LPDIRECT3DTEXTURE9 lpMush; //きのこ
	LPDIRECT3DTEXTURE9 lpPotato; //じゃが

	//料理UI
	LPDIRECT3DTEXTURE9 lpChickenFry; //唐揚げ
	LPDIRECT3DTEXTURE9 lpChoko; //チョコレート
	LPDIRECT3DTEXTURE9 lpCurry; //カレー
	LPDIRECT3DTEXTURE9 lpPudding; //プリン
	LPDIRECT3DTEXTURE9 lpStew; //シチュー

	//時間のUI
	LPDIRECT3DTEXTURE9 lpStart;
	LPDIRECT3DTEXTURE9 lpTimeUp;
	LPDIRECT3DTEXTURE9 lpNumber;
	LPDIRECT3DTEXTURE9 lpNumber_r;
	LPDIRECT3DTEXTURE9 lpMark;
	LPDIRECT3DTEXTURE9 lpMark_r;


	//リザルトUI
	LPDIRECT3DTEXTURE9 lpDark;
	LPDIRECT3DTEXTURE9 lpFirst;
	LPDIRECT3DTEXTURE9 lpSecond;
	LPDIRECT3DTEXTURE9 lpThird;
	LPDIRECT3DTEXTURE9 lpFourth;
	LPDIRECT3DTEXTURE9 lpFifth;



	//==================================
	//UI行列
	//==================================
	struct UI_State
	{
		D3DXMATRIX mMat;
		RECT rc;
	};

	//ゲージ
	UI_State uiGage;
	UI_State uiStart;
	UI_State uiEnd;

	//時間表示に使う番号
	UI_State uiNumMinute;
	UI_State uiNumColon;
	UI_State uiNumSec_tens;
	UI_State uiNumSec_ones;



	//======================================================================================
	//スコア表示関連
	//1の位から10万の位まで設定する用の関数。リザルト表示で行が増えそうなので作りました
	//======================================================================================
	//スコア用の構造体
	struct UI_ScoreStr
	{
		UI_State one;
		UI_State ten;
		UI_State hun;
		UI_State tho;
		UI_State tth;
		UI_State hth;
	};

	//全ての桁の行列を設定する関数
	void Update_ScoreInfo(std::shared_ptr<UI_ScoreStr> _Scorestr, int _Score, float _x, float _y, float _scal = 1.0f);
	//全ての桁を描画する関数
	void Draw_ScoreInfo(std::shared_ptr<UI_ScoreStr> _Scorestr);

	//-------------------------------------------------------------------------------------

	//スコア表示に使う番号
	UI_State uiScore_one;
	UI_State uiScore_ten;
	UI_State uiScore_hun;
	UI_State uiScore_tho;
	UI_State uiScore_tth;
	UI_State uiScore_hth;

	std::shared_ptr<UI_ScoreStr> strNowScore;

	//スコア加算時に使う番号
	UI_State uiPlusScore_pls;
	UI_State uiPlusScore_one;
	UI_State uiPlusScore_ten;
	UI_State uiPlusScore_hun;
	UI_State uiPlusScore_tho;
	int PlusScoreFlg = false;

	//開始前のカウントに使う
	UI_State uiStartCount;


	//リザルト用
	UI_State uiDark;

	UI_State uiFirst;
	UI_State uiSecond;
	UI_State uiThird;
	UI_State uiFourth;
	UI_State uiFifth;

	std::shared_ptr<UI_ScoreStr> strFirstScore;
	std::shared_ptr<UI_ScoreStr> strSecondScore;
	std::shared_ptr<UI_ScoreStr> strThirdScore;
	std::shared_ptr<UI_ScoreStr> strFourthScore;
	std::shared_ptr<UI_ScoreStr> strFifthScore;
	

	enum Rank { FIRST, SECOND, THIRD, FOURTH, FIFTH, RANKOUT = 999 };
	enum FoodType { BEEF, CACAO, CARROT, CHICKEN, EGG, MILK, MUSH, POTATO ,OTHER};
	enum CookType { CHIKENFRY, CHOKO, CURRY, PUDDING, STEW, NONE=999 };
	//食材格納枠
	UI_State uiHolder;
	UI_State uiFood[5];

	//料理
	UI_State uiCook;

	

//	D3DXMATRIX mTime;
//	RECT rcTime;
	DWORD ST;
	int iTimeCount = 3;

	int PlusScore;
	float fUp_GetPoint = 0.0f;
	DWORD Time_DrawScore;
	int Alpha_DrawScore;

	bool Blink_ScoreFlg = false;
	DWORD Time_BlinkScore = 0;
};
#endif