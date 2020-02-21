#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <memory>
#include "SpecialAbilities.h"

class CCard
{
public:
	CCard(int type, std::string name);
	int GetType();
	std::string GetName();
	int GetProtection();
	void IncreaseProtection(int x);
	virtual int GetAttack() = 0;
	virtual int GetHealth() = 0;
	virtual int GetSpecialAbility() = 0;
	virtual void ReduceHealth(int x) = 0;
	virtual void IncreaseHealth(int x) = 0;
	virtual void IncreaseAttack(int x) = 0;

private:
	int type = -1;
	std::string name;
	int protection = 0;
};
