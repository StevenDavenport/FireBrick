#include "pch.h"
#include "Equipment.h"

CEquipment::CEquipment(const int& type, const std::string& name)
	: CCard(type, name) {}

const bool& CEquipment::IsSpell()
{
	return mSPELL;
}

int& CEquipment::GetHealth()
{
	int x = 0;
	return x;
}

void CEquipment::ReduceHealth(const int& attackDammage)
{
	return;
}

void CEquipment::IncreaseHealth(const int& heal)
{
	return;
}

int& CEquipment::GetAttack()
{
	int x = 0;
	return x;
}

void CEquipment::IncreaseAttack(const int& x)
{
	return;
}

void CEquipment::SetAttack(const int& x)
{
	return;
}