#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();
	void Load();


private:
	//enemy地震に関するメンバ変数
	int EnemyHandle;
	VECTOR position;

};

