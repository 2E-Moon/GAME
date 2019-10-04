#ifndef __Player_h__
#define __Player_h__
class Player : public ObjBase {
public:

	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();

	//アタック時処理
	void Attack(D3DXMATRIX _mRot);

	//オブジェクト衝突判定処理
	void ObjColl(int ObjType,D3DXMATRIX _mMat,D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//ステージ衝突判定処理
	void StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//エネミーヒット時処理
	bool HitEnemy(D3DXMATRIX _mRot,D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//近くのエネミーを所持する処理
	void HaveEnemy();

	//ゲッター
	//Attack_ChargeCnt
	int GetChargeCnt() { return Attack_ChargeCnt; }
private:
	//メッシュ
	XFILE xLHand; //左手
	XFILE xRHand; //右手
	XFILE xLFoot; //左足
	XFILE xRFoot; //右足

	//視点移動用変数
	int Crad = 0;
	float Urad = 0;

	//移動ベクトル
	D3DXVECTOR3 MoveVec;

	//移動フラグ変数
	bool MoveFlg = false;
	//手足移動してるかフラグ変数
	bool Change_LimbShakeFlg = false;
	//手足移動数値変数
	float LimbValue = 0.0f;

	//手足の行列
	D3DXMATRIX mLHand; //左手
	D3DXMATRIX mRHand; //右手
	D3DXMATRIX mLFoot; //左足
	D3DXMATRIX mRFoot; //右足

	//ジャンプフラグ変数
	bool JFlg=false;

	//アタックフラグ変数
	bool AttackFlg = false;
	//アタック中フラグ変数
	bool OnAttackFlg = false;
	//アタックしている時間の変数
	float AttackTime = 0;
	//アタックのクールタイム変数
	float AttackCoolTime = 0;

	//エネミー持ってるか判定用フラグ
	bool HaveEnemyFlg = false;
	//持ったり離したりした時のディレイ変数
	DWORD HaveTime = 0;

	//エフェクト用カウント変数
	int Attack_ChargeCnt = 0;
	//左クリック押してるかのフラグ用変数
	bool Attack_LButtonFlg = false;

	//デバッグ描画するかのフラグ
	bool b_DebugFlg = false;
	LPD3DXFONT lpFont;
	bool d_Hit;
};

#endif