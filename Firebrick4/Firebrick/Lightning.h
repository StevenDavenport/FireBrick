#pragma once
#include "Spell.h"

class CLightning : public CSpell
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
	int type = 3;
	std::string name = "Lightning";
	int attack = 1;
	int specialAbility = lightning;
};

