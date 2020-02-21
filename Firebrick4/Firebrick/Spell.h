#pragma once
#include "Card.h"

class CSpell : public CCard
{
public:
	CSpell(int type, std::string name, int specialAbility);
	int GetAttack();
	int GetHealth();
	int GetSpecialAbility();
	void ReduceHealth(int x);
	void IncreaseHealth(int x);
	void IncreaseAttack(int x);

private:
	int specialAbility = none;

};

