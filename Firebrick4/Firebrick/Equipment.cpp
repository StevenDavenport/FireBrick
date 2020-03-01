#include "pch.h"
#include "Equipment.h"

CEquipment::CEquipment(const int& type, const std::string& name, const int& specialAbility)
	: CSpell(type, name, specialAbility)
{
}

int CEquipment::GetAttack()
{
	return 0;
}

int CEquipment::GetHealth()
{
	return 0;
}

void CEquipment::ReduceHealth(const int& x)
{
}

void CEquipment::IncreaseHealth(const int& x)
{
}

void CEquipment::IncreaseAttack(const int& x)
{
}

