#ifndef __Background_h__
#define __Background_h__

class Background : public ObjBase {
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
	//背景を回す用変数
	//角度
	float rad = 0;
	//速さ
	D3DXMATRIX mSpeed;

};

#endif