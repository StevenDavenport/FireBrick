#pragma once
#include "Card.h"

class CSpell : public CCard
{
public:
	// Constructor
	CSpell(const int& type, const std::string& name, const int& attack);

	// Spell identifier
	const bool& IsSpell() override final;

	// Getter for mHealth
	virtual int& GetHealth() override final;

	// Setter for mHealth
	virtual void ReduceHealth(const int& attackDammage) override final;

	// Setter for mHealth
	virtual void IncreaseHealth(const int& heal) override final;

	// Getter for mAttack
	virtual int& GetAttack() override final;

	// Setter for mAttack
	virtual void IncreaseAttack(const int& x) override final;

	// Setter for mAttack
	virtual void SetAttack(const int& x) override final;

	// Activates a card
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override = 0;

private:
	int mAttack = -1;				// Attack of the card
	int mHealth = 0;				// Health of the card
	bool mSpell = true;			    // Spell flag regoniser

};

