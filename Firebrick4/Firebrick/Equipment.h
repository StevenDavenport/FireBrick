#pragma once
#include "Spell.h"

class CEquipment : public CSpell								 // Equiptment is a type of spell card
{																 
public:															  
	CEquipment(const int& type, const std::string& name, const int& specialAbility);  // Constructor 
	int GetAttack();											 // Getter
	int GetHealth();											 // Getter
	void ReduceHealth(const int& x);									 // Setter
	void IncreaseHealth(const int& x);									 // Setter
	void IncreaseAttack(const int& x);									 // Setter

};

