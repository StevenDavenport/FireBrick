#include "pch.h"
#include "Fireball.h"

int CFireball::GetType()
{
	return type;
}

std::string CFireball::GetName()
{
	return name;
}

int CFireball::GetAttack()
{
	return attack;
}

int CFireball::GetHealth()
{
	return 0;
}

int CFireball::GetSpecialAbility()
{
	return specialAbility;
}

void CFireball::ReduceHealth(int x)
{
}

void CFireball::IncreaseHealth(int x)
{
}

void CFireball::IncreaseAttack(int x)
{
}

void CFireball::IncreaseProtection(int x)
{
}

int CFireball::GetProtection()
{
	return 0;
}
