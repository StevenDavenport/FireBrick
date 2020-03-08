#include "pch.h"
#include "Minion.h"
#include "Player.h"
 
//Type redefinition
typedef std::vector<std::unique_ptr<CCard>> Deck;

CMinion::CMinion(const int& type, const std::string& name, const int& attack, const int& health)
	: CCard(type, name), mAttack(attack), mHealth(health) {}

int& CMinion::GetHealth()
{
	return mHealth;
}

void CMinion::ReduceHealth(const int& attackDammage)
{
	mHealth -= (attackDammage - this->GetProtection());
}

void CMinion::IncreaseHealth(const int& heal)
{
	mHealth += heal;
}

const bool& CMinion::IsSpell()
{
	return mSPELL;
}

int& CMinion::GetAttack()
{
	return mAttack;
}

void CMinion::IncreaseAttack(const int& x)
{
	mAttack += x;
}

void CMinion::SetAttack(const int& x)
{
	mAttack = x;
}

void CMinion::Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	// flag
	bool wallOnField = false;

	// Index of wall card
	int wallIndex = -1;

	// Minion being attacked
	std::string minionUnderAttack;

	// Check if wall is in play
	for (size_t i = 0; i < enemyPlayer->mField.size(); i++)
	{
		if (enemyPlayer->mField[i]->GetName() == "Wall")
		{
			wallOnField = true;
			wallIndex = i;
		}
	}
	// Attack wall
	if (wallOnField)
	{
		// Wall takes dammage
		enemyPlayer->mField[wallIndex]->ReduceHealth(GetAttack());

		// Output to console
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->mField[wallIndex]->GetName(),
			enemyPlayer->mField[wallIndex]->GetHealth());

		// Been killed
		if (enemyPlayer->mField[wallIndex]->GetHealth() <= 0)
		{
			enemyPlayer->RemoveCardFromField(wallIndex);
		}
	}
	// Attack Player
	else if (enemyPlayer->mField.size() <= 0)
	{
		// Player takes dammage
		enemyPlayer->ReduceHealth(GetAttack());

		// Output to console
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->GetName(), enemyPlayer->GetHealthPoints());
	}
	else // Attack a Minion
	{
		//  Pick a random card
		int r = CRandom::Random(enemyPlayer->mField.size() - 1);

		// Reduce that cards health
		enemyPlayer->mField[r]->ReduceHealth(this->GetAttack());

		// Console output
		CCard::ConsoleOutput(this->GetName(), enemyPlayer->mField[r]->GetName(), enemyPlayer->mField[r]->GetHealth());

		// Lethal dammage
		if (enemyPlayer->mField[r]->GetHealth() <= 0)
		{
			enemyPlayer->RemoveCardFromField(r);
		}
	}
}

