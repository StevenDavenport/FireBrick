#include "pch.h"
#include "Trample.h"

CTrample::CTrample(std::string name) : name(name) {}

int CTrample::GetType()
{
	return type;
}

std::string CTrample::GetName()
{
	return name;
}

int CTrample::GetAttack()
{
	return attack;
}

int CTrample::GetHealth()
{
	return health;
}

int CTrample::GetSpecialAbility()
{
	return 0;
}

void CTrample::ReduceHealth(int x)
{
	health -= x;
}

void CTrample::IncreaseHealth(int x)
{
	health += x;
}

void CTrample::IncreaseAttack(int x)
{
}

void CTrample::IncreaseProtection(int x)
{
	protection += x;
}

int CTrample::GetProtection()
{
	return protection;
}

