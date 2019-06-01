#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>

#include "../GameData.h"
#include "../Game/Object/ObjBase.h"
#include "Shader.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

void SimpleShader::Init()
{

	// �G�t�F�N�g�t�@�C���̃��[�h
	LPD3DXBUFFER pErr = NULL;
	HRESULT hr;
	hr = D3DXCreateEffectFromFile(
		GAMEDATA.lpD3DDevice,"Sample.fx",
		NULL, NULL, 0, NULL, &m_Effect, &pErr);

	if (hr != D3D_OK) {
		MessageBox(NULL, (LPCSTR)pErr->GetBufferPointer(), "�V�F�[�_�R���p�C���G���[", MB_OK);
		return;
	}

	LoadText(&lpWhite, "Resource/Chara/Texture/White.png", 10, 10, NULL);




	// 

}

void SimpleShader::DrawMesh(LPD3DXMESH _Mesh,DWORD _NumMaterial,D3DMATERIAL9* _Mat,LPDIRECT3DTEXTURE9 _Tex)
{
/*	// �e�N�j�b�N�I��
	m_Effect->SetTechnique("Tech");
	// �e�N�j�b�N�J�n
	m_Effect->Begin(0, 0);
	// �p�X�J�n
	m_Effect->BeginPass(0);

	// ���C�g���Q�b�g
	D3DLIGHT9 light;
	GAMEDATA.lpD3DDevice->GetLight(0, &light);

	// �}�e���A���̐��Ԃ񃋁[�v
	for (int i = 0; i < _NumMaterial; i++)
	{
		D3DMATERIAL9*		pMate = &_Mat[i];
		LPDIRECT3DTEXTURE9	pTex = _Tex[i];
		//		CTexture*		pTex = &pMesh->GetTextures()[i];

		// �f�B�t���[�Y
		D3DXVECTOR4 vDif;
		vDif.x = pMate->Diffuse.r * light.Diffuse.r;
		vDif.y = pMate->Diffuse.g * light.Diffuse.g;
		vDif.z = pMate->Diffuse.b * light.Diffuse.b;
		vDif.w = pMate->Diffuse.a;
		m_Effect->SetVector("Diffuse", &vDif);

		// �A���r�G���g
		m_Effect->SetFloat("Ambient", light.Ambient.r);

		// �X�y�L����
		D3DXVECTOR4 vSpe;
		vSpe.x = pMate->Specular.r * light.Specular.r;
		vSpe.y = pMate->Specular.g * light.Specular.g;
		vSpe.z = pMate->Specular.b * light.Specular.b;
		vSpe.w = 1;
		m_Effect->SetVector("Specular", &vSpe);

		// Power
		m_Effect->SetFloat("Power", pMate->Power);

		// �e�N�X�`��������Ƃ�
		if (pTex) {
			// ���̃e�N�X�`�����Z�b�g
			m_Effect->SetTexture("MeshTex", pTex);
		}
		// �e�N�X�`����������
		else {
			
		}

		// ��������Ă΂Ȃ��ƁA�V�F�[�_���ɂ��܂��p�����[�^���Z�b�g����Ȃ���I
		m_Effect->CommitChanges();

		// ���b�V����`��
		_Mesh->DrawSubset(i);
	}

	// �p�X�I��
	m_Effect->EndPass();
	// �e�N�j�b�N�I��
	m_Effect->End();*/
}


void SimpleShader::LoadText(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(GAMEDATA.lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
}