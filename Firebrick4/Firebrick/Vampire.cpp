#include "pch.h"
#include "Vampire.h"
#include "Player.h"

CVampire::CVampire(const int& type, const std::string& name, const int& attack, const int& health)
	: CMinion(type, name, attack, health) {}

const bool& CVampire::IsSpell()
{
	return mSPELL;
}

void CVampire::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	CMinion::Activate(friendlyPlayer, enemyPlayer);
	this->IncreaseHealth(mHEAL);
}
