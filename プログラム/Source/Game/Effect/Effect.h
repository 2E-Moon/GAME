#ifndef __Effect_h__
#define __Effect_h__

#define EFFECT Effect::GetInstance()

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
class Effect  {
public:


	//------------------
	//	�V���O���g������
	//------------------
	static Effect& GetInstance()
	{
		static Effect Instance;
		return Instance;

	}

	void Init();
	void Update();
	void Draw();
	void Release();

	//�G�t�F�N�g�����t���O�𗧂�����p
	void CreateEffect();

	//�G�t�F�N�g�폜�t���O�𗧂�����p
	void DeleateEffect();

private:


	//�e�N�X�`���ǂݍ���
	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);


	//�e�N�X�`��
	LPDIRECT3DTEXTURE9 lpCharge;

	struct VERTEX
	{
		D3DXVECTOR3 Pos;
		D3DCOLOR Color;
		D3DXVECTOR2 Tex;
	};
	VERTEX v[4];

	//�`���[�W���t���O
	bool Effect_ChargeFlg;
	//�G�t�F�N�g���L����p�ϐ�
	float CCnt = 100;
	//�G�t�F�N�g�̃t�F�[�h�p�ϐ�
	int FeadCnt = 255;

	//�s��
	D3DXMATRIX mCharge;



};
#endif