#pragma once
#include "Equipment.h"

class CSword :	public CEquipment
{
public:
	// Constructor
	CSword(const int& type, const std::string& name);

	// functionality of the car
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override final;

private:
	const int mATTACK_INC = 2;
};

