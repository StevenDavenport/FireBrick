#pragma once
#include "pch.h"
#include "Minion.h"

class CBasicMinion : public CMinion 
{
public:
	CBasicMinion(std::string name, int attack, int health);
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
	int type = 1;
	std::string name;
	int attack = -1;
	int health = -1;
	int protection = 0;
};
