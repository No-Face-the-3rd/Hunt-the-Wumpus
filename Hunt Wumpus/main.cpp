#include <string>
#include <cstring>
#include "sfwdraw.h"


void main()
{
	const int screenW = 800, screenH = 600;
	const std::string title = "Test";
	sfw::initContext(screenW, screenH, title.c_str);


	return;
}