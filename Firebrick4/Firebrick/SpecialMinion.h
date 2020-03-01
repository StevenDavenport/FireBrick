#pragma once
#include "Minion.h"

class CSpecialMinion : public CMinion					      // Special minion is a type of minion card
{
public:																			   // Constructor
	CSpecialMinion(const int& type, const std::string& name, 
		const int& attack, const int& health, const int& specialAbility);
	int GetSpecialAbility(); 										// Getter

private:
	int mSpecialAbility = none;										// Stores a special ability property
};

