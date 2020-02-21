#pragma once
#include "Minion.h"

class CSpecialMinion : public CMinion
{
public:
	CSpecialMinion(int type, std::string name, int attack, int health, int specialAbility);
	int GetSpecialAbility();

private:
	int specialAbility = none;
};

