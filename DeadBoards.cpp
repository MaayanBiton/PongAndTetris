#include "deadBoards.h"



//Once the player misses the ball we need to create a copy of it and print it according to the insructions
void DeadBoards:: printDead(Board b)
{
	int temp = 0;
	int i,j, num_of_moves = b.getX();
	//if it's right player calculate it's distance from the right wall
	if (num_of_moves > LEFT_EDGE)
		num_of_moves = EDGE_RIGHT_SCREEN - num_of_moves;

	b.erase();
	bool flag = true;

	//if the array is empty - if it's the first miss move it to the until it gets to the wall
	if (getTop() == 0)
	{
		for (i = 1; i < num_of_moves; i++)
		{	
			b.setX();			
		}
		b.draw();

	}
	else
	{
		// go through the array  
		for (i = num_of_moves; i > 1 && flag == true ; i--)
		{
		
			b.erase();

			//check if there are any other dead boards that gets in the way
			if (getPointY(i-5) > b.getDownY() || getPointY(i-5) + 2 < b.getUpY()) //if not, move it 1 step closer to the wall
			{
				b.setX();
				b.draw();				
				b.erase();
			}
			else
			{
				// calculate the distans between the last dead board and the current board
				if (b.getX() < 20)//if it's the keft player
					temp = abs((b.getX()) - ((getPointX(i - 5) + 1)));
				else
					temp = abs((b.getX()) - ((getPointX(i - 5) - 1)));

				for (j = 0; j < temp; j++) //move it ^that^ amount of times
				{
					b.setX();
					b.draw();
					b.erase();
					flag = false;
				}

			}
		
			b.draw();

		}

	}
	//insert the current board (after the movement) to the array 
	dead[top].setPoint(b.getX(), b.getUpY());
	top++;
}
