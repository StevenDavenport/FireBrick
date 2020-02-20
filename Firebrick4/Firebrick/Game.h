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
	void Turn(int i);
	void WelcomeMessage();
	void DoSpecialAbility(int sa, int i, int enemy);
	void PrintCardsOnTable();
	void MinionsActivate(int f, int enemy);
	void CastFireball(int i, int enemy);
	void CastLightning(int f, int enemy);
	void CastBless(int f, int enemy);
	void CastHorde(int f);
	void CastTrample(int i, int f, int enemy, int attackDammage);
	void CastSword(int f);
	void CastArmour(int i);

	int roundCount = 0;
	std::shared_ptr<CPlayer> players[2];
	bool gameOver = false;
};
