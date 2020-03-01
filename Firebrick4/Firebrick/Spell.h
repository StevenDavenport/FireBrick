#pragma once
#include "Card.h"

class CSpell : public CCard									 // A spell is a type of card
{
public:
	CSpell(const int& type, const std::string& name, const int& specialAbility);  // Constructor
	int GetAttack();										 // Getter
	int GetHealth();										 // Getter
	int GetSpecialAbility();								 // Getter
	void ReduceHealth(const int& x);						 // Setter
	void IncreaseHealth(const int& x);						 // Setter
	void IncreaseAttack(const int& x);						 // Setter
															 
private:													  
	int mSpecialAbility = none;								 // Special ability value of the card

};

