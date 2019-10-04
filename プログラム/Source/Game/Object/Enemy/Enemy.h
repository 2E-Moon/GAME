#ifndef __Enemy_h__
#define __Enemy_h__

class Enemy : public ObjBase {
public:
	//�H�ނ̎�ޗp
	enum FoodType{BEEF,CACAO,CARROT,CHICKEN,EGG,MILK,MUSH,POTATO};

	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();

	//�I�u�W�F�N�g����
	void ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//�X�e�[�W�Փ˔��菈��
	void StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//�����ʒu�ݒ�
	void SetStartPos(float _x, float _y, float _z);

	void SetMove();

	//�H�ނ̎��
	int iFoodType;


	//�Q�b�^�[
	bool GetCarryToPlayerFlg() { return CarryToPlayerFlg; }
	//�Z�b�^�[
	void SetCarryToPlayerFlg(bool _flg) { CarryToPlayerFlg = _flg; }

private:

	//�����ʒu�p
	D3DXVECTOR3 vStartPos;

	//�H�ރT�C�Y�p�ϐ�
	int Size = 1;

	//�s��
	D3DXMATRIX mPos; //���W
	D3DXMATRIX mRot; //��]
	
	bool CarryToPlayerFlg = false;


};

#endif