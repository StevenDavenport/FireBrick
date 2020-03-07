//#pragma once
//#include "pch.h"
//#include <fstream>
//#include <iostream>
//#include <string>
//#include "Spell.h"
//#include "Minion.h"
//#include "SpecialMinion.h"
//#include "Equipment.h"
//#include "Random.h"
//#include "MockCard.h"
//
//// Type redefinitions 
//typedef std::vector<std::string> List;
//typedef std::vector<MockCard> MockDeck;
//typedef std::vector<std::unique_ptr<CCard>> Deck;
//
//class OldPlayer															 // Used per player
//{
//public:
//	OldPlayer(const std::string& name, const std::string& filename, const std::string& shuffle); // Constuctor 
//	int GetHealthPoints();												  // Getter
//	std::string GetName();												  // Getter
//	void FDraw();														  // First draw of the game
//	void Draw();														  // Called to draw cards
//	int PlayCard();														  // Plays a card to the table
//	MockDeck GetField();												  // Getter
//	int GetFieldSize();													  // Getter
//	void ReducePlayerHealth(const int& x);								  // Setter
//	void ReduceCardHealth(const int& i, const int& x);					  // Setter
//	void IncreasePlayerHealth(const int& x);							  // Setter
//	void IncreaseCardHealth(const int& i, const int& x);				  // Setter
//	void IncreaseCardAttack(const int& i, const int& x);				  // Setter
//	void IncreaseCardProtection(const int& i, const int& x);			  // Setter
//	void DeleteFromField(const int& i);									  // Setter
//	void SetUpDeck();													  // Set up deck of objects
//	void ReadInCards();													  // Reads in cards from file
//	void ShuffleDeck();													  // Shuffles the deck
//																		   
//private:																   
//	std::string mFilename;												  // Stores a filename
//	Deck mUnshuffledDeck;												  // Deck before shuffle
//	Deck mDeck;														      // Deck after shuffle
//	List mCards;														  // Read into this list										  // Deck after shuffle
//	Deck mHand;														      // Hand of player
//	Deck mField;														  // Field of player
//	std::string mName;													  // Name of player
//	int mHealthPoints = 30;												  // Health of player
//};
