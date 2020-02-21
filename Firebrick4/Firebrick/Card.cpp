#include "pch.h"
#include "Card.h"

CCard::CCard(int type, std::string name) : type(type), name(name) 
{
}

int CCard::GetType()
{
	return type;
}

std::string CCard::GetName()
{
	return name;
}

int CCard::GetProtection()
{
	return protection;
}

void CCard::IncreaseProtection(int x)
{
	protection += x;
}
