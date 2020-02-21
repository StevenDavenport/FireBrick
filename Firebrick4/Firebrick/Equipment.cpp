#include "pch.h"
#include "Equipment.h"

CEquipment::CEquipment(int type, std::string name, int specialAbility)
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

void CEquipment::ReduceHealth(int x)
{
}

void CEquipment::IncreaseHealth(int x)
{
}

void CEquipment::IncreaseAttack(int x)
{
}

