#include "pch.h"
#include "Vampire.h"

CVampire::CVampire()
{
}

int CVampire::GetType()
{
	return type;
}

std::string CVampire::GetName()
{
	return name;
}

int CVampire::GetAttack()
{
	return attack;
}

int CVampire::GetHealth()
{
	return health;
}

int CVampire::GetSpecialAbility()
{
	return 0;
}

void CVampire::ReduceHealth(int x)
{
	health -= x;
}

void CVampire::IncreaseHealth(int x)
{
	health += x;
}

void CVampire::IncreaseAttack(int x)
{
}

void CVampire::IncreaseProtection(int x)
{
	protection += x;
}

int CVampire::GetProtection()
{
	return protection;
}
