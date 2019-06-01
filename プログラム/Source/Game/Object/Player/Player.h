#ifndef __Player_h__
#define __Player_h__
class Player : public ObjBase {
public:

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	void Attack(D3DXMATRIX _mRot);

	void ObjColl(int ObjType,D3DXMATRIX _mMat,D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	bool HitEnemy(D3DXMATRIX _mRot,D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);


	int GetChargeCnt() { return Attack_ChargeCnt; }
private:
	XFILE xLHand;
	XFILE xRHand;
	XFILE xLFoot;
	XFILE xRFoot;

	LPD3DXMESH lpTeapot;
	
	long rad = 0;
	D3DXMATRIX mSpeed;

	int Crad = 0;
	float Urad = 0;

	bool MoveFlg = false;
	bool Change_LimbShakeFlg = false;
	float LimbValue = 0.0f;
	D3DXMATRIX mLHand;
	D3DXMATRIX mRHand;
	D3DXMATRIX mLFoot;
	D3DXMATRIX mRFoot;

	bool JFlg=false;

	bool AttackFlg = false;
	bool OnAttackFlg = false;
	float AttackTime = 0;
	float AttackCoolTime = 0;

	int Attack_ChargeCnt = 0;
	bool Attack_LButtonFlg = false;

	bool b_DebugFlg = false;
	LPD3DXFONT lpFont;
};

#endif