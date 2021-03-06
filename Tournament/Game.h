#ifndef TOURNAMENT_GAME_H_
#define TOURNAMENT_GAME_H_

#include <string>
#include <iostream>
#include <vector>
#include "../Player/Player.h"
#include "../Map/Map.h"

class Game {

private:
	Map* map;
	Player* win;
	vector<Player*> players;
	Deck* deck;
	int gameNumber;
	int maxTurns;

public:
	Game(Map*,vector<Player*>,int,int,Deck*);
	void startGame();
	string getWinnerName();
};

#endif
