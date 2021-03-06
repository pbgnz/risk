/*
 * Deck.h
 *
 *  Created on: Sep 17, 2017
 *      Author: dylanfernandes
 */

#ifndef DECK_H_
#define DECK_H_

#include "Card.h"
#include <vector>
using namespace std;

class Deck {
public:
	Deck(int);
	Card Draw();
	void PrintStatistics();
	int getNumberCards();
private:
	vector<Card> cards;
	int size;
	int numInfantry;
	int numArtillery;
	int numCavalry;
};

#endif /* DECK_H_ */
