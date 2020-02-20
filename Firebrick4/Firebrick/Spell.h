#pragma once
#include "Card.h"

class CSpell : public CCard
{
public:
	virtual int GetType() = 0;
	virtual std::string GetName() = 0;
	virtual int GetAttack() = 0;
	virtual int GetSpecialAbility() = 0;
	virtual void ReduceHealth(int x) = 0;
	virtual void IncreaseHealth(int x) = 0;
	virtual void IncreaseAttack(int x) = 0;

};

