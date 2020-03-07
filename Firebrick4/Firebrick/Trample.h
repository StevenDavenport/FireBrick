#pragma once
#include "Minion.h"
#include "Player.h"

class CTrample : public CMinion
{
public:
	// Constructor
	CTrample(const int& type, const std::string& name, const int& attack, const int& health);

	// Spell identifier
	virtual const bool& IsSpell() override final;

	// This cards attack function
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;

private:
	const bool mSPELL = false;									  // Spell flag regoniser
	const int mDEFAULT_ATTACK = 3;								  // Stores the origonal attack

};

