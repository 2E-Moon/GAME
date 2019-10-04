#ifndef __Enemy_h__
#define __Enemy_h__

class Enemy : public ObjBase {
public:
	//食材の種類用
	enum FoodType{BEEF,CACAO,CARROT,CHICKEN,EGG,MILK,MUSH,POTATO};

	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();

	//オブジェクト判定
	void ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//ステージ衝突判定処理
	void StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//初期位置設定
	void SetStartPos(float _x, float _y, float _z);

	void SetMove();

	//食材の種類
	int iFoodType;


	//ゲッター
	bool GetCarryToPlayerFlg() { return CarryToPlayerFlg; }
	//セッター
	void SetCarryToPlayerFlg(bool _flg) { CarryToPlayerFlg = _flg; }

private:

	//初期位置用
	D3DXVECTOR3 vStartPos;

	//食材サイズ用変数
	int Size = 1;

	//行列
	D3DXMATRIX mPos; //座標
	D3DXMATRIX mRot; //回転
	
	bool CarryToPlayerFlg = false;


};

#endif