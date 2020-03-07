#include "pch.h"
#include "Sword.h"
#include "Player.h"

CSword::CSword(const int& type, const std::string& name) : CEquipment(type, name) {};

void CSword::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	if (friendlyPlayer->mField.size() > 1)
	{
		// Find a target
		int r = CRandom::Random(friendlyPlayer->mField.size() - 2);

		// Increase the attack of the target
		friendlyPlayer->mField[r]->IncreaseAttack(mATTACK_INC);
	}
	else
	{
		// Heal the player
		friendlyPlayer->IncreaseHealth(mATTACK_INC);
	}

	// Remove the spell from the field
	friendlyPlayer->RemoveCardFromField(friendlyPlayer->mField.size() - 1);
}
