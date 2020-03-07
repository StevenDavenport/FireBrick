#pragma once
#include "Spell.h"

class CBless : public CSpell
{
public:
	// Constructor
	CBless(const int& type, const std::string& name, const int& attack);

	// Activates a card
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;

private:
	const int mHEALS = 2;

};

