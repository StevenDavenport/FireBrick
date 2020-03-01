#pragma once
#include "Player.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// Type redefinitions 
typedef std::vector<std::shared_ptr<CPlayer>> pPlayerList;

class CGame											// Game class manages the game play itself
{													
public:												
	CGame();										// Constuctor
	void Play();									// Plays the game 
													
private:											
	void Round();									// Plays each round 
	void Turn();									// Plays each turn
	void WelcomeMessage();							// Welcome round
	void PrintCardsOnTable();						// Prints table to console
	//void MinionsActivate();							// Attack function
	bool OverChecker();								// Check if games is over
													
	void CastOnPlaySpecialAbility();				// Checks which special ability a card has 
	//void CastFireball();							// Cast Spell
	//void CastLightning();							// Cast Spell
	//void CastBless();								// Cast Spell
	//void CastSword();								// Cast Spell
	//void CastArmour();								// Cast Spell
													
	//void CastHorde();								// Cast Spell
	//void CastTrample(const int& i);					// Cast Spell
													 
													 
	int mRoundCount = 0;							// Number of rounds that have been played
	pPlayerList mPlayers;							// Array of the player objects
	bool mGameOver = false;							// Game over flag
	int mFriendlyIndex = 0;							// Index of which mPlayers turn it is
	int mEnemyIndex = 1;							// Index of which mPlayers turn it is not
	int mCardSpecialAbility = none;					// Stores a special ability
	//weakList mFriendlyField;						// Stores friendly field
	//weakList mEnemyField;							// Stores enemy field
	//weakCard mFriendlyCard;							// Stores a friendly card
	//weakCard mEnemyCard;							// Stores an ememy card
	int mFriendlyFieldSize = 0;						// Stores how many cards are on each field
	int mEnemyFieldSize = 0;						// Stores how many cards are on each field
	int mR = 0;										// Stores a random number 
	int mAttackDammage = 0;							// Stores attack dammage of a card
	std::string mAttackingMinionName = "";				// Stores a name of a card
	std::string mEnemyPlayerName = "";					// Stores the name of the enemy player
	std::string mFriendlyPlayerName = "";				// Stores the name of the friendly player
	std::string mMinionUnderAttack = "";					// Stores a name of a minion
	int mMinionUnderAttackHealth = 0;				// Stores the health of a minion
};
