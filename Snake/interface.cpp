#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <windows.h>

#include "control.h"

using namespace std;

struct snake_struct
{
	int x;
	int y;
};

void runInterface(bool& left, bool& right, bool& up, bool& down, bool& check_press, bool& check_game_finish) {
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

	char space[26][26], wall_ch = '#', area_ch = ' ', food_ch = '@', snake_ch = '*';
	int size_h = sizeof(space) / sizeof(space[0]) - 1,
	size_w = sizeof(space[size_h]) / sizeof(space[size_h][0]) - 1,
	x_food = 0, y_food = 0, result = 0;
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
		check_press = false;

		//Надаєм рандомні координати їжі
		if (check_eaten) {
			do {
				x_food = 1 + mersenne() % (size_h - 2);
				y_food = 1 + mersenne() % (size_w - 2);
				for (size_t i = 0; i < snake.size(); i++)
					if (snake.at(i).x != x_food && snake.at(i).y != y_food)
						check_collision_generation_food = true;
			} while (!check_collision_generation_food);
			check_collision_generation_food = false;
		}

		//Перевіряємо чи зїджено їжу
		if (snake.at(0).x == x_food && snake.at(0).y == y_food)
		{
			check_eaten = true;
			result++;
			snake.resize(snake.size() + 1);

		}
		else
			check_eaten = false;

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
		{
			for (int j = 0; j <= size_w; j++)
			{
				if (i == 0 || i == size_h - 1 || j == 0 || j == size_w - 1) 
					space[i][j] = wall_ch;
				else space[i][j] = area_ch;

				if (i == x_food && j == y_food)
					space[i][j] = food_ch;
				for (size_t it = 0; it < snake.size(); it++)
					if (i == snake.at(it).x && j == snake.at(it).y)
						space[i][j] = snake_ch;
			}
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
				cout << "GAME OVER!" << endl << "Result: " << result << endl << "Press Enter for restart or ESC for exit";
				return;
			}
			if (snake.size() > 2)
				for (size_t itt = 2; itt < snake.size(); itt++) {
					if (snake.at(0).x == snake.at(itt).x && snake.at(0).y == snake.at(itt).y)
					{
						cout << "GAME OVER!" << endl << "Result: " << result << endl << "Press Enter for restart or ESC for exit";
						return;
					}
				}
		}

		cout << "Result: " << result << endl;
		Sleep(40);
		system("cls");
	}
}