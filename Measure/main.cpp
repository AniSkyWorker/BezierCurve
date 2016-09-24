#include "stdafx.h"
#include "Window.h"
#include <SDL2/SDL.h>

int main(int, char *[])
{
	glewInit();

	CWindow window;
	window.Show({ WINDOW_WIDTH, WINDOW_HEIGTH });
	window.DoGameLoop();

	return 0;
}

