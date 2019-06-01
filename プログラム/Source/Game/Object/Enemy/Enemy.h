#ifndef __Enemy_h__
#define __Enemy_h__

class Enemy : public ObjBase {
public:
	//食材の種類用
	enum FoodType{BEEF,CACAO,CARROT,CHICKEN,EGG,MILK,MUSH,POTATO};

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	//オブジェクト判定
	void ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//初期位置設定
	void SetStartPos(float _x, float _y, float _z);

	void SetMove();

	//プレイヤーのアタック衝突時
	void DamageProc();

	//食材の種類
	int iFoodType;

private:

	//初期位置用
	D3DXVECTOR3 vStartPos;

	//食材サイズ用変数
	int Size = 1;

	//行列
	D3DXMATRIX mPos; //座標
	D3DXMATRIX mRot; //回転
	


};

#endif