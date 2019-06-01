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

#include<dsound.h>//2Dサウンド
#include"Sound/wavread.h"
#include"Sound/Sound.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "dsound.lib")//2Dサウンド

#define	FULLSCREEN	0		// フルスクリーン時に 1 にする
#define	SCRW		640		// Width
#define	SCRH		480		// Height

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)










void UpdateProc() {

	//カーソル関連
	GetCursorPos(&GAMEDATA.NowPt);
	ScreenToClient(GAMEDATA.T_hwnd, &GAMEDATA.NowPt);


	//シーン更新
	GAMEDATA.p_scene->Update();


}

void RenderProc() {

	//シーン描画
	GAMEDATA.p_scene->Draw();

}


void DrawFrame(void)
{
	// 描画開始
	GAMEDATA.lpD3DDevice->BeginScene();

	// バックバッファと Z バッファをクリア
	GAMEDATA.lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);


	//ビューポート設定
	D3DVIEWPORT9 ViewP;

	ViewP.X = 0;
	ViewP.Y = 0;
	ViewP.Width = 640;
	ViewP.Height = 480;
	ViewP.MinZ = 0;
	ViewP.MaxZ = 1;
	GAMEDATA.lpD3DDevice->SetViewport(&ViewP);
	GAMEDATA.lpD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);









	// 視点行列の設定
	D3DXMatrixLookAtLH(&GAMEDATA.mView,
		&GAMEDATA.CPos,
		&GAMEDATA.CLook,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&GAMEDATA.mProj, D3DXToRadian(60), 4.0f / 3.0f, 1.0f, 1200.0f);

	//行列設定
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_VIEW, &GAMEDATA.mView);
	GAMEDATA.lpD3DDevice->SetTransform(D3DTS_PROJECTION, &GAMEDATA.mProj);


	D3DLIGHT9 light;
	GAMEDATA.lpD3DDevice->GetLight(0, &light);
	GAMEDATA.m_SampSh.SetLightDir(&(D3DXVECTOR3)light.Direction);


	//ゲーム内処理更新
	UpdateProc();

	//ゲーム内処理描画
	RenderProc();


	// 描画終了
	GAMEDATA.lpD3DDevice->EndScene();

	// バックバッファをプライマリバッファにコピー
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

	//フルスクリーンにするか選ぶウィンドウ
	if ((MessageBox(GAMEDATA.T_hwnd, "フルスクリーンにしますか。", " ", MB_YESNO)) == IDYES) {
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

	//---------------------DirectX Graphics関連-----------------------

	// Direct3D オブジェクトを作成
	GAMEDATA.lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!GAMEDATA.lpD3D)
	{
		// オブジェクト作成失敗
		MessageBox(NULL, "Direct3D の作成に失敗しました。", "ERROR", MB_OK | MB_ICONSTOP);
		// 終了する
		return 0;
	}
	// 使用するアダプタ番号
	adapter = 0;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D 初期化パラメータの設定
	if (FullScreen)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
		//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		D3DDISPLAYMODE disp;
		// 現在の画面モードを取得
		GAMEDATA.lpD3D->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// 表示領域サイズの設定
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!FullScreen)
	{
		// ウインドウモード
		d3dpp.Windowed = 1;
	}

	// Z バッファの自動作成
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//ﾊﾞｯｸﾊﾞｯﾌｧをﾛｯｸ可能にする(GetDCも可能になる)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// デバイスの作成 - T&L HAL
	if (FAILED(GAMEDATA.lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, GAMEDATA.T_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &GAMEDATA.lpD3DDevice)))
	{
		// 失敗したので HAL で試行
		if (FAILED(GAMEDATA.lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, GAMEDATA.T_hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &GAMEDATA.lpD3DDevice)))
		{
			// 失敗したので REF で試行
			if (FAILED(GAMEDATA.lpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, GAMEDATA.T_hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &GAMEDATA.lpD3DDevice)))
			{
				// 結局失敗した
				MessageBox(NULL, "DirectX9が初期化できません。\n未対応のパソコンと思われます。", "ERROR", MB_OK | MB_ICONSTOP);
				GAMEDATA.lpD3D->Release();
				// 終了する
				return 0;
			}
		}
	}

	// レンダリング・ステートを設定
	// Z バッファ有効化->前後関係の計算を正確にしてくれる
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// アルファブレンディング有効化
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// アルファブレンディング方法を設定
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// レンダリング時のアルファ値の計算方法の設定
	GAMEDATA.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// テクスチャの色を使用
	GAMEDATA.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// 頂点の色を使用
	GAMEDATA.lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// レンダリング時の色の計算方法の設定
	GAMEDATA.lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//裏面カリング
	GAMEDATA.lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// フィルタ設定
	GAMEDATA.lpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	GAMEDATA.lpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GAMEDATA.lpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// ライト
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

	// 頂点フォーマットの設定
	GAMEDATA.lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);

	//シーン作成
	std::shared_ptr<Scene> scene=std::make_shared<Scene>();
	scene->Init();
	GAMEDATA.p_scene = scene;

	//サウンド関連初期化
	SOUND.Init();

	//カーソル非表示の際は真ん中に固定させる
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

	//サウンド関連解放
	SOUND.Release();

	//現在のシーン解放
	scene->Release();

	lpBackbuffer->Release();

	// Direct3D オブジェクトを解放
	GAMEDATA.lpD3DDevice->Release();
	GAMEDATA.lpD3D->Release();

	return (int)msg.wParam;
}