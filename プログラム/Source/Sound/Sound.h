#include<map>

#ifndef __Sound_h__
#define __Sound_h__


//シングルトン呼び出す用
#define SOUND Sound::GetInstance()

class Sound{
public:

	//------------------
	//	シングルトン生成
	//------------------
	static Sound& GetInstance()
	{
		static Sound Instance;
		return Instance;

	}
	
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	//解放
	void Release();

	//サウンド関連初期処理
	void SoundInit();

	//============
	//BGM関連処理
	//===========
	//BGM読み込み
	void BGM_Load(std::string _Type, char *_Path);
	//BGM再生
	void BGM_Play(std::string _Path);
	//BGM停止
	void BGM_Stop();

	//============
	//SE関連処理
	//===========
	//SE読み込み
	void SE_Load(std::string _Type, char *_Path);
	//SE再生
	void SE_Play(std::string _Path);
	//SE停止
	void SE_Stop();


	//DirectSoundオブジェクト
	LPDIRECTSOUND8 lpDSound;

private:
	//サウンド読込関数
	void LoadWAVE(LPDIRECTSOUNDBUFFER8 &pDSData, char *fname);

	LPDIRECTSOUNDBUFFER lpSPrimary;

	//=================
	//サウンド用マップ
	//ここから使用するサウンドを呼び出す
	//================
	//BGM用マップ
	std::map<std::string, LPDIRECTSOUNDBUFFER8> m_mapBGM;
	//SE用マップ
	std::map<std::string, LPDIRECTSOUNDBUFFER8> m_mapSE;

	//現在再生しているBGMを入れる
	std::string st_NowPlay="NotPlay";
	DWORD Hz;
	//ボリュームとパン
	long vol, pan=100;

};

#endif