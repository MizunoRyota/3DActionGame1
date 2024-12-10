#pragma once

class EnemyAttackRangeChecker : public HitChecker
{
public:
	EnemyAttackRangeChecker();
	virtual~EnemyAttackRangeChecker();

	void Update(const Player& player, const Enemy& enemy)override;	// XV
	bool CheckShortHit(const Player& player, const Enemy& enemy);
	bool CheckMiddleHit(const Player& player, const Enemy& enemy);
	bool CheckLongHit(const Player& player, const Enemy& enemy);

	void DrawCircle()override;
	// ”ÍˆÍ“à‚É“ü‚Á‚Ä‚¢‚é‚©‚Ìæ“¾.
	const bool& GetisShortWithin() const { return isShortWithin; }
	const bool& GetisMiddleWithin() const { return isMiddleWithin; }
	const bool& GetisLongWithin() const { return isLongWithin; }

private:
	bool isShortWithin;				//‹ß‹——£”»’è
	bool isMiddleWithin;			//’†‹——£”»’è
	bool isLongWithin;				//‰“‹——£”»’è
	float AttackShrotRange;			//‹ß‹——£”ÍˆÍ
	float AttackMiddleRange;		//’†‹——£”ÍˆÍ
	float AttackLongRange;			//‰“‹——£”ÍˆÍ
	float LengthRange;				//‰~‚Æ‰~‚Ì‹——£
	VECTOR keepDistance;			//‹——£‚ğ•Û‚·‚é•Ï”
	float Distance;					//‹——£
	float Length;					//ƒvƒŒƒCƒ„[‚Ì‰~‚ÆEnemy‚Ì‰~‚Ì”¼Œa‚Ì‡Œv
};