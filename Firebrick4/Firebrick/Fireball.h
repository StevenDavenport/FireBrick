#pragma once
#include "Spell.h"

class CFireball : public CSpell
{
public:
	int GetType();
	std::string GetName();
	int GetAttack();
	int GetHealth();
	int GetSpecialAbility();
	void ReduceHealth(int x);
	void IncreaseHealth(int x);
	void IncreaseAttack(int x);
	void IncreaseProtection(int x);
	int GetProtection();

private:
	int type = 2;
	std::string name = "Fireball";
	int attack = 3;
	int specialAbility = fireball;
};

