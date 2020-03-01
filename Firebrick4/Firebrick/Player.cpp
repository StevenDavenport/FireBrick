#include "pch.h"
#include "Player.h"


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
		mDeck = mUnshuffledDeck;
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
					mUnshuffledDeck.push_back(std::make_shared<CEquipment>(10, "Sword", sword));
					break;

				case '1':				// mType 11
					mUnshuffledDeck.push_back(std::make_shared<CEquipment>(11, "Armour", armour));
					break;

				case ' ':				// mType 1
					switch (mType[2])
					{
					case 'O':
						mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Orc", 2, 2));
						break;

					case 'G':
						mCards[i][3] == 'o' ? mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Goblin", 2, 1))
							: mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Giant", 4, 4));
						break;

					case 'P':
						mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Pooka", 2, 4));
						break;

					case 'T':
						mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Thorns", 1, 4));
						break;

					case 'D':
						mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Dwarf", 2, 4));
						break;

					case 'C':
						mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Cannon", 4, 1));
						break;

					case 'S':
						mCards[i][3] == 'w' ? mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Swordswinger", 2, 2))
							: mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Spearcarrier", 2, 1));
						break;

					case 'E':
						mUnshuffledDeck.push_back(std::make_shared<CMinion>(1, "Elf", 1, 4));
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
				mUnshuffledDeck.push_back(std::make_shared<CSpell>(2, "Fireball", fireball));
				break;

			case '3':				// mType 3
				mUnshuffledDeck.push_back(std::make_shared<CSpell>(3, "Lightning", lightning));
				break;

			case '4':				// mType 4
				mUnshuffledDeck.push_back(std::make_shared<CSpell>(4, "Bless", bless));
				break;

			case '5':				// mType 5
				mUnshuffledDeck.push_back(std::make_shared<CSpecialMinion>(5, "Vampire", 2, 3, vampire));
				break;

			case '6':				// mType 6
				mUnshuffledDeck.push_back(std::make_shared<CSpecialMinion>(6, "Wall", 0, 6, wall));
				break;

			case '7':				// mType 7
				mUnshuffledDeck.push_back(std::make_shared<CSpecialMinion>(7, "Rat", 1, 2, horde));
				break;

			case '8':				// mType 8
				if (mType[2] == 'E')
				{
					mUnshuffledDeck.push_back(std::make_shared<CSpecialMinion>(8, "Elephant", 3, 6, trample));
				}
				else
				{
					mUnshuffledDeck.push_back(std::make_shared<CSpecialMinion>(8, "Dragon", 3, 6, trample));
				}
				break;

			case '9':				// mType 9
				mUnshuffledDeck.push_back(std::make_shared<CSpecialMinion>(9, "Leech", 2, 2, leech));
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

void CPlayer::FDraw()
{
	// Put a drawn card into the hand
	mHand.push_back(mDeck[mDeck.size() - 1]);
	std::cout << mName << " begins with " << mDeck[mDeck.size() - 1]->GetName() << std::endl;

	// Delete the drawn card from the mList
	mDeck.pop_back();
}


void CPlayer::Draw()
{
	// Put a drawn card into the hand
	mHand.push_back(mDeck[mDeck.size() - 1]);
	std::cout << mName << " draws " << mDeck[mDeck.size() - 1]->GetName() << std::endl;

	// Delete the drawn card from the mList
	mDeck.pop_back();
}

int CPlayer::PlayCard()
{
	// Pick a random card in the hand to play
	int r = CRandom::Random(mHand.size() - 1);

	// Play that card to the field
	mField.push_back(mHand[r]);
	std::cout << mName << " plays " << mHand[r]->GetName() << std::endl;

	// Erase from hand
	mHand.erase(mHand.begin() + r);

	// Return the played cards special ability
	return mField[mField.size() - 1]->GetSpecialAbility();
}

weakList CPlayer::GetField()
{
	weakList tempList;
	for (size_t i = 0; i < mField.size(); i++)
	{
		tempList.push_back(GetCard(i));
	}
	return tempList;
}

int CPlayer::GetFieldSize()
{
	return mField.size();
}

weakCard CPlayer::GetCard(const int& i)
{
	return mField[i];
}

std::string CPlayer::GetName()
{
	return mName;
}

void CPlayer::ReducePlayerHealth(const int& x)
{
	mHealthPoints -= x;
}

void CPlayer::ReduceCardHealth(const int& i, const int& x)
{
	mField[i]->ReduceHealth(x - mField[i]->GetProtection());
}

void CPlayer::IncreasePlayerHealth(const int& x)
{
	mHealthPoints += x;
}

void CPlayer::IncreaseCardHealth(const int& i, const int& x)
{
	mField[i]->IncreaseHealth(x);
}

void CPlayer::IncreaseCardAttack(const int& i, const int& x)
{
	mField[i]->IncreaseAttack(x);
}

void CPlayer::IncreaseCardProtection(const int& i, const int& x)
{
	mField[i]->IncreaseProtection(x);
}

void CPlayer::DeleteFromField(const int& i)
{
	mField.erase(mField.begin() + i);
}
