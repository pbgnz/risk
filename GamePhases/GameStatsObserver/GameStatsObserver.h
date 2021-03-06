/*
 * GameStatsObserver.h
 *
 *  Created on: Nov 17, 2017
 *      Author: Philippe
 */

#ifndef GAMEPHASES_GAMESTATSOBSERVER_GAMESTATSOBSERVER_H_
#define GAMEPHASES_GAMESTATSOBSERVER_GAMESTATSOBSERVER_H_

#include "../../Common/Observer/Observer.h"
#include "../MainLoop.h"

class MainLoop;

class GameStatsObserver : public Observer {

private:
	bool locked;

protected:
	MainLoop* mainLoop;

public:
	GameStatsObserver(MainLoop* m);
	~GameStatsObserver();
	void update();
	MainLoop* getMainLoop();
	bool getLock();
	void lock();

};

#endif /* GAMEPHASES_GAMESTATSOBSERVER_GAMESTATSOBSERVER_H_ */
