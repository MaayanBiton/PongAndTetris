#pragma once

#include <iostream>
#include "utils.h"

class Point {
	int x, y;
	char ch;
	void draw(char c) {
		gotoxy(x, y);
		std::cout << c;
	}
	friend class Screen;

public:
	Point() :x(0), y(0),ch('#') {}
	Point(int x1, int y1, char c): x(x1), y(y1), ch(c) {}
	void move(int dir_x, int dir_y) {
		x += dir_x;
		y += dir_y;
	}
	void draw() {
		draw(ch);
	}
	void erase() {
		setColor(COLOR::BLACK_BACKGROUND);
		draw(' ');
	}
	int getX()const {
		return x;
	}
	int getY()const {
		return y;
	}
	bool operator!=(const Point& other) const {
		return x != other.x || y != other.y;
	}

	void setBoard(int key,int changeY) {
		x += key;
		y = changeY;
	}
	void setBall(int changeX, int changeY) {
		x = changeX;
		y = changeY;
	}
	void move_x(int new_x)
	{
		x += new_x;
	}

	void setPoint (int x1,int y1) {
		x = x1;
		y = y1;

	}
};