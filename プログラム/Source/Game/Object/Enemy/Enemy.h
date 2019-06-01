#ifndef __Enemy_h__
#define __Enemy_h__

class Enemy : public ObjBase {
public:
	//�H�ނ̎�ޗp
	enum FoodType{BEEF,CACAO,CARROT,CHICKEN,EGG,MILK,MUSH,POTATO};

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();

	//�I�u�W�F�N�g����
	void ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//�����ʒu�ݒ�
	void SetStartPos(float _x, float _y, float _z);

	void SetMove();

	//�v���C���[�̃A�^�b�N�Փˎ�
	void DamageProc();

	//�H�ނ̎��
	int iFoodType;

private:

	//�����ʒu�p
	D3DXVECTOR3 vStartPos;

	//�H�ރT�C�Y�p�ϐ�
	int Size = 1;

	//�s��
	D3DXMATRIX mPos; //���W
	D3DXMATRIX mRot; //��]
	


};

#endif