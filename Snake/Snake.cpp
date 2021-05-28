#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <vector>
#include <windows.h>
#include <conio.h>

#include "control.h"

using namespace std;

struct snake_struct
{
	int x;
	int y;
};

void _interface(bool *left, bool *right, bool *up, bool *down, bool *check_press, bool *check_gameover) {
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

	char space[26][26], wall = '#', area = ' ', snake_ch = '*', food = '@';
	int size_h = sizeof(space) / sizeof(space[0]) - 1,
	size_w = sizeof(space[size_h]) / sizeof(space[size_h][0]) - 1,
	xFood = 0, yFood = 0, result = 0;

	bool check_eaten = true, check_collision_generation_food = false;

	vector<snake_struct> snake;
	snake_struct buffer1, buffer2;

	snake.resize(2);
	snake.at(0).x = size_h / 2;
	snake.at(0).y = size_w / 2;

	while (true) {
		//Міняєм координати головки змійки
		if (left && snake.at(0).y > 0) --snake.at(0).y;
		else if (right && snake.at(0).y < size_w - 1) ++snake.at(0).y;
		else if (up && snake.at(0).x > 0) --snake.at(0).x;
		else if (down && snake.at(0).x < size_h - 1) ++snake.at(0).x;
		*check_press = false;

		//Надаєм рандомні координати їжі
		if (check_eaten) {
			do {
				xFood = 1 + mersenne() % (size_h - 2);
				yFood = 1 + mersenne() % (size_w - 2);
				for (size_t i = 0; i < snake.size(); i++) 
					if (snake.at(i).x != xFood && snake.at(i).y != yFood)
						check_collision_generation_food = true;
			} while (!check_collision_generation_food);
			check_collision_generation_food = false;
		}

		//Перевіряємо чи зїджено їжу
		if (snake.at(0).x == xFood && snake.at(0).y == yFood)
		{
			check_eaten = true;
			result++;
			snake.resize(snake.size() + 1);
		}
		else check_eaten = false;

		//переміщаєм координати тіла змійки
		for (size_t i = 0; i < snake.size() - 1; i++)
		{
			if (i == 0)													//Вибравши комірку, записуємо її наступну в буфер,
			{															//а тоді вибрану записуємо в наступну
				buffer1 = snake.at(static_cast<__int64>(i) + 1);		//з буфера отримуємо старе значення перезаписаної
				snake.at(static_cast<__int64>(i) + 1) = snake.at(i);
			}
			else
			{
				buffer2 = snake.at(static_cast<__int64>(i) + 1);
				snake.at(static_cast<__int64>(i) + 1) = buffer1;
				buffer1 = buffer2;
			}
		}

		//головний цикл заповнення поля
		for (int i = 0; i <= size_h; i++)
			for (int j = 0; j <= size_w; j++)
			{
				if (i == 0 || i == size_h - 1 || j == 0 || j == size_w - 1) 
					space[i][j] = wall;
				else space[i][j] = area;

				if (i == xFood && j == yFood) space[i][j] = food;

				for (size_t it = 0; it < snake.size(); it++)
					if (i == snake.at(it).x && j == snake.at(it).y)
						space[i][j] = snake_ch;
			}

		//Виводим поле
		for (int i = 0; i < size_h; i++)
		{
			for (int j = 0; j < size_w; j++)
				cout << space[i][j] << " ";
			cout << endl;
		}

		//Перевіряєм на колізію
		for (size_t it = 0; it < snake.size(); it++)
		{
			if (snake.at(it).x == 0 || snake.at(it).x == size_h - 1
				|| snake.at(it).y == 0 || snake.at(it).y == size_w - 1)
			{
				*check_gameover = true;
				cout << "GAME OVER!" << endl << "Result: " << result << endl << "Restart? press Enter: ";
				if (_getch() == 13)
				{
					system("cls");
					*check_gameover = false;
					*check_press = false;
					_interface(left, right, up, down, check_press, check_gameover);
				}
				return;
			}
			if (snake.size() > 2)
			for (size_t itt = 2; itt < snake.size(); itt++)
				if (snake.at(0).x == snake.at(itt).x && snake.at(0).y == snake.at(itt).y) 
				{
					*check_gameover = true;
					cout << "GAME OVER!" << endl << "Result: " << result << endl << "Restart? press Enter: ";
					if (_getch() == 13)
					{
						system("cls");
						*check_gameover = false;
						*check_press = false;
						_interface(left, right, up, down, check_press, check_gameover);
					}
					return;
				}
		}

		cout << "Result: " << result << endl;
		Sleep(40);
		system("cls");
	}
}

int main()
{
	bool left = false, right = false, up = false, down = true, check_press = false, check_gameover = false;	

	thread runControl(runControl, ref(left), ref(right), ref(up), ref(down), ref(check_press), ref(check_gameover));
	runControl.detach();

	_interface(&left, &right, &up, &down, &check_press, &check_gameover);

	return 0;
}