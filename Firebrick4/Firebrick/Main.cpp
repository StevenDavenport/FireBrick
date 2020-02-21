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

	- On play spec &&&&&& - On attack spec === enum



	- Test and Debug
		- make test function or class.

	- #ifndef / #define

	- change inheritence variables and constructors /  Look where "Protected" variables could be used.

	- Check if constants could be used

	- Efficiency 
		- Restructure game.cpp considering friend. 
		- Minimise .push_back()
		- Look for where things are being copied unnessaserily 
		- google more

	- Memory leaks
		- Use livrary that checks for them / pretty sure their is none.

	- Change the way read in works, make it dynamic, reading in each attribute (only 1 switch(type{})
		- If i can think of a better way

	- Comment / refacter make it pretty / Style guide
		- zzZZZ
*/
