#include "PcBoard.h"


void PcBoard::CalcPosLeft(const Ball& ball_pos) {
	int numOfMoves1 = 0, numOfMoves2 = 0;
	int hitX = 0, hitY = 0;


	//if the ball direction is left up 
	if (!(ball_pos.getXDirection()) && ball_pos.getYDirection())
	{

		// check the option that the ball doesnt touch the up wall
		numOfMoves1 = (ball_pos.getY()) - TOP_WALL;
		hitX = (ball_pos.getX()) - numOfMoves1;
		if (hitX <= getX())
		{
			numOfMoves2 = getX() - hitX + 1;
			numOfMoves1 -= numOfMoves2;
			hitY = (ball_pos.getY()) - numOfMoves1;
			movePcPlayer(hitY);

		}
		else {
			numOfMoves2 = hitX - (getX() + 1);
			hitY = TOP_WALL + numOfMoves2;
			//move + check up or down
			movePcPlayer(hitY);
		}
	}

	//if the ball direction is left down
	else if (!(ball_pos.getXDirection()) && !(ball_pos.getYDirection()))
	{
		numOfMoves1 = BOTTOM_WALL - (ball_pos.getY());
		hitX = (ball_pos.getX()) - numOfMoves1;

		if (hitX <= getX())
		{

			numOfMoves2 = getX() - hitX + 1;
			numOfMoves1 -= numOfMoves2;
			hitY = (ball_pos.getY()) + numOfMoves1;
			movePcPlayer(hitY);
		}

		else {
			// check the option that the ball doesnt touch the down wall

			numOfMoves2 = hitX - (getX() + 1);
			hitY = BOTTOM_WALL - numOfMoves2;
			//move + check up or down
			movePcPlayer(hitY);
		}

	}

}



void PcBoard::CalcPosRight(const Ball& ball_pos) {

	int numOfMoves1 = 0, numOfMoves2 = 0;
	int hitX = 0, hitY = 0;



	//if the ball direction is up right  
	if (((ball_pos.getXDirection()) && ball_pos.getYDirection()))
	{

		// check the option that the ball doesnt touch the up wall
		numOfMoves1 = (ball_pos.getY()) - TOP_WALL;
		hitX = (ball_pos.getX()) + numOfMoves1;

		if (hitX > getX())
		{
			numOfMoves2 = hitX + 1 - getX();
			numOfMoves1 -= numOfMoves2;
			hitY = (ball_pos.getY()) - numOfMoves1;
			movePcPlayer(hitY);

		}
		else {

			numOfMoves2 = (getX() - 1) - hitX;
			hitY = TOP_WALL + numOfMoves2;
			//move + check up or down
			movePcPlayer(hitY);
		}



	}

	else if ((ball_pos.getXDirection()) && !(ball_pos.getYDirection()))
	{

		numOfMoves1 = BOTTOM_WALL - (ball_pos.getY());
		hitX = (ball_pos.getX()) + numOfMoves1;

		if (hitX > getX())
		{

			numOfMoves2 = hitX + 1 - getX();
			numOfMoves1 -= numOfMoves2;
			hitY = (ball_pos.getY()) + numOfMoves1;
			movePcPlayer(hitY);
		}

		else {
			// check the option that the ball doesnt touch the down wall

			numOfMoves2 = getX() - 1 - hitX;
			hitY = BOTTOM_WALL - numOfMoves2;
			//move + check up or down
			movePcPlayer(hitY);
		}

	}


}


void PcBoard::movePcPlayer(int y) {
	int dir = 0;
	int numOfIteration = 0;


	if (boardDir(y) == -1)
	{
		//move up
		dir=boardDir(y);
		numOfIteration = getUpY() - y  ;
		moveXiteration(numOfIteration, dir);
	

	}
	else {
		//move down
		dir = boardDir(y);
		numOfIteration = y - getDownY() ;
		moveXiteration(numOfIteration, dir);
	}
}


int PcBoard::boardDir(int y) {

	if (y < getUpY())
	{
		return -1;
	}
	else if (y > getDownY())
	{
		return 1;
	}

	return 0;

}

void PcBoard::moveXiteration(int itr,int dir) {
	int i;

	for ( i = 0; i < itr; i++)
	{
		//move up
		if (dir==-1) {
			down.erase();
			down.move(0, -1);
			up.move(0, -1);
			setColor(COLOR::GRAY_BACKGROUND);
			up.draw();
		}
		
		//move down
		else if (dir == 1) {
			up.erase();
			up.move(0, 1);
			down.move(0, 1);
			setColor(COLOR::GRAY_BACKGROUND);
			down.draw();
		}
		else return;
	}

}

