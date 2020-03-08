#include "pch.h"
#include "Spell.h"

CSpell::CSpell(const int& type, const std::string& name, const int& attack)
	: CCard(type, name), mAttack(attack) {}

int& CSpell::GetAttack()
{
	return mAttack;
}

void CSpell::IncreaseAttack(const int& x)
{
	mAttack += x;
}

void CSpell::SetAttack(const int& x)
{
	mAttack = x;
}

const bool &CSpell::IsSpell()
{
	return mSpell;
}

int& CSpell::GetHealth()
{
	return mHealth;
}

void CSpell::ReduceHealth(const int& attackDammage)
{
	mHealth -= attackDammage - this->GetProtection();
}

void CSpell::IncreaseHealth(const int& heal)
{
	mHealth += heal;
}
