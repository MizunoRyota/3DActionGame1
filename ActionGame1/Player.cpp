#include"DxLib.h"
#include"EffekseerForDXLib.h"
#include"Player.h"
Player::Player()
	:Positon(VGet(0.0f,0.0f,0.0f))
	
{
	// 処理なし
}

Player::~Player()
{
	// 処理なし
}

void Player::Load()
{
	//値の初期化
	Positon = VGet(0.0f, 0.0f, 0.0f);
	// モデルの読み込み

}

void Player::Update()
{
	// パッド入力によって移動パラメータを設定する
	VECTOR MoveVec;			// このフレームの移動ベクトル
	State prevState = currentState;

}