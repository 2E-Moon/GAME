#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<memory>
#include<iostream>


#include "../../GameData.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include"ObjBase.h"


void ObjBase::Init()
{
	
}

void ObjBase::Update()
{

}

void ObjBase::Draw()
{

}

void ObjBase::Release()
{

}


//���b�V���ǂݍ���
void ObjBase::LoadMesh(LPDIRECT3DDEVICE9 lpD3DDevice, XFILE *XFile, const char FName[])
{
	LPD3DXBUFFER lpD3DXBuffer;

	D3DXLoadMeshFromX(FName, D3DXMESH_MANAGED, lpD3DDevice, NULL, &lpD3DXBuffer, NULL, &(XFile->NumMaterial), &(XFile->lpMesh));

	XFile->Mat = new D3DMATERIAL9[XFile->NumMaterial];
	XFile->Tex = new LPDIRECT3DTEXTURE9[XFile->NumMaterial];

	D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)lpD3DXBuffer->GetBufferPointer();

	DWORD i;
	for (i = 0; i<XFile->NumMaterial; i++) {
		XFile->Mat[i] = D3DXMat[i].MatD3D;
		XFile->Mat[i].Ambient = XFile->Mat[i].Diffuse;
		if (FAILED(D3DXCreateTextureFromFile(lpD3DDevice, D3DXMat[i].pTextureFilename, &(XFile->Tex[i])))) {
			XFile->Tex[i] = NULL;
		}
	}

	lpD3DXBuffer->Release();
}

//���b�V���`��
void ObjBase::DrawMesh(LPDIRECT3DDEVICE9 lpD3DDevice, struct XFILE *xFile, D3DXMATRIX* _Mat, bool isShaderRender) {

	//�V�F�[�_���g�p���ĕ`�悷�邩�B�f�t�H���g�͎g�p����
	switch (isShaderRender)
	{
	case true:


		//�V�F�[�_�ɍs���ݒ�
		GAMEDATA.m_SampSh.SetTransformWorld(_Mat);

		// �e�N�j�b�N�I��
		GAMEDATA.m_SampSh.m_Effect->SetTechnique("Tech");
		// �e�N�j�b�N�J�n
		GAMEDATA.m_SampSh.m_Effect->Begin(0, 0);
		// �p�X�J�n
		GAMEDATA.m_SampSh.m_Effect->BeginPass(0);

		// ���C�g���Q�b�g
		D3DLIGHT9 light;
		GAMEDATA.lpD3DDevice->GetLight(0, &light);

		// �}�e���A���̐��Ԃ񃋁[�v
		for (int i = 0; i < xFile->NumMaterial; i++)
		{
			D3DMATERIAL9*		pMate = &(xFile->Mat[i]);
			LPDIRECT3DTEXTURE9	pTex = xFile->Tex[i];

			// �f�B�t���[�Y
			D3DXVECTOR4 vDif;
			vDif.x = pMate->Diffuse.r * light.Diffuse.r;
			vDif.y = pMate->Diffuse.g * light.Diffuse.g;
			vDif.z = pMate->Diffuse.b * light.Diffuse.b;
			vDif.w = pMate->Diffuse.a;
			GAMEDATA.m_SampSh.m_Effect->SetVector("Diffuse", &vDif);

			// �A���r�G���g
			GAMEDATA.m_SampSh.m_Effect->SetFloat("Ambient", light.Ambient.r);

			// �X�y�L����
			D3DXVECTOR4 vSpe;
			vSpe.x = pMate->Specular.r * light.Specular.r;
			vSpe.y = pMate->Specular.g * light.Specular.g;
			vSpe.z = pMate->Specular.b * light.Specular.b;
			vSpe.w = 1;
			GAMEDATA.m_SampSh.m_Effect->SetVector("Specular", &vSpe);

			// Power
			GAMEDATA.m_SampSh.m_Effect->SetFloat("Power", pMate->Power);

			// �e�N�X�`��������Ƃ�
			if (pTex) {
				// ���̃e�N�X�`�����Z�b�g
				GAMEDATA.m_SampSh.m_Effect->SetTexture("MeshTex", pTex);
			}
			// �e�N�X�`����������
			else {
				GAMEDATA.m_SampSh.m_Effect->SetTexture("MeshTex", GAMEDATA.m_SampSh.lpWhite);
			}


			// ��������Ă΂Ȃ��ƁA�V�F�[�_���ɂ��܂��p�����[�^���Z�b�g����Ȃ���I
			GAMEDATA.m_SampSh.m_Effect->CommitChanges();

			// ���b�V����`��
			xFile->lpMesh->DrawSubset(i);
		}

		// �p�X�I��
		GAMEDATA.m_SampSh.m_Effect->EndPass();
		// �e�N�j�b�N�I��
		GAMEDATA.m_SampSh.m_Effect->End();


		break;
	case false:

			DWORD i;

		for (i = 0; i < xFile->NumMaterial; i++) {
		lpD3DDevice->SetMaterial(&(xFile->Mat[i]));
		lpD3DDevice->SetTexture(0, xFile->Tex[i]);


		// DrawPrimitiveUP���ŕ`��
		xFile->lpMesh->DrawSubset(i);


		}

		break;
	}

}


//���b�V�����
void ObjBase::ReleaseMesh(struct XFILE *XFile) {
	if (XFile->lpMesh != NULL) {
		DWORD i;

		delete[] XFile->Mat;
		for (i = 0; i<XFile->NumMaterial; i++) {
			if (XFile->Tex[i] != NULL) {
				XFile->Tex[i]->Release();
				XFile->Tex[i] = NULL;
			}
		}
		delete[] XFile->Tex;
		XFile->lpMesh->Release();

		XFile->lpMesh = NULL;
	}
}

float ObjBase::GetLength(D3DXVECTOR3 _form, D3DXVECTOR3 _prev)
{
	D3DXVECTOR3 Vec;

	//���茳�ƃ^�����̊Ԃ̋�����ݒ�
	Vec = _prev- _form;
	float Len;
	Len = D3DXVec3Length(&Vec);
	return Len;
}
