#ifndef __Pot_h__
#define __Pot_h__

class Pot : public ObjBase {
public:
	//�H�ޗp
	enum FoodType { BEEF, CACAO, CARROT, CHICKEN, EGG, MILK, MUSH, POTATO, NONE = 999 };
	//�����p
	enum CookType { CHIKENFRY, CHOKO, CURRY, PUDDING, STEW };

	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();

	//�H�ފi�[�z���_�[�̒��g�̏�������Ă���
	int Get_FoodHolder(int _num) { return iFoodHolder[_num]; }
	//�����\�����肷��֐�
	int GetCook();

private:
	//�I�u�W�F�N�g�Փ˗p
	void ObjColl(int ObjType, D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);
	//�X�e�[�W�Փ˔��菈��
	void StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//�H�ފl���p
	void GetFood();
	//�z���_�[�̐H�ނ��\�[�g����
	void SortFood();


	//�H�ފi�[�z���_�[�p�ϐ�
	int iFoodHolder[6];

};

#endif