#include "Game.h"
bool Game::isOver = false;
bool Game::IterationFlag = true;
 int Game:: IterationCounter=1;

void Game::run(int ind1, int ind2, int level1, int level2) {

	DeadBoards left, right;
	hideConsoleCursor();
	//place the board according to instructions

	KeyboardManager kbManager;
	bool missedleft = false;
	bool missedright = false;

	UserBoard usboard1({ BOARD_LEFT_X,BOARD_LEFT_UP,'#' }, { BOARD_LEFT_X, BOARD_LEFT_DOWN, '#' }, "qas");
	UserBoard usboard2({ BOARD_RIGHT_X,BOARD_RIGHT_UP,'#' }, { BOARD_RIGHT_X,BOARD_RIGHT_DOWN,'#' }, "plk");

	PcBoard pcboard1({ BOARD_LEFT_X,BOARD_LEFT_UP,'#' }, { BOARD_LEFT_X, BOARD_LEFT_DOWN, '#' });
	PcBoard pcboard2({ BOARD_RIGHT_X,BOARD_RIGHT_UP,'#' }, { BOARD_RIGHT_X,BOARD_RIGHT_DOWN,'#' });

	Ball ball({ BALL_X ,BALL_Y, 'O' });
	Screen s;
	s.draw();
	int playerOption;
	//int state =Ball:: BALL;


	playerOption = what_players(ind1, ind2);
	setPlayers(usboard1, usboard2, pcboard1, pcboard2, playerOption, kbManager);

	


	while (!isOver)
	{

		while (!missedleft && !missedright)
		{
			for (int i = 0; i < 10; ++i)//Get users keyboard input
			{
				kbManager.handleKeyboard(ball);
				Sleep(10);
			}

			if (ball.getFlag() && (IterationCounter)% 8!=0&& IterationFlag) {
			
                //counter		
				IterationCounter++;
				ball.SetState(Ball::BECOMING_A_BOMB);

			}

			else if (ball.getFlag() &&(IterationCounter)%8==0)
			{
				ball.SetState(Ball::BOMB);
				//state = Ball::BOMB;
				IterationFlag = false;
				IterationCounter = 1;
			}
			
				ball.draw();
			
			//change ball direction if needed
				missingChecks(ind1, ind2, usboard1, usboard2, pcboard1, pcboard2, ball, missedleft, missedright,
					level1, level2);

			ball.move(ball.getState());
		}

		//if somebody missed the ball

		ball.ballReset();//stop the ball
		ball.Originalball(BALL_X, BALL_Y);

		if (playerOption == HUMAN_VS_HUMAN)
		{
			checkWhoMissed(usboard1, usboard2, missedleft, missedright, s, left, right,ball.getBigMiss());
		}
		else if (playerOption == HUMAN_VS_COMPUTER)
		{
			checkWhoMissed(usboard1, pcboard2, missedleft, missedright, s, left, right,ball.getBigMiss());

		}
		else
		{
			checkWhoMissed(pcboard1, pcboard2, missedleft, missedright, s, left, right,ball.getBigMiss());
		}

		missedleft = false;
		missedright = false;

	}
}



//When one player misses we need to check who missed
void Game::checkWhoMissed(Board& left, Board& right, bool flagLeft, bool flagRight, Screen& s, DeadBoards& deadBoardsLeft, DeadBoards& deadBoardsRight, bool state)
{
	//if the left player miss and it's less than 20 misses 
	if (flagLeft == true && left.getX() != 20 && right.getX() != 60)
	{			
		//print the current dead board and restart the original positions 

		deadBoardsLeft.printDead(left);
		if (state)
		{
			left.OriginalBoard(RESTART_X_LEFT_MISS_BOMB, BOARD_LEFT_UP, BOARD_LEFT_DOWN);
			s.check_max_left(3);
		}
		else
		{
			s.check_max_left(1);

		}
		left.OriginalBoard(RESTART_X_LEFT_MISS, BOARD_LEFT_UP, BOARD_LEFT_DOWN);
		left.draw();
		right.erase();
		right.OriginalBoard(RESTART_X, BOARD_RIGHT_UP, BOARD_RIGHT_DOWN);
		right.draw();

		IterationFlag = true;
	}

	//if the right player miss and it's less than 20 misses 
	else if (flagRight == true && right.getX() != 60 && left.getX() != 20)
	{
		deadBoardsRight.printDead(right);
		if (state)
		{
			right.OriginalBoard(RESTART_X_RIGHT_MISS_BOMB, BOARD_RIGHT_UP, BOARD_RIGHT_DOWN);
			s.check_max_right(3);

		}
		else
		{
			s.check_max_right(1);

		}
		right.OriginalBoard(RESTART_X_RIGHT_MISS, BOARD_RIGHT_UP, BOARD_RIGHT_DOWN);
		right.draw();
		left.erase();
		left.OriginalBoard(RESTART_X, BOARD_LEFT_UP, BOARD_LEFT_DOWN);
		left.draw();

		IterationFlag = true;
	}

	else
	{
		isOver = true;
		system("cls");
	}
}

//print the menu
void Game::menu()
{

	int level1 = 0;
	int level2 = 0;

	char ch;

	gotoxy(MAX_X / 2, MAX_Y / 2);
	system("Color E");
	cout << "MENU\n";

	gotoxy(MAX_X / 3, (MAX_Y / 2) + 2);
	cout << "New game - Human vs Human - press 1" << endl;
	gotoxy(MAX_X / 3, (MAX_Y / 2) + 3);
	cout << "New game - Human vs Computer - press 2" << endl;
	gotoxy(MAX_X / 3, (MAX_Y / 2) + 4);
	cout << "New game - Computer vs Computer - press 3" << endl;
	gotoxy(MAX_X / 3, (MAX_Y / 2) + 5);
	cout << "Instructions and keys - press 8" << endl;
	gotoxy(MAX_X / 3, (MAX_Y / 2) + 6);
	cout << "Exit - press 9" << endl;

	ch = _getch();

	switch (ch)
	{
	case'1':
		system("cls");
		run(HUMAN, HUMAN);
		break;

	case'2':
		system("cls");
		gotoxy(MAX_X / 2, (MAX_Y / 2) - 2);
		cout << "choose the computer's level";
		level1 = chooseLeval();
		system("cls");
		run(HUMAN, COMPUTER, level1);
		break;

	case'3':
		system("cls");
		gotoxy(MAX_X / 2, (MAX_Y / 2) - 2);
		cout << "choose the  right computer's level";
		level1 = chooseLeval();
		system("cls");
		gotoxy(MAX_X / 2, (MAX_Y / 2) - 2);
		cout << "choose left computer's level";
		level2 = chooseLeval();
		system("cls");
		run(COMPUTER, COMPUTER, level1, level2);
		break;

	case '8':
		system("cls");
		Instructions();
		system("cls");
		break;
	case '9':
		isOver = true;
		break;
	};
}



int Game::chooseLeval() {

	char ch;

	gotoxy(MAX_X / 2, MAX_Y / 2);
	system("Color E");
	cout << "WHAT LEVEL ARE YOU ?\n";

	gotoxy(MAX_X / 3, (MAX_Y / 2) + 2);
	cout << "BEST - press 1" << endl;
	gotoxy(MAX_X / 3, (MAX_Y / 2) + 3);
	cout << "GOOD - press 2" << endl;
	gotoxy(MAX_X / 3, (MAX_Y / 2) + 4);
	cout << "NOVICE- press 3" << endl;

	ch = _getch();

	switch (ch)
	{

	case '1':
		return BEST;
		break;

	case '2':
		return GOOD;
		break;

	case '3':
		return NOVICE;
		break;

	};
	return 0;
}


void Game::Instructions() const
{

	char key;

	setColor(COLOR::RED_TEXT);
	cout << "Dear examiner!" << endl << endl;

	setColor(COLOR::TEAL_TEXT);

	cout << "Your goal is to hit the ball with the board." << endl <<
		"Once you miss the ball a copy of your board will appear at the edge of the wall" << endl <<
		"and the new position of the board will go 'up' by one," << endl << "making him one step closer to losing." <<
		"When you get to 20 disqualification you lose and the game will be over." << endl <<
		"The new improved version offers you the option to set a BOMB!" << endl << "Once you press the bomb key you have 8 ball movements" <<
		endl << " to return the bomb to a regular ball by catching it befor it turns red." << endl << "If you hit the bomb when its red your player will move 3 steps closer to the middle " <<
		endl << endl;

	setColor(COLOR::GREEN_TEXT);

		cout << "REMEMBER -  STAY AWAY FROM THE BOMB !!! " << endl << endl;
	
	setColor(COLOR::WHITE_TEXT);

	cout << "KEYBOARD:" << endl;

	setColor(COLOR::GRAY_TEXT);

	cout << "Right player: up - p/P" << endl << "	    down - l/L" <<endl<< "	    set a bomb - k/K" << endl;

	cout << "Left player: up - q/Q" << endl << "	    down - a/A" <<endl<<  "	    set a bomb - s/S"  <<endl << endl;

	setColor(COLOR::PINK_TEXT);
	cout << "Good Luck" << endl << "WE HAVE FAITH IN YOU!" << endl << endl << endl;

	setColor(COLOR::YELLOW_TEXT);

	cout << "press 0 and enter to return to start playing" << endl;

	cin >> key;
	return;
}

int Game::what_players(int ind1, int ind2)
{
	//check what game players option

	if (ind1 == HUMAN && ind2 == HUMAN) {
		return HUMAN_VS_HUMAN;
	}
	else if (ind1 == HUMAN && ind2 == COMPUTER) {
		return HUMAN_VS_COMPUTER;
	}
	else {
		return COMPUTER_VS_COMPUTER;
	}
}

void Game::setPlayers(UserBoard& ub1, UserBoard& ub2, PcBoard& pb1, PcBoard& pb2, int option, KeyboardManager& kbManager)
{
	//if both players are human draw them and register each one to the Keyboard Manager
	if (option == HUMAN_VS_HUMAN)
	{
		ub1.draw();
		kbManager.registerKbListener(&ub1);
		ub2.draw();
		kbManager.registerKbListener(&ub2);

	}

	//if one of the players is human draw them and register it to the Keyboard Manager
	else if (option == HUMAN_VS_COMPUTER)
	{
		ub1.draw();
		kbManager.registerKbListener(&ub1);
		pb2.draw();

	}
	else
	{
		pb1.draw();
		pb2.draw();
	}
}

void Game::missingChecks(int ind1, int ind2, UserBoard& usboard1, UserBoard& usboard2, PcBoard& pcboard1, PcBoard& pcboard2,Ball& ball,bool&missedleft,bool&missedright,
	int level1,int level2)
{
	//if the left player is human check if he missed the ball
	if (ind1 == HUMAN) {

		missedleft = usboard1.switchBallPosition(ball, missedleft);

		//if the right player is human check if he missed the ball
		if (ind2 == HUMAN)
		{
			missedright = usboard2.switchBallPosition(ball, missedright);
		}

		//if the right player is a computer we disqualify according to the chosen level 
		else
		{
			if (ball.getX() == (pcboard2.getX() - 16))
			{
				if ((level1 == 2 && ((Board::get_counter()) % 40 != 0)) ||
					(level1 == 3 && ((Board::get_counter()) % 10 != 0)) ||
					level1 == 1)
				{
					pcboard2.CalcPosRight(ball);
				}
			}
			missedleft = pcboard2.switchBallPosition(ball, missedleft);
		}
	}
	else
	{
		//if both players are computer disqualify each one according to its chosen level
		if (ball.getX() == (pcboard1.getX() + 16))
		{
			if ((level2 == 2 && ((Board::get_counter()) % 41 != 0)) ||
				(level2 == 3 && ((Board::get_counter()) % 11 != 0)) ||
				level2 == 1)
			{
				pcboard1.CalcPosLeft(ball);
			}

		}

		else if (ball.getX() == (pcboard2.getX() - 16))
		{
			if ((level1 == 2 && ((Board::get_counter()) % 40 != 0)) ||
				(level1 == 3 && ((Board::get_counter()) % 10 != 0)) ||
				level1 == 1)
			{
				pcboard2.CalcPosRight(ball);
			}
		}
		missedleft = pcboard1.switchBallPosition(ball, missedleft);
		missedright = pcboard2.switchBallPosition(ball, missedright);
	}
}