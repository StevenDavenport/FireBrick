#pragma once
#include "Minion.h"

class CHorde : public CMinion
{
public:
	CHorde(std::string name); 
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
	int type = 7;
	std::string name = "";
	int attack = 1;
	int health = 3;
	int specialAbility = horde;
	int protection = 0;
};

