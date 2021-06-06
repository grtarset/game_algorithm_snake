#include <iostream>
#include <conio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

using namespace std;

struct snake_struct
{
	int x;
	int y;
};

enum Control { STOP = 0, UP = 72, LEFT = 75, DOWN = 80, RIGHT = 77 };
Control ctr = STOP;

char space[26][26], wall_ch = '#', area_ch = ' ', food_ch = '@', snake_ch = '*';
int size_h = sizeof(space) / sizeof(space[0]) - 1,
size_w = sizeof(space[size_h]) / sizeof(space[size_h][0]) - 1,
x_food = 0, y_food = 0, result = 0, key = 0;
bool check_eaten = true, check_collision_generation_food = false,  game_over = false;

vector<snake_struct> snake;
snake_struct buffer1, buffer2;

void draw()
{
	system("cls");
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

		for (int i = 0; i < size_h; i++)
		{
			for (int j = 0; j < size_w; j++)
				cout << space[i][j] << " ";
			cout << endl;
		}
}

void input()
{
	if(_kbhit())
      	{
		key = _getch();
        	switch(key)
		{
	        	case UP:
			ctr = UP;
        		break;
	        	case LEFT:
			ctr = LEFT;
       	 		break;
	        	case DOWN:
			ctr = DOWN;
        		break;
	        	case RIGHT:
			ctr = RIGHT;
        		break;
        	}
        }
}

void logic()
{
   if (ctr == LEFT && ctr != RIGHT && snake.at(0).y > 0) --snake.at(0).y;
		else if (ctr == RIGHT && ctr != LEFT && snake.at(0).y < size_w - 1) ++snake.at(0).y;
		else if (ctr == UP && ctr != DOWN && snake.at(0).x > 0) --snake.at(0).x;
		else if (ctr == DOWN && ctr != UP && snake.at(0).x < size_h - 1) ++snake.at(0).x;

		if (check_eaten) {
			do {
				x_food = rand() % (size_h - 2) + 1;
				y_food = rand() % (size_w - 2) + 1;
				for (size_t i = 0; i < snake.size(); i++)
					if (snake.at(i).x != x_food && snake.at(i).y != y_food)
						check_collision_generation_food = true;
			} while (!check_collision_generation_food);
			check_collision_generation_food = false;
		}

		if (snake.at(0).x == x_food && snake.at(0).y == y_food)
		{
			check_eaten = true;
			result++;
			snake.resize(snake.size() + 1);

		}
		else
			check_eaten = false;

		for (size_t i = 0; i < snake.size() - 1; i++)
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

		for (size_t it = 0; it < snake.size(); it++)
		{
			if (snake.at(it).x == 0 || snake.at(it).x == size_h - 1
				|| snake.at(it).y == 0 || snake.at(it).y == size_w - 1)
			{
				cout << "\nGAME OVER!" << endl << "Result: " << result << endl;
				game_over = true;
				return;
			}
			if (snake.size() > 2)
				for (size_t itt = 2; itt < snake.size(); itt++) {
					if (snake.at(0).x == snake.at(itt).x && snake.at(0).y == snake.at(itt).y)
					{
						cout << "\nGAME OVER!" << endl << "Result: " << result << endl;
						game_over = true;
						return;
					}
				}
		}
}

int main() {
	srand(time(NULL));

	snake.resize(2);
	snake.at(0).x = size_h / 2;
	snake.at(0).y = size_w / 2;
	while(!game_over)
  	{
   		draw();
		Sleep(40);
      		input();
		logic();
    	}
	return 0;
}
