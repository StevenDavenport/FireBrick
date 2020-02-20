#pragma once
#include "Spell.h"


class CBless : public CSpell
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
	int type = 4;
	std::string name = "Bless";
	int attack = 2;
	int specialAbility = bless;
};

