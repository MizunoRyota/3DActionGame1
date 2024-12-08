#pragma once
#include"HitChecker.h"

class Player;
class Enemy;

class EnemyAttackRangeChecker : public HitChecker
{
public:
	EnemyAttackRangeChecker();
	virtual~EnemyAttackRangeChecker();

	void Update(const Player& playerPos, const Enemy& enemypos)override;			// 更新
	bool CheckHit(const Player& playerPos, const Enemy& enemypos) override;
	void DrawCircle()override;
	// 範囲内に入っているかの取得.
	const bool& GetPos() const { return isWithin; }
private:
	bool isWithin;
	float AttackRange;
	float LengthRange;
};

