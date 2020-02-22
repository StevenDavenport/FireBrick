#include "pch.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Game.h"

int main()
{
	std::unique_ptr<CGame> Game = std::make_unique<CGame>();
	Game->Play();

	system("pause");
}
 

////-------- TODO: --------////

/*
	- Test and Debug
		- make test function or class.

	- #ifndef / #define

	- Check if constants could be used

	- Memory leaks
		- Use livrary that checks for them / pretty sure their is none.

	- Comment / refacter make it pretty / Style guide
		- zzZZZ
*/
