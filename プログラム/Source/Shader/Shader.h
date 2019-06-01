#ifndef __Shader_h__
#define __Shader_h__

//======================================================
// �T���v���V�F�[�_
//	Sample.fx�𓮍삳���邽�߂̃N���X
//======================================================
class SimpleShader {
public:
	LPD3DXEFFECT	m_Effect;		// �G�t�F�N�g
	LPDIRECT3DTEXTURE9 lpWhite;

									// 
	SimpleShader() {
		m_Effect = NULL;
	}
	~SimpleShader() {
		Release();
	}

	//======================================================
	// �G�t�F�N�g�ǂݍ��݁�����Ȃ�
	//======================================================
	// �����ݒ�
	void Init();

	// ���
	void Release()
	{
		if (m_Effect) { m_Effect->Release(); m_Effect = NULL; }
		

	}

	//======================================================
	// �p�����[�^�ݒ�n
	//======================================================
	// �V�F�[�_�ɍs���ݒ�
	// ���[���h
	void SetTransformWorld(const D3DXMATRIX* mat) {
		if (m_Effect == NULL)return;
		m_Effect->SetMatrix("mW", mat);
	}
	// �r���[
	void SetTransformView(const D3DXMATRIX* mat) {
		if (m_Effect == NULL)return;
		m_Effect->SetMatrix("mV", mat);
	}
	// �ˉe
	void SetTransformProj(const D3DXMATRIX* mat) {
		if (m_Effect == NULL)return;
		m_Effect->SetMatrix("mP", mat);
	}
	// ���C�g���
	void SetLightDir(const D3DXVECTOR3* vDir) {
		if (m_Effect == NULL)return;
		m_Effect->SetValue("LightDir", vDir, sizeof(D3DXVECTOR3));		// ����
	}
	// �J�����ʒu�ݒ�
	void SetCamPos(const D3DXVECTOR3* lpvPos) {
		if (m_Effect == NULL)return;
		m_Effect->SetValue("CamPos", lpvPos, sizeof(D3DXVECTOR3));
	}

	//======================================================
	// �`��W
	//======================================================
	// ���b�V���`��
	void DrawMesh(LPD3DXMESH _Mesh,
	DWORD _NumMaterial,
	D3DMATERIAL9* _Mat,
	LPDIRECT3DTEXTURE9 _Tex);


	//2D�摜���[�h
	void LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);


};

#endif
