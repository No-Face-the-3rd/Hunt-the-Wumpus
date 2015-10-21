#include "consts.h"
#include <iostream>

STATE MainMenu()
{
	system("cls");
	char choice = '\0';
	std::cout << "Main Menu\n(S)plash\n(P)lay\nE(x)it\n";
	std::cin >> choice;
	switch (choice)
	{
	case 's':
	case 'S':
		return INIT;
	case 'p':
	case 'P':
		return PLAY;
	case 'x':
	case 'X':
		return EXIT;
	default:
		return MAIN;
	}
}

void splash()
{
	system("cls");
	std::cout << "Welcome to Hunt Wumpus!\n\nBy: Jacob Dodson, foodflare@yahoo.com, 10/21/2015\n";
	system("pause");
}

STATE rules()
{
	system("cls");
	std::cout << "You are entering a randomly generated cave.\nYou get a limited number of arrows.\n" <<
		"Each arrow can only shoot into an adjacent room.\nYou need to kill all the Wumpus without getting killed yourself.\n" <<
		"If you go into a room with a wumpus, you will die.\nIf you go into a room with bats they will transport you to a random room.\n" <<
		"If you go into a room with a pit, you will fall in.\nIf you run out of arrows you lose.\n" <<
		"Rooms may have one way doors with certain settings.\n";
	system("pause");
	return GAME;
}

void exit()
{
	system("cls");
	std::cout << "Thanks for playing!\n\n•••••   ••  •• ••••••\n•••••   ••  •• ••••••\n••  ••    ••   ••\n••  ••    ••   ••\n•••••     ••   ••••••\n•••••     ••   ••••••\n••  ••    ••   ••\n••  ••    ••   ••\n•••••     ••   ••••••\n•••••     ••   ••••••\n";
	system("pause");
}