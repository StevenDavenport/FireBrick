#include "pch.h"
#include "Horde.h"
#include "Player.h"

CHorde::CHorde(const int& type, const std::string& name, const int& attack, const int& health)
	: CMinion(type, name, attack, health) {}

const bool& CHorde::IsSpell()
{
	return mSPELL;
}

void CHorde::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	//Loop through the friendly field checking for horde cards
	int hordeCount = 0;
	const int defaultAttack = this->GetAttack();
	for (size_t i = 0; i < friendlyPlayer->mField.size(); i++)
	{
		if (friendlyPlayer->mField[i]->GetType() == 7)
		{
			hordeCount++;
		}
	}
	// Increase the horde card attack
	this->IncreaseAttack((hordeCount - 1) * mATTACK_INCREMENT);

	// Call acttack function
	CMinion::Activate(friendlyPlayer, enemyPlayer);

	// Reset attack 
	this->SetAttack(defaultAttack);
}
