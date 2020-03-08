#include "pch.h"
#include "Card.h"
#include "Player.h"

CCard::CCard(const int& type, const std::string& name) : mType(type), mName(name) {}

std::string& CCard::GetName()
{
	return mName;
}

const int& CCard::GetType()
{
	return mType;
}

const int& CCard::GetProtection()
{
	return mProtection;
}

void CCard::ConsoleOutput(const std::string& attackerName, const std::string& defenderName, const int& health)
{
	if (health > 0)
	{
		// Dammaged
		std::cout << attackerName << " attacks " << defenderName << ". ";
		std::cout << defenderName << " health now " << health << std::endl;
	}
	else
	{
		// Killed
		std::cout << attackerName << " attacks " << defenderName << ". ";
		std::cout << defenderName << " killed\n";
	}
}

void CCard::IncreaseProtection(const int& x)
{
	mProtection += x;
}
