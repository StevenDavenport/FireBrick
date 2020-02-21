#include "pch.h"
#include "Minion.h"

CMinion::CMinion(int type, std::string name, int attack, int health) 
	: CCard(type, name), attack(attack), health(health)
{
}

int CMinion::GetSpecialAbility()
{
	return 0;
}

int CMinion::GetAttack()
{
	return attack;
}

int CMinion::GetHealth()
{
	return health;
}

void CMinion::ReduceHealth(int x)
{
	health -= x;
}

void CMinion::IncreaseHealth(int x)
{
	health += x;
}

void CMinion::IncreaseAttack(int x)
{
	attack += x;
}
