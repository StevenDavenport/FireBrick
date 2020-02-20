#pragma once
#include "Minion.h"

class CLeech : public CMinion
{
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
	int type = 9;
	std::string name = "Leech";
	int attack = 2;
	int health = 2;
	int protection = 0;
};

