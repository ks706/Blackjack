#include <iostream>
#include <string>
#include <ctime>
#include "blackjack.h"
using namespace std;


int main()
{
	srand(time(0));
	CardArray a;
	getNewDeck(a);
	printDeck(a);
	shuffleDeck(a);
	cout << "shuffled" << endl;
	printDeck(a);
	playGames(a);
	delete[] a.cards;
	return 0;
}

