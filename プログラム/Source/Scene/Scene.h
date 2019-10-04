#ifndef __Scene_h__
#define __Scene_h__

#define MODE_TITLE 0
#define MODE_GAME 1

class Scene {
public:

	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();

	//シーン切り替え
	void ChangeScene(int _Mode);

private:

	std::shared_ptr<Title> title;
	std::shared_ptr<Game> game;

	int GameMode;
};

#endif