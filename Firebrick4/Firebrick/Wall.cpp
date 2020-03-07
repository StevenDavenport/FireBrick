#include "pch.h"
#include "Wall.h"

CWall::CWall(const int& type, const std::string& name, const int& attack, const int& health)
	: CMinion(type, name, attack, health) {}

const bool& CWall::IsSpell()
{
	return mSPELL;
}