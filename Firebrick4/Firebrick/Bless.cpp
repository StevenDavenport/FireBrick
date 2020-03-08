#include "pch.h"
#include "Bless.h"
#include "Player.h"

CBless::CBless(const int& type, const std::string& name, const int& attack)
	: CSpell(type, name, attack) {}

void CBless::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	// Generate a random number
	int r = CRandom::Random(enemyPlayer->mField.size() + friendlyPlayer->mField.size() + 1);

	// Attack enemy minion
	if (r < enemyPlayer->mField.size())
	{
		// Dammage the minion
		enemyPlayer->mField[r]->ReduceHealth(this->GetAttack());

		// Console output
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->mField[r]->GetName(),
			enemyPlayer->mField[r]->GetHealth());

		// the minion under attack is killed
		if (enemyPlayer->mField[r]->GetHealth() <= 0)
		{
			enemyPlayer->RemoveCardFromField(r);
		}
	}
	// Attack enemy player
	else if (r == enemyPlayer->mField.size())
	{
		// Reduce the enemy mPlayers health
		enemyPlayer->ReduceHealth(GetAttack());
		
		// Console output
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->GetName(), enemyPlayer->GetHealthPoints());
	}
	// Heal friendly minion
	else if (r < enemyPlayer->mField.size() + friendlyPlayer->mField.size() + 1)
	{
		// Increase the health of a friendly minion
		friendlyPlayer->mField[r - enemyPlayer->mField.size()]->IncreaseHealth(mHEALS);
	}
	// Heal friendly player
	else
	{
		//Increase the friendly mPlayers health
		friendlyPlayer->IncreaseHealth(mHEALS);
	}
}

