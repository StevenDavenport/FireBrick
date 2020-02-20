#include "pch.h"
#include "Wall.h"

CWall::CWall()
{
}

int CWall::GetType()
{
	return type;
}

std::string CWall::GetName()
{
	return name;
}

int CWall::GetAttack()
{
	return attack;
}

int CWall::GetHealth()
{
	return health;
}

int CWall::GetSpecialAbility()
{
	return 0;
}

void CWall::ReduceHealth(int x)
{
	health -= x;
}

void CWall::IncreaseHealth(int x)
{
	health += x;
}

void CWall::IncreaseAttack(int x)
{
}

void CWall::IncreaseProtection(int x)
{
	protection += x;
}

int CWall::GetProtection()
{
	return protection;
}
