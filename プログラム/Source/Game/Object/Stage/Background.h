#ifndef __Background_h__
#define __Background_h__

class Background : public ObjBase {
public:

	//������
	virtual void Init();
	//�X�V
	virtual void Update();
	//�`��
	virtual void Draw();
	//���
	virtual void Release();

private:
	//�w�i���񂷗p�ϐ�
	//�p�x
	float rad = 0;
	//����
	D3DXMATRIX mSpeed;

};

#endif