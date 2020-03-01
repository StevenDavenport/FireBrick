#include "pch.h"
#include "Spell.h"

CSpell::CSpell(const int& type, const std::string& name, const int& specialAbility)
	: CCard(type, name), mSpecialAbility(specialAbility)
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
	return mSpecialAbility;
}

void CSpell::ReduceHealth(const int& x)
{
}

void CSpell::IncreaseHealth(const int& x)
{
}

void CSpell::IncreaseAttack(const int& x)
{
}
