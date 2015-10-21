#pragma once

enum STATE {INIT,MAIN,PLAY,GAME,RULES,EXIT};

STATE MainMenu();

void splash();

STATE rules();

void exit();