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
					unshuffledDeck.push_back(std::make_shared<CEquipment>(10, "Sword", sword));
					break;

				case '1':				// Type 11
					unshuffledDeck.push_back(std::make_shared<CEquipment>(11, "Armour", armour));
					break;

				case ' ':				// Type 1
					switch (type[2])
					{
					case 'O':
						unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Orc", 2, 2));
						break;

					case 'G':
						cards[i][3] == 'o' ? unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Goblin", 2, 1))
							: unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Giant", 4, 4));
						break;

					case 'P':
						unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Pooka", 2, 4));
						break;

					case 'T':
						unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Thorns", 1, 4));
						break;

					case 'D':
						unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Dwarf", 2, 4));
						break;

					case 'C':
						unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Cannon", 4, 1));
						break;

					case 'S':
						cards[i][3] == 'w' ? unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Swordswinger", 2, 2))
							: unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Spearcarrier", 2, 1));
						break;

					case 'E':
						unshuffledDeck.push_back(std::make_shared<CMinion>(1, "Elf", 1, 4));
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
				unshuffledDeck.push_back(std::make_shared<CSpell>(2, "Fireball", fireball));
				break;

			case '3':				// Type 3
				unshuffledDeck.push_back(std::make_shared<CSpell>(3, "Lightning", lightning));
				break;

			case '4':				// Type 4
				unshuffledDeck.push_back(std::make_shared<CSpell>(4, "Bless", bless));
				break;

			case '5':				// Type 5
				unshuffledDeck.push_back(std::make_shared<CSpecialMinion>(5, "Vampire", 2, 3, vampire));
				break;

			case '6':				// Type 6
				unshuffledDeck.push_back(std::make_shared<CSpecialMinion>(6, "Wall", 0, 6, wall));
				break;

			case '7':				// Type 7
				unshuffledDeck.push_back(std::make_shared<CSpecialMinion>(7, "Rat", 1, 2, horde));
				break;

			case '8':				// Type 8
				if (type[2] == 'E')
				{
					unshuffledDeck.push_back(std::make_shared<CSpecialMinion>(8, "Elephant", 3, 6, trample));
				}
				else
				{
					unshuffledDeck.push_back(std::make_shared<CSpecialMinion>(8, "Dragon", 3, 6, trample));
				}
				break;

			case '9':				// Type 9
				unshuffledDeck.push_back(std::make_shared<CSpecialMinion>(9, "Leech", 2, 2, leech));
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
