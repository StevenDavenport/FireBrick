#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <typeinfo>

// Forward decleration dependencies 
class CPlayer;
typedef std::unique_ptr<CPlayer>& PlayerRef;

// Class card
class CCard
{
public:
	// Constructor
	CCard(const int& type, const std::string& name);

	// Getter for mName
	std::string& GetName();

	// Getter for mType
	const int& GetType();

	// Getter for mProtection
	const int& GetProtection();

	// Outputs messages to the console, minion killed
	void ConsoleOutput(const std::string& attackerName, const std::string& defenderName, const int& health);

	// Setter for mProtection
	void IncreaseProtection(const int& x);

	// Getter for mHealth
	virtual int& GetHealth() = 0;

	// Setter for mHealth
	virtual void ReduceHealth(const int& attackDammage) = 0;

	// Setter for mHealth
	virtual void IncreaseHealth(const int& heal) = 0;

	// Getter for mAttack
	virtual int& GetAttack() = 0;

	// Setter for mAttack
	virtual void IncreaseAttack(const int& x) = 0;

	// Setter for mAttack
	virtual void SetAttack(const int& x) = 0;

	// Getter for mSpell
	virtual const bool& IsSpell() = 0;

	// The attack or spell function of the card
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) = 0;
										
private:				
	int mType = -1;					 // Type of the card
	std::string mName;				 // Name of the card
	int mProtection = 0;
};
