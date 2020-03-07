#include "pch.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Game.h"

int main()
{
	// Create the game object
	std::unique_ptr<CGame> pGame = std::make_unique<CGame>();

	// Play the game
	pGame->Play();

	// Pause before closing
	system("pause");
}