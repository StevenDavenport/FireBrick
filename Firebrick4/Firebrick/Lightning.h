#pragma once
#include "Spell.h"

class CLightning : public CSpell
{
public:
	// Constructor
	CLightning(const int& type, const std::string& name, const int& attack);

	// Activates a card
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;
};

