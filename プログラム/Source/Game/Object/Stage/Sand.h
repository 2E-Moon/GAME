#ifndef __Sand_h__
#define __Sand_h__

class Sand : public ObjBase {
public:
	//初期化
	virtual void Init();
	//更新
	virtual void Update();
	//描画
	virtual void Draw();
	//解放
	virtual void Release();

private:

};

#endif