#ifndef __ObjBase_h__
#define __ObjBase_h__



class ObjBase {
public:
	//���b�V���֘A
	struct XFILE {
		LPD3DXMESH lpMesh;
		DWORD NumMaterial;
		D3DMATERIAL9 *Mat;
		LPDIRECT3DTEXTURE9 *Tex;
	};


	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();

	//=============
	//�Q�b�^�[
	//=============
	//���b�V��
	XFILE GetMesh() { return xMesh; }
	//���W
	D3DXVECTOR3 GetPos() { return Pos; }
	//�s��
	D3DXMATRIX GetMat() { return mMat; }
	//�ΏۂƂ̋���
	float GetLength(D3DXVECTOR3 _form,D3DXVECTOR3 _prev);
	//�I�u�W�F�N�g�^�C�v
	int Get_ObjType() { return ObjType; }
	//�폜�t���O
	bool Get_DeleteFlg() { return DeleteFlg; }

	//=============
	//�Z�b�^�[
	//=============
	//�_���[�W
	void SetDamage(bool _flg, D3DXVECTOR3 _PushVec, float _accel) { DamageFlg = _flg; DamageVec = _PushVec; Accel = _accel; }
	//�I�u�W�F�N�g�^�C�v
	void Set_ObjType(int _type) { ObjType = _type; }
	//�폜�t���O
	void Set_DeleteFlg(bool _flg) { DeleteFlg = _flg; }

	//�I�u�W�F�N�g�^�C�v�p
	enum { PLAYER, ENEMY, STAGE, POT, OTHER };

private:

	//�I�u�W�F�N�g�^�C�v�i�[�ϐ�
	int ObjType;



protected:
	//=============
	//���b�V���֘A
	//=============
	//�ǂݍ���
	void LoadMesh(LPDIRECT3DDEVICE9 lpD3DDevice, XFILE *XFile, const char FName[]);
	//�`��
	void DrawMesh(LPDIRECT3DDEVICE9 lpD3DDevice, struct XFILE *xFile, D3DXMATRIX* _Mat ,bool isShaderRender = true);
	//���
	void ReleaseMesh(struct XFILE *XFile);
	//���b�V���ϐ�
	struct XFILE xMesh;

	//�s��
	D3DXMATRIX mMat;
	//���W
	D3DXVECTOR3 Pos;

	//�������x�p�ϐ�
	float Accel;

	//�_���[�W��e����
	bool DamageFlg;
	//�_���[�W��e���̔�ԋ����p
	D3DXVECTOR3 DamageVec;
	//�_���[�W��e����
	float DamageTime;

	//�폜�t���O
	//�������ۂ�true�ɂ���
	bool DeleteFlg = false;
};

#endif