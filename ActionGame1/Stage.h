#pragma once
class Stage
{
public:
	Stage();
	~Stage();

	void Load();	//������
	void Draw();	//�`��

private:
	static constexpr float Scale = 0.004f;		//�傫��
	VECTOR position;	//�|�W�V����.
	int StageHandle;	//3D���f���n���h��


};

