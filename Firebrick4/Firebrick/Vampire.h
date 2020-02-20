#pragma once
#include "Minion.h"

class CVampire : public CMinion
{
public:
	CVampire();
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
	int type = 5;
	std::string name = "Vampire";
	int attack = 2;
	int health = 3;
	int protection = 0;
};

