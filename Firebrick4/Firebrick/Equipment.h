#pragma once
#include "Spell.h"

class CEquipment : public CSpell
{
public:
	CEquipment(int type, std::string name, int specialAbility);
	int GetAttack();
	int GetHealth();
	void ReduceHealth(int x);
	void IncreaseHealth(int x);
	void IncreaseAttack(int x);

};

