#pragma once
#include "Minion.h"

class CWall : public CMinion
{
public:
	// Constructor
	CWall(const int& type, const std::string& name, const int& attack, const int& health);

	// Check if the card has an on play spell
	virtual const bool& IsSpell() override final;

private:
	const bool mSPELL = false;									  // Spell flag regoniser

};

