#ifndef __Pot_h__
#define __Pot_h__

class Pot : public ObjBase {
public:
	enum FoodType { BEEF, CACAO, CARROT, CHICKEN, EGG, MILK, MUSH, POTATO,NONE = 999 };
	enum CookType { CHIKENFRY, CHOKO, CURRY, PUDDING, STEW };

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	int Get_FoodHolder(int _num) { return iFoodHolder[_num]; }
	int GetCook();

private:
	D3DXMATRIX mTmp;
	D3DXMATRIX mRot;

	int iFoodHolder[6];

	void ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);
	void GetFood();

	void SortFood();


};

#endif