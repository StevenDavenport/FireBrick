#pragma once
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

class CRandom
{
public: 
	static int Random(const int n);				 // Generates a random number between 0 -> n
	static void SetSeed();						 // Sets the random seed, read in from file

private:

};

