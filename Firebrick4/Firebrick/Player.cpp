#include "pch.h"
#include "Player.h"

typedef std::unique_ptr<CPlayer>& PlayerRef;

CPlayer::CPlayer(const std::string& name, const std::string& filename, const std::string& shuffle)
	: mName(name), mFilename(filename)
{
	SetUpDeck();
	//If the player wants to shuffle, call shuffle
	if (shuffle == "y" || shuffle == "Y")
	{
		ShuffleDeck();
	}
	else
	{
		mDeck = std::move(mUnshuffledDeck);
	}
}

void CPlayer::SetUpDeck()
{
	// Read in the cards
	ReadInCards();

	// Loop through cards
	for (size_t i = 0; i < mCards.size(); i++)
	{
		// If the first character is not nothing
		if (mCards[i][0] != *"")
		{
			// Variables taken from the strings in the array, used in the switch statments
			char mType[3] = { mCards[i][0], mCards[i][1], mCards[i][2] };

			switch (mType[0])
			{
			case '1':
				switch (mType[1])
				{
				case '0':				// mType 10
					mUnshuffledDeck.push_back(std::make_unique<CSword>(10, "Sword"));
					break;

				case '1':				// mType 11
					mUnshuffledDeck.push_back(std::make_unique<CArmour>(11, "Armour"));
					break;

				case ' ':				// mType 1
					switch (mType[2])
					{
					case 'O':
						mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Orc", 2, 2));
						break;

					case 'G':
						mCards[i][3] == 'o' ? mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Goblin", 2, 1))
							: mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Giant", 4, 4));
						break;

					case 'P':
						mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Pooka", 2, 4));
						break;

					case 'T':
						mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Thorns", 1, 4));
						break;

					case 'D':
						mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Dwarf", 2, 4));
						break;

					case 'C':
						mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Cannon", 4, 1));
						break;

					case 'S':
						mCards[i][3] == 'w' ? mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Swordswinger", 2, 2))
							: mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Spearcarrier", 2, 1));
						break;

					case 'E':
						mUnshuffledDeck.push_back(std::make_unique<CMinion>(1, "Elf", 1, 4));
						break;

					default:
						break;
					}
					break;

				default:
					break;
				}
				break;

			case '2':				// mType 2

				mUnshuffledDeck.push_back(std::make_unique<CFireball>(2, "Fireball", 3));
				break;

			case '3':				// mType 3
				mUnshuffledDeck.push_back(std::make_unique<CLightning>(3, "Lightning", 1));
				break;

			case '4':				// mType 4
				mUnshuffledDeck.push_back(std::make_unique<CBless>(4, "Bless", 2));
				break;

			case '5':				// mType 5
				mUnshuffledDeck.push_back(std::make_unique<CVampire>(5, "Vampire", 2, 3));
				break;

			case '6':				// mType 6
				mUnshuffledDeck.push_back(std::make_unique<CWall>(6, "Wall", 0, 6));
				break;

			case '7':				// mType 7
				mUnshuffledDeck.push_back(std::make_unique<CHorde>(7, "Rat", 1, 2));
				break;

			case '8':				// mType 8
				if (mType[2] == 'E')
				{
					mUnshuffledDeck.push_back(std::make_unique<CTrample>(8, "Elephant", 3, 6));
				}
				else
				{
					mUnshuffledDeck.push_back(std::make_unique<CTrample>(8, "Dragon", 3, 6));
				}
				break;

			case '9':				// mType 9
				mUnshuffledDeck.push_back(std::make_unique<CLeech>(9, "Leech", 2, 2));
				break;

			default:
				break;
			}
		}
	}
}

void CPlayer::ReadInCards()
{
	// Stores a line
	std::string temp;

	// Read in stream
	std::ifstream inFile(mFilename);

	// Read in line by line
	while (getline(inFile, temp))
	{
		// Dont pushback if string is empty
		if (temp.size() > 0)
		{
			mCards.push_back(temp);
		}
	}
	// Close file
	inFile.close();
}


void CPlayer::ShuffleDeck()
{
	while (mUnshuffledDeck.size() > 0)							// Loop through unshuffled List untill there is nothing in it
	{
		int r = CRandom::Random(mUnshuffledDeck.size() - 1);	// Random number between 0 and n
		mDeck.push_back(std::move(mUnshuffledDeck[r]));			// puts a random card from unshuffled into shuffled List
		mUnshuffledDeck.erase(mUnshuffledDeck.begin() + r);		// delete that card from shuffled List
	}
}

int CPlayer::GetHealthPoints()
{
	return mHealthPoints;
}

void CPlayer::FirstDraw()
{
	// Get the name of the card drawn
	std::string name = mDeck[0]->GetName();

	// Put a drawn card into the hand
	std::cout << mName << " begins with " << name << "\n";
	mHand.push_back(std::move(mDeck[0]));

	// Delete the drawn card from the mList
	mDeck.erase(mDeck.begin());
}

void CPlayer::Draw()
{
	// Get the name of the card drawn
	std::string name = mDeck[0]->GetName();

	// Put a drawn card into the hand
	std::cout << mName << " draws " << name << std::endl;
	mHand.push_back(std::move(mDeck[0]));

	// Delete the drawn card from the mList
	mDeck.erase(mDeck.begin());
}

void CPlayer::PrintTable()
{
	std::string name;
	int health = -1;

	// Prints both players fields to console window
	std::cout << "Cards On Table: ";
	for (size_t i = 0; i < mField.size(); i++)
	{
		health = mField[i]->GetHealth();
		name = mField[i]->GetName();

		std::cout << name << " (" << health << ")  ";
	}
	std::cout << std::endl;
}

std::string CPlayer::GetName()
{
	return mName;
}

void CPlayer::RemoveCardFromField(const int& i)
{
	mField.erase(mField.begin() + i);
}

void CPlayer::ReduceHealth(const int& attackDammage)
{
	mHealthPoints -= attackDammage;
}

void CPlayer::IncreaseHealth(const int& heal)
{
	mHealthPoints += heal;
}

void CPlayer::PlayCard(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	// Pick a random card in the hand to play
	int r = CRandom::Random(mHand.size() - 1);

	// Get the name of the card drawn
	std::string name = mHand[r]->GetName();

	// Play that card to the field
	std::cout << mName << " plays " << name << std::endl;
	mField.push_back(std::move(mHand[r]));

	// Erase from hand
	mHand.erase(mHand.begin() + r);

	// Cast on play spell
	if (mField[mField.size() - 1]->IsSpell() == true)
	{
		mField[mField.size() - 1]->Activate(friendlyPlayer, enemyPlayer);
		if (enemyPlayer->GetHealthPoints() <= 0)
		{
			return;
		}
	}
}

void CPlayer::Attack(PlayerRef friendlyPlayer, PlayerRef enemyPlayer)
{
	for (size_t i = 0; i < mField.size(); i++)
	{
		mField[i]->Activate(friendlyPlayer, enemyPlayer);
		if (enemyPlayer->GetHealthPoints() <= 0)
		{
			return;
		}
	}
}