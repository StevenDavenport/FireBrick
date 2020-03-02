#include "pch.h"
#include "Game.h"

// Consructor for Game class
CGame::CGame()																	
{	
	// Sets the seed for random
	CRandom::SetSeed();	

	// Asking the user to shuffle or not
	std::cout << "Would you like to shuffle the Decks? (Y/N)" << std::endl;	

	// Stores the users response 
	std::string yn = "";	

	// User inputs responce 
	std::cin >> yn;		

	// Line spacing 
	std::cout << "\n\n\n";				

	// Instantiate Players
	mPlayers.push_back(std::make_unique<CPlayer>("Sorceress", "sorceress.txt", yn));
	mPlayers.push_back(std::make_unique<CPlayer>("Wizard", "wizard.txt", yn));
}

// Play runs the game, only public function in CGame class
void CGame::Play()																 
{	
	// Game loop with play conditions 
	while (!mGameOver && mRoundCount < 30)										
	{		
		// Calls each round
		mRoundCount == 0 ? WelcomeMessage() : Round();							
	}						

	// Whos the winner
	if (mRoundCount >= 30)
	{
		// Find the winners name
		std::string winner = mPlayers[0]->GetHealthPoints() > mPlayers[1]->GetHealthPoints() 
			? mPlayers[0]->GetName() : mPlayers[1]->GetName();

		// Print winning message to console 
		std::cout << std::endl << winner << ", you have won!\n";
	}
}

// Handles each round 
void CGame::Round()																
{					
	// Round statment  
	std::cout << std::endl << "============" << std::endl;						
	std::cout << "ROUND " << mRoundCount << std::endl;							
	std::cout << "============" << std::endl;			

	// Loops through each player
	for (mFriendlyIndex = 0; mFriendlyIndex < 2; mFriendlyIndex++)					
	{							
		// Game over checker
		if (!mGameOver)															
		{		
			// Start friendly turn
			Turn();																
		}																		
		else																	
		{		
			// Game Over
			return;																
		}																		
	}			
	// Increase round count
	mRoundCount++;																
}

// Handles the first round
void CGame::WelcomeMessage()													
{		
	// Publishing message
	std::cout << "FireBrick by SLDavenport\n\n";					

	// Loop through each player
	for (int i = 0; i < 2; i++)													
	{					
		// Each player draws a card
		mPlayers[i]->FDraw();													
	}			
	// Increase round count
	mRoundCount++;																
}

// Handles each turn
void CGame::Turn() 																
{
	// Output Spacing
	std::cout << std::endl;				

	// Finding the index of enemy
	mEnemyIndex = mFriendlyIndex == 0 ? mEnemyIndex = 1 : mEnemyIndex = 0;	

	// Drawing a card
	mPlayers[mFriendlyIndex]->Draw();	

	// Playing a card
	mCardSpecialAbility = mPlayers[mFriendlyIndex]->PlayCard();		

	// Cast special ability
	CastOnPlaySpecialAbility();		

	// Game over checker
	if (OverChecker() == true)													
	{
		// Stop the game
		return;																	
	}
	// Print table to screen
	PrintCardsOnTable();		

	// Attacking Phase
	MinionsActivate();				

	// Game over checker
	if (OverChecker() == true)													
	{			
		// Stop the game
		return;																	
	}
}

// Game over checker function
bool CGame::OverChecker()														
{
	// Game over condition
	if (mPlayers[mEnemyIndex]->GetHealthPoints() <= 0)							
	{
		// Return true
		mGameOver = true;
		return true;															
	}
}

// Cast Special Ability 
void CGame::CastOnPlaySpecialAbility() 											
{				
	// Check which ability to cast
	// Then cast the appropriate spell
	switch (mCardSpecialAbility)													
	{																				
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

// Prints table
void CGame::PrintCardsOnTable()    												
{							
	// Prints both players fields to console window
	std::cout << "--------------" << std::endl;									
	std::cout << "CARDS ON TABLE" << std::endl;	
	
	// Get both fields
	mFriendlyField = mPlayers[0]->GetField();
	mEnemyField = mPlayers[1]->GetField();

	// Printing field
	std::cout << "Sorceress : ";
	for (size_t i = 0; i < mFriendlyField.size(); i++)
	{
		std::cout << mFriendlyField[i].name << " (" << mFriendlyField[i].health << ")  ";
	}
	std::cout << std::endl;

	// Printing field
	std::cout << "Wizard : ";		
	for (size_t i = 0; i < mEnemyField.size(); i++)
	{
		std::cout << mEnemyField[i].name << " (" << mEnemyField[i].health << ")  ";
	}
	std::cout << std::endl;
	std::cout << "--------------" << std::endl;
}

void CGame::MinionsActivate()
{
	// Table in play
	mFriendlyField = mPlayers[mFriendlyIndex]->GetField();

	// Size of table in play
	mFriendlyFieldSize = mPlayers[mFriendlyIndex]->GetFieldSize();

	// Player names
	mFriendlyPlayerName = mPlayers[mFriendlyIndex]->GetName();
	mEnemyPlayerName = mPlayers[mEnemyIndex]->GetName();

	// Loop through the friendly field 
	for (size_t i = 0; i < mFriendlyFieldSize; i++)
	{
		// Table
		mEnemyField = mPlayers[mEnemyIndex]->GetField();
		mEnemyFieldSize = mPlayers[mEnemyIndex]->GetFieldSize();

		// Attack dammage of attacking card
		mAttackDammage = mFriendlyField[i].attack;

		// Name of the attacking minion
		mAttackingMinionName = mFriendlyField[i].name;

		// flag
		bool wallOnField = false;

		// Index of wall card
		int wallIndex = -1;

		// Check if wall is in play
		for (size_t i = 0; i < mEnemyFieldSize; i++) 
		{
			if (mEnemyField[i].specialAbility == wall) 
			{
				wallOnField = true;
				wallIndex = i;
			}
		}
		// Attack wall
		if (wallOnField) 
		{
			// Wall takes dammage
			mPlayers[mEnemyIndex]->ReduceCardHealth(wallIndex, mAttackDammage);

			// Refresh 
			mEnemyField = mPlayers[mEnemyIndex]->GetField();
			mMinionUnderAttack = mEnemyField[wallIndex].name;

			// If minion dies
			if (mEnemyField[wallIndex].health <= 0)
			{
				// Delete from play
				std::cout << mAttackingMinionName << " attacks " << mMinionUnderAttack << "... ";
				std::cout << mMinionUnderAttack << " has been killed." << std::endl;
				mPlayers[mEnemyIndex]->DeleteFromField(wallIndex);
			}
			// Take dammage
			else
			{
				std::cout << mAttackingMinionName << " attacks " << mMinionUnderAttack << "... ";
				std::cout << mMinionUnderAttack << " health now : " << mEnemyField[wallIndex].health << std::endl;
			}
		}
		// Attack Player
		else if (mEnemyFieldSize <= 0) 
		{
			// Player takes dammage
			mPlayers[mEnemyIndex]->ReducePlayerHealth(mAttackDammage);

			// Player dies
			if (mPlayers[mEnemyIndex]->GetHealthPoints() <= 0)
			{
				
				std::cout << mAttackingMinionName << " attacks " << mEnemyPlayerName << "... ";
				std::cout << mEnemyPlayerName << " has been killed." << std::endl << std::endl; 
				std::cout << mFriendlyPlayerName << ", you win!" << std::endl; // end game
				return;
			}
			else
			{
				std::cout << mAttackingMinionName << " attacks " << mEnemyPlayerName << "... ";
				std::cout << mEnemyPlayerName << " health now : " << mPlayers[mEnemyIndex]->GetHealthPoints() << std::endl;
			}
		}
		else // Attack a Minion
		{
			//  Pick a random card
			mR = CRandom::Random(mEnemyFieldSize - 1);

			// Card health
			mMinionUnderAttackHealth = mEnemyField[mR].health;

			// Reduce that cards health
			mPlayers[mEnemyIndex]->ReduceCardHealth(mR, mAttackDammage);

			// Dammaged minions name
			mMinionUnderAttack = mEnemyField[mR].name;

			// Refresh
			mEnemyField = mPlayers[mEnemyIndex]->GetField();

			// Minion dies
			if (mEnemyField[mR].health <= 0)
			{
				// Delete from play
				std::cout << mAttackingMinionName << " attacks " << mMinionUnderAttack << "... ";
				std::cout << mMinionUnderAttack << " has been killed." << std::endl;
				mPlayers[mEnemyIndex]->DeleteFromField(mR);
				mAttackDammage -= mMinionUnderAttackHealth;
				// Check for trample 
				if (mAttackDammage > 0 && mFriendlyField[i].specialAbility == trample) 
				{
					CastTrample(i);
				}
			}
			// Minion takes dammage
			else 
			{
				std::cout << mAttackingMinionName << " attacks " << mMinionUnderAttack << "... ";
				std::cout << mMinionUnderAttack << " health now : " << mEnemyField[mR].health << std::endl;
			}
		}
		// If card is a vampire heal it
		if (mFriendlyField[i].specialAbility == vampire) 
		{
			mPlayers[mFriendlyIndex]->IncreaseCardHealth(i, 1);
			std::cout << mAttackingMinionName << " heals... ";
			std::cout << mAttackingMinionName << " health now : " << mFriendlyField[i].health << std::endl;
		}
		// If card is a leech heal player
		if (mFriendlyField[i].specialAbility == leech) 
		{
			mPlayers[mFriendlyIndex]->IncreasePlayerHealth(2);
			std::cout << mAttackingMinionName << " heals " << mPlayers[mFriendlyIndex]->GetName() << "... ";
			std::cout << mPlayers[mFriendlyIndex]->GetName() << " health now : " << mPlayers[mFriendlyIndex]->GetHealthPoints() << std::endl;
		}
	}
}

void CGame::CastFireball()
{
	// Delete this card from the field because it is a spell
	mPlayers[mFriendlyIndex]->DeleteFromField(mPlayers[mFriendlyIndex]->GetField().size() - 1);

	// Enemy field
	mEnemyField = mPlayers[mEnemyIndex]->GetField();

	// Size of the enemy field
	mEnemyFieldSize = mEnemyField.size();

	// Generate random number within the enemy field size
	mR= CRandom::Random(mEnemyFieldSize);

	// Name of enemy player
	mEnemyPlayerName = mPlayers[mEnemyIndex]->GetName();

	// Flag
	bool wallOnField = false;

	// Index of a card
	int wallIndex = -1;

	// Check if wall is in play
	for (size_t i = 0; i < mEnemyFieldSize; i++) 
	{
		if (mEnemyField[i].specialAbility == wall)
		{
			wallOnField = true;
			wallIndex = i;
		}
	}
	// Attack wall
	if (wallOnField) 
	{
		// Reduce Card health
		mPlayers[mEnemyIndex]->ReduceCardHealth(wallIndex, 3);

		// Card under attack name
		mMinionUnderAttack = mEnemyField[wallIndex].name;

		// Enemy Card has been killed
		if (mEnemyField[wallIndex].health <= 0)
		{
			std::cout << "Fireball strikes " << mMinionUnderAttack << "... ";
			std::cout << mMinionUnderAttack << " has been killed." << std::endl;
			mPlayers[mEnemyIndex]->DeleteFromField(wallIndex);
		}
		// Enemy Card has been dammaged
		else
		{
			std::cout << "Fireball strikes " << mMinionUnderAttack << "... ";
			std::cout << mMinionUnderAttack << " health now : " << mEnemyField[wallIndex].health << std::endl;
		}
	}
	else if (mR == mEnemyFieldSize) // Attack player
	{
		// Reduce enemy player health
		mPlayers[mEnemyIndex]->ReducePlayerHealth(3);
		
		// If player is killed
		if (mPlayers[mEnemyIndex]->GetHealthPoints() <= 0) 
		{
			std::cout << "Fireball strikes " << mEnemyPlayerName << "... ";
			std::cout << mEnemyPlayerName << " has been killed." << std::endl << std::endl;
			std::cout << mPlayers[mFriendlyIndex]->GetName() << ", you win!" << std::endl; // end game
			return;
		}
		// Dammages Player
		else 
		{
			std::cout << "Fireball strikes " << mEnemyPlayerName << "... ";
			std::cout << mEnemyPlayerName << " health now : " << mPlayers[mEnemyIndex]->GetHealthPoints() << std::endl;
		}
	}
	// Attack minion
	else 
	{
		// Card takes dammage
		mPlayers[mEnemyIndex]->ReduceCardHealth(mR, 3);

		// Name of minion to be attacked
		mMinionUnderAttack = mEnemyField[mR].name;

		// If the minion is killed
		if (mEnemyField[mR].health <= 0)
		{
			// Delete that minion from the dield
			std::cout << "Fireball strikes " << mMinionUnderAttack << "... ";
			std::cout << mMinionUnderAttack << " has been killed." << std::endl;
			mPlayers[mEnemyIndex]->DeleteFromField(mR);
		}
		// Minion is dammaged
		else
		{
			std::cout << "Fireball strikes " << mMinionUnderAttack << "... ";
			std::cout << mMinionUnderAttack << " health now : " << mEnemyField[mR].health << std::endl;
		}
	}
}

void CGame::CastLightning()
{
	// Delete the spell from the field
	mPlayers[mFriendlyIndex]->DeleteFromField(mPlayers[mFriendlyIndex]->GetField().size() - 1);

	// Loop throuhg the enemy field
	for (size_t i = 0; i < mPlayers[mEnemyIndex]->GetField().size(); i++)
	{
		// Card takes dammage
		mPlayers[mEnemyIndex]->ReduceCardHealth(i, 1);

		// Enemy field
		mEnemyField = mPlayers[mEnemyIndex]->GetField();

		// Name of enemy minion
		std::string enemyMinion = mEnemyField[i].name;

		// Minion has been killed
		if (mEnemyField[i].health <= 0) 
		{
			// Output to console
			std::cout << "Lightning strikes " << enemyMinion << "... ";
			std::cout << enemyMinion << " has been killed." << std::endl;

			// Delete from field
			mPlayers[mEnemyIndex]->DeleteFromField(i);

			// Change the index because array size has changed
			i -= 1;
		}
		// Damages minion
		else 
		{
			// Output to console
			std::cout << "Lightning strikes " << enemyMinion << "... ";
			std::cout << enemyMinion << " health now : " << mEnemyField[i].health << std::endl;
		}
	}
	// enemy player takes dammage
	mPlayers[mEnemyIndex]->ReducePlayerHealth(1);

	// Name of the enemy player
	std::string enemyName = mPlayers[mEnemyIndex]->GetName();

	// Player has been killed
	if (mPlayers[mEnemyIndex]->GetHealthPoints() <= 0) 
	{
		std::cout << "Lightning strikes " << enemyName << "... ";
		std::cout << enemyName << " has been killed." << std::endl << std::endl;
		std::cout << mPlayers[mFriendlyIndex]->GetName() << ", you win!" << std::endl; // end game
	}
	// Dammages Player
	else 
	{
		std::cout << "Lightning strikes " << enemyName << "... ";
		std::cout << enemyName << " health now : " << mPlayers[mEnemyIndex]->GetHealthPoints() << std::endl;
	}
}

void CGame::CastBless()
{
	// Delete the card from the field because it's a spell card
	mPlayers[mFriendlyIndex]->DeleteFromField(mPlayers[mFriendlyIndex]->GetField().size() - 1);

	// Generate a random number between 0 and 1
	int who = CRandom::Random(1);

	// Refresh what is the enemy mPlayers name
	mEnemyPlayerName = mPlayers[mEnemyIndex]->GetName();

	// Attack the Enemy
	if (who == 0) 
	{
		// Refresh enemy field size
		mEnemyFieldSize = mPlayers[mEnemyIndex]->GetField().size();
		mR= CRandom::Random(mEnemyFieldSize);

		// Attack the enemy player
		if (mR == mEnemyFieldSize)
		{
			// Reduce the enemy mPlayers health 
			mPlayers[mEnemyIndex]->ReducePlayerHealth(2);

			// If the player has been killed
			if (mPlayers[mEnemyIndex]->GetHealthPoints() <= 0) 
			{
				std::cout << "Bless strikes " << mEnemyPlayerName << "... ";
				std::cout << mEnemyPlayerName << " has been killed." << std::endl << std::endl;
				std::cout << mPlayers[mFriendlyIndex]->GetName() << ", you win!" << std::endl; // end game
			}
			else // Dammages Player
			{
				std::cout << "Bless strikes " << mEnemyPlayerName << "... ";
				std::cout << mEnemyPlayerName << " health now : " << mPlayers[mEnemyIndex]->GetHealthPoints() << std::endl;
			}
		}
		// Attack enemy minion
		else 
		{
			// Reduce the health of the minion being attacked
			mPlayers[mEnemyIndex]->ReduceCardHealth(mR, 2);

			// Refresh the enemy field
			mEnemyField = mPlayers[mEnemyIndex]->GetField();

			// Refresh minion under attack
			mMinionUnderAttack = mEnemyField[mR].name;

			// the minion under attack is killed
			if (mEnemyField[mR].health <= 0)
			{
				// Delete that minion from the field
				mPlayers[mEnemyIndex]->DeleteFromField(mR);
				std::cout << "Bless strikes " << mMinionUnderAttack << "... ";
				std::cout << mMinionUnderAttack << " has been killed." << std::endl;
			}
			// The minion recievs dammage
			else 
			{
				std::cout << "Bless strikes " << mMinionUnderAttack << "... ";
				std::cout << mMinionUnderAttack << " health now : " << mEnemyField[mR].health << std::endl;
			}
		}
	}
	// The friendly player will be healed
	else if (who == 1) 
	{
		// Refresh the friendly field
		mFriendlyField = mPlayers[mFriendlyIndex]->GetField();

		// Refresh the size of the friendly field
		mFriendlyFieldSize = mFriendlyField.size();

		// Pick a random number within the size of the friendly field
		mR = CRandom::Random(mFriendlyFieldSize);

		// Refresh the name of the friendly player
		mFriendlyPlayerName = mPlayers[mFriendlyIndex]->GetName();

		// Heal the friendly player
		if (mR == mFriendlyFieldSize)
		{
			// Increase the friendly mPlayers health
			mPlayers[mFriendlyIndex]->IncreasePlayerHealth(2);
			std::cout << "Bless heals " << mFriendlyPlayerName << "... ";
			std::cout << mFriendlyPlayerName << " health now : " << mPlayers[mFriendlyIndex]->GetHealthPoints() << std::endl;
		}
		// Heals a friendly minion
		else 
		{
			// Increase the health of a friendly minion
			mPlayers[mFriendlyIndex]->IncreaseCardHealth(mR, 2);
			
			// Name of the minion being healed 
			std::string minionHealed = mFriendlyField[mR].name;

			std::cout << "Bless heals " << minionHealed << "... ";
			std::cout << minionHealed << " health now : " << mFriendlyField[mR].health << std::endl;
		}
	}
}

void CGame::CastHorde()
{
	// Refresh the friendly field
	mFriendlyField = mPlayers[mFriendlyIndex]->GetField();

	// Refresh the size of the friendly field
	mFriendlyFieldSize = mFriendlyField.size();

	// Sores the number of rats on the field
	int hordeCount = 0;

	// Loop through and check the field for cards with horde special ability
	for (size_t i = 0; i < mFriendlyFieldSize; i++)
	{
		if (mFriendlyField[i].specialAbility == horde)
		{
			hordeCount++;
		}
	}
	// Loop through and increase the attack of any cards with horde, when is more than one on the field
	for (size_t i = 0; i < mFriendlyFieldSize; i++)
	{
		if (mFriendlyField[i].specialAbility == horde && hordeCount > 1)
		{
			mPlayers[mFriendlyIndex]->IncreaseCardAttack(i, 1);
			std::cout << mFriendlyField[i].name << " increases it's attack by one" << std::endl;
		}
	}
}

void CGame::CastTrample(const int& i)
{
	// Refresh what is on the friendly field
	mFriendlyField = mPlayers[mFriendlyIndex]->GetField();

	// The name of the attacking minion
	mAttackingMinionName = mFriendlyField[i].name;

	// Refresh what is on the enemy field
	mEnemyField = mPlayers[mEnemyIndex]->GetField();

	// Refresh the size of the enemy field
	mEnemyFieldSize = mEnemyField.size();

	// Generate a random number between 0 and the size of the enemy field
	mR = CRandom::Random(mEnemyFieldSize - 1);

	// Refresh who is the enemy player
	mEnemyPlayerName = mPlayers[mEnemyIndex]->GetName();

	// Refresh who is the friendly player
	mFriendlyPlayerName = mPlayers[mFriendlyIndex]->GetName();

	// If the enemy has no cards on the field, attack the player
	if (mEnemyFieldSize <= 0) 
	{
		// Reducing the enemy mPlayers health
		mPlayers[mEnemyIndex]->ReducePlayerHealth(mAttackDammage);

		// If the enemy is dead, end the game
		if (mPlayers[mEnemyIndex]->GetHealthPoints() <= 0)
		{

			std::cout << mAttackingMinionName << " attacks " << mEnemyPlayerName << "... ";
			std::cout << mEnemyPlayerName << " has been killed." << std::endl << std::endl;
			std::cout << mFriendlyPlayerName << ", you win!" << std::endl; // end game
			return;
		}
		else
		{
			std::cout << mAttackingMinionName << " attacks " << mEnemyPlayerName << "... ";
			std::cout << mEnemyPlayerName << " health now : " << mPlayers[mEnemyIndex]->GetHealthPoints() << std::endl;
		}
	}
	// If the enemy has cards on the field, attack them
	else
	{
		// Refresh the minion under attack
		mMinionUnderAttack = mEnemyField[mR].name;

		// Refresh the health of that minion
		mMinionUnderAttackHealth = mEnemyField[mR].health;

		// Dammage that minion 
		mPlayers[mEnemyIndex]->ReduceCardHealth(mR, mAttackDammage);

		// Recalculate attack dammage
		mAttackDammage -= mMinionUnderAttackHealth;

		//  If the minion dies 
		if (mEnemyField[mR].health <= 0)
		{
			// Delete the minion from the field
			std::cout << mAttackingMinionName << " attacks " << mMinionUnderAttack << "... ";
			std::cout << mMinionUnderAttack << " has been killed." << std::endl;
			mPlayers[mEnemyIndex]->DeleteFromField(mR);

			// Look to attack again
			if (mAttackDammage > 0)
			{
				CastTrample(i);
			}
		}
		// If the minion doesnt die
		else
		{
			std::cout << mAttackingMinionName << " attacks " << mMinionUnderAttack << "... ";
			std::cout << mMinionUnderAttack << " health now : " << mEnemyField[mR].health << std::endl;
		}
	}
}

void CGame::CastSword()
{
	// Delete Armour from field as soon as it's played
	mPlayers[mFriendlyIndex]->DeleteFromField(mPlayers[mFriendlyIndex]->GetField().size() - 1);

	// Refresh who is in the friendly field
	mFriendlyField = mPlayers[mFriendlyIndex]->GetField();

	// Refresh the friendly field size
	mFriendlyFieldSize = mPlayers[mFriendlyIndex]->GetField().size();

	// Generate a random number between 0 and friendly Field Size
	mR= CRandom::Random(mFriendlyFieldSize - 1);

	// If there are cards on the friendly field, increase their atack and output it
	if (mFriendlyFieldSize > 0)
	{
		mPlayers[mFriendlyIndex]->IncreaseCardAttack(mR, 2);
		std::cout << "Sword increases " << mFriendlyField[mR].name << "'s attack by by 2" << std::endl;
	}
	// If there are no cards on the friendly field, increase the mPlayers health and output it
	else 
	{
		mPlayers[mFriendlyIndex]->IncreasePlayerHealth(2);
		std::cout << "Sword heals " << mPlayers[mFriendlyIndex]->GetName() << " by 2" << std::endl;
	}
}

void CGame::CastArmour()
{
	// Delete Armour from field as soon as it's played
	mPlayers[mFriendlyIndex]->DeleteFromField(mPlayers[mFriendlyIndex]->GetField().size() - 1);

	// Refresh which cards are on the frieldly field 
	mFriendlyField = mPlayers[mFriendlyIndex]->GetField();

	// find how many cards are on the friendly field
	mFriendlyFieldSize = mPlayers[mFriendlyIndex]->GetField().size();

	// Generate a random number between 0 and n
	mR = CRandom::Random(mFriendlyFieldSize - 1);

	// If there are cards on the friendly field, increase their protection and output it
	if (mFriendlyFieldSize > 0)
	{
		mPlayers[mFriendlyIndex]->IncreaseCardProtection(mR, 2);
		std::cout << "Armour increases " << mFriendlyField[mR].name << "'s protection by 2" << std::endl;
	}
	// If there are no cards on the friendly field, increase the mPlayers health and output it
	else
	{
		mPlayers[mFriendlyIndex]->IncreasePlayerHealth(2);
		std::cout << "Armour heals " << mPlayers[mFriendlyIndex]->GetName() << " by 2" << std::endl;
	}
}