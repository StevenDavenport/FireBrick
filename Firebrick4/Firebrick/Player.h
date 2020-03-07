#pragma once
#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include "Minion.h"
#include "Fireball.h"
#include "Lightning.h"
#include "Bless.h"
#include "Vampire.h"
#include "Wall.h"
#include "Horde.h"
#include "Trample.h"
#include "Leech.h"
#include "Sword.h"
#include "Armour.h"
#include "Random.h"

// Type redefinitions 
typedef std::vector<std::string> List;
typedef std::vector<std::unique_ptr<CCard>> Deck;

class CPlayer
{
public:
	CPlayer(const std::string& name, const std::string& filename, const std::string& shuffle); // Constuctor 
	void SetUpDeck();													  // Set up deck of objects
	void ReadInCards();													  // Reads in cards from file
	void ShuffleDeck();													  // Shuffles the deck
	int GetHealthPoints();												  // Getter
	void ReduceHealth(const int& attackDammage);					      // Setter
	void IncreaseHealth(const int& heal);								  // Setter
	std::string GetName();												  // Get the players name
	void FirstDraw();													  // First draw of the game
	void Draw();														  // Called to draw cards
	void PrintTable();													  // Prints table 
	void PlayCard(PlayerRef friendlyPlayer, PlayerRef enemyPlayer);		  // Plays a card to the table
	void Attack(PlayerRef friendlyPlayer,PlayerRef enemyPlayer);		  // Attacks enemy
	void RemoveCardFromField(const int& i);								  // Removes card from field when dead
	Deck mField;														  // Field of player

private:
	std::string mFilename;												  // Stores a filename
	Deck mUnshuffledDeck;												  // Deck before shuffle
	Deck mDeck;														      // Deck after shuffle
	List mCards;														  // Read into this list										  // Deck after shuffle
	Deck mHand;														      // Hand of player
	std::string mName;													  // Name of player
	int mHealthPoints = 30;												  // Health of player
};

