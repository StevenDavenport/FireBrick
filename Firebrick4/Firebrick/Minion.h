#pragma once
#include "Card.h"

class CMinion : public CCard									  // Minion type of card obj
{
public:
	CMinion(const int& type, const std::string& name,  const int& attack, const int& health);  // Constructor
	virtual int GetSpecialAbility();							  // Virtual Getter
	int GetAttack();											  // Getter
	int GetHealth();											  // Getter
	void ReduceHealth(const int& x);									  // Setter
	void IncreaseHealth(const int& x);									  // Setter
	void IncreaseAttack(const int& x);									  // Setter
																
private:														
	int mAttack = -1;											  // Attack value of a card
	int mHealth = -1;											  // Health value of a card

};

