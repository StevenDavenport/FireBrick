#include "pch.h"
#include "Fireball.h"
#include "Player.h"

//Type redefinition
typedef std::vector<std::unique_ptr<CCard>> Deck;

CFireball::CFireball(const int& type, const std::string& name, const int& attack)
	: CSpell(type, name, attack) {}

void CFireball::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	// Generate random number within the enemy field size
	int r = CRandom::Random(enemyPlayer->mField.size() - 1);

	// Flag
	bool wallOnField = false;

	// Index of a card
	int wallIndex = -1;

	// Check if wall is in play
	for (size_t i = 0; i < enemyPlayer->mField.size(); i++)
	{
		if (enemyPlayer->GetName() == "Wall")
		{
			wallOnField = true;
			wallIndex = i;
		}
	}
	// Attack wall
	if (wallOnField)
	{
		// Reduce Card health
		enemyPlayer->mField[wallIndex]->ReduceHealth(GetAttack());

		// Output to console
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->mField[wallIndex]->GetName(),
			enemyPlayer->mField[wallIndex]->GetHealth());

		// Lethal dammage taken
		if (enemyPlayer->mField[wallIndex]->GetHealth() <= 0)
		{
			enemyPlayer->RemoveCardFromField(wallIndex);
		}
	}
	else if (r == enemyPlayer->mField.size()) // Attack player
	{
		// Reduce enemy player health
		enemyPlayer->ReduceHealth(GetAttack());

		// Output to console
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->GetName(), enemyPlayer->GetHealthPoints());
	}
	// Attack minion
	else
	{
		// Card takes dammage
		enemyPlayer->mField[r]->ReduceHealth(GetAttack());
		
		// Output to console
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->mField[r]->GetName(),
			enemyPlayer->mField[r]->GetHealth());

		// If the minion is killed
		if (enemyPlayer->mField[r]->GetHealth() <= 0)
		{
			enemyPlayer->RemoveCardFromField(r);
		}
	}
}

