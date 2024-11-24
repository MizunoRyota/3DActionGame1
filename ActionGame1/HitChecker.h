#pragma once

class Player;

class HitChecker
{
public:
	HitChecker();
	~HitChecker();
	void Update(const Player& playerPos);

	void circleDraw();								//当たり判定の球描画
private:
	//プレイヤーの当たり判定変数
	VECTOR playerCircle;							//プレイヤーの当たり判定のポジション
	float playerRadius;								//プレイヤーの当たり判定の半径
	static constexpr  float PlayerHight=0.8f;
	//プレイヤーの攻撃の当たり判定
	VECTOR playerAttackCircle;						//プレイヤーの当たり判定のポジション
	float playerAttackRadius;						//プレイヤーの当たり判定の半径
	static constexpr float AttackFront = 0.8f;

};

