#pragma once

#include"UserBoard.h"
#include "PcBoard.h"
#include "Board.h"
#include "KeyBoardManager.h"
#include "Ball.h"
#include "Screen.h"
#include "DeadBoards.h"
#include <conio.h>
#include <iostream>


class Game {
	enum { MAX_X = 80, MAX_Y = 25 };
	enum {
		BOARD_RIGHT_X = 76, BOARD_LEFT_X = 4, BOARD_RIGHT_UP = 11, BOARD_RIGHT_DOWN = 13,
		BOARD_LEFT_UP = 10, BOARD_LEFT_DOWN = 12, BALL_X = 38, BALL_Y = 10, RESTART_X_LEFT_MISS = 1,
		RESTART_X_RIGHT_MISS = -1, RESTART_X = 0, RESTART_X_LEFT_MISS_BOMB = 3,
		RESTART_X_RIGHT_MISS_BOMB=-3
	};
	enum { HUMAN, COMPUTER };
	enum { BEST = 1, GOOD, NOVICE };
	static bool isOver;
	static int IterationCounter;
	static bool IterationFlag;
	void Instructions() const;
public:
	enum { HUMAN_VS_HUMAN, HUMAN_VS_COMPUTER, COMPUTER_VS_COMPUTER };
	void run(int ind1, int ind2, int level1 = 0, int level2 = 0);
	void checkWhoMissed(Board& left, Board& right, bool flagLeft, bool flagRight, Screen& s, DeadBoards& deadBoardsLeft, DeadBoards& deadBoardsRight,bool state);
	void menu();
	int chooseLeval();
	int what_players(int ind1, int ind2);
	void setPlayers(UserBoard& ub1, UserBoard& ub2, PcBoard& pb1, PcBoard& pb2, int option, KeyboardManager& kbManager);
	void missingChecks(int ind1, int ind2, UserBoard& usboard1, UserBoard& usboard2, PcBoard& pcboard1, PcBoard& pcboard2, Ball& ball, bool&missedleft, bool&missedright,
		int level1, int level2);
};