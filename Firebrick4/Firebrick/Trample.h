#pragma once
#include "Minion.h"

class CTrample : public CMinion
{
public:
	CTrample(std::string name);
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
	int type = 8;
	std::string name = "";
	int attack = 3;
	int health = 6;
	int protection = 0;
};

