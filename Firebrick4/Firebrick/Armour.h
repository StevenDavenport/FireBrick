#pragma once
#include "Equipment.h"

class CArmour :	public CEquipment
{
public:
	// Constructor
	CArmour(const int& type, const std::string& name);

	// Casts the effect of the card
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;

private:
	const int mPROTECT_INC = 1;			// How much the cards protection will be incremented
};

