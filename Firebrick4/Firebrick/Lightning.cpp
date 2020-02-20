#include "pch.h"
#include "Lightning.h"

int CLightning::GetType()
{
	return type;
}

std::string CLightning::GetName()
{
	return name;
}

int CLightning::GetAttack()
{
	return attack;
}

int CLightning::GetHealth()
{
	return 0;
}

int CLightning::GetSpecialAbility()
{
	return specialAbility;
}

void CLightning::ReduceHealth(int x)
{
}

void CLightning::IncreaseHealth(int x)
{
}

void CLightning::IncreaseAttack(int x)
{
}

void CLightning::IncreaseProtection(int x)
{
}

int CLightning::GetProtection()
{
	return 0;
}

