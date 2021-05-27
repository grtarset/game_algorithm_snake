#include <conio.h>

//«читуЇм натисканн€ клав≥ш≥ в ≥ншому потоц≥
void runControl(bool& left, bool& right, bool& up, bool& down, bool& check_press, bool& check_restart) {
	char ch;
	while (true) {
		ch = _getch();
		if (!down && ch == 'w' && !check_press)
		{
			left = false;
			right = false;
			up = true;
			down = false;
			check_press = true;
		}
		else if (!up && ch == 's' && !check_press)
		{
			left = false;
			right = false;
			up = false;
			down = true;
			check_press = true;
		}
		else if (!left && ch == 'd' && !check_press)
		{
			left = false;
			right = true;
			up = false;
			down = false;
			check_press = true;
		}
		else if (!right && ch == 'a' && !check_press)
		{
			left = true;
			right = false;
			up = false;
			down = false;
			check_press = true;
		}
		else if (ch == 'r')
		{
			check_restart = true;
			check_press = true;
		}
	}
}