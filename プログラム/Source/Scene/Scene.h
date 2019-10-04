#ifndef __Scene_h__
#define __Scene_h__

#define MODE_TITLE 0
#define MODE_GAME 1

class Scene {
public:

	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();

	//�V�[���؂�ւ�
	void ChangeScene(int _Mode);

private:

	std::shared_ptr<Title> title;
	std::shared_ptr<Game> game;

	int GameMode;
};

#endif