#include "utils.h"
#include "Board.h"
#include "Ball.h"

int Board::counter = 1;

//we draw the board from the bottom up
void Board::draw()
{
	Point temp = down;
	setColor(COLOR::GRAY_BACKGROUND);
	temp.draw();
	while (temp != up) {
		temp.move(0, -1);
		temp.draw();
	} 
}


//We want to know where the ball is on the screen 
Board::BallPosition Board::checkBallPosition( Ball & ball)
{
	//ball options
	enum { MISSED, CENTER_HIT, CORNER_HIT, AWAY };
	//calculate the distance between the ball x coordinate and the board x coordinate
	int X_dist =abs(ball.getX() - this->getX());

	//if it is 0 than the ball already missed the board
	if (X_dist == 0) {
		ball.SetState(Ball::BALL);
		ball.setFlag(false);
		return BallPosition::MISSED;
	}
	//if it's 1 than we need to check if it hits the board
	 if (X_dist == 1) {
	
		 if (getUpY() <= ball.getY() && getDownY() >= ball.getY()) {
			 if (ball.getState() == Ball::BECOMING_A_BOMB)
			 {
				 ball.SetState(Ball::BALL);
				 ball.setFlag(false);
			 }
			 else  if (ball.getState() == Ball::BOMB)
			 {
				 ball.setBigMiss(true);
				 ball.SetState(Ball::BALL);
				 ball.setFlag(false);
				 return BallPosition::MISSED;

			 }
			counter++;
			return BallPosition::CENTER_HIT;
		}
		else if (ball.getY() == getUpY() - 1 && ball.getYDirection() == Ball::DOWN
			  || ball.getY() == getDownY() + 1 && ball.getYDirection() == Ball::UP) {
			if (ball.getState() == Ball::BECOMING_A_BOMB)
			{
				ball.SetState(Ball::BALL);
				ball.setFlag(false);

			}
			else  if (ball.getState() == Ball::BOMB)
			{
				ball.setBigMiss(true);
				ball.SetState(Ball::BALL);
				ball.setFlag(false);
				return BallPosition::MISSED;

			}
			counter++;
			return BallPosition::CORNER_HIT;
		}

	}
	return BallPosition::AWAY;
}

//Once we got the ball's position we need to change it's direction
bool Board:: switchBallPosition( Ball& ball,bool flag )
{

	Board::BallPosition state;
	state = checkBallPosition(ball);

	switch (state) {
	case Board::BallPosition::AWAY:
		break;
	case Board::BallPosition::MISSED:
		flag = true;
		break;
	case Board::BallPosition::CORNER_HIT:
		ball.changeXDirection();
		ball.changeYDirection();
		break;
	case Board::BallPosition::CENTER_HIT:
		ball.changeXDirection();
		break;
	}
	return flag;
}



void Board::erase()
{
	up.erase();
	up.move(0, 1);
	up.erase();
	up.move(0, -1);
	down.erase();
}


void Board:: setX()
{
	int x = getX();
	//if it's the left board
	if (x< 20)
	{
		up.move_x(-1);
		down.move_x(-1);
	}
	else
	{
		up.move_x(1);
		down.move_x(1);
	}
}
