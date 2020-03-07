#include "pch.h"
#include "Trample.h"

CTrample::CTrample(const int& type, const std::string& name, const int& attack, const int& health)
	: CMinion(type, name, attack, health) {}

const bool& CTrample::IsSpell()
{
	return mSPELL;
}

void CTrample::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	bool trample = false;
	int newAttack = -1;

	// Keep attacking while got remaining attack
	while (trample == true)
	{
		// Generate a random target
		int r = CRandom::Random(enemyPlayer->mField.size() - 1);

		// If the enemy has no cards on the field, attack the player
		if (enemyPlayer->mField.size() <= 0)
		{
			// Reducing the enemy mPlayers health
			enemyPlayer->ReduceHealth(this->GetAttack());

			// Console Output
			CCard::ConsoleOutput(this->GetName(), enemyPlayer->GetName(), enemyPlayer->GetHealthPoints());

			// If the enemy is dead, end the game
			if (enemyPlayer->GetHealthPoints() <= 0)
			{
				return;
			}
		}
		// If the enemy has cards on the field, attack them
		else
		{
			// Recalculate attack dammage
			newAttack = this->GetAttack() - enemyPlayer->mField[r]->GetHealth();

			// Enemy take dammage
			enemyPlayer->mField[r]->ReduceHealth(this->GetAttack());

			// Console Output
			CCard::ConsoleOutput(this->GetName(), enemyPlayer->mField[r]->GetName(),
				enemyPlayer->mField[r]->GetHealth());

			//  If the minion dies 
			if (enemyPlayer->mField[r]->GetHealth() <= 0)
			{
				enemyPlayer->RemoveCardFromField(r);
				newAttack > 0 ? trample = true : trample = false;
			}
		}
		// Set new attack
		this->SetAttack(newAttack);
	}
	// Reset attack
	this->SetAttack(mDEFAULT_ATTACK);
}