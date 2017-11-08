#include <iostream>
#include "MainLoop.h"

using namespace std;

// Get the winning player, return NULL if no one has won yet
Player* MainLoop::getWinner() {
    Player* currPlayer = currMap->getCountries()[0]->getOwner();
    int currIndex = 1;

    while (currIndex < currMap->getCountries().size()) {
        if (currPlayer != currMap->getCountries()[currIndex++]->getOwner()) {
            return NULL;
        }
    }

    return currPlayer;
}

MainLoop::MainLoop(vector<Player*> players, Map* theMap, Deck* theDeck) {
    playerOrder = players;
    currMap = theMap;
    currDeck = theDeck;
}

// Play the game
void MainLoop::play() {
    Player* winner;
    Player* currPlayer;
    int playingIndex = 0;
    int numTurns = 0;

    // While no one has won keep playing
    while ((winner = getWinner()) == NULL) {
        currPlayer = playerOrder[playingIndex];

        currPlayer->reinforce(currMap->getContinents());
        currPlayer->attack(currDeck);
        currPlayer->fortify(currPlayer->getCountries()[0], currPlayer->getCountries()[1], 1);

        playingIndex = (playingIndex + 1) % playerOrder.size();
        numTurns += 1;
    }

    cout << "Winner: " << winner->getName() << endl;
}
