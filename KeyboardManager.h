#pragma once

#include <list>
#include "Board.h"
#include "UserBoard.h"

//Taken from Amir's class
class KeyboardManager {
	
	enum {NUM_CHARS = 26};
	// an array of 'char' => list of kbListener
	std::list<UserBoard*> kbListeners[NUM_CHARS];

	// helper method - get index in array per a given char
	int getIndex(char c) {
		int index = c - 'a';
		if (index < 0 || index >= NUM_CHARS) {
			index = c - 'A';
			if (index < 0 || index >= NUM_CHARS) {
				return -1;
			}
		}
		return index;
	}
public:
	void registerKbListener(UserBoard* pKbListener);
	void handleKeyboard(Ball& ball);
};