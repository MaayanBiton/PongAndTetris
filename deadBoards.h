#pragma once

#include "Board.h"

class DeadBoards
{
	enum { MAX_DEAD = 20 };
	enum { LEFT_EDGE = 20, EDGE_RIGHT_SCREEN=80};

	
	//we save all the 'dead' boards in an array that saves the top point of the board
	Point dead[MAX_DEAD];
	int top;
public:
	DeadBoards()
	{
		top = 0;
	}
	void setTop()
	{
		top++;
	}
	int getTop()
	{
		return top;
	}
	
	void printDead(Board b);
	int getPointX(int index)
	{
		return dead[index].getX();
	}
	int getPointY(int index)
	{
		return dead[index].getY();
	}
};