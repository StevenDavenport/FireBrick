#include "pch.h"
#include "Bless.h"

int CBless::GetType()
{
	return type;
}

std::string CBless::GetName()
{
	return name;
}

int CBless::GetAttack()
{
	return attack;
}

int CBless::GetHealth()
{
	return 0;
}

int CBless::GetSpecialAbility()
{
	return specialAbility;
}

void CBless::ReduceHealth(int x)
{
}

void CBless::IncreaseHealth(int x)
{
}

void CBless::IncreaseAttack(int x)
{
}

void CBless::IncreaseProtection(int x)
{
}

int CBless::GetProtection()
{
	return 0;
}

