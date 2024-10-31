#pragma once

class Player
{
public:
	// 状態
	enum class State : int
	{
		Stand = 0,		// 立ち止まり
		Run = 1,		// 走り
		Jump = 2,		// ジャンプ
	};

	Player();
	~Player();

	void Load();	//初期化
	void Update();  //更新

private:
	//プレイヤー自身に関するメンバ変数
	VECTOR	Velocity;					// 移動力.
	VECTOR Positon;						// ポジション.
	VECTOR	Dir;						// 回転方向.

	State		currentState;			// 状態

};