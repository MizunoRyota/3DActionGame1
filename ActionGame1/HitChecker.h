#pragma once

class Player;
class Enemy;

class HitChecker 
{
public:
	HitChecker();
	virtual~HitChecker();
	 virtual void Update(const Player& playerPos,const Enemy& enemypos) ;		// 更新
	 virtual bool CheckHit(const Player& playerPos, const Enemy& enemypos);		//当たり判定チェック
	virtual void DrawCircle();													//当たり判定の球描画
protected:
	static constexpr  float PlayerHight=0.8f;		//プレイヤーの高さ
	bool isHit;

	//プレイヤーの当たり判定変数
	VECTOR playerCircle;				//プレイヤーの当たり判定のポジション
	float playerRadius;					//プレイヤーの当たり判定の半径

	//Enemyの当たり判定
	VECTOR enemyCircle;					//Enemyの当たり判定のポジション
	float enemyRadius;					//Enemyの当たり判定の半径

	VECTOR keepDistance;				//距離を保持する変数
	float Distance;						//距離
	float Length;						//プレイヤーの円とEnemyの円の半径の合計

};

