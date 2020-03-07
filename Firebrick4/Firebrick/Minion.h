#pragma once
#include "Card.h"

// Minion type of card obj
class CMinion : public CCard								  
{
public:
	// Constructor
	CMinion(const int& type, const std::string& name, const int& attack, const int& health);  

	// Returns the health of a card
	virtual int& GetHealth() override final;	

	// Dammages a card
	virtual void ReduceHealth(const int& attackDammage) override final;	

	// Setter for mHealth
	virtual void IncreaseHealth(const int& heal) override final;

	// Spell identifier
	virtual const bool& IsSpell() override;

	// Getter for mAttack
	virtual int& GetAttack() override final;

	// Setter for mAttack
	virtual void IncreaseAttack(const int& x) override final;

	// Setter for mAttack
	virtual void SetAttack(const int& x) override final;

	// Basic minion attack function
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override;

private:								
	int mAttack = -1;											  // Attack value of a card
	int mHealth = -1;											  // Health value of a card
	const bool mSPELL = false;									  // Spell flag regoniser

};

