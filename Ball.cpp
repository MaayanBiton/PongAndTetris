#include "Ball.h"
#include "Screen.h"

//Move the ball according to it's direction
void Ball::move(int state)
{
	if (Screen::isOn_X_Edge(location)) {
		dir_y *= -1;
	}
	if (Screen::isOn_Y_Edge(location)) {
		dir_x *= -1;
	}

	location.erase();
	location.move(dir_x, dir_y);
	if (state == BECOMING_A_BOMB) {
		setColor(COLOR::YELLOW_BACKGROUND);
	}
	else if (state == BOMB) {
		setColor(COLOR::RED_BACKGROUND);
	}
	else {
		setColor(COLOR::WHITE_BACKGROUND);
	}
	location.draw();
}

//When one player misses the ball we want to erase it from the screen
void Ball:: ballReset() {
	location.erase();
	dir_x = 0;
	dir_y = 0;
}


//When one player misses we need the ball to move again randomly
void Ball::Originalball(int x, int y)
{
	location.setBall(x, y);
	int dir = rand() % 4;
	if (dir == UP_LEFT)
	{
		dir_x = -1;
		dir_y = -1;
	}
	 else if (dir == DOWN_LEFT)
	{
		dir_x = -1;
		dir_y = 1;
	}
	else if (dir == UP_RIGHT)
	{
		dir_x = 1;
		dir_y = -1;
	}
	else if (dir == DOWN_RIGHT)
	{
		dir_x = 1;
		dir_y = 1;
	}
}
