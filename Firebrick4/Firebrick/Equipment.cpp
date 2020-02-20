#include "pch.h"
#include "Equipment.h"

CEquipment::CEquipment(std::string name) : name(name)
{
	if (name == "Sword")
	{
		type = 10;
		specialAbility = sword;
	}
	else
	{
		type = 11;
		specialAbility = armour;
	}
}

int CEquipment::GetType()
{
	return type;
}

std::string CEquipment::GetName()
{
	return name;
}

int CEquipment::GetAttack()
{
	return 0;
}

int CEquipment::GetHealth()
{
	return 0;
}

int CEquipment::GetSpecialAbility()
{
	return specialAbility;
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

void CEquipment::IncreaseProtection(int x)
{
}

int CEquipment::GetProtection()
{
	return 0;
}


