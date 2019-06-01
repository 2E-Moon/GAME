#include<map>

#ifndef __Sound_h__
#define __Sound_h__



#define SOUND Sound::GetInstance()

class Sound{
public:

	//------------------
	//	�V���O���g������
	//------------------
	static Sound& GetInstance()
	{
		static Sound Instance;
		return Instance;

	}
	

	void Init();
	void Update();
	void Draw();
	void Release();

	void SoundInit();

	void BGM_Load(std::string _Type, char *_Path);
	void BGM_Play(std::string _Path);
	void BGM_Stop();

	void SE_Load(std::string _Type, char *_Path);
	void SE_Play(std::string _Path);
	void SE_Stop();



	LPDIRECTSOUND8 lpDSound;	//DirectSound�I�u�W�F�N�g

	LPDIRECTSOUNDBUFFER8 lpCursor;
	LPDIRECTSOUNDBUFFER8 lpDecision;
private:
	//�T�E���h�Ǎ��֐�
	void LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData, char *fname);

	LPDIRECTSOUNDBUFFER lpSPrimary;

	std::map<std::string, LPDIRECTSOUNDBUFFER8> m_mapBGM;
	std::map<std::string, LPDIRECTSOUNDBUFFER8> m_mapSE;

	std::string st_NowPlay="NotPlay";
	DWORD Hz;
	long vol, pan=100;

};

#endif