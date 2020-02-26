#pragma once
#include "Board.h"
#include "Ball.h"



class PcBoard: public Board {
	enum {TOP_WALL=4,BOTTOM_WALL=24};

	public:
		PcBoard(const Point& p1, const Point& p2) : Board(p1, p2) {}
		void CalcPosLeft(const Ball& ball_pos);
		void movePcPlayer(int y);
		int boardDir(int y);
		void moveXiteration(int itr,int dir);
		void CalcPosRight(const Ball& ball_pos);

};