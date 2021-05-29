#include <thread>

#include "control.h"
#include "interface.h"

using namespace std;

int main()
{
	bool left = false, right = false, up = false, down = true, check_press = false, check_game_finish = false;
	thread runInterface(runInterface, ref(left), ref(right), ref(up), ref(down), ref(check_press));
	runInterface.detach();
	thread runControl(runControl, ref(left), ref(right), ref(up), ref(down), ref(check_press), ref(check_game_finish));
	runControl.detach();


	while (!check_game_finish);

	return 0;
}