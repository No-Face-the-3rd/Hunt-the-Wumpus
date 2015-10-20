#pragma once


struct Room
{
	bool wumpus, bats, pit;
	int *adjacent;
	int numRooms;

	Room()
	{
		wumpus = false;
		bats = false;
		pit = false;
		numRooms = 0;
		adjacent = nullptr;
	}
	Room(const int roomNum)
	{
		wumpus = false;
		bats = false;
		pit = false;
		adjacent = new int[numRooms = roomNum];
	}
	~Room() 
	{ 
		if (!adjacent) 
			delete adjacent; 
	}

	Room &operator=(const Room &a)
	{
		if (!adjacent)
			delete adjacent;
		wumpus = a.wumpus;
		bats = a.bats;
		pit = a.pit;
		numRooms = a.numRooms;
		if (numRooms > 0 && a.adjacent)
		{
			adjacent = new int[numRooms];
			for (int i = 0; i < numRooms; i++)
				adjacent[i] = a.adjacent[i];
		}
		else
			adjacent = nullptr;
	}
};