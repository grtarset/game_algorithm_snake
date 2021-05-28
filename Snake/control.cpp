#include <conio.h>

#define UP_ARROW 72
#define LEFT_ARROW 75
#define DOWN_ARROW 80
#define RIGHT_ARROW 77
#define ENTER 13


void runControl(bool& left, bool& right, bool& up, bool& down, bool& check_press, bool& check_gameover) {
	int i;
	while (!check_gameover) {
		while (!_kbhit());
		if (!check_gameover)
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
	}
	return;
}