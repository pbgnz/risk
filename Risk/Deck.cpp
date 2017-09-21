/*
 * Deck.cpp
 *
 *  Created on: Sep 17, 2017
 *      Author: dylanfernandes
 */

#include "Deck.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Deck::Deck(int numCountries) {
	size = numCountries;
	numInfantry = numCountries/3;
	numArtillery = numCountries/3;
	numCavalry = numCountries/3;
	int random;
	for(int i = 0;i< numCountries;i++)
	{
		random = rand() % 3;
		if(random == 0 && numInfantry > 0)
		{
			cards.push_back(Card(Card::Infantry));
			numInfantry--;
		}
		else if (random == 1 && numArtillery > 0)
		{
			cards.push_back(Card(Card::Artillery));
			numArtillery--;
		}
		else if (random == 2 && numCavalry > 0)
		{
			cards.push_back(Card(Card::Cavalry));
			numCavalry--;
		}
	}
}
Card Deck::Draw()
{
	if(!cards.empty())
	{
		Card draw = cards.pop_back();
		Card::cardType type = draw.getCardVal();
		if(type == Card::Infantry)
		{
			numInfantry++;
		}
		else if (type == Card::Artillery)
		{
			numArtillery++;
		}
		else
		{
			numCavalry++;
		}
		return draw;
	}
	else
	{
		cout << "The deck is empty\n";
	}
	return NULL;
}
void Deck::PrintStatistics()
{
	cout << "Number of Infantry: " << numInfantry << "\n";
	cout << "Number of Artillery: " << numArtillery << "\n";
	cout << "Number of Cavalry: " << numCavalry << "\n";
}
Deck::~Deck() {
	// TODO Auto-generated destructor stub
}

