#pragma once
#include "Room.h"
#include <fstream>
#include "string.h"
#include "consts.h"

class Game
{
private:
	int state[255], stateRef[255], *layout, latestState, columns, numRooms,numConnect,numWumpus,numBats, numPits,numArrows,currentState,currentRoom,currentArrows;
	Room *rooms;
	std::fstream file;
	sfw::string stateTypes[13];
	bool nearWump, nearBats, nearPit;
public:
	Game();
	~Game();
	STATE update();
	void checkRooms();
	void newGame();
	void move();
	STATE shoot();
};

