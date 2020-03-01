#include "pch.h"
//
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include <fstream>
#include <string>
#include <iostream>
#include "Game.h"

int main()
{

	_CrtDumpMemoryLeaks();


	// Create the game object
	std::unique_ptr<CGame> pGame = std::make_unique<CGame>();
	
	// Play the game
	pGame->Play();

	// Check for memory leaks
	//_CrtDumpMemoryLeaks();

	// Pause before closing
	system("pause");
}

// Memory leaks --- card drawn order