#ifndef __Background_h__
#define __Background_h__

class Background : public ObjBase {
public:

	//‰Šú‰»
	virtual void Init();
	//XV
	virtual void Update();
	//•`‰æ
	virtual void Draw();
	//‰ğ•ú
	virtual void Release();

private:
	//”wŒi‚ğ‰ñ‚·—p•Ï”
	//Šp“x
	float rad = 0;
	//‘¬‚³
	D3DXMATRIX mSpeed;

};

#endif