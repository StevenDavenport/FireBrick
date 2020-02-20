#include "pch.h"
#include "Leech.h"

int CLeech::GetType()
{
	return type;
}

std::string CLeech::GetName()
{
	return name;
}

int CLeech::GetAttack()
{
	return attack;
}

int CLeech::GetHealth()
{
	return health;
}

int CLeech::GetSpecialAbility()
{
	return 0;
}

void CLeech::ReduceHealth(int x)
{
	health -= x;
}

void CLeech::IncreaseHealth(int x)
{
	health += x;
}

void CLeech::IncreaseAttack(int x)
{
}

void CLeech::IncreaseProtection(int x)
{
	protection += x;
}

int CLeech::GetProtection()
{
	return protection;
}
