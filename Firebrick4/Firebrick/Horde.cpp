#include "pch.h"
#include "Horde.h"

CHorde::CHorde(std::string name) : name(name) {}

int CHorde::GetType()
{
	return type;
}

std::string CHorde::GetName()
{
	return name;
}

int CHorde::GetAttack()
{
	return attack;
}

int CHorde::GetHealth()
{
	return health;
}

int CHorde::GetSpecialAbility()
{
	return specialAbility;
}

void CHorde::ReduceHealth(int x)
{
	health -= x;
}

void CHorde::IncreaseHealth(int x)
{
	health += x;
}

void CHorde::IncreaseAttack(int x)
{
	attack += x;
}

void CHorde::IncreaseProtection(int x)
{
	protection += x;
}

int CHorde::GetProtection()
{
	return protection;
}
