#pragma once
#include "Card.h"

class CEquipment : public CCard
{
public:
	// Constructor
	CEquipment(const int& type, const std::string& name);

	// Getter for mSpell
	virtual const bool& IsSpell() override final;

	// Getter for mHealth
	virtual int& GetHealth() override final;

	// Setter for mHealth
	virtual void ReduceHealth(const int& attackDammage) override final;

	// Setter for mHealth
	virtual void IncreaseHealth(const int& heal) override final;

	// Getter for mAttack
	virtual int& GetAttack() override final;

	// Setter for mAttack
	virtual void IncreaseAttack(const int& x) override final;

	// Setter for mAttack
	virtual void SetAttack(const int& x) override final;

	// The attack or spell function of the card
	virtual void Activate(PlayerRef friendlyPlayer, PlayerRef enemyPlayer) override = 0;

private:
	const bool mSPELL = true;

};

