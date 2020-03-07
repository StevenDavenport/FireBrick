#include "pch.h"
#include "Leech.h"
#include "Player.h"

CLeech::CLeech(const int& type, const std::string& name, const int& attack, const int& health)
	: CMinion(type, name, attack, health) {}

const bool& CLeech::IsSpell()
{
	return mSPELL;
}

void CLeech::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	// Call attack function 
	CMinion::Activate(friendlyPlayer, enemyPlayer);
	
	// Heal the friendly player
	friendlyPlayer->IncreaseHealth(mATTACK_INC);
}


