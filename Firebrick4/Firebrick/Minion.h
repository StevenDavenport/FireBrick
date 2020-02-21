#pragma once
#include "Card.h"

class CMinion : public CCard
{
public:
	CMinion(int type, std::string name, int attack, int health);
	virtual int GetSpecialAbility();
	int GetAttack();
	int GetHealth();
	void ReduceHealth(int x);
	void IncreaseHealth(int x);
	void IncreaseAttack(int x);

private:
	int attack = -1;
	int health = -1;

};

