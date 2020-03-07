#pragma once
#include "Player.h"

// Type redefinitions
typedef std::vector<std::unique_ptr<CPlayer>> PlayerList;

class CGame
{
public:
	CGame();										// Constuctor
	void Play();									// Plays the game
	void RoundZero();								// Starting round
	void Round();									// Plays each round 
	void Turn();									// Plays each turn
	bool CheckGameOver();							// Check if games is over

private:
	int mRoundCount = 0;							// Number of rounds that have been played
	PlayerList mPlayers;							// Array of the player objects
	bool mGameOver = false;							// Game over flag
	int mFriendlyIndex = 0;							// Index of which mPlayers turn it is
	int mEnemyIndex = 1;							// Index of which mPlayers turn it is not
};

