#pragma once
#include "pch.h"
#include "vector"
#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include "BasicMinion.h"
#include "Fireball.h"
#include "Lightning.h"
#include "Bless.h"
#include "Vampire.h"
#include "Wall.h"
#include "Horde.h"
#include "Trample.h"
#include "Leech.h"
#include "Equipment.h"
#include "Random.h"
#include "shorthand.h"

class CPlayer
{
public:
	CPlayer(std::string name, std::string filename, std::string shuffle);
	CPlayer(std::string name);
	int GetHealthPoints();
	std::string GetName();
	Deck GetDeck();
	void FDraw();
	void Draw();
	int PlayCard();
	Deck GetField();
	std::vector<std::string> GetHand();
	void ReducePlayerHealth(int x);
	void ReduceCardHealth(int i, int x);
	void IncreasePlayerHealth(int x);
	void IncreaseCardHealth(int i, int x);
	void IncreaseCardAttack(int i, int x);
	void IncreaseCardProtection(int i, int x);
	void DeleteFromField(int i);
	void SetUpDeck(std::string filename);
	void ReadInCards(std::string (&cards)[100], std::string filename);
	void ShuffleDeck();
	int Random(const float n);

private:
	friend class CGame;
	Deck unshuffledDeck;
	Deck deck;
	Deck hand;
	Deck field;
	std::string cards[100];
	std::string name;
	int healthPoints = 30;
	
	/*	std::string basicMinionNames[10] = { "Orc", "Goblin", "Pooka", "Thorns",
		"Giant", "Dwarf","Cannon", "Swordswinger", "Spearcarrier", "Elf" };
	int basicMinionAttack[10] = { 2, 2, 2, 1, 4, 2, 4, 2, 2, 1 };
	int basicMinionHealth[10] = { 2, 1, 4, 4, 4, 4, 1, 2, 1, 4 }; TAKEN FROM MINION*/
};
