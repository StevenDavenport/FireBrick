#pragma once
#include "Card.h"
#include "Spell.h"

class CFireball : public CSpell
{
public:
	// Constructor
	CFireball(const int& type, const std::string& name, const int& attack);

	// Activates a card
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;

private:

};
