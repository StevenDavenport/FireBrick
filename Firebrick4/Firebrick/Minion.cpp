#include "pch.h"
#include "Minion.h"

CMinion::CMinion(const int& type, const std::string& name, const int& attack, const int& health)
	: CCard(type, name), mAttack(attack), mHealth(health)
{
}

int CMinion::GetSpecialAbility()
{
	return 0;
}

int CMinion::GetAttack()
{
	return mAttack;
}

int CMinion::GetHealth()
{
	return mHealth;
}

void CMinion::ReduceHealth(const int& x)
{
	mHealth -= x;
}

void CMinion::IncreaseHealth(const int& x)
{
	mHealth += x;
}

void CMinion::IncreaseAttack(const int& x)
{
	mAttack += x;
}
