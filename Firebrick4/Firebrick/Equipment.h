#pragma once
#include "Spell.h"

class CEquipment : public CSpell
{
public:
	CEquipment(std::string name);
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
	int type;
	std::string name;
	int specialAbility;
};

