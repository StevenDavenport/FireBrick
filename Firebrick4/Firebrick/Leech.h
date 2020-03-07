#pragma once
#include "Minion.h"

class CLeech :	public CMinion
{
public:
	// Constructor
	CLeech(const int& type, const std::string& name, const int& attack, const int& health);

	// Spell identifier
	virtual const bool& IsSpell() override;

	// Attack function
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;

private:
	const bool mSPELL = false;									  // Spell flag regoniser
	const int mATTACK_INC = 2;									  // Attack Increment
};

