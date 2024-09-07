#include <iostream>
#include <string>
#include <ctime>
using namespace std;

const int DECK_SIZE = 52;
const int HAND_SIZE = 12;
const string DIVIDER = "-----------------";
const int ACE_VALUE1 = 11;
const int JQK_VALUE = 10;

//a structure to represent a card, with member functions
//including a string for the suit name(spades, hearts, etc..), a string
//to represent the card itself,an integer to represent the cards rank,
//and an integer to represent the cards value.
struct Card
{
	string suitName;
	string cardSummary;
	int cardRank;
	int cardValue; 

	Card()
	{
		suitName = "";
		cardSummary = "";
		cardRank = 0;
		cardValue = 0;
	}
};

//a structure to represent an array of cards, with member functions including
//a card pointer to populate the array with cards, an int the represent the max number
//of cards in the array, and an int to represent the cards being used in the array.
struct CardArray
{
	Card* cards;
	int maxElements;
	int usedElements;

	CardArray()
	{
		cards = nullptr;
		maxElements = 0;
		usedElements = 0;
	}
};

void getNewDeck(CardArray& deck);
void printDeck(const CardArray& deck);
void shuffleDeck(CardArray& deck);
int randNum(int start, int end);
int blackJack(CardArray& deck);
void deal(const CardArray& deck, const CardArray& hand, int& countP, int& countD);
void getNewHand(CardArray& hand);
void setValue(const CardArray& deck, CardArray& hand, int countH, int countD);
void printHand(const CardArray& hand);
int handScore(const CardArray& hand);
void inputCheck(string& input);
void playGames(CardArray& deck);
int aces(const CardArray& hand);
void blackJackAdvice(int pScore, const CardArray& dHand);

//Gives the player advice on whether they should hit or stand.
void blackJackAdvice(int pScore, const CardArray& dHand)
{
	int dealerCard = 0;
	dealerCard = dHand.cards[0].cardValue;

	if ((dealerCard == 7) || (dealerCard == 8) || (dealerCard == 9) || (dealerCard == 10) || (dealerCard == 11))
	{
		if (pScore >= 17)
		{
			cout << "You should stand. Your score is " << pScore;
			cout << " don't risk going bust." << endl;
		}

		else if (pScore < 17)
		{
			cout << "You should hit. Your score is " << pScore;
			cout << " since the dealer's hidden card is good, aim for a score of at least 17." << endl;
		}
	}

	else if ((dealerCard == 4) || (dealerCard == 5) || (dealerCard == 6))
	{
		if (pScore >= 12)
		{
			cout << "You should stand. Your score is " << pScore;
			cout << " the dealer's hidden card is poor, don't risk going bust." << endl;
		}

		else if (pScore < 12)
		{
			cout << "You should hit. Your score is " << pScore;
			cout << " since the dealer's hidden card is poor, aim for a score of at least 12." << endl;
		}
	}

	else if ((dealerCard == 2) || (dealerCard == 3))
	{
		if (pScore >= 13)
		{
			cout << "You should stand. Your score is " << pScore;
			cout << " the dealer's hidden card is fair, don't risk going bust." << endl;
		}

		else if (pScore < 13)
		{
			cout << "You should hit. Your score is " << pScore;
			cout << " since the dealer's hidden card is fair, aim for a score of at least 13." << endl;
		}
	}
}

//checks if the hand contains aces, if the score
//exceeds 21 it will change the value of the aces to 11.
int aces(const CardArray& hand)
{
	int result = 0;
	result = handScore(hand);

	if (result > 21)
	{
		for (int i = 0; i < HAND_SIZE; i++)
		{
			if ((hand.cards[i].cardValue == 11) && (result > 21))
			{
				result -= 10;
			}
		}
		return result;
	}

	else if (result <= 21)
	{
		return result;
	}
    return result;
}

//plays multiple games of blackjack, prints out the number of wins, losses
//and draws.
void playGames(CardArray& deck)
{
	int losses = 0;
	int wins = 0;
	int draws = 0;
	int result = 0;
	string answer;
	cout << "BLACKJACK" << endl << DIVIDER << endl;
	cout << "Do you want to play a hand of blackjack? y to play or n not to play. ";
	cin >> answer;

	while ((answer != "y") && (answer != "Y") && (answer != "n") && (answer != "N"))
	{
		cout << endl << DIVIDER << endl << endl << "Do you want to play a hand of blackjack? y to play or n not to play. ";
		cin >> answer;
	}

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << endl << DIVIDER << endl << endl << "Do you want to play a hand of blackjack? y to play or n not to play. ";
		cin >> answer;
	}

	while ((answer == "y") || (answer == "Y"))
	{
		cout << endl;
		printDeck(deck);
		cout << endl;
		result = blackJack(deck);

		if (result == 1)
		{
			wins++;
		}

		else if (result == -1)
		{
			losses++;
		}

		else if (result == 0)
		{
			draws++;
		}

		shuffleDeck(deck);

		cout << endl << DIVIDER << endl << endl;
		cout << "Do you want to play a hand of blackjack? y to play or n not to play. ";
		cin >> answer;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << endl << DIVIDER << endl << endl;
			cout << "Do you want to play a hand of blackjack? y to play or n not to play. ";
			cin >> answer;
		}
	}

	if ((answer == "n") || (answer == "N"))
	{
		cout << endl << endl << "Thanks for playing.";
		cout << endl << "Wins: " << wins << endl;
		cout << "Losses: " << losses << endl;
		cout << "Draws: " << draws << endl;
	}
}

//plays a game of blackjack against the computer
//return 1 if you win, -1 if you lose, and 0 if its
//a draw.
int blackJack(CardArray& deck)
{
	int countHPlayer = 0;
	int countHDealer = 0;
	int playerScore = 0;
	int dealerScore = 0;
	string playerInput;
	int countD = DECK_SIZE - 1;
	CardArray player;
	getNewHand(player);
	CardArray dealer;
	getNewHand(dealer);
	player.cards[countHPlayer];

	cout << endl << "Deal first card" << endl;
	cout << DIVIDER << endl;
	cout << "Player: ";

	setValue(deck, player, countHPlayer, countD);
	deal(deck, player, countHPlayer, countD);
	printHand(player);

	cout << endl << "Dealer: ";

	setValue(deck, dealer, countHDealer, countD);
	deal(deck, dealer, countHDealer, countD);
	printHand(dealer);

	cout << endl << endl << "Deal second card" << endl;
	cout << DIVIDER;
	cout << endl << "Player: ";

	setValue(deck, player, countHPlayer, countD);
	deal(deck, player, countHPlayer, countD);
	printHand(player);

	cout << endl << "Dealer: ";

	setValue(deck, dealer, countHDealer, countD);
	deal(deck, dealer, countHDealer, countD);
	cout << dealer.cards[0].cardSummary << "  ??";
	playerScore = aces(player);
	dealerScore = aces(dealer);

	if ((playerScore == 21) && (dealerScore == 21))
	{
		cout << endl << "It's a draw. No one wins.";
		return 0;
	}

	else if (playerScore > 21)
	{
		cout << "Bust! The dealer wins.";
		return -1;
	}

	else if (dealerScore > 21)
	{
		cout << "Bust! The player wins.";
		return 1;
	}

	else if ((playerScore == 21) && (dealerScore < 21))
	{
		cout << endl << "Blackjack! The player wins.";
		return 1;
	}

	else if ((playerScore == 21) && (dealerScore > 21))
	{
		cout << endl << "Blackjack! The player wins.";
		return 1;
	}

	else if ((dealerScore == 21) && (playerScore < 21))
	{
		cout << endl << "Blackjack! The dealer wins.";
		return -1;
	}

	else if ((dealerScore == 21) && (playerScore > 21))
	{
		cout << endl << "Blackjack! The dealer wins.";
		return -1;
	}

	else if (playerScore < 21 && dealerScore < 21)
	{
		cout << endl << endl << "Dealing to player" << endl;
		cout << DIVIDER << endl;
		blackJackAdvice(playerScore, dealer);
		cout << "Enter h to hit, otherwise enter s to stand: ";
		cin >> playerInput;
	}

	inputCheck(playerInput);

	while ((playerInput != "s") && (playerInput != "S") && (playerScore < 21) && (dealerScore < 21))
	{
		setValue(deck, player, countHPlayer, countD);
		deal(deck, player, countHPlayer, countD);
		cout << endl << "Player: ";
		printHand(player);
		cout << endl;
		playerScore = aces(player);

		if (playerScore == 21)
		{
			cout << "Blackjack! The player wins.";
			return 1;
		}

		else if (playerScore > 21)
		{
			cout << "Bust! The dealer wins.";
			return -1;
		}

		else if (playerScore < 21)
		{
			blackJackAdvice(playerScore, dealer);
			cout << "Enter h to hit, otherwise enter s to stand: ";
			cin >> playerInput;
			inputCheck(playerInput);
		}
	}

	if ((playerInput == "s" || playerInput == "S") && (playerScore < 21))
	{
		cout << endl << "Dealing to dealer" << endl;
		cout << DIVIDER << endl;
		cout << "Dealer: ";
		printHand(dealer);
		cout << endl;

		if (dealerScore > 21)
		{
			cout << "Bust! The player wins.";
			return 1;
		}

		if ((dealerScore >= 17 && dealerScore < 21) && (dealerScore > playerScore))
		{
			cout << "The highest score wins. The dealer wins";
			return -1;
		}

		else if ((dealerScore >= 17 && dealerScore < 21) && (dealerScore < playerScore))
		{
			cout << "The highest score wins. The player wins";
			return 1;
		}

		else if ((dealerScore >= 17 && dealerScore < 21) && (dealerScore == playerScore))
		{
			cout << "It's a draw. No one wins";
			return 0;
		}

		while (dealerScore < 17)
		{
			setValue(deck, dealer, countHDealer, countD);
			deal(deck, dealer, countHDealer, countD);
			dealerScore = aces(dealer);
			cout << "Dealer: ";
			printHand(dealer);
			cout << endl;

			if (dealerScore == 21)
			{
				cout << "Blackjack! The dealer wins.";
				return -1;
			}

			else if (dealerScore > 21)
			{
				cout << "Bust! The player wins";
				return 1;
			}

			else if ((dealerScore >= 17 && dealerScore < 21) && (dealerScore > playerScore))
			{
				cout << "The highest score wins. The dealer wins";
				return -1;
			}

			else if ((dealerScore >= 17 && dealerScore < 21) && (dealerScore < playerScore))
			{
				cout << "The highest score wins. The player wins";
				return 1;
			}

			else if ((dealerScore >= 17 && dealerScore < 21) && (dealerScore == playerScore))
			{
				cout << "It's a draw. No one wins";
				return 0;
			}

		}
	}

	delete[] player.cards;
	delete[] dealer.cards;
    return 0;
}

//Checks if the input is h or s, repeatedly asks for input
//while its not.
void inputCheck(string& playerInput)
{
	while ((playerInput != "h") && (playerInput != "H") && (playerInput != "s") && (playerInput != "S"))
	{
		cout << "Enter h to hit, otherwise enter s to stand: ";
		cin >> playerInput;
	}

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Enter h to hit, otherwise enter s to stand: ";
		cin >> playerInput;
	}
}

//takes a hand CardArray as a parameter, and returns the total
//score of the hand as an int.
int handScore(const CardArray& hand)
{
	int score = 0;

	for (int i = 0; i < HAND_SIZE; i++)
	{
		score += hand.cards[i].cardValue;
	}

	return score;
}

//takes a hand CardArray as a parameter and
//prints out every card in the hand.
void printHand(const CardArray& hand)
{
	for (int i = 0; i < HAND_SIZE; i++)
	{
		if (hand.cards[i].cardValue > 0)
		{
			cout << hand.cards[i].cardSummary << "  ";
		}
	}
}

//sets the value of a index in a hand CardArray as
//a value of an index in a deck CardArray.
void setValue(const CardArray& deck, CardArray& hand, int countH, int countD)
{
	hand.cards[countH] = deck.cards[countD];
}

//simulates removing the last card in the deck
//and giving it to a player or dealer's hand
void deal(const CardArray& deck, const CardArray& hand, int& countP, int& countD)
{
	CardArray d;
	CardArray h;
	d = deck;
	h = hand;

	h.cards[countP].cardSummary = d.cards[countD].cardSummary;

	countP++;
	countD--;
}

//creates a CardArray representing a hand
//with no cards, with a max size 12.
void getNewHand(CardArray& hand)
{
	hand.maxElements = DECK_SIZE;
	hand.usedElements = DECK_SIZE;
	hand.cards = new Card[DECK_SIZE];

	for (int i = 0; i < DECK_SIZE; i++)
	{
		hand.cards[i].cardRank = 0;
		hand.cards[i].cardSummary = "";
		hand.cards[i].cardValue = 0;
		hand.cards[i].suitName = "";
	}
}

//Populates a deck of cards with 52 cards
void getNewDeck(CardArray& deck)
{
	deck.maxElements = DECK_SIZE;
	deck.usedElements = DECK_SIZE;
	deck.cards = new Card[DECK_SIZE];

	for (int i = 0; i < 13; i++)
	{
		deck.cards[i].suitName = "spades";
		deck.cards[i].cardRank = i + 1;

		if (deck.cards[i].cardRank == 1)
		{
			deck.cards[i].cardSummary = "AS";
			deck.cards[i].cardValue = ACE_VALUE1;
		}

		else if (deck.cards[i].cardRank == 2)
		{
			deck.cards[i].cardSummary = "2S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 3)
		{
			deck.cards[i].cardSummary = "3S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 4)
		{
			deck.cards[i].cardSummary = "4S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 5)
		{
			deck.cards[i].cardSummary = "5S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 6)
		{
			deck.cards[i].cardSummary = "6S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 7)
		{
			deck.cards[i].cardSummary = "7S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 8)
		{
			deck.cards[i].cardSummary = "8S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 9)
		{
			deck.cards[i].cardSummary = "9S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 10)
		{
			deck.cards[i].cardSummary = "10S";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 11)
		{
			deck.cards[i].cardSummary = "JS";
			deck.cards[i].cardValue = JQK_VALUE;
		}

		else if (deck.cards[i].cardRank == 12)
		{
			deck.cards[i].cardSummary = "QS";
			deck.cards[i].cardValue = JQK_VALUE;
		}

		else if (deck.cards[i].cardRank == 13)
		{
			deck.cards[i].cardSummary = "KS";
			deck.cards[i].cardValue = JQK_VALUE;
		}
	}

	for (int i = 13; i < 26; i++)
	{
		deck.cards[i].suitName = "hearts";
		deck.cards[i].cardRank = (i - 13) + 1;

		if (deck.cards[i].cardRank == 1)
		{
			deck.cards[i].cardSummary = "AH";
			deck.cards[i].cardValue = ACE_VALUE1;
		}

		else if (deck.cards[i].cardRank == 2)
		{
			deck.cards[i].cardSummary = "2H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 3)
		{
			deck.cards[i].cardSummary = "3H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 4)
		{
			deck.cards[i].cardSummary = "4H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 5)
		{
			deck.cards[i].cardSummary = "5H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 6)
		{
			deck.cards[i].cardSummary = "6H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 7)
		{
			deck.cards[i].cardSummary = "7H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 8)
		{
			deck.cards[i].cardSummary = "8H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 9)
		{
			deck.cards[i].cardSummary = "9H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 10)
		{
			deck.cards[i].cardSummary = "10H";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 11)
		{
			deck.cards[i].cardSummary = "JH";
			deck.cards[i].cardValue = JQK_VALUE;
		}

		else if (deck.cards[i].cardRank == 12)
		{
			deck.cards[i].cardSummary = "QH";
			deck.cards[i].cardValue = JQK_VALUE;
		}

		else if (deck.cards[i].cardRank == 13)
		{
			deck.cards[i].cardSummary = "KH";
			deck.cards[i].cardValue = JQK_VALUE;
		}
	}

	for (int i = 26; i < 39; i++)
	{
		deck.cards[i].suitName = "diamonds";
		deck.cards[i].cardRank = (i - 26) + 1;

		if (deck.cards[i].cardRank == 1)
		{
			deck.cards[i].cardSummary = "AD";
			deck.cards[i].cardValue = ACE_VALUE1;
		}

		else if (deck.cards[i].cardRank == 2)
		{
			deck.cards[i].cardSummary = "2D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 3)
		{
			deck.cards[i].cardSummary = "3D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 4)
		{
			deck.cards[i].cardSummary = "4D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 5)
		{
			deck.cards[i].cardSummary = "5D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 6)
		{
			deck.cards[i].cardSummary = "6D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 7)
		{
			deck.cards[i].cardSummary = "7D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 8)
		{
			deck.cards[i].cardSummary = "8D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 9)
		{
			deck.cards[i].cardSummary = "9D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 10)
		{
			deck.cards[i].cardSummary = "10D";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 11)
		{
			deck.cards[i].cardSummary = "JD";
			deck.cards[i].cardValue = JQK_VALUE;
		}

		else if (deck.cards[i].cardRank == 12)
		{
			deck.cards[i].cardSummary = "QD";
			deck.cards[i].cardValue = JQK_VALUE;
		}

		else if (deck.cards[i].cardRank == 13)
		{
			deck.cards[i].cardSummary = "KD";
			deck.cards[i].cardValue = JQK_VALUE;
		}
	}

	for (int i = 39; i < 52; i++)
	{
		deck.cards[i].suitName = "clubs";
		deck.cards[i].cardRank = (i - 39) + 1;

		if (deck.cards[i].cardRank == 1)
		{
			deck.cards[i].cardSummary = "AC";
			deck.cards[i].cardValue = ACE_VALUE1;
		}

		else if (deck.cards[i].cardRank == 2)
		{
			deck.cards[i].cardSummary = "2C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 3)
		{
			deck.cards[i].cardSummary = "3C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 4)
		{
			deck.cards[i].cardSummary = "4C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 5)
		{
			deck.cards[i].cardSummary = "5C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 6)
		{
			deck.cards[i].cardSummary = "6C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 7)
		{
			deck.cards[i].cardSummary = "7C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 8)
		{
			deck.cards[i].cardSummary = "8C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 9)
		{
			deck.cards[i].cardSummary = "9C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 10)
		{
			deck.cards[i].cardSummary = "10C";
			deck.cards[i].cardValue = deck.cards[i].cardRank;
		}

		else if (deck.cards[i].cardRank == 11)
		{
			deck.cards[i].cardSummary = "JC";
			deck.cards[i].cardValue = JQK_VALUE;
		}

		else if (deck.cards[i].cardRank == 12)
		{
			deck.cards[i].cardSummary = "QC";
			deck.cards[i].cardValue = JQK_VALUE;
		}

		else if (deck.cards[i].cardRank == 13)
		{
			deck.cards[i].cardSummary = "KC";
			deck.cards[i].cardValue = JQK_VALUE;
		}
	}
}

//prints a deck of 52 cards, in rows
//of 13
void printDeck(const CardArray& deck)
{
	for (int i = 0; i < 13; i++)
	{
		cout << deck.cards[i].cardSummary << " ";
	}

	cout << endl;

	for (int i = 13; i < 26; i++)
	{
		cout << deck.cards[i].cardSummary << " ";
	}

	cout << endl;

	for (int i = 26; i < 39; i++)
	{
		cout << deck.cards[i].cardSummary << " ";
	}

	cout << endl;

	for (int i = 39; i < 52; i++)
	{
		cout << deck.cards[i].cardSummary << " ";
	}

	cout << endl;
}

//shuffles a deck of cards randomly
void shuffleDeck(CardArray& deck)
{
	for (int i = 0; i < DECK_SIZE; i++)
	{
		int randomNum = 0;
		randomNum = randNum(0, (DECK_SIZE - 1));
		Card temp;
		temp = deck.cards[i];
		deck.cards[i] = deck.cards[randomNum];
		deck.cards[randomNum] = temp;
	}
}

//returns a random int between the start and end values.
int randNum(int start, int end)
{
	int number = 0;
	number = rand() % (end - start + 1) + start;
	return number;
}
