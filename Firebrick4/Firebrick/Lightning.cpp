#include "pch.h"
#include "Lightning.h"
#include "Player.h"

CLightning::CLightning(const int& type, const std::string& name, const int& attack)
	: CSpell(type, name, attack) {}

void CLightning::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	// Loop throuhg the enemy field
	for (size_t i = 0; i < enemyPlayer->mField.size(); i++)
	{
		// Card takes dammage
		enemyPlayer->mField[i]->ReduceHealth(GetAttack());

		// Output to console
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->mField[i]->GetName(),
			enemyPlayer->mField[i]->GetHealth());

		// Minion has been killed
		if (enemyPlayer->mField[i]->GetHealth() <= 0)
		{
			// Delete from field
			enemyPlayer->RemoveCardFromField(i);

			// Change the index because array size has changed
			i -= 1;
		}
	}
	// enemy player takes dammage
	enemyPlayer->ReduceHealth(GetAttack());

	// Output to console
	CCard::ConsoleOutput(this->GetName(), enemyPlayer->GetName(), enemyPlayer->GetHealthPoints());

	// Delete the spell from the field
	friendlyPlayer->RemoveCardFromField(friendlyPlayer->mField.size() - 1);
}

