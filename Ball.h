#pragma once
#include "Point.h"


class Ball {
	enum {UP_RIGHT,DOWN_RIGHT,UP_LEFT,DOWN_LEFT};
	Point location;
	int dir_x = -1;
	int dir_y =1;
	int state = BALL;
	bool bombFlag = false;
	bool bigMiss = false;

public:
	Ball(Point p) : location(p) {}
	enum YDirection { DOWN, UP };
	enum XDirection { LEFT, RIGHT };
	enum {BALL,BECOMING_A_BOMB,BOMB};
	void move(int state);
	void SetState(int newstate) { state = newstate; }
	int getState()const { return state; }
	void setFlag(bool newflag) { bombFlag = newflag; }
	bool getFlag() const { return bombFlag; }
	void setBigMiss(bool newMiss) { bigMiss = newMiss; }
	bool getBigMiss() const { return bigMiss; }

	void draw()
	{
		location.draw();
	}
	int getY()const {
		return location.getY();
	}
	int getX()const {
		return location.getX();
	}
	void changeYDirection() {
		dir_y *= -1;
	}
	void changeXDirection() {
		dir_x *= -1;
	}
	Ball::YDirection getYDirection() const {
		return dir_y == 1 ? DOWN : UP;
	}
	Ball::XDirection getXDirection() const {
		return dir_x == 1 ? RIGHT : LEFT;
	}
	void ballReset();

	void Originalball(int x, int y); 
	
};