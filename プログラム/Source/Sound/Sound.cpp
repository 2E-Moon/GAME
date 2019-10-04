#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<string>
#include<map>


#include"wavread.h"
#include<dsound.h>//2Dサウンド

#include"../GameData.h"

#include"Sound.h"



void Sound::Init()
{
	//---------------------DirectSound関連-----------------------
	DirectSoundCreate8(NULL, &lpDSound, NULL);


	//協調レベルを設定
	lpDSound->SetCooperativeLevel(GAMEDATA.T_hwnd, DSSCL_PRIORITY);

	// プライマリ・バッファの作成
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// プライマリ・バッファを指定
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	// バッファを作る
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

	// プライマリ・バッファのWaveフォーマットを設定
	// 　　　優先協調レベル以上の協調レベルが設定されている必要があります．
	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;		// ２チャンネル（ステレオ）
	pcmwf.nSamplesPerSec = 44100;	// サンプリング・レート　44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = 16;		// 16ビット
	lpSPrimary->SetFormat(&pcmwf);


	//サウンドの設定とWAVファイル読み込み
	SoundInit();


}

void Sound::SoundInit()
{
	//ボリューム
	lpSPrimary->GetVolume(&vol);
	//パン
	lpSPrimary->GetPan(&pan);

	CoInitialize(NULL);

	//===================
	//サウンドを読みこみ
	//===================
	//BGM
	BGM_Load("Battle", (char *)"Resource/Sound/BGM.wav");
	BGM_Load("Title", (char *)"Resource/Sound/Title.wav");
	
	//SE
	SE_Load("Hit", (char *)"Resource/Sound/Hit.wav");
	SE_Load("Attack", (char *)"Resource/Sound/Attack.wav");
	SE_Load("Jump", (char *)"Resource/Sound/Jump.wav");
	SE_Load("Cursor", (char *)"Resource/Sound/Cursor.wav");
	SE_Load("Decision", (char *)"Resource/Sound/Decision.wav");
	SE_Load("Get", (char *)"Resource/Sound/Get.wav");
	SE_Load("Whistle", (char *)"Resource/Sound/Whistle.wav");


}

void Sound::Update()
{

}

void Sound::Draw()
{

}

void Sound::Release()
{

	CoUninitialize();

	//読み込んだBGMとBGMマップの解放
	for (auto it : m_mapBGM) {
		it.second->Release();
	}
	m_mapBGM.clear();

	//読み込んだSEの解放
	for (auto it : m_mapSE) {
		it.second->Release();
	}
	m_mapSE.clear();


	
	
}

void Sound::BGM_Load(std::string _Type, char * _Path)
{
	//マップに指定したタイプがなければ読み込む
	if (m_mapBGM.find(_Type) == m_mapBGM.end())
	{

		LPDIRECTSOUNDBUFFER8 lpSData;
		LoadWAVE(lpSData, _Path);
		lpSData->GetFrequency(&Hz);
		//マップに追加
		m_mapBGM.insert(std::pair<std::string, LPDIRECTSOUNDBUFFER8>(_Type, lpSData));
	}
}

void Sound::BGM_Play(std::string _Type)
{
	//マップに指定したタイプがなければリターン
	if (m_mapBGM.find(_Type) == m_mapBGM.end())
	{
		return;
	}

	auto it = m_mapBGM.find(_Type);


	//ループで再生
	it->second->Play(0, 0, 0);
	st_NowPlay = _Type;
}

void Sound::BGM_Stop()
{
	//マップに指定したタイプがなければリターン
	if (m_mapBGM.find(st_NowPlay) == m_mapBGM.end())
	{
		return;
	}

	auto it = m_mapBGM.find(st_NowPlay);


	//ループで再生
	it->second->Stop();
}







void Sound::SE_Load(std::string _Type, char * _Path)
{
	//マップに指定したタイプがなければ読み込む
	if (m_mapBGM.find(_Type) == m_mapBGM.end())
	{

		LPDIRECTSOUNDBUFFER8 lpSData;
		LoadWAVE(lpSData, _Path);
		lpSData->GetFrequency(&Hz);
		//マップに追加
		m_mapSE.insert(std::pair<std::string, LPDIRECTSOUNDBUFFER8>(_Type, lpSData));
	}
}

void Sound::SE_Play(std::string _Type)
{
	//マップに指定したタイプがなければリターン
	if (m_mapSE.find(_Type) == m_mapSE.end())
	{
		return;
	}

	auto it = m_mapSE.find(_Type);


	//ループで再生
	it->second->Play(0, 0, 0);
}

void Sound::SE_Stop()
{

}








//サウンド読込関数
void Sound::LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData, char *fname)
{
	HRESULT hr;

	// WAVEファイルを開く
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	// バッファを作る
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSData);
	pDSTmp->Release();

	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1;		// 最初のブロックのポインタ
	DWORD dwBytes1;		// 最初のブロックのサイズ
	LPVOID lpvPtr2;		// ２番目のブロックのポインタ
	DWORD dwBytes2;		// ２番目のブロックのサイズ

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}
}

