#pragma once
#include"HitChecker.h"

class Player;
class Enemy;

class EnemyAttackRangeChecker : public HitChecker
{
public:
	EnemyAttackRangeChecker();
	virtual~EnemyAttackRangeChecker();

	void Update(const Player& playerPos, const Enemy& enemypos)override;			// XV
	bool CheckHit(const Player& playerPos, const Enemy& enemypos) override;
	void DrawCircle()override;
	// ”ÍˆÍ“à‚É“ü‚Á‚Ä‚¢‚é‚©‚Ìæ“¾.
	const bool& GetPos() const { return isWithin; }
private:
	bool isWithin;
	float AttackRange;
	float LengthRange;
};

