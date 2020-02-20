#pragma once
#include "Minion.h"

class CWall : public CMinion
{
public:
	CWall();
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
	int type = 6;
	std::string name = "Wall";
	int attack = 0;
	int health = 6;
	int protection = 0;
};

