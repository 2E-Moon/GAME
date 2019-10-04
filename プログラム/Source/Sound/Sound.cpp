#include<windows.h>
#include<stdio.h>
#include<d3dx9.h>
#include<time.h>
#include<list>
#include<string>
#include<map>


#include"wavread.h"
#include<dsound.h>//2D�T�E���h

#include"../GameData.h"

#include"Sound.h"



void Sound::Init()
{
	//---------------------DirectSound�֘A-----------------------
	DirectSoundCreate8(NULL, &lpDSound, NULL);


	//�������x����ݒ�
	lpDSound->SetCooperativeLevel(GAMEDATA.T_hwnd, DSSCL_PRIORITY);

	// �v���C�}���E�o�b�t�@�̍쐬
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// �v���C�}���E�o�b�t�@���w��
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	// �o�b�t�@�����
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

	// �v���C�}���E�o�b�t�@��Wave�t�H�[�}�b�g��ݒ�
	// �@�@�@�D�拦�����x���ȏ�̋������x�����ݒ肳��Ă���K�v������܂��D
	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;		// �Q�`�����l���i�X�e���I�j
	pcmwf.nSamplesPerSec = 44100;	// �T���v�����O�E���[�g�@44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = 16;		// 16�r�b�g
	lpSPrimary->SetFormat(&pcmwf);


	//�T�E���h�̐ݒ��WAV�t�@�C���ǂݍ���
	SoundInit();


}

void Sound::SoundInit()
{
	//�{�����[��
	lpSPrimary->GetVolume(&vol);
	//�p��
	lpSPrimary->GetPan(&pan);

	CoInitialize(NULL);

	//===================
	//�T�E���h��ǂ݂���
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

	//�ǂݍ���BGM��BGM�}�b�v�̉��
	for (auto it : m_mapBGM) {
		it.second->Release();
	}
	m_mapBGM.clear();

	//�ǂݍ���SE�̉��
	for (auto it : m_mapSE) {
		it.second->Release();
	}
	m_mapSE.clear();


	
	
}

void Sound::BGM_Load(std::string _Type, char * _Path)
{
	//�}�b�v�Ɏw�肵���^�C�v���Ȃ���Γǂݍ���
	if (m_mapBGM.find(_Type) == m_mapBGM.end())
	{

		LPDIRECTSOUNDBUFFER8 lpSData;
		LoadWAVE(lpSData, _Path);
		lpSData->GetFrequency(&Hz);
		//�}�b�v�ɒǉ�
		m_mapBGM.insert(std::pair<std::string, LPDIRECTSOUNDBUFFER8>(_Type, lpSData));
	}
}

void Sound::BGM_Play(std::string _Type)
{
	//�}�b�v�Ɏw�肵���^�C�v���Ȃ���΃��^�[��
	if (m_mapBGM.find(_Type) == m_mapBGM.end())
	{
		return;
	}

	auto it = m_mapBGM.find(_Type);


	//���[�v�ōĐ�
	it->second->Play(0, 0, 0);
	st_NowPlay = _Type;
}

void Sound::BGM_Stop()
{
	//�}�b�v�Ɏw�肵���^�C�v���Ȃ���΃��^�[��
	if (m_mapBGM.find(st_NowPlay) == m_mapBGM.end())
	{
		return;
	}

	auto it = m_mapBGM.find(st_NowPlay);


	//���[�v�ōĐ�
	it->second->Stop();
}







void Sound::SE_Load(std::string _Type, char * _Path)
{
	//�}�b�v�Ɏw�肵���^�C�v���Ȃ���Γǂݍ���
	if (m_mapBGM.find(_Type) == m_mapBGM.end())
	{

		LPDIRECTSOUNDBUFFER8 lpSData;
		LoadWAVE(lpSData, _Path);
		lpSData->GetFrequency(&Hz);
		//�}�b�v�ɒǉ�
		m_mapSE.insert(std::pair<std::string, LPDIRECTSOUNDBUFFER8>(_Type, lpSData));
	}
}

void Sound::SE_Play(std::string _Type)
{
	//�}�b�v�Ɏw�肵���^�C�v���Ȃ���΃��^�[��
	if (m_mapSE.find(_Type) == m_mapSE.end())
	{
		return;
	}

	auto it = m_mapSE.find(_Type);


	//���[�v�ōĐ�
	it->second->Play(0, 0, 0);
}

void Sound::SE_Stop()
{

}








//�T�E���h�Ǎ��֐�
void Sound::LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData, char *fname)
{
	HRESULT hr;

	// WAVE�t�@�C�����J��
	CWaveSoundRead WaveFile;
	WaveFile.Open(fname);

	// �Z�J���_���E�o�b�t�@���쐬����
	// DSBUFFERDESC�\���̂�ݒ�
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	// �o�b�t�@�����
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&pDSData);
	pDSTmp->Release();

	// �Z�J���_���E�o�b�t�@��Wave�f�[�^����������
	LPVOID lpvPtr1;		// �ŏ��̃u���b�N�̃|�C���^
	DWORD dwBytes1;		// �ŏ��̃u���b�N�̃T�C�Y
	LPVOID lpvPtr2;		// �Q�Ԗڂ̃u���b�N�̃|�C���^
	DWORD dwBytes2;		// �Q�Ԗڂ̃u���b�N�̃T�C�Y

	hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOST���Ԃ��ꂽ�ꍇ�CRestore���\�b�h���g���ăo�b�t�@�𕜌�����
	if (DSERR_BUFFERLOST == hr)
	{
		pDSData->Restore();
		hr = pDSData->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ���b�N����

		// �����ŁC�o�b�t�@�ɏ�������
		// �o�b�t�@�Ƀf�[�^���R�s�[����
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// �������݂��I������炷����Unlock����D
		hr = pDSData->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}
}

