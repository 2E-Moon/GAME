#ifndef __Stage_h__
#define __Stage_h__

//�X�e�[�W�̃u���b�N�̐�
#define STAGEVALUE 30

class Stage : public ObjBase {
public:

	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();

	//�X�e�[�W�s��̃Q�b�^�[
	D3DXMATRIX GetStageMat(int _x, int _z) { return mBMat[_x][_z]; }
	D3DXVECTOR3 GetStagePos(int _x, int _z) { return D3DXVECTOR3(mBMat[_x][_z]._41, mBMat[_x][_z]._42, mBMat[_x][_z]._43); }

	void SetHitFlg(bool _flg, int _x, int _z) { isHitFlg[_x][_z] = _flg; }
private:
	//�X�e�[�W����
	void CreateStage();

	XFILE xHitMesh;


	D3DXMATRIX mBMat[STAGEVALUE][STAGEVALUE];
	D3DXVECTOR3 vBPos[STAGEVALUE][STAGEVALUE];
	int iBHeight[STAGEVALUE][STAGEVALUE];

	bool isHitFlg[STAGEVALUE][STAGEVALUE];


};

#endif