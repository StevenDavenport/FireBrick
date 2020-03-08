#include "pch.h"
#include "Armour.h"
#include "Player.h"

CArmour::CArmour(const int& type, const std::string& name)
	: CEquipment(type, name) {}

void CArmour::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	if (friendlyPlayer->mField.size() > 1)
	{
		// Generate a target
		int r = CRandom::Random(friendlyPlayer->mField.size() - 2);

		// Increase targets protection
		friendlyPlayer->mField[r]->IncreaseProtection(mPROTECT_INC);
	}
	else
	{
		// Heal player
		friendlyPlayer->IncreaseHealth(mPROTECT_INC * 2);
	}
}
