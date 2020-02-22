#include "pch.h"
#include "Game.h"

CGame::CGame()																	// Consructor for Game class
{																				
	CRandom::SetSeed();															// Sets the seed for random
	std::cout << "Would you like to shuffle the decks? (Y/N)" << std::endl;		// Asking the user to shuffle or not
	std::string yn = "";														// Stores the users response 
	std::cin >> yn;																// User inputs responce 
	std::cout << "\n\n\n";														// Line spacing 
	players[0] = std::make_shared<CPlayer>("Sorceress", "sorceress.txt", yn);	// Instantiate Sorc player
	players[1] = std::make_shared<CPlayer>("Wizard", "wizard.txt", yn);			// Instantiate Wizard player
}

void CGame::Play()																// Play runs the game, only public function in CGame class
{																				
	while (!gameOver && roundCount < 30)										// Game loop with play conditions 
	{																			
		roundCount == 0 ? WelcomeMessage() : Round();							// Calls each round
	}																			
}

void CGame::Round()																// Handles each round 
{																				
	std::cout << std::endl << "============" << std::endl;						
	std::cout << "ROUND " << roundCount << std::endl;							// Round statment  
	std::cout << "============" << std::endl;									
	for (friendlyIndex = 0; friendlyIndex < 2; friendlyIndex++)					// Loops through each player
	{																			
		if (!gameOver)															// Game over checker
		{																		
			Turn();																// Start friendly turn
		}																		
		else																	
		{																		
			return;																// Game Over
		}																		
	}																			
	roundCount++;																// Increase round count
}

void CGame::WelcomeMessage()													// Handles the first round
{																				
	std::cout << "FireBrick by SLDavenport\n\n";								// Publishing message
	for (int i = 0; i < 2; i++)													// Loop through each player
	{																			
		players[i]->FDraw();													// Each player draws a card
	}																			
	roundCount++;																// Increase round count
}

void CGame::Turn() 																// Handles each turn
{
	std::cout << std::endl;														// Output Spacing 
	enemyIndex = friendlyIndex == 0 ? enemyIndex = 1 : enemyIndex = 0;			// Finding the index of enemy 
	players[friendlyIndex]->Draw();												// Drawing a card
	cardSpecialAbility = players[friendlyIndex]->PlayCard();					// Playing a card
	CastOnPlaySpecialAbility();													// Cast special ability
	if (OverChecker() == true)													// Game over checker
	{
		return;																	// Stop the game
	}
	PrintCardsOnTable();														// Print table to screen
	MinionsActivate();									// Attacking Phase
	if (OverChecker() == true)													// Game over checker
	{														
		return;																	// Stop the game
	}
}

bool CGame::OverChecker()														// Game over checker function
{
	if (players[enemyIndex]->GetHealthPoints() <= 0)							// Game over condition
	{
		gameOver = true;
		return true;															// Return true
	}
}

void CGame::CastOnPlaySpecialAbility() 											// Cast Special Ability 
{																				
	switch (cardSpecialAbility)													// Check which ability to cast
	{																			// Then cast the appropriate spell
	case none:																	
		break;																	
																				
	case fireball:																
		CastFireball();								
		break;																	
																				
	case lightning:																
		CastLightning();								
		break;																	
																				
	case bless:																	
		CastBless();									
		break;																	
																				
	case horde:																	
		CastHorde();												
		break;																	
																				
	case sword:																	
		CastSword();												
		break;																	
																				
	case armour:																
		CastArmour();												
		break;																	
																				
	default:																	
		break;																	
	}																			
}

void CGame::PrintCardsOnTable()    												// Prints each players cards
{																				// On field to console
	Deck scards = players[0]->GetField();										// Sorcerers field
	Deck wcards = players[1]->GetField();										// Wizards field
	std::cout << "--------------" << std::endl;									// Output messages
	std::cout << "CARDS ON TABLE" << std::endl;									
	std::cout << "Sorceress : ";												
	for (size_t i = 0; i < scards.size(); i++)									// Printing field
	{
		std::cout << scards[i]->GetName() << " (" << scards[i]->GetHealth() << ")  ";
	}
	std::cout << std::endl;
	std::cout << "Wizard : ";													// Printing field
	for (size_t i = 0; i < wcards.size(); i++)
	{
		std::cout << wcards[i]->GetName() << " (" << wcards[i]->GetHealth() << ")  ";
	}
	std::cout << std::endl;
	std::cout << "--------------" << std::endl;
}

void CGame::MinionsActivate()
{
	// Table in play
	friendlyField = players[friendlyIndex]->GetField();

	// Size of table in play
	friendlyFieldSize = friendlyField.size();

	// Player names
	friendlyPlayerName = players[friendlyIndex]->GetName();
	enemyPlayerName = players[enemyIndex]->GetName();

	// Loop through the friendly field 
	for (size_t i = 0; i < friendlyFieldSize; i++)
	{
		// Table
		enemyField = players[enemyIndex]->GetField();
		enemyFieldSize = enemyField.size();

		// Attack dammage of attacking card
		attackDammage = friendlyField[i]->GetAttack();

		// Name of the attacking minion
		attackingMinionName = friendlyField[i]->GetName();

		// flag
		bool wallOnField = false;

		// Index of wall card
		int wallIndex = -1;

		// Check if wall is in play
		for (size_t i = 0; i < enemyFieldSize; i++) 
		{
			if (enemyField[i]->GetSpecialAbility() == wall) 
			{
				wallOnField = true;
				wallIndex = i;
			}
		}
		// Attack wall
		if (wallOnField) 
		{
			// Wall takes dammage
			players[enemyIndex]->ReduceCardHealth(wallIndex, attackDammage);

			// Refresh 
			enemyField = players[enemyIndex]->GetField();
			minionUnderAttack = enemyField[wallIndex]->GetName();

			// If minion dies
			if (enemyField[wallIndex]->GetHealth() <= 0)
			{
				// Delete from play
				players[enemyIndex]->DeleteFromField(wallIndex);
				std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " has been killed." << std::endl;
			}
			// Take dammage
			else
			{
				std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " health now : " << enemyField[wallIndex]->GetHealth() << std::endl;
			}
		}
		// Attack Player
		else if (enemyFieldSize <= 0) 
		{
			// Player takes dammage
			players[enemyIndex]->ReducePlayerHealth(attackDammage);

			// Player dies
			if (players[enemyIndex]->GetHealthPoints() <= 0)
			{
				
				std::cout << attackingMinionName << " attacks " << enemyPlayerName << "... ";
				std::cout << enemyPlayerName << " has been killed." << std::endl << std::endl; 
				std::cout << friendlyPlayerName << ", you win!" << std::endl; // end game
				return;
			}
			else
			{
				std::cout << attackingMinionName << " attacks " << enemyPlayerName << "... ";
				std::cout << enemyPlayerName << " health now : " << players[enemyIndex]->GetHealthPoints() << std::endl;
			}
		}
		else // Attack a Minion
		{
			//  Pick a random card
			r = CRandom::Random(enemyFieldSize - 1);

			// Card health
			minionUnderAttackHealth = enemyField[r]->GetHealth();

			// Reduce that cards health
			players[enemyIndex]->ReduceCardHealth(r, attackDammage);

			// Dammaged minions name
			minionUnderAttack = enemyField[r]->GetName();

			// Refresh
			enemyField = players[enemyIndex]->GetField();

			// Minion dies
			if (enemyField[r]->GetHealth() <= 0)
			{
				// Delete from play
				players[enemyIndex]->DeleteFromField(r);
				std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " has been killed." << std::endl;
				attackDammage -= minionUnderAttackHealth;
				// Check for trample 
				if (attackDammage > 0 && friendlyField[i]->GetSpecialAbility() == trample) 
				{
					CastTrample(i);
				}
			}
			// Minion takes dammage
			else 
			{
				std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " health now : " << enemyField[r]->GetHealth() << std::endl;
			}
		}
		// If card is a vampire heal it
		if (friendlyField[i]->GetSpecialAbility() == vampire) 
		{
			players[friendlyIndex]->IncreaseCardHealth(i, 1);
			std::cout << attackingMinionName << " heals... ";
			std::cout << attackingMinionName << " health now : " << friendlyField[i]->GetHealth() << std::endl;
		}
		// If card is a leech heal player
		if (friendlyField[i]->GetSpecialAbility() == leech) 
		{
			players[friendlyIndex]->IncreasePlayerHealth(2);
			std::cout << attackingMinionName << " heals " << players[friendlyIndex]->GetName() << "... ";
			std::cout << players[friendlyIndex]->GetName() << " health now : " << players[friendlyIndex]->GetHealthPoints() << std::endl;
		}
	}
}

void CGame::CastFireball()
{
	// Delete this card from the field because it is a spell
	players[friendlyIndex]->DeleteFromField(players[friendlyIndex]->GetField().size() - 1);

	// Enemy field
	enemyField = players[enemyIndex]->GetField();

	// Size of the enemy field
	enemyFieldSize = enemyField.size();

	// Generate random number within the enemy field size
	int r = CRandom::Random(enemyFieldSize);

	// Name of enemy player
	enemyPlayerName = players[enemyIndex]->GetName();

	// Flag
	bool wallOnField = false;

	// Index of a card
	int wallIndex = -1;

	// Check if wall is in play
	for (size_t i = 0; i < enemyFieldSize; i++) 
	{
		if (enemyField[i]->GetSpecialAbility() == wall)
		{
			wallOnField = true;
			wallIndex = i;
		}
	}
	// Attack wall
	if (wallOnField) 
	{
		// Reduce Card health
		players[enemyIndex]->ReduceCardHealth(wallIndex, 3);

		// Card under attack name
		minionUnderAttack = enemyField[wallIndex]->GetName();

		// Enemy Card has been killed
		if (enemyField[wallIndex]->GetHealth() <= 0)
		{
			players[enemyIndex]->DeleteFromField(wallIndex);
			std::cout << "Fireball strikes " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " has been killed." << std::endl;
		}
		// Enemy Card has been dammaged
		else
		{
			std::cout << "Fireball strikes " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " health now : " << enemyField[wallIndex]->GetHealth() << std::endl;
		}
	}
	else if (r == enemyFieldSize) // Attack player
	{
		// Reduce enemy player health
		players[enemyIndex]->ReducePlayerHealth(3);
		
		// If player is killed
		if (players[enemyIndex]->GetHealthPoints() <= 0) 
		{
			std::cout << "Fireball strikes " << enemyPlayerName << "... ";
			std::cout << enemyPlayerName << " has been killed." << std::endl << std::endl;
			std::cout << players[friendlyIndex]->GetName() << ", you win!" << std::endl; // end game
			return;
		}
		// Dammages Player
		else 
		{
			std::cout << "Fireball strikes " << enemyPlayerName << "... ";
			std::cout << enemyPlayerName << " health now : " << players[enemyIndex]->GetHealthPoints() << std::endl;
		}
	}
	// Attack minion
	else 
	{
		// Card takes dammage
		players[enemyIndex]->ReduceCardHealth(r, 3);

		// Name of minion to be attacked
		minionUnderAttack = enemyField[r]->GetName();

		// If the minion is killed
		if (enemyField[r]->GetHealth() <= 0)
		{
			// Delete that minion from the dield
			players[enemyIndex]->DeleteFromField(r);
			std::cout << "Fireball strikes " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " has been killed." << std::endl;
		}
		// Minion is dammaged
		else
		{
			std::cout << "Fireball strikes " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " health now : " << enemyField[r]->GetHealth() << std::endl;
		}
	}
}

void CGame::CastLightning()
{
	// Delete the spell from the field
	players[friendlyIndex]->DeleteFromField(players[friendlyIndex]->GetField().size() - 1);

	// Loop throuhg the enemy field
	for (size_t i = 0; i < players[enemyIndex]->GetField().size(); i++)
	{
		// Card takes dammage
		players[enemyIndex]->ReduceCardHealth(i, 1);

		// Enemy field
		enemyField = players[enemyIndex]->GetField();

		// Name of enemy minion
		std::string enemyMinion = enemyField[i]->GetName();

		// Minion has been killed
		if (enemyField[i]->GetHealth() <= 0) 
		{
			// Delete from field
			players[enemyIndex]->DeleteFromField(i);
			std::cout << "Lightning strikes " << enemyMinion << "... ";
			std::cout << enemyMinion << " has been killed." << std::endl;
		}
		// Damages minion
		else 
		{
			std::cout << "Lightning strikes " << enemyMinion << "... ";
			std::cout << enemyMinion << " health now : " << enemyField[i]->GetHealth() << std::endl;
		}
	}
	// enemy player takes dammage
	players[enemyIndex]->ReducePlayerHealth(1);

	// Name of the enemy player
	std::string enemyName = players[enemyIndex]->GetName();

	// Player has been killed
	if (players[enemyIndex]->GetHealthPoints() <= 0) 
	{
		std::cout << "Lightning strikes " << enemyName << "... ";
		std::cout << enemyName << " has been killed." << std::endl << std::endl;
		std::cout << players[friendlyIndex]->GetName() << ", you win!" << std::endl; // end game
	}
	// Dammages Player
	else 
	{
		std::cout << "Lightning strikes " << enemyName << "... ";
		std::cout << enemyName << " health now : " << players[enemyIndex]->GetHealthPoints() << std::endl;
	}
}

void CGame::CastBless()
{
	// Delete the card from the field because it's a spell card
	players[friendlyIndex]->DeleteFromField(players[friendlyIndex]->GetField().size() - 1);

	// Generate a random number between 0 and 1
	int who = CRandom::Random(1);

	// Refresh what is the enemy players name
	enemyPlayerName = players[enemyIndex]->GetName();

	// Attack the Enemy
	if (who == 0) 
	{
		// Refresh enemy field size
		enemyFieldSize = players[enemyIndex]->GetField().size();
		int r = CRandom::Random(enemyFieldSize);

		// Attack the enemy player
		if (r == enemyFieldSize) 
		{
			// Reduce the enemy players health 
			players[enemyIndex]->ReducePlayerHealth(2);

			// If the player has been killed
			if (players[enemyIndex]->GetHealthPoints() <= 0) 
			{
				std::cout << "Bless strikes " << enemyPlayerName << "... ";
				std::cout << enemyPlayerName << " has been killed." << std::endl << std::endl;
				std::cout << players[friendlyIndex]->GetName() << ", you win!" << std::endl; // end game
			}
			else // Dammages Player
			{
				std::cout << "Bless strikes " << enemyPlayerName << "... ";
				std::cout << enemyPlayerName << " health now : " << players[enemyIndex]->GetHealthPoints() << std::endl;
			}
		}
		// Attack enemy minion
		else 
		{
			// Reduce the health of the minion being attacked
			players[enemyIndex]->ReduceCardHealth(r, 2);

			// Refresh the enemy field
			enemyField = players[enemyIndex]->GetField();

			// Refresh minion under attack
			minionUnderAttack = enemyField[r]->GetName();

			// the minion under attack is killed
			if (enemyField[r]->GetHealth() <= 0) 
			{
				// Delete that minion from the field
				players[enemyIndex]->DeleteFromField(r);
				std::cout << "Bless strikes " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " has been killed." << std::endl;
			}
			// The minion recievs dammage
			else 
			{
				std::cout << "Bless strikes " << minionUnderAttack << "... ";
				std::cout << minionUnderAttack << " health now : " << enemyField[r]->GetHealth() << std::endl;
			}
		}
	}
	// The friendly player will be healed
	else if (who == 1) 
	{
		// Refresh the friendly field
		friendlyField = players[friendlyIndex]->GetField();

		// Refresh the size of the friendly field
		friendlyFieldSize = friendlyField.size();

		// Pick a random number within the size of the friendly field
		r = CRandom::Random(friendlyFieldSize);

		// Refresh the name of the friendly player
		friendlyPlayerName = players[friendlyIndex]->GetName();

		// Heal the friendly player
		if (r == friendlyFieldSize) 
		{
			// Increase the friendly players health
			players[friendlyIndex]->IncreasePlayerHealth(2);
			std::cout << "Bless heals " << friendlyPlayerName << "... ";
			std::cout << friendlyPlayerName << " health now : " << players[friendlyIndex]->GetHealthPoints() << std::endl;
		}
		// Heals a friendly minion
		else 
		{
			// Increase the health of a friendly minion
			players[friendlyIndex]->IncreaseCardHealth(r, 2);
			
			// Name of the minion being healed 
			std::string minionHealed = friendlyField[r]->GetName();

			std::cout << "Bless heals " << minionHealed << "... ";
			std::cout << minionHealed << " health now : " << friendlyField[r]->GetHealth() << std::endl;
		}
	}
}

void CGame::CastHorde()
{
	// Refresh the friendly field
	friendlyField = players[friendlyIndex]->GetField();

	// Refresh the size of the friendly field
	friendlyFieldSize = friendlyField.size();

	// Sores the number of rats on the field
	int hordeCount = 0;

	// Loop through and check the field for cards with horde special ability
	for (size_t i = 0; i < friendlyFieldSize; i++)
	{
		if (friendlyField[i]->GetSpecialAbility() == horde)
		{
			hordeCount++;
		}
	}
	// Loop through and increase the attack of any cards with horde, when is more than one on the field
	for (size_t i = 0; i < friendlyFieldSize; i++)
	{
		if (friendlyField[i]->GetSpecialAbility() == horde && hordeCount > 1)
		{
			players[friendlyIndex]->IncreaseCardAttack(i, 1);
			std::cout << friendlyField[i]->GetName() << " increases it's attack by one" << std::endl;
		}
	}
}

void CGame::CastTrample(int i)
{
	// Refresh what is on the friendly field
	friendlyField = players[friendlyIndex]->GetField();

	// The name of the attacking minion
	attackingMinionName = friendlyField[i]->GetName();

	// Refresh what is on the enemy field
	enemyField = players[enemyIndex]->GetField();

	// Refresh the size of the enemy field
	enemyFieldSize = enemyField.size();

	// Generate a random number between 0 and the size of the enemy field
	r = CRandom::Random(enemyFieldSize - 1);

	// Refresh who is the enemy player
	enemyPlayerName = players[enemyIndex]->GetName();

	// Refresh who is the friendly player
	friendlyPlayerName = players[friendlyIndex]->GetName();

	// If the enemy has no cards on the field, attack the player
	if (enemyFieldSize <= 0) 
	{
		// Reducing the enemy players health
		players[enemyIndex]->ReducePlayerHealth(attackDammage);

		// If the enemy is dead, end the game
		if (players[enemyIndex]->GetHealthPoints() <= 0)
		{

			std::cout << attackingMinionName << " attacks " << enemyPlayerName << "... ";
			std::cout << enemyPlayerName << " has been killed." << std::endl << std::endl;
			std::cout << friendlyPlayerName << ", you win!" << std::endl; // end game
			return;
		}
		else
		{
			std::cout << attackingMinionName << " attacks " << enemyPlayerName << "... ";
			std::cout << enemyPlayerName << " health now : " << players[enemyIndex]->GetHealthPoints() << std::endl;
		}
	}
	// If the enemy has cards on the field, attack them
	else
	{
		// Refresh the minion under attack
		minionUnderAttack = enemyField[r]->GetName();

		// Refresh the health of that minion
		minionUnderAttackHealth = enemyField[r]->GetHealth();

		// Dammage that minion 
		players[enemyIndex]->ReduceCardHealth(r, attackDammage);

		// Recalculate attack dammage
		attackDammage -= minionUnderAttackHealth;

		//  If the minion dies 
		if (enemyField[r]->GetHealth() <= 0)
		{
			// Delete the minion from the field
			players[enemyIndex]->DeleteFromField(r);
			std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " has been killed." << std::endl;

			// Look to attack again
			if (attackDammage > 0)
			{
				CastTrample(i);
			}
		}
		// If the minion doesnt die
		else
		{
			std::cout << attackingMinionName << " attacks " << minionUnderAttack << "... ";
			std::cout << minionUnderAttack << " health now : " << enemyField[r]->GetHealth() << std::endl;
		}
	}
}

void CGame::CastSword()
{
	// Delete Armour from field as soon as it's played
	players[friendlyIndex]->DeleteFromField(players[friendlyIndex]->GetField().size() - 1);

	// Refresh who is in the friendly field
	friendlyField = players[friendlyIndex]->GetField();

	// Refresh the friendly field size
	friendlyFieldSize = players[friendlyIndex]->GetField().size();

	// Generate a random number between 0 and friendly Field Size
	int r = CRandom::Random(friendlyFieldSize - 1);

	// If there are cards on the friendly field, increase their atack and output it
	if (friendlyFieldSize > 0)
	{
		players[friendlyIndex]->IncreaseCardAttack(r, 2);
		std::cout << "Sword increases " << friendlyField[r]->GetName() << "'s attack by by 2" << std::endl;
	}
	// If there are no cards on the friendly field, increase the players health and output it
	else 
	{
		players[friendlyIndex]->IncreasePlayerHealth(2);
		std::cout << "Sword heals " << players[friendlyIndex]->GetName() << " by 2" << std::endl;
	}
}

void CGame::CastArmour()
{
	// Delete Armour from field as soon as it's played
	players[friendlyIndex]->DeleteFromField(players[friendlyIndex]->GetField().size() - 1);

	// Refresh which cards are on the frieldly field 
	friendlyField = players[friendlyIndex]->GetField();

	// find how many cards are on the friendly field
	friendlyFieldSize = players[friendlyIndex]->GetField().size();

	// Generate a random number between 0 and n
	r = CRandom::Random(friendlyFieldSize - 1);

	// If there are cards on the friendly field, increase their protection and output it
	if (friendlyFieldSize > 0)
	{
		players[friendlyIndex]->IncreaseCardProtection(r, 2);
		std::cout << "Armour increases " << friendlyField[r]->GetName() << "'s protection by 2" << std::endl;
	}
	// If there are no cards on the friendly field, increase the players health and output it
	else
	{
		players[friendlyIndex]->IncreasePlayerHealth(2);
		std::cout << "Armour heals " << players[friendlyIndex]->GetName() << " by 2" << std::endl;
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