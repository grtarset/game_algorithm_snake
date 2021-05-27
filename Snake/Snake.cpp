#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <vector>

#include "control.h"

using namespace std;

struct snake_struct
{
	int x;
	int y;
};

//Функція для реалізації затримки стирання поля
void delay(int ms)
{
	int c = clock() + ms;
	while (clock() < c);
}

void restart(bool& left, bool& right, bool& up, bool& down, bool& check_press, bool& check_restart);

void runInterface(bool& left, bool& right, bool& up, bool& down, bool& check_press, bool& check_restart) {
	random_device rd;
	mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

	//ініціалізація масиву ігрового поля та його розмірів
	char space[26][26];
	int size_h = sizeof(space) / sizeof(space[0]) - 1;
	int size_w = sizeof(space[size_h]) / sizeof(space[size_h][0]) - 1;

	int xFood = 0, yFood = 0;						//ініціалізуєм координати їжі
	bool check_eaten = true;						//перевірку з'їдження згенерованої їжі змійкою
	bool check_collision_generation_food = false;	//та перевірку при генерації їжі колізії з тілом змійки

	int result = 0;

	vector<snake_struct> snake;
	snake_struct buffer1;
	snake_struct buffer2;

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
				xFood = 1 + mersenne() % (size_h - 2);
				yFood = 1 + mersenne() % (size_w - 2);
				for (int i = 0; i < snake.size(); i++) 
					if (snake.at(i).x == xFood && snake.at(i).y != yFood)
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
		else
			check_eaten = false;

		//переміщаєм координати тіла змійки
		for (int i = 0; i < snake.size() - 1; i++)
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
					if (i == 0 || i == size_h - 1 || j == 0 || j == size_w - 1) //заповнюєм стінки 
					space[i][j] = '#';
				else //поля та простір всередині
					space[i][j] = ' ';

				if (i == xFood && j == yFood) //позначаєм на полі їжу
					space[i][j] = '@';
				for (int it = 0; it < snake.size(); it++)
				{
					if (i == snake.at(it).x && j == snake.at(it).y) //позначаєм на полі змійку
						space[i][j] = '*';
				}
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
		for (int it = 0; it < snake.size(); it++) 
		{
			if (snake.at(it).x == 0 || snake.at(it).x == size_h - 1
				|| snake.at(it).y == 0 || snake.at(it).y == size_w - 1)
			{
				cout << "GAME OVER!" << endl << "Result: " << result << endl;
				cout << "Restart? press 'r' (wait 2 sec): ";
				delay(2000);
				if (check_restart)
				{
					check_restart = false;
					check_press = false;
					restart(ref(left), ref(right), ref(up), ref(down), ref(check_press), ref(check_restart));
				}
				return;
			}
			if (snake.size() > 2)
			for (int itt = 2; itt < snake.size(); itt++) {
				if (snake.at(0).x == snake.at(itt).x && snake.at(0).y == snake.at(itt).y) 
				{
					cout << "GAME OVER!" << endl << "Result: " << result << endl;
					cout << "Restart? press 'r' (wait 2 sec): ";
					delay(2000);
					if (check_restart)
					{
						check_restart = false;
						check_press = false;
						restart(ref(left), ref(right), ref(up), ref(down), ref(check_press), ref (check_restart));
					}
					return;
				}
			}
		}

		cout << "Result: " << result << endl;
		delay(70);
		system("cls");
	}
}

void restart(bool& left, bool& right, bool& up, bool& down, bool& check_press, bool& check_restart) {
	thread runInterface(runInterface, ref(left), ref(right), ref(up), ref(down), ref(check_press), ref(check_restart));	//запускаєм основний потік з інферфейсом та алгоритмом
	runInterface.join();
}

int main()
{
	bool left = false, right = false, up = false, down = true, check_press = false, check_restart = false;					//створюєм перевірки для фіксації напрямку руху змійки
	thread runInterface(runInterface, ref(left), ref(right), ref(up), ref(down), ref(check_press), ref(check_restart));	//запускаєм основний потік з інферфейсом та алгоритмом
	thread runControl(runControl, ref(left), ref(right), ref(up), ref(down), ref(check_press), ref(check_restart));		//запускаєм потік з керуванням змійкою за допомогою клавіатури
	runControl.join();
	runInterface.join();

	return 0;
}