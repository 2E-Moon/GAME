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
	//UI�e�N�X�`��
	//==================================

	//�^�b�N���̃`���[�WUI
	LPDIRECT3DTEXTURE9 lpPowerGage_f;
	LPDIRECT3DTEXTURE9 lpPowerGage_g;

	//�H�ފi�[UI
	LPDIRECT3DTEXTURE9 lpHolder;

	//�H��UI
	LPDIRECT3DTEXTURE9 lpBeef; //����
	LPDIRECT3DTEXTURE9 lpCacao; //�J�J�I
	LPDIRECT3DTEXTURE9 lpCarrot; //�l�Q
	LPDIRECT3DTEXTURE9 lpChicken; //�{��
	LPDIRECT3DTEXTURE9 lpEgg; //���܂�
	LPDIRECT3DTEXTURE9 lpMilk; //����
	LPDIRECT3DTEXTURE9 lpMush; //���̂�
	LPDIRECT3DTEXTURE9 lpPotato; //���Ⴊ

	//����UI
	LPDIRECT3DTEXTURE9 lpChickenFry; //���g��
	LPDIRECT3DTEXTURE9 lpChoko; //�`���R���[�g
	LPDIRECT3DTEXTURE9 lpCurry; //�J���[
	LPDIRECT3DTEXTURE9 lpPudding; //�v����
	LPDIRECT3DTEXTURE9 lpStew; //�V�`���[

	//���Ԃ�UI
	LPDIRECT3DTEXTURE9 lpStart;
	LPDIRECT3DTEXTURE9 lpTimeUp;
	LPDIRECT3DTEXTURE9 lpNumber;
	LPDIRECT3DTEXTURE9 lpNumber_r;
	LPDIRECT3DTEXTURE9 lpMark;
	LPDIRECT3DTEXTURE9 lpMark_r;


	//���U���gUI
	LPDIRECT3DTEXTURE9 lpDark;
	LPDIRECT3DTEXTURE9 lpFirst;
	LPDIRECT3DTEXTURE9 lpSecond;
	LPDIRECT3DTEXTURE9 lpThird;
	LPDIRECT3DTEXTURE9 lpFourth;
	LPDIRECT3DTEXTURE9 lpFifth;



	//==================================
	//UI�s��
	//==================================
	struct UI_State
	{
		D3DXMATRIX mMat;
		RECT rc;
	};

	//�Q�[�W
	UI_State uiGage;
	UI_State uiStart;
	UI_State uiEnd;

	//���ԕ\���Ɏg���ԍ�
	UI_State uiNumMinute;
	UI_State uiNumColon;
	UI_State uiNumSec_tens;
	UI_State uiNumSec_ones;



	//======================================================================================
	//�X�R�A�\���֘A
	//1�̈ʂ���10���̈ʂ܂Őݒ肷��p�̊֐��B���U���g�\���ōs�����������Ȃ̂ō��܂���
	//======================================================================================
	//�X�R�A�p�̍\����
	struct UI_ScoreStr
	{
		UI_State one;
		UI_State ten;
		UI_State hun;
		UI_State tho;
		UI_State tth;
		UI_State hth;
	};

	//�S�Ă̌��̍s���ݒ肷��֐�
	void Update_ScoreInfo(std::shared_ptr<UI_ScoreStr> _Scorestr, int _Score, float _x, float _y, float _scal = 1.0f);
	//�S�Ă̌���`�悷��֐�
	void Draw_ScoreInfo(std::shared_ptr<UI_ScoreStr> _Scorestr);

	//-------------------------------------------------------------------------------------

	//�X�R�A�\���Ɏg���ԍ�
	UI_State uiScore_one;
	UI_State uiScore_ten;
	UI_State uiScore_hun;
	UI_State uiScore_tho;
	UI_State uiScore_tth;
	UI_State uiScore_hth;

	std::shared_ptr<UI_ScoreStr> strNowScore;

	//�X�R�A���Z���Ɏg���ԍ�
	UI_State uiPlusScore_pls;
	UI_State uiPlusScore_one;
	UI_State uiPlusScore_ten;
	UI_State uiPlusScore_hun;
	UI_State uiPlusScore_tho;
	int PlusScoreFlg = false;

	//�J�n�O�̃J�E���g�Ɏg��
	UI_State uiStartCount;


	//���U���g�p
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
	//�H�ފi�[�g
	UI_State uiHolder;
	UI_State uiFood[5];

	//����
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