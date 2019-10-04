#ifndef __Player_h__
#define __Player_h__
class Player : public ObjBase {
public:

	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();

	//�A�^�b�N������
	void Attack(D3DXMATRIX _mRot);

	//�I�u�W�F�N�g�Փ˔��菈��
	void ObjColl(int ObjType,D3DXMATRIX _mMat,D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//�X�e�[�W�Փ˔��菈��
	void StageColl(D3DXMATRIX _mMat, D3DXVECTOR3* _Pos, D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//�G�l�~�[�q�b�g������
	bool HitEnemy(D3DXMATRIX _mRot,D3DXVECTOR3 _Normal, D3DXVECTOR3 _Push);

	//�߂��̃G�l�~�[���������鏈��
	void HaveEnemy();

	//�Q�b�^�[
	//Attack_ChargeCnt
	int GetChargeCnt() { return Attack_ChargeCnt; }
private:
	//���b�V��
	XFILE xLHand; //����
	XFILE xRHand; //�E��
	XFILE xLFoot; //����
	XFILE xRFoot; //�E��

	//���_�ړ��p�ϐ�
	int Crad = 0;
	float Urad = 0;

	//�ړ��x�N�g��
	D3DXVECTOR3 MoveVec;

	//�ړ��t���O�ϐ�
	bool MoveFlg = false;
	//�葫�ړ����Ă邩�t���O�ϐ�
	bool Change_LimbShakeFlg = false;
	//�葫�ړ����l�ϐ�
	float LimbValue = 0.0f;

	//�葫�̍s��
	D3DXMATRIX mLHand; //����
	D3DXMATRIX mRHand; //�E��
	D3DXMATRIX mLFoot; //����
	D3DXMATRIX mRFoot; //�E��

	//�W�����v�t���O�ϐ�
	bool JFlg=false;

	//�A�^�b�N�t���O�ϐ�
	bool AttackFlg = false;
	//�A�^�b�N���t���O�ϐ�
	bool OnAttackFlg = false;
	//�A�^�b�N���Ă��鎞�Ԃ̕ϐ�
	float AttackTime = 0;
	//�A�^�b�N�̃N�[���^�C���ϐ�
	float AttackCoolTime = 0;

	//�G�l�~�[�����Ă邩����p�t���O
	bool HaveEnemyFlg = false;
	//�������藣�����肵�����̃f�B���C�ϐ�
	DWORD HaveTime = 0;

	//�G�t�F�N�g�p�J�E���g�ϐ�
	int Attack_ChargeCnt = 0;
	//���N���b�N�����Ă邩�̃t���O�p�ϐ�
	bool Attack_LButtonFlg = false;

	//�f�o�b�O�`�悷�邩�̃t���O
	bool b_DebugFlg = false;
	LPD3DXFONT lpFont;
	bool d_Hit;
};

#endif