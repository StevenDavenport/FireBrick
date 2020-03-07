#pragma once
#include "Minion.h"

class CHorde :	public CMinion
{
public:
	// Constructor
	CHorde(const int& type, const std::string& name, const int& attack, const int& health);

	// Spell identifier
	virtual const bool& IsSpell() override;

	// Attacking function for 
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;

private:
	const bool mSPELL = false;								// Spell flag regoniser
	const int mATTACK_INCREMENT = 1;						// Attack increment
	bool mSpecialCast = false;								// Prevents special being used multiple times

};

