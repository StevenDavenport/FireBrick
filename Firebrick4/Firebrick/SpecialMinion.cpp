#include "pch.h"
#include "SpecialMinion.h"

CSpecialMinion::CSpecialMinion(const int& type, const std::string& name,
	const int& attack, const int& health, const int& specialAbility)
	: CMinion(type, name, attack, health), mSpecialAbility(specialAbility)
{
}

int CSpecialMinion::GetSpecialAbility()
{
	return mSpecialAbility;
}