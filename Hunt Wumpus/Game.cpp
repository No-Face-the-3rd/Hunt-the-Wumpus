#include "Game.h"
#include <fstream>
#include <string.h>
#include <algorithm>


Game::Game()
{
	char tmp[20];
	tmp[0] = '\0';
	file.open("Room_Info.txt", std::ios_base::out);
	file.close;
	file.open("Room_Info.txt",std::ios_base::in|std::ios_base::out);
	file >> tmp;
	if (tmp[0] == '\0')
	{

		file << "Rooms: 20 Columns: 5 Connected: 4 Wumpus: 1 Bats: 2 Pits: 2 Arrows: 5";
		file.close();
		numRooms = 20;
		columns = 5;
		numConnect = 4;
		numWumpus = 1;
		numBats = 2;
		numPits = 2;
		numArrows = 5;
	}
	else
	{
		file >> tmp >> numRooms >> tmp >> columns >> tmp >> numConnect >> tmp >> numWumpus >> tmp >> numBats >> tmp >> numPits >> tmp >> numArrows;
		if (columns <= 1)
			columns = 2;
		else if (columns > 6)
			columns = 6;
		if (numConnect <= 1)
			numConnect = 2;
		else if (numConnect > 6)
			numConnect = 6;
		if (numArrows > numRooms / 4)
			numArrows = numRooms / 4;
		else if (!numArrows)
			numArrows = 1;
		if (numWumpus > numRooms / 4)
			numWumpus = numRooms / 4;
		else if (!numWumpus)
			numWumpus = 1;
		else if (numWumpus > numArrows)
			numWumpus = numArrows;
		if (numBats > numRooms / 4)
			numBats = numRooms / 4;
		else if (!numBats)
			numBats = 1;
		if (numPits > numRooms / 6)
			numPits = numRooms / 6;
		else if (!numPits)
			numPits = 1;
		file << "Rooms: " << numRooms << " Columns: " << columns << " Connected: " << numConnect << " Wumpus: " << numWumpus << " Bats: " << numBats << " Pits: " << numPits << " Arrows: " << numArrows;
	}
	file.close();
	layout = new int[numRooms];
	for (int i = 0; i < numRooms; i++)
		layout[i] = i;
	std::random_shuffle(layout[0], layout[numRooms]);
	rooms = new Room[numRooms];
	for (int i = 0; i < numRooms; i++)
	{
		rooms[i].adjacent = new int[numConnect];
		for (int j = 0; j < numRooms; j++)
		{
			if (layout[j] == i) 
			{
				switch (numConnect)
				{
				case 6:
				case 5:
				case 4:
				case 3:
				case 2:
					if (!j)
						rooms[i].adjacent[0] = layout[numRooms - 1];
					else if()
						rooms[i].adjacent[0] = layout[j - 1];
					break;
				default:
					break;
				}
			}
		}
	}
}


Game::~Game()
{
	if(!layout)
		delete layout;
	if(!rooms)
		delete rooms;
}
