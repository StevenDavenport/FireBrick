#include "pch.h"
#include "SpecialMinion.h"

CSpecialMinion::CSpecialMinion(int type, std::string name, int attack, int health, int specialAbility)
	: CMinion(type, name, attack, health), specialAbility(specialAbility)
{
}

int CSpecialMinion::GetSpecialAbility()
{
	return specialAbility;
}