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
	std::cout << "\n";

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
		mRoundCount == 0 ? RoundZero() : Round();
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

// Handles the first round
void CGame::RoundZero()
{
	// Publishing message
	std::cout<< "SLDavenport FireBrick\n\n";

	// Loop through each player
	for (int i = 0; i < 2; i++)
	{
		// Each player draws a card
		mPlayers[i]->FirstDraw();
	}
	std::cout << std::endl;
	// Increase round count
	mRoundCount++;
}

// Handles each round 
void CGame::Round()
{
	// Round statment  
	std::cout << "Round " << mRoundCount << std::endl;

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

// Handles each turn
void CGame::Turn()
{
	// Finding the index of enemy
	mEnemyIndex = mFriendlyIndex == 0 ? mEnemyIndex = 1 : mEnemyIndex = 0;

	// Drawing a card
	mPlayers[mFriendlyIndex]->Draw();

	// Playing a card
	mPlayers[mFriendlyIndex]->PlayCard(mPlayers[mFriendlyIndex] ,mPlayers[mEnemyIndex]); 

	// Game over checker
	if (CheckGameOver() == true)
	{
		// Stop the game
		return;
	}

	// Print table to screen
	mPlayers[mFriendlyIndex]->PrintTable();

	// Attacking Phase
	mPlayers[mFriendlyIndex]->Attack(mPlayers[mFriendlyIndex], mPlayers[mEnemyIndex]);

	// Game over checker
	if (CheckGameOver() == true)
	{
		// Stop the game
		return;
	}
	std::cout << "\n";
}

// Game over checker function
bool CGame::CheckGameOver()
{
	// Game over condition
	if (mPlayers[mEnemyIndex]->GetHealthPoints() <= 0)
	{
		// Return true
		mGameOver = true;
		return true;
	}
	return false;
}
