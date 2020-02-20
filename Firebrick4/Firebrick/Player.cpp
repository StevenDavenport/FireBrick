#include "pch.h"
#include "Player.h"

CPlayer::CPlayer(std::string name, std::string filename, std::string shuffle) : name(name)
{
	SetUpDeck(filename);
	if (shuffle == "y" || shuffle == "Y")
	{
		ShuffleDeck();
	}
	else
	{
		deck = unshuffledDeck;
	}
}

CPlayer::CPlayer(std::string name) : name(name) {} // test constructor

void CPlayer::SetUpDeck(std::string filename)
{
	std::string cards[100];
	ReadInCards(cards, filename);

	for (int i = 0; i < 100; i++)
	{
		if (cards[i][0] != *"")
		{
			char type[3] = { cards[i][0], cards[i][1], cards[i][2] };

			switch (type[0])
			{
			case '1':
				switch (type[1])
				{
				case '0':				// Type 10
					unshuffledDeck.push_back(std::make_shared<CEquipment>("Sword"));
					break;

				case '1':				// Type 11
					unshuffledDeck.push_back(std::make_shared<CEquipment>("Armour"));
					break;

				case ' ':				// Type 1
					switch (type[2])
					{
					case 'O':
						unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Orc", 2, 2));
						break;

					case 'G':
						cards[i][3] == 'o' ? unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Goblin", 2, 1)) 
							: unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Giant", 4, 4));
						break;

					case 'P':
						unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Pooka", 2, 4));
						break;

					case 'T':
						unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Thorns", 1, 4));
						break;

					case 'D':
						unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Dwarf", 2, 4));
						break;

					case 'C':
						unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Cannon", 4, 1));
						break;

					case 'S':
						cards[i][3] == 'w' ? unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Swordswinger", 2, 2)) 
							: unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Spearcarrier", 2, 1));
						break;

					case 'E':
						unshuffledDeck.push_back(std::make_shared<CBasicMinion>("Elf", 1, 4));
						break;

					default:
						break;

					}
					break;

				default:
					break;
				}
				break;
				
			case '2':				// Type 2
				unshuffledDeck.push_back(std::make_shared<CFireball>());
				break;

			case '3':				// Type 3
				unshuffledDeck.push_back(std::make_shared<CLightning>());
				break;

			case '4':				// Type 4
				unshuffledDeck.push_back(std::make_shared<CBless>());
				break;

			case '5':				// Type 5
				unshuffledDeck.push_back(std::make_shared<CVampire>());
				break;

			case '6':				// Type 6
				unshuffledDeck.push_back(std::make_shared<CWall>());
				break;

			case '7':				// Type 7
				unshuffledDeck.push_back(std::make_shared<CHorde>("Rat"));
				break;

			case '8':				// Type 8
				if (type[2] == 'E')
				{
					unshuffledDeck.push_back(std::make_shared<CTrample>("Elephant"));
				}
				else
				{
					unshuffledDeck.push_back(std::make_shared<CTrample>("Dragon"));
				}
				break;

			case '9':				// Type 9
				unshuffledDeck.push_back(std::make_shared<CLeech>());
				break;

			default:
				break;
			}
		}
	}
}


void CPlayer::ReadInCards(std::string (&cards)[100], std::string filename)
{
	std::ifstream MyReadFile(filename);			 // Read from the text file
	for (int i = 0; i < 100; i++)				 // put each line of the file into the array
	{
		getline(MyReadFile, cards[i]);
	}
	MyReadFile.close();							 // Close file
}


void CPlayer::ShuffleDeck()
{
	while (unshuffledDeck.size() > 0)						// Loop through unshuffled deck untill there is nothing in it
	{
		int r = CRandom::Random(unshuffledDeck.size() - 1);	// Random number between 0 and n
		deck.push_back(unshuffledDeck[r]);					// puts a random card from unshuffled into shuffled deck
		unshuffledDeck.erase(unshuffledDeck.begin() + r);	// delete that card from shuffled deck
	}
}

int CPlayer::Random(const float n)
{
	return 0;
}

int CPlayer::GetHealthPoints()
{
	return healthPoints;
}

Deck CPlayer::GetDeck()
{
	return deck;
}
void CPlayer::FDraw()
{
	hand.push_back(deck[deck.size() - 1]);
	std::cout << name << " begins with " << deck[deck.size() - 1]->GetName() << std::endl;
	deck.pop_back();
}


void CPlayer::Draw()
{
	hand.push_back(deck[deck.size() - 1]);
	std::cout << name << " draws " << deck[deck.size() - 1]->GetName() << std::endl;
	deck.pop_back();
}

int CPlayer::PlayCard()
{
	int r = CRandom::Random(hand.size() - 1);
	field.push_back(hand[r]);
	std::cout << name << " plays " << hand[r]->GetName() << std::endl;
	hand.erase(hand.begin() + r);
	return field[field.size() - 1]->GetSpecialAbility();
}

Deck CPlayer::GetField() 
{
	return field;
}

std::string CPlayer::GetName()
{
	return name;
}

std::vector<std::string> CPlayer::GetHand()
{
	std::vector<std::string> cardsInHand;
	for (size_t i = 0; i < hand.size(); i++)
	{
		//cardsInHand.push_back(hand[i]->GetName());
	}
	return cardsInHand;
}

void CPlayer::ReducePlayerHealth(int x)
{
	healthPoints -= x;
}

void CPlayer::ReduceCardHealth(int i, int x)
{
	if (field[i]->GetProtection() <= 0)
	{
		field[i]->ReduceHealth(x);
	}
	else
	{
		field[i]->ReduceHealth(x - field[i]->GetProtection());
	}
}

void CPlayer::IncreasePlayerHealth(int x)
{
	healthPoints += x;
}

void CPlayer::IncreaseCardHealth(int i, int x)
{
	field[i]->IncreaseHealth(x);
}

void CPlayer::IncreaseCardAttack(int i, int x)
{
	field[i]->IncreaseAttack(x);
}

void CPlayer::IncreaseCardProtection(int i, int x)
{
	field[i]->IncreaseProtection(x);
}

void CPlayer::DeleteFromField(int i)
{
	field.erase(field.begin() + i);
}
