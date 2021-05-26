#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include <thread>
#include <vector>

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

void runInterface(bool& left, bool& right, bool& up, bool& down, bool& check_press) {
	//ініціалізація масиву ігрового поля та його розмірів
	char space[26][26];
	int size_h = sizeof(space) / sizeof(space[0]) - 1;
	int size_w = sizeof(space[size_h]) / sizeof(space[size_h][0]) - 1;

	int xFood = 0, yFood = 0; //ініціалізуєм координати їжі
	bool check = true;
	bool check1 = false;

	std::random_device rd;
	std::mt19937 mersenne(rd()); // инициализируем Вихрь Мерсенна случайным стартовым числом 

	int result = 0;

	vector<snake_struct> snake;
	snake_struct buffer1;
	snake_struct buffer2;
	snake.resize(2);

	snake.at(0).x = 4;
	snake.at(0).y = 4;

	while (true) {
		//Міняєм координати головки змійки
			if (left && snake.at(0).y > 0) --snake.at(0).y;
			else if (right && snake.at(0).y < size_w - 1) ++snake.at(0).y;
			else if (up && snake.at(0).x > 0) --snake.at(0).x;
			else if (down && snake.at(0).x < size_h - 1) ++snake.at(0).x;
			check_press = false;

		//Надаєм рандомні координати їжі
		if (check) {
			do {
				xFood = 1 + mersenne() % (size_h - 2);
				yFood = 1 + mersenne() % (size_w - 2);
				for (int i = 0; i < snake.size(); i++) 
					if (snake.at(i).x == xFood && snake.at(i).y != yFood)
						check1 = true;
			} while (!check1);
			check1 = false;
		}

		//Перевіряємо чи зїджено їжу
		if (snake.at(0).x == xFood && snake.at(0).y == yFood)
		{
			check = true;
			result++;
			snake.resize(snake.size() + 1);

		}
		else
			check = false;

		//переміщаєм координати тіла змійки
		for (int i = 0; i < snake.size() - 1; i++)
		{
			if (i == 0)
			{
				buffer1 = snake.at(static_cast<__int64>(i) + 1);
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

		for (int it = 0; it < snake.size(); it++) 
		{
			if (snake.at(it).x == 0 || snake.at(it).x == size_h - 1
				|| snake.at(it).y == 0 || snake.at(it).y == size_w - 1)
			{
				cout << "GAME OVER!" << endl << "Result: " << result << endl;
				system("pause");
			}
			if (snake.size() > 2)
			for (int itt = 2; itt < snake.size(); itt++) {
				if (snake.at(0).x == snake.at(itt).x && snake.at(0).y == snake.at(itt).y) 
				{
					cout << "GAME OVER!" << endl << "Result: " << result << endl;
					system("pause");
				}
			}
		}

		cout << "Result: " << result << endl;
		delay(70);
		system("cls");
	}
}

//Зчитуєм натискання клавіші в іншому потоці
void runControl(bool& left, bool& right, bool& up, bool& down, bool& check_press) {
	char ch;
	while(true) {
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
	}
}

int main()
{
	bool left = false, right = false, up = false, down = true, check_press = false;
	thread runInterface(runInterface, ref(left), ref(right), ref(up), ref(down), ref(check_press));
	thread runControl(runControl, ref(left), ref(right), ref(up), ref(down), ref(check_press));
	runControl.join();
	runInterface.join();

	return 0;
}