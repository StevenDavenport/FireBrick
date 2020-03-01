#include "pch.h"
#include "Card.h"

CCard::CCard(const int& type, const std::string& name) : mType(type), mName(name) {}

int CCard::GetType()
{
	return mType;
}

std::string CCard::GetName()
{
	return mName;
}

int CCard::GetProtection()
{
	return mProtection;
}

void CCard::IncreaseProtection(const int& x)
{
	mProtection += x;
}


