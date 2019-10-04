#ifndef __Stage_h__
#define __Stage_h__

//ステージのブロックの数
#define STAGEVALUE 30

class Stage : public ObjBase {
public:

	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();

	//ステージ行列のゲッター
	D3DXMATRIX GetStageMat(int _x, int _z) { return mBMat[_x][_z]; }
	D3DXVECTOR3 GetStagePos(int _x, int _z) { return D3DXVECTOR3(mBMat[_x][_z]._41, mBMat[_x][_z]._42, mBMat[_x][_z]._43); }

	void SetHitFlg(bool _flg, int _x, int _z) { isHitFlg[_x][_z] = _flg; }
private:
	//ステージ生成
	void CreateStage();

	XFILE xHitMesh;


	D3DXMATRIX mBMat[STAGEVALUE][STAGEVALUE];
	D3DXVECTOR3 vBPos[STAGEVALUE][STAGEVALUE];
	int iBHeight[STAGEVALUE][STAGEVALUE];

	bool isHitFlg[STAGEVALUE][STAGEVALUE];


};

#endif