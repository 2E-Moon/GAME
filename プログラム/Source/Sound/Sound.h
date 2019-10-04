#include<map>

#ifndef __Sound_h__
#define __Sound_h__


//�V���O���g���Ăяo���p
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
	
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//���
	void Release();

	//�T�E���h�֘A��������
	void SoundInit();

	//============
	//BGM�֘A����
	//===========
	//BGM�ǂݍ���
	void BGM_Load(std::string _Type, char *_Path);
	//BGM�Đ�
	void BGM_Play(std::string _Path);
	//BGM��~
	void BGM_Stop();

	//============
	//SE�֘A����
	//===========
	//SE�ǂݍ���
	void SE_Load(std::string _Type, char *_Path);
	//SE�Đ�
	void SE_Play(std::string _Path);
	//SE��~
	void SE_Stop();


	//DirectSound�I�u�W�F�N�g
	LPDIRECTSOUND8 lpDSound;

private:
	//�T�E���h�Ǎ��֐�
	void LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData, char *fname);

	LPDIRECTSOUNDBUFFER lpSPrimary;

	//=================
	//�T�E���h�p�}�b�v
	//��������g�p����T�E���h���Ăяo��
	//================
	//BGM�p�}�b�v
	std::map<std::string, LPDIRECTSOUNDBUFFER8> m_mapBGM;
	//SE�p�}�b�v
	std::map<std::string, LPDIRECTSOUNDBUFFER8> m_mapSE;

	//���ݍĐ����Ă���BGM������
	std::string st_NowPlay="NotPlay";
	DWORD Hz;
	//�{�����[���ƃp��
	long vol, pan=100;

};

#endif