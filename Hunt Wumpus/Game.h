#pragma once
#include "Room.h"
#include <fstream>

class Game
{
private:
	int state[255], stateRef[255], *layout, latestState, columns, numRooms,numConnect,numWumpus,numBats, numPits,numArrows;
	Room *rooms;
	std::fstream file;
public:
	Game();
	~Game();
};

