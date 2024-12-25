#pragma once

class HitChecker;
class  AttackHit : public HitChecker
{
public:
	 AttackHit();
	 virtual ~AttackHit();
	 bool CheckPlayerDamage(const Player& player, const Enemy& enemy);
private:

};

