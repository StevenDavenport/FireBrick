#pragma once
#include "Player.h"

class CGame
{
public:
	CGame();
	CGame(bool test);
	void Play();

private:
	void Round();
	void Turn();
	void WelcomeMessage();
	void PrintCardsOnTable();
	void MinionsActivate();
	bool OverChecker();

	void CastOnPlaySpecialAbility();
	void CastFireball();
	void CastLightning();
	void CastBless();
	void CastSword();
	void CastArmour();

	void CastHorde();
	void CastTrample(int i);


	int roundCount = 0;														// Number of rounds that have been played
	std::shared_ptr<CPlayer> players[2];									// Array of the player objects
	bool gameOver = false;													// Game over flag
	int friendlyIndex = 0;													// Index of which players turn it is
	int enemyIndex = 1;														// Index of which players turn it is not
	int cardSpecialAbility = none;											// Stores a special ability
	Deck friendlyField;														// Stores friendly field
	Deck enemyField;														// Stores enemy field
	int friendlyFieldSize = 0;												// Stores how many cards are on each field
	int enemyFieldSize = 0;													// Stores how many cards are on each field
	int r = 0;																// Stores a random number 
	int attackDammage = 0;													// Stores attack dammage of a card
	std::string attackingMinionName;										// Stores a name of a card
	std::string enemyPlayerName;											// Stores the name of the enemy player
	std::string friendlyPlayerName;											// Stores the name of the friendly player
	std::string minionUnderAttack;											// Stores a name of a minion
	int minionUnderAttackHealth = 0;										// Stores the health of a minion
};
