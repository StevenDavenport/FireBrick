#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <memory>
#include "SpecialAbilities.h"

class CCard
{
public:
	CCard(const int& type, const std::string& name);// Constructor
	int GetType();									// Getter
	std::string GetName();							// Getter
	int GetProtection();							// Getter
	void IncreaseProtection(const int& x);			// Setter
	virtual int GetAttack() = 0;					// Virtual Getter
	virtual int GetHealth() = 0;					// Virtual Getter
	virtual int GetSpecialAbility() = 0;			// Virtual Getter
	virtual void ReduceHealth(const int& x) = 0;	// Virtual Setter
	virtual void IncreaseHealth(const int& x) = 0;	// Virtual Setter
	virtual void IncreaseAttack(const int& x) = 0;	// Virtual Setter
													
private:				
	int mType = -1;									// Variable that stores the type of the card object
	std::string mName;								// Variable that stores the name of the card object
	int mProtection = 0;							// Variable that stores the protection of the card object

};
