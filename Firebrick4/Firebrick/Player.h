#pragma once
#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Spell.h"
#include "Minion.h"
#include "SpecialMinion.h"
#include "Equipment.h"
#include "Random.h"

typedef std::vector<std::shared_ptr<CCard>> Deck;

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

private:
	//friend class CGame;
	Deck unshuffledDeck;
	Deck deck;
	Deck hand;
	Deck field;
	std::string cards[100];
	std::string name;
	int healthPoints = 30;
};
