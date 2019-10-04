#ifndef __Pot_h__
#define __Pot_h__

class Pot : public ObjBase {
public:
	//食材用
	enum FoodType { BEEF, CACAO, CARROT, CHICKEN, EGG, MILK, MUSH, POTATO, NONE = 999 };
	//料理用
	enum CookType { CHIKENFRY, CHOKO, CURRY, PUDDING, STEW };

	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();

	//食材格納ホルダーの中身の情報を取ってくる
	int Get_FoodHolder(int _num) { return iFoodHolder[_num]; }
	//調理可能か判定する関数
	int GetCook();

private:
	//オブジェクト衝突用
	void ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);
	//ステージ衝突判定処理
	void StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//食材獲得用
	void GetFood();
	//ホルダーの食材をソートする
	void SortFood();


	//食材格納ホルダー用変数
	int iFoodHolder[6];

};

#endif