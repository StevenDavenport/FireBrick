#pragma once
#include "pch.h"
#include <string>
#include "SpecialAbilities.h"

class CCard
{
public:
	virtual int GetType() = 0;
	virtual std::string GetName() = 0;
	virtual int GetAttack() = 0;
	virtual int GetHealth() = 0;
	virtual int GetSpecialAbility() = 0;
	virtual void ReduceHealth(int x) = 0;
	virtual void IncreaseHealth(int x) = 0;
	virtual void IncreaseAttack(int x) = 0;
	virtual void IncreaseProtection(int x) = 0;
	virtual int GetProtection() = 0;

};
