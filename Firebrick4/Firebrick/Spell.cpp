#include "pch.h"
#include "Spell.h"

CSpell::CSpell(int type, std::string name, int specialAbility)
	: CCard(type, name), specialAbility(specialAbility)
{
}

int CSpell::GetAttack()
{
	return 0;
}

int CSpell::GetHealth()
{
	return 0;
}

int CSpell::GetSpecialAbility()
{
	return specialAbility;
}

void CSpell::ReduceHealth(int x)
{
}

void CSpell::IncreaseHealth(int x)
{
}

void CSpell::IncreaseAttack(int x)
{
}
