#include "pch.h"
#include "Game.h"

CGame::CGame()
{
	CRandom::SetSeed();
	std::cout << "Would you like to shuffle the decks? (Y/N)" << std::endl;
	std::string yn = "";
	std::cin >> yn;
	std::cout << "\n\n\n";
	players[0] = std::make_shared<CPlayer>("Sorceress", "sorceress.txt", yn);
	players[1] = std::make_shared<CPlayer>("Wizard", "wizard.txt", yn);
}

void CGame::Play()
{
	while (!gameOver && roundCount < 30)
	{
		roundCount == 0 ? WelcomeMessage() : Round();
	}
}

void CGame::Round()
{
	std::cout << std::endl << "============" << std::endl;
	std::cout << "ROUND " << roundCount << std::endl;
	std::cout << "============" << std::endl;
	for (int i = 0; i < 2; i++)
	{
		if (players[i]->GetHealthPoints() > 0)
		{
			Turn(i);
		}
		else
		{
			return;
		}
	}
	roundCount++;
}

void CGame::WelcomeMessage()
{
	std::cout << "FireBrick by SLDavenport\n\n";
	for (int i = 0; i < 2; i++)
	{
		players[i]->FDraw();
	}
	roundCount++;
}

void CGame::Turn(int i) 
{
	std::cout << std::endl;
	int enemy = i == 0 ? enemy = 1 : enemy = 0;
	int sa = 0;

	// Drawing Phase
	players[i]->Draw();

	// Playing Phase
	sa = players[i]->PlayCard();
	if (sa != 0)
	{
		DoSpecialAbility(sa, i, enemy);
	}
	if (players[enemy]->GetHealthPoints() <= 0) // game over
	{
		gameOver = true;
		return;
	}
	PrintCardsOnTable();

	// Attacking Phase
	MinionsActivate(i, enemy);
	if (players[enemy]->GetHealthPoints() <= 0) // game over
	{
		gameOver = true;
		return;
	}
}

void CGame::DoSpecialAbility(int sa, int i, int enemy) //////////// make another like this - refactor
{
	switch (sa)
	{
	case none:
		break;

	case fireball:
		CastFireball(i, enemy);
		break;

	case lightning:
		CastLightning(i, enemy);
		break;

	case bless:
		CastBless(i, enemy);
		break;
		
	case horde:
		CastHorde(i); 
		break;

	case sword:
		CastSword(i);
		break;

	case armour:
		CastArmour(i);
		break;

	default:
		break;
	}
}

void CGame::PrintCardsOnTable()    
{
	Deck scards = players[0]->GetField();
	Deck wcards = players[1]->GetField();

	std::cout << "--------------" << std::endl;
	std::cout << "CARDS ON TABLE" << std::endl;
	std::cout << "Sorceress : ";
	for (size_t i = 0; i < scards.size(); i++)
	{
		std::cout << scards[i]->GetName() << " (" << scards[i]->GetHealth() << ")  ";
	}
	std::cout << std::endl;

	std::cout << "Wizard : ";
	for (size_t i = 0; i < wcards.size(); i++)
	{
		std::cout << wcards[i]->GetName() << " (" << wcards[i]->GetHealth() << ")  ";
	}
	std::cout << std::endl;
	std::cout << "--------------" << std::endl;
}

void CGame::MinionsActivate(int f, int enemy)
{
	Deck friendlyField = players[f]->GetField();
	Deck enemyField;
	std::string friendlyName = players[f]->GetName();
	std::string enemyName = players[enemy]->GetName();

	for (size_t i = 0; i < friendlyField.size(); i++)
	{
		int efsize = players[enemy]->GetField().size();
		int attackDammage = friendlyField[i]->GetAttack();
		std::string attackingMinionName = friendlyField[i]->GetName();
		Deck ef = players[enemy]->GetField();
		bool wallOnField = false;
		int wallIndex = -1;

		for (size_t i = 0; i < ef.size(); i++) // Check if wall is in play
		{
			if (ef[i]->GetType() == 6)
			{
				wallOnField = true;
				wallIndex = i;
			}
		}
		if (wallOnField) // Attack wall
		{
			players[enemy]->ReduceCardHealth(wallIndex, attackDammage);
			enemyField = players[enemy]->GetField();
			std::string minionUnderAttack = enemyField[wallIndex]->GetName();

			if (enemyField[wallIndex]->GetHealth() <= 0)
			{
				players[enemy]->DeleteFromField(wallIndex);
				std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " has been killed." << std::endl;
			}
			else
			{
				std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " health now : " << enemyField[wallIndex]->GetHealth() << std::endl;
			}
		}
		else if (efsize <= 0) // Attack Player
		{
			players[enemy]->ReducePlayerHealth(attackDammage);
			if (players[enemy]->GetHealthPoints() <= 0)
			{
				
				std::cout << attackingMinionName << " attacks " << enemyName << "... ";
				std::cout << enemyName << " has been killed." << std::endl << std::endl; 
				std::cout << friendlyName << ", you win!" << std::endl; // end game
				return;
			}
			else
			{
				std::cout << attackingMinionName << " attacks " << enemyName << "... ";
				std::cout << enemyName << " health now : " << players[enemy]->GetHealthPoints() << std::endl;
			}
		}
		else // Attack a Minion
		{
			Deck enemyField = players[enemy]->GetField();
			Deck friendlyField = players[f]->GetField();
			int r = CRandom::Random(efsize-1);
			int minionUnderAttackHealth = enemyField[r]->GetHealth();
			players[enemy]->ReduceCardHealth(r, attackDammage);
			enemyField = players[enemy]->GetField();
			std::string minionUnderAttack = enemyField[r]->GetName();

			if (enemyField[r]->GetHealth() <= 0)
			{
				players[enemy]->DeleteFromField(r);
				std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " has been killed." << std::endl;
				attackDammage -= minionUnderAttackHealth;
				if (attackDammage > 0 && friendlyField[i]->GetType() == 8)
				{
					CastTrample(i, f, enemy, attackDammage);
				}
			}
			else
			{
				std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " health now : " << enemyField[r]->GetHealth() << std::endl;
			}
		}
		if (friendlyField[i]->GetType() == 5) // After attacking, heal if card type 5 (vampire)
		{
			players[f]->IncreaseCardHealth(i, 1);
			std::cout << attackingMinionName << " heals... ";
			std::cout << attackingMinionName << " health now : " << friendlyField[i]->GetHealth() << std::endl;
		}
		if (friendlyField[i]->GetType() == 9) // After attacking, heal player if type 9
		{
			players[f]->IncreasePlayerHealth(2);
			std::cout << attackingMinionName << " heals " << players[f]->GetName() << "... ";
			std::cout << players[f]->GetName() << " health now : " << players[f]->GetHealthPoints() << std::endl;
		}
	}
}

void CGame::CastFireball(int i, int enemy)
{
	int n = players[enemy]->GetField().size();
	int r = CRandom::Random(n);
	std::string enemyName = players[enemy]->GetName();
	Deck ef = players[enemy]->GetField();
	bool wallOnField = false;
	int wallIndex = -1;

	for (size_t i = 0; i < ef.size(); i++) // Check if wall is in play
	{
		if (ef[i]->GetType() == 6)
		{
			wallOnField = true;
			wallIndex = i;
		}
	}
	if (wallOnField) // Attack wall
	{
		players[enemy]->ReduceCardHealth(wallIndex, 3);
		Deck enemyField = players[enemy]->GetField();
		std::string minionUnderAttack = enemyField[wallIndex]->GetName();

		if (enemyField[wallIndex]->GetHealth() <= 0)
		{
			players[enemy]->DeleteFromField(wallIndex);
			std::cout << "Fireball strikes " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " has been killed." << std::endl;
		}
		else
		{
			std::cout << "Fireball strikes " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " health now : " << enemyField[wallIndex]->GetHealth() << std::endl;
		}
	}
	else if (r == n) // Attack player
	{
		players[enemy]->ReducePlayerHealth(3);
		
		if (players[enemy]->GetHealthPoints() <= 0) // Kills Player
		{
			std::cout << "Fireball strikes " << enemyName << "... ";
			std::cout << enemyName << " has been killed." << std::endl << std::endl;
			std::cout << players[i]->GetName() << ", you win!" << std::endl; // end game
			return;
		}
		else // Dammages Player
		{
			std::cout << "Fireball strikes " << enemyName << "... ";
			std::cout << enemyName << " health now : " << players[enemy]->GetHealthPoints() << std::endl;
		}
	}
	else // Attack minion
	{
		players[enemy]->ReduceCardHealth(r, 3);
		Deck enemyField = players[enemy]->GetField();
		std::string minionUnderAttack = enemyField[r]->GetName();

		if (enemyField[r]->GetHealth() <= 0)
		{
			players[enemy]->DeleteFromField(r);
			std::cout << "Fireball strikes " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " has been killed." << std::endl;
		}
		else
		{
			std::cout << "Fireball strikes " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " health now : " << enemyField[r]->GetHealth() << std::endl;
		}
	}
	players[i]->DeleteFromField(players[i]->GetField().size()-1);
}

void CGame::CastLightning(int f, int enemy)
{
	for (size_t i = 0; i < players[enemy]->GetField().size(); i++)
	{
		players[enemy]->ReduceCardHealth(i, 1);
		Deck enemyField = players[enemy]->GetField();
		std::string enemyMinion = enemyField[i]->GetName();

		if (enemyField[i]->GetHealth() <= 0) // Kills Minion
		{
			players[enemy]->DeleteFromField(i);
			std::cout << "Lightning strikes " << enemyMinion << "... ";
			std::cout << enemyMinion << " has been killed." << std::endl;
		}
		else // Dammages Minion
		{
			std::cout << "Lightning strikes " << enemyMinion << "... ";
			std::cout << enemyMinion << " health now : " << enemyField[i]->GetHealth() << std::endl;
		}
	}

	players[enemy]->ReducePlayerHealth(1);
	std::string enemyName = players[enemy]->GetName();

	if (players[enemy]->GetHealthPoints() <= 0) // Kills Player
	{
		std::cout << "Lightning strikes " << enemyName << "... ";
		std::cout << enemyName << " has been killed." << std::endl << std::endl;
		std::cout << players[f]->GetName() << ", you win!" << std::endl; // end game
	}
	else // Dammages Player
	{
		std::cout << "Lightning strikes " << enemyName << "... ";
		std::cout << enemyName << " health now : " << players[enemy]->GetHealthPoints() << std::endl;
	}
	players[f]->DeleteFromField(players[f]->GetField().size() - 1);
}

void CGame::CastBless(int f, int enemy)
{

	players[f]->DeleteFromField(players[f]->GetField().size() - 1);
	int who = std::rand() % 1 + 1;
	std::string enemyName = players[enemy]->GetName();

	if (who == 0) // Enemy
	{
		int n = players[enemy]->GetField().size();
		int r = CRandom::Random(n);

		if (r == n) // Attack enemy player
		{
			players[enemy]->ReducePlayerHealth(2);

			if (players[enemy]->GetHealthPoints() <= 0) // Kills Player
			{
				std::cout << "Bless strikes " << enemyName << "... ";
				std::cout << enemyName << " has been killed." << std::endl << std::endl;
				std::cout << players[f]->GetName() << ", you win!" << std::endl; // end game
			}
			else // Dammages Player
			{
				std::cout << "Bless strikes " << enemyName << "... ";
				std::cout << enemyName << " health now : " << players[enemy]->GetHealthPoints() << std::endl;
			}
		}
		else // Attack enemy minion
		{
			players[enemy]->ReduceCardHealth(r, 2);
			Deck enemyField = players[enemy]->GetField();
			std::string minionUnderAttack = enemyField[r]->GetName();

			if (enemyField[r]->GetHealth() <= 0) // Kills minion
			{
				players[enemy]->DeleteFromField(r);
				std::cout << "Bless strikes " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " has been killed." << std::endl;
			}
			else // Dammage minion
			{
				std::cout << "Bless strikes " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " health now : " << enemyField[r]->GetHealth() << std::endl;
			}
		}
	}
	else if (who == 1) // Friendly 
	{
		int n = players[f]->GetField().size();
		int r = CRandom::Random(n);
		std::string friendlyName = players[f]->GetName();

		if (r == n) // Heal Player
		{
			players[f]->IncreasePlayerHealth(2);
			std::cout << "Bless heals " << friendlyName << "... ";
			std::cout << friendlyName << " health now : " << players[f]->GetHealthPoints() << std::endl;
		}
		else // Heal Minion
		{
			players[f]->IncreaseCardHealth(r, 2);
			Deck friendlyMinions = players[f]->GetField();
			std::string minionHealed = friendlyMinions[r]->GetName();

			std::cout << "Bless heals " << minionHealed << "... ";
			std::cout << minionHealed << " health now : " << friendlyMinions[r]->GetHealth() << std::endl;
		}
	}
}

void CGame::CastHorde(int f)
{
	Deck friendlyField = players[f]->GetField();
	int ratCount = 0;

	for (size_t i = 0; i < friendlyField.size(); i++)
	{
		if (friendlyField[i]->GetType() == 7)
		{
			ratCount++;
		}
	}
	for (size_t i = 0; i < friendlyField.size(); i++)
	{
		if (friendlyField[i]->GetType() == 7 && ratCount > 1)
		{
			players[f]->IncreaseCardAttack(i, 1);
			std::cout << friendlyField[i]->GetName() << " increases it's attack by one" << std::endl;
			friendlyField = players[f]->GetField();
		}
	}
}

void CGame::CastTrample(int i, int f, int enemy, int attackDammage)
{
	Deck friendlyField = players[f]->GetField();
	std::string attackingMinionName = friendlyField[i]->GetName();
	int efsize = players[enemy]->GetField().size() - 1;
	int r = CRandom::Random(efsize);
	Deck enemyField = players[enemy]->GetField();
	std::string enemyName = players[enemy]->GetName();
	std::string friendlyName = players[f]->GetName();

	if (efsize <= 0) /// game over condtion needed
	{
		players[enemy]->ReducePlayerHealth(attackDammage);
		if (players[enemy]->GetHealthPoints() <= 0)
		{

			std::cout << attackingMinionName << " attacks " << enemyName << "... ";
			std::cout << enemyName << " has been killed." << std::endl << std::endl;
			std::cout << friendlyName << ", you win!" << std::endl; // end game
			return;
		}
		else
		{
			std::cout << attackingMinionName << " attacks " << enemyName << "... ";
			std::cout << enemyName << " health now : " << players[enemy]->GetHealthPoints() << std::endl;
		}
	}
	else
	{
		std::string minionUnderAttack = enemyField[r]->GetName();
		int minionUnderAttackHealth = enemyField[r]->GetHealth();
		players[enemy]->ReduceCardHealth(r, attackDammage);
		attackDammage -= minionUnderAttackHealth;
		if (enemyField[r]->GetHealth() <= 0)
		{
			players[enemy]->DeleteFromField(r);
			std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " has been killed." << std::endl;
			if (attackDammage > 0)
			{
				CastTrample(i, f, enemy, attackDammage);
			}
		}
		else
		{
			std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " health now : " << enemyField[r]->GetHealth() << std::endl;
		}
	}
}

void CGame::CastSword(int f)
{
	players[f]->DeleteFromField(players[f]->GetField().size() - 1);
	int n = players[f]->GetField().size() - 1;
	int r = CRandom::Random(n);
	int fieldSize = players[f]->GetField().size();
	Deck friendlyField = players[f]->GetField();

	if (fieldSize > 0)
	{
		players[f]->IncreaseCardAttack(r, 2);
		std::cout << "Sword increases " << friendlyField[r]->GetName() << "'s attack by by 2" << std::endl;
	}
	else 
	{
		players[f]->IncreasePlayerHealth(2);
		std::cout << "Sword heals " << players[f]->GetName() << " by 2" << std::endl;
	}
}

void CGame::CastArmour(int f)
{
	players[f]->DeleteFromField(players[f]->GetField().size() - 1);
	int n = players[f]->GetField().size() - 1;
	int r = CRandom::Random(n);
	int fieldSize = players[f]->GetField().size();
	Deck friendlyField = players[f]->GetField();

	if (fieldSize > 0)
	{
		players[f]->IncreaseCardProtection(r, 2);
		std::cout << "Armour increases " << friendlyField[r]->GetName() << "'s protection by 2" << std::endl;
	}
	else
	{
		players[f]->IncreasePlayerHealth(2);
		std::cout << "Armour heals " << players[f]->GetName() << " by 2" << std::endl;
	}
}

CGame::CGame(bool test)
{
	//players[0] = std::make_shared<CPlayer>("Sorceress");
	//players[1] = std::make_shared<CPlayer>("Wizard");

	//// Set deck
	//for (size_t i = 0; i < 20; i++)
	//{
	//	players[0]->deck.push_back(std::make_shared<CEquipment>("Sword"));
	//}
	//for (size_t i = 0; i < 20; i++)
	//{
	//	players[1]->deck.push_back(std::make_shared<CEquipment>("Armour"));
	//}

	//// Set hand
	//players[0]->hand.push_back(std::make_shared<CEquipment>("Sword"));
	//players[1]->hand.push_back(std::make_shared<CEquipment>("Armour"));

	//// Set field
	//for (size_t i = 0; i < 1; i++)
	//{
	//	players[0]->field.push_back(std::make_shared<CBasicMinion>("Orc"));
	//}
	////for (size_t i = 0; i < 3; i++)
	//{
	//	//players[1]->field.push_back(std::make_shared<CBasicMinion>("Orc"));
	//}
}

// Check protection works
// trample
// bless