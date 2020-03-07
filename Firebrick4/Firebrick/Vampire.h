#pragma once
#include "Minion.h"

class CVampire : public CMinion
{
public:
	// Constructor
	CVampire(const int& type, const std::string& name, const int& attack, const int& health);

	// Spell identifier
	const bool& IsSpell() override final;
	
	// Attack function
	void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;

private:
	const int mHEAL = 1;					// How much the vampire will heal after attacking
	const bool mSPELL = false;				// On play spell ability
};

