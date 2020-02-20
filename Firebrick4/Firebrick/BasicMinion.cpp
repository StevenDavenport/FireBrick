#include "pch.h"
#include "BasicMinion.h"

CBasicMinion::CBasicMinion(std::string name, int attack, int health) 
	: name(name), attack(attack), health(health) {}

int CBasicMinion::GetType()
{
	return type;
}

std::string CBasicMinion::GetName()
{
	return name;
}

int CBasicMinion::GetAttack()
{
	return attack;
}

int CBasicMinion::GetHealth()
{
	return health;
 }

int CBasicMinion::GetSpecialAbility()
{
	return 0;
}

void CBasicMinion::ReduceHealth(int x)
{
	health -= x;
}

void CBasicMinion::IncreaseHealth(int x)
{
	health += x;
}

void CBasicMinion::IncreaseAttack(int x)
{
	attack += x;
}

void CBasicMinion::IncreaseProtection(int x)
{
	protection += x;
}

int CBasicMinion::GetProtection()
{
	return protection;
}
