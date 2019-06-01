#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<string>




#include"Game/Object/ObjBase.h"
#include"Game/Object/Player/Player.h"
#include"Game/Object/Enemy/Enemy.h"
#include"Game/Object/Stage/Stage.h"
#include"Game/Object/Stage/BackGround.h"
#include"Game/Object/Stage/Sand.h"
#include"Game/Object/Gimmick/Pot.h"
#include"Game/Result/Result.h"
#include"Game/Game.h"
#include"GameData.h"

#include"Shader/Shader.h"

#include"Game/Effect/Effect.h"

#include"UI/UIBase.h"
#include"Title/Title_UI/Title_UI.h"

#include"Title/Title.h"

#include"UI/GameUI/GameUI.h"

#include"Scene/Scene.h"

#include<dsound.h>//2D�T�E���h
#include"Sound/wavread.h"
#include"Sound/Sound.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "dsound.lib")//2D�T�E���h

#define	FULLSCREEN	0		// �t���X�N���[������ 1 �ɂ���
#define	SCRW		640		// Width
#define	SCRH		480		// Height

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)










void UpdateProc() {

	//�J�[�\���֘A
	GetCursorPos(&GAMEDATA.NowPt);
	ScreenToClient(GAMEDATA.T_hwnd, &GAMEDATA.NowPt);


	//�V�[���X�V
	GAMEDATA.p_scene->Update();


}

void RenderProc() {

	//�V�[���`��
	GAMEDATA.p_scene->Draw();

}


void DrawFrame(void)
{
	// �`��J�n
	GAMEDATA.lpD3DDevice->BeginScene();

	// �o�b�N�o�b�t�@�� Z �o�b�t�@���N���A
	GAMEDATA.lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);


	//�r���[�|�[�g�ݒ�
	D3DVIEWPORT9 ViewP;

	ViewP.X = 0;
	ViewP.Y = 0;
	ViewP.Width = 640;
	ViewP.Height = 480;
	ViewP.MinZ = 0;
	ViewP.MaxZ = 1;
	GAMEDATA.lpD3DDevice->SetViewport(&ViewP);
	GAMEDATA.lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);









	// ���_�s��̐ݒ�
	D3DXMatrixLookAtLH(&GAMEDATA.mView,
		&GAMEDATA.CPos,
		&GAMEDATA.CLook,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)
	);

	// ���e�s��̐ݒ�
	D3DXMatrixPerspectiveFovLH(&GAMEDATA.mProj, D3DXToRadian(60), 4.0f / 3.0f, 1.0f, 1200.0f);

	//�s��ݒ�
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_VIEW, &GAMEDATA.mView);
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_PROJECTION, &GAMEDATA.mProj);


	D3DLIGHT9 light;
	GAMEDATA.lpD3DDevice->GetLight(0, &light);
	GAMEDATA.m_SampSh.SetLightDir(&(D3DXVECTOR3)light.Direction);


	//�Q�[���������X�V
	UpdateProc();

	//�Q�[���������`��
	RenderProc();


	// �`��I��
	GAMEDATA.lpD3DDevice->EndScene();

	// �o�b�N�o�b�t�@���v���C�}���o�b�t�@�ɃR�s�[
	GAMEDATA.lpD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LRESULT APIENTRY WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPSTR lpszCmdParam, int nCmdshow)
{
	LPDIRECT3DSURFACE9 lpBackbuffer;
	D3DPRESENT_PARAMETERS d3dpp;

	int adapter;

	bool FullScreen=false;
	MSG msg;

//	HWND hwnd;
	WNDCLASS wc;
	char szAppName[] = "Generic Game SDK Window";

	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WndFunc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	RegisterClass(&wc);

	GAMEDATA.T_hwnd = CreateWindowEx(
		//		WS_EX_TOPMOST,
		0,
		szAppName,
		"Direct X",
		//		WS_VISIBLE|WS_POPUP,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCRW, SCRH,
		NULL, NULL, hInst,
		NULL);

	if (!GAMEDATA.T_hwnd)return FALSE;

	ShowWindow(GAMEDATA.T_hwnd, nCmdshow);
	UpdateWindow(GAMEDATA.T_hwnd);
	SetFocus(GAMEDATA.T_hwnd);

	//�t���X�N���[���ɂ��邩�I�ԃE�B���h�E
	if ((MessageBox(GAMEDATA.T_hwnd, "�t���X�N���[���ɂ��܂����B", " ", MB_YESNO)) == IDYES) {
		FullScreen = 1;
	}
	else {
		FullScreen = 0;
	}

	if (FullScreen) {
		ShowCursor(TRUE);
	}
	else {
		ShowCursor(TRUE);
		RECT rc = { 0,0,SCRW,SCRH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(GAMEDATA.T_hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOZORDER);
	}

	//---------------------DirectX Graphics�֘A-----------------------

	// Direct3D �I�u�W�F�N�g���쐬
	GAMEDATA.lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!GAMEDATA.lpD3D)
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL, "Direct3D �̍쐬�Ɏ��s���܂����B", "ERROR", MB_OK | MB_ICONSTOP);
		// �I������
		return 0;
	}
	// �g�p����A�_�v�^�ԍ�
	adapter = 0;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D �������p�����[�^�̐ݒ�
	if (FullScreen)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		D3DDISPLAYMODE disp;
		// ���݂̉�ʃ��[�h���擾
		GAMEDATA.lpD3D->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// �\���̈�T�C�Y�̐ݒ�
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!FullScreen)
	{
		// �E�C���h�E���[�h
		d3dpp.Windowed = 1;
	}

	// Z �o�b�t�@�̎����쐬
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�ޯ��ޯ̧��ۯ��\�ɂ���(GetDC���\�ɂȂ�)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(GAMEDATA.lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, GAMEDATA.T_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &GAMEDATA.lpD3DDevice)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(GAMEDATA.lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, GAMEDATA.T_hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &GAMEDATA.lpD3DDevice)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(GAMEDATA.lpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, GAMEDATA.T_hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &GAMEDATA.lpD3DDevice)))
			{
				// ���ǎ��s����
				MessageBox(NULL, "DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B", "ERROR", MB_OK | MB_ICONSTOP);
				GAMEDATA.lpD3D->Release();
				// �I������
				return 0;
			}
		}
	}

	// �����_�����O�E�X�e�[�g��ݒ�
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�u�����f�B���O�L����
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// �A���t�@�u�����f�B���O���@��ݒ�
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�
	GAMEDATA.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// �e�N�X�`���̐F���g�p
	GAMEDATA.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// ���_�̐F���g�p
	GAMEDATA.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// �����_�����O���̐F�̌v�Z���@�̐ݒ�
	GAMEDATA.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//���ʃJ�����O
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �t�B���^�ݒ�
	GAMEDATA.lpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	GAMEDATA.lpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GAMEDATA.lpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// ���C�g
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	D3DLIGHT9 Light;
	ZeroMemory(&Light, sizeof(Light));
	Light.Type = D3DLIGHT_DIRECTIONAL;
	Light.Diffuse.r = 1.3f;
	Light.Diffuse.g = 1.3f;
	Light.Diffuse.b = 1.3f;

	Light.Ambient.r = 0.3f;
	Light.Ambient.g = 0.3f;
	Light.Ambient.b = 0.3f;

	Light.Specular.r = 1.0f;
	Light.Specular.g = 1.0f;
	Light.Specular.b = 1.0f;
	Light.Specular.a = 0.0f;

	Light.Direction = D3DXVECTOR3(0, -1, -1);
	GAMEDATA.lpD3DDevice->SetLight(0, &Light);
	GAMEDATA.lpD3DDevice->LightEnable(0, TRUE);
	//
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

	GAMEDATA.lpD3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &lpBackbuffer);

	// ���_�t�H�[�}�b�g�̐ݒ�
	GAMEDATA.lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);

	//�V�[���쐬
	std::shared_ptr<Scene> scene=std::make_shared<Scene>();
	scene->Init();
	GAMEDATA.p_scene = scene;

	//�T�E���h�֘A������
	SOUND.Init();

	//�J�[�\����\���̍ۂ͐^�񒆂ɌŒ肳����
	GAMEDATA.BasePt.x = 320;
	GAMEDATA.BasePt.y = 240;
	ClientToScreen(GAMEDATA.T_hwnd, &GAMEDATA.BasePt);
	SetCursorPos(GAMEDATA.BasePt.x, GAMEDATA.BasePt.y);

	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			DrawFrame();
		}
	}

	timeEndPeriod(1);

	//�T�E���h�֘A���
	SOUND.Release();

	//���݂̃V�[�����
	scene->Release();

	lpBackbuffer->Release();

	// Direct3D �I�u�W�F�N�g�����
	GAMEDATA.lpD3DDevice->Release();
	GAMEDATA.lpD3D->Release();

	return (int)msg.wParam;
}