#include "Game.h"
#include "consts.h"

void main()
{
	Game Game1;
	STATE current = INIT;
	
	while (true)
	{
		switch (current)
		{
		case INIT:
			splash();
		case MAIN:
			current = MainMenu();
			break;
		case PLAY:
			Game1.newGame();
		case GAME:
			current = Game1.update();
			break;
		case RULES: 
			current = rules();
			break;
		case EXIT:
			exit();
			return;
		}
	}
}