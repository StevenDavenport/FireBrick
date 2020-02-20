#include "pch.h"
#include "Random.h"

int CRandom::Random(const float n)
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1));
}

void CRandom::SetSeed()
{
	std::string strSeed = "";
	std::ifstream MyReadFile("seed.txt");			// Read from the text file
	getline(MyReadFile, strSeed);					// Read into seed variable
	MyReadFile.close();								// Close file
	int seed = std::stoi(strSeed);					// Casting string to int
	std::srand(static_cast<unsigned int>(seed));	// Setting seed
}

