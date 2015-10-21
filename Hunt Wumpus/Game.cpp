#include "Game.h"
#include <fstream>
#include <string.h>
#include <algorithm>
#include <time.h>
#include <iostream>

Game::Game()
{
	char tmp[20];
	srand(time(NULL));
	tmp[0] = '\0';
	file.open("Room_Info.txt", std::ios_base::out);
	file.close();
	file.open("Room_Info.txt", std::ios_base::in | std::ios_base::out);
	file >> tmp;
	if (tmp[0] == '\0')
	{

		file << "Rooms: 20\nColumns: 5\nConnected: 4\nWumpus: 1\nBats: 2\nPits: 2\nArrows: 5";
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
		if (numRooms > 40)
			numRooms = 40;
		else if (numRooms <= 10)
			numRooms = 11;
		if (columns <= 1)
			columns = 2;
		else if (columns > 6)
			columns = 6;
		if (numConnect < 1)
			numConnect = 1;
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
		file << "Rooms: " << numRooms << "\nColumns: " << columns << "\nConnected: " << numConnect << "\nWumpus: " << numWumpus << "\nBats: " << numBats << "\nPits: " << numPits << "\nArrows: " << numArrows;
	}
	file.close();
	stateTypes[0] = " ";
	stateTypes[1] = "You are in room ";
	stateTypes[2] = "You were evaporated by a wumpus!";
	stateTypes[3] = "You were grabbed by some bats and transported to ";
	stateTypes[4] = "You fell into an unavoidable pit!";
	stateTypes[5] = "A stench reaches your nostrils!";
	stateTypes[6] = "You hear a flapping!";
	stateTypes[7] = "You hear wind howling!";
	stateTypes[8] = "You shot into ";
	stateTypes[9] = "(M)ove, (S)hoot, (R)ules, E(x)it: ";
	stateTypes[10] = "You see doors that say: ";
	stateTypes[11] = "You killed a wumpus!";
	stateTypes[12] = "You missed!";
	layout = new int[numRooms];
	for (int i = 0; i < numRooms; i++)
		layout[i] = i;
	std::random_shuffle(&layout[0], &layout[numRooms]);
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
					if (j > numRooms - columns)
					{
						if (!j % columns)
						{
							rooms[i].adjacent[5] = layout[columns - j % columns - 1];
						}
						else
						{
							rooms[i].adjacent[5] = layout[j % columns - 1];
						}
					}
					else
					{
						if (!j % columns)
						{
							if (j + 2 * columns - 1 < numRooms)
								rooms[i].adjacent[5] = layout[j + 2 * columns - 1];
							else
								rooms[i].adjacent[5] = layout[numRooms % columns - 1];
						}
						else
						{
							rooms[i].adjacent[5] = layout[j + columns - 1];
						}
					}
				case 5:
					if (j < columns)
					{
						int cmp = numRooms - columns + j + (columns - numRooms % columns) + 1;
						if (cmp == numRooms)
							cmp = cmp - columns - numRooms % columns;
						if (cmp > numRooms)
							cmp -= columns;
						rooms[i].adjacent[4] = layout[cmp];
					}
					else
					{
						if (j % columns == columns - 1)
							rooms[i].adjacent[4] = layout[j - (columns + j % columns)];
						else
							rooms[i].adjacent[4] = layout[j - columns + 1];
					}
				case 4:
					if (j >= numRooms - columns)
						rooms[i].adjacent[3] = layout[j % columns];
					else
						rooms[i].adjacent[3] = layout[j + columns];
				case 3:
					if (j < columns)
					{
						int cmp = numRooms - columns + j + (columns - numRooms % columns);
						if (cmp > numRooms - 1)
							cmp -= columns;
						rooms[i].adjacent[2] = layout[cmp];
					}
					else
						rooms[i].adjacent[2] = layout[j - columns];
				case 2:
					if (j == numRooms - 1)
						rooms[i].adjacent[1] = layout[0];
					else
						rooms[i].adjacent[1] = layout[j + 1];
				case 1:
					if (!j)
						rooms[i].adjacent[0] = layout[numRooms - 1];
					else
						rooms[i].adjacent[0] = layout[j - 1];
					break;
				default:
					break;
				}
			}
		}
	}
	nearWump = nearBats = nearPit = false;
	for (int i = 0; i < numWumpus; i++)
		rooms[rand() % numRooms].wumpus = true;
	for (int i = 0; i < numBats; i++)
		rooms[rand() % numRooms].bats = true;
	for (int i = 0; i < numPits; i++)
		rooms[rand() % numRooms].pit = true;
	currentRoom = rand() % numRooms;
	currentState = 0;
	state[currentState] = 1;
	stateRef[currentState++] = currentRoom;
	currentArrows = numArrows;
}


Game::~Game()
{
	if(!layout)
		delete layout;
	if(!rooms)
		delete rooms;
}

STATE Game::update()
{
	char check;
	system("cls");
	for (int i = 0; i < currentState; i++)
	{
		std::cout << stateTypes[state[i]];
		if (state[i] == 1 || state[i] == 3 || state[i] == 8)
			std::cout << stateRef[i] + 1;
		if (state[i] == 10)
			for (int j = 0; j < numConnect; j++)
				std::cout << rooms[stateRef[i]].adjacent[j] + 1 << " ";
		std::cout << std::endl;
	}
	if (!rooms[currentRoom].wumpus && !rooms[currentRoom].pit && currentArrows > 0)
	{
		std::cout << stateTypes[9];
		std::cin >> check;
		switch (check)
		{
		case 'm':
		case 'M':
			move();
			return GAME;
		case 's':
		case 'S':
			return shoot();
		case 'r':
		case 'R':
			return RULES;
		case 'x':
		case 'X':
			return MAIN;
		default:
			return GAME;
		}
	}
	else
	{
		std::cout << "You lose!\n";
		system("pause");
		return MAIN;
	}
}

void Game::checkRooms()
{
	if (rooms[currentRoom].wumpus)
	{
		state[currentState] = 2;
		stateRef[currentState++] = currentRoom;
		return;
	}
	if (rooms[currentRoom].bats)
	{
		currentRoom = rand() % numRooms;
		state[currentState] = 3;
		stateRef[currentState++] = currentRoom;
		state[currentState] = 0;
		stateRef[currentState++] = currentRoom;
		state[currentState] = 1;
		stateRef[currentState++] = currentRoom;
		checkRooms();
		return;
	}
	if (rooms[currentRoom].pit)
	{
		state[currentState] = 4;
		stateRef[currentState++] = currentRoom;
		return;
	}
	for (int i = 0; i < numConnect; i++)
	{
		if (rooms[rooms[currentRoom].adjacent[i]].wumpus && !nearWump)
		{
			nearWump = true;
			state[currentState] = 5;
			stateRef[currentState++] = currentRoom;
		}
		if (rooms[rooms[currentRoom].adjacent[i]].bats && !nearBats)
		{
			nearBats = true;
			state[currentState] = 6;
			stateRef[currentState++] = currentRoom;
		}
		if (rooms[rooms[currentRoom].adjacent[i]].pit && !nearPit)
		{
			nearPit = true;
			state[currentState] = 7;
			stateRef[currentState++] = currentRoom;
		}
	}
	nearWump = nearBats = nearPit = false;
}

void Game::newGame()
{
	if(!layout)
		delete layout;
	layout = new int[numRooms];
	for (int i = 0; i < numRooms; i++)
		layout[i] = i;
	std::random_shuffle(&layout[0], &layout[numRooms]);
	if(!rooms)
		delete rooms;
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
					if (j > numRooms - columns)
					{
						if (!j % columns)
						{
							rooms[i].adjacent[5] = layout[columns - j % columns - 1];
						}
						else
						{
							rooms[i].adjacent[5] = layout[j % columns - 1];
						}
					}
					else
					{
						if (!j % columns)
						{
							if (j + 2 * columns - 1 < numRooms)
								rooms[i].adjacent[5] = layout[j + 2 * columns - 1];
							else
								rooms[i].adjacent[5] = layout[numRooms % columns - 1];
						}
						else
						{
							rooms[i].adjacent[5] = layout[j + columns - 1];
						}
					}
				case 5:
					if (j < columns)
					{
						int cmp = numRooms - columns + j + (columns - numRooms % columns) + 1;
						if (cmp == numRooms)
							cmp = cmp - columns - numRooms % columns;
						if (cmp > numRooms)
							cmp -= columns;
						rooms[i].adjacent[4] = layout[cmp];
					}
					else
					{
						if (j % columns == columns - 1)
							rooms[i].adjacent[4] = layout[j - (columns + j % columns)];
						else
							rooms[i].adjacent[4] = layout[j - columns + 1];
					}
				case 4:
					if (j >= numRooms - columns)
						rooms[i].adjacent[3] = layout[j % columns];
					else
						rooms[i].adjacent[3] = layout[j + columns];
				case 3:
					if (j < columns)
					{
						int cmp = numRooms - columns + j + (columns - numRooms % columns);
						if (cmp > numRooms - 1)
							cmp -= columns;
						rooms[i].adjacent[2] = layout[cmp];
					}
					else
						rooms[i].adjacent[2] = layout[j - columns];
				case 2:
					if (j == numRooms - 1)
						rooms[i].adjacent[1] = layout[0];
					else
						rooms[i].adjacent[1] = layout[j + 1];
				case 1:
					if (!j)
						rooms[i].adjacent[0] = layout[numRooms - 1];
					else
						rooms[i].adjacent[0] = layout[j - 1];
					break;
				default:
					break;
				}
			}
		}
	}
	nearWump = nearBats = nearPit = false;
	for (int i = 0; i < numWumpus; i++)
		rooms[rand() % numRooms].wumpus = true;
	for (int i = 0; i < numBats; i++)
		rooms[rand() % numRooms].bats = true;
	for (int i = 0; i < numPits; i++)
		rooms[rand() % numRooms].pit = true;
	currentRoom = rand() % numRooms;
	currentState = 0;
	state[currentState] = 1;
	stateRef[currentState++] = currentRoom;
	checkRooms();
	state[currentState] = 10;
	stateRef[currentState++] = currentRoom;
	state[currentState] = 0;
	stateRef[currentState++] = currentRoom;
	currentArrows = numArrows;
}



void Game::move()
{
	int room;
	std::cout << "Enter the room in which you wish to move: ";
	std::cin >> room;
	if (room - 1 >= 0 && room < numRooms)
		for (int i = 0; i < numConnect; i++)
			if (room - 1 == rooms[currentRoom].adjacent[i])
			{
				currentRoom = room - 1;
				state[currentState] = 1;
				stateRef[currentState++] = currentRoom;
				checkRooms();
				state[currentState] = 10;
				stateRef[currentState++] = currentRoom;
				state[currentState] = 0;
				stateRef[currentState++] = currentRoom;
			}


}

STATE Game::shoot()
{
	int room;
	bool win = true;
	std::cout << "Enter the room in which you wish to shoot: ";
	std::cin >> room;
	if (room - 1 >= 0 && room - 1 < numRooms)
		for (int i = 0; i < numConnect;i++)
			if (room - 1 == rooms[currentRoom].adjacent[i] )
			{
				state[currentState] = 8;
				stateRef[currentState++] = room - 1;
				if (rooms[rooms[currentRoom].adjacent[i]].wumpus)
				{
					state[currentState] = 11;
					stateRef[currentState++] = currentRoom;
					rooms[room - 1].wumpus = false;
				}
				else
				{
					state[currentState] = 12;
					stateRef[currentState++] = currentRoom;
				}
			}
	for (int i = 0; i < numRooms; i++)
		if (rooms[i].wumpus)
			win = false;
	if (win)
	{
		std::cout << "You win!\n";
		system("pause");
		return MAIN;
	}
	else
	{
		checkRooms();
		return GAME;
	}
}