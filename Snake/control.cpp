#include <conio.h>
#include <thread>

#include "interface.h"

using namespace std;

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77
#define ENTER 13
#define ESC 27

void runControl(bool& left, bool& right, bool& up, bool& down, bool& check_press, bool& check_game_finish) {
	bool game_exit = false;
	int i;
	while (!game_exit) {
		while (!_kbhit());
			i = _getch();
		if (!down && i == UP_ARROW && !check_press)
		{
			left = false;
			right = false;
			up = true;
			down = false;
			check_press = true;
		}
		else if (!up && i == DOWN_ARROW && !check_press)
		{
			left = false;
			right = false;
			up = false;
			down = true;
			check_press = true;
		}
		else if (!left && i == RIGHT_ARROW && !check_press)
		{
			left = false;
			right = true;
			up = false;
			down = false;
			check_press = true;
		}
		else if (!right && i == LEFT_ARROW && !check_press)
		{
			left = true;
			right = false;
			up = false;
			down = false;
			check_press = true;
		}
		else if (i == ENTER)
		{
			thread runInterface(runInterface, ref(left), ref(right), ref(up), ref(down), ref(check_press));
			runInterface.detach();
		}
		else if (i == ESC)
		{
			check_game_finish = true;
			game_exit = true;
		}
	}
	return;
}