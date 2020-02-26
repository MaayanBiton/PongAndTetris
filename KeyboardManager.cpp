#include <conio.h>
#include "KeyboardManager.h"

//Taken from Amir's class

void KeyboardManager::registerKbListener(UserBoard * pKbListener)
{
	const char * chars = pKbListener->getKbChars();
	size_t numCharToRegister = strlen(chars);
	for (size_t i = 0; i < numCharToRegister; ++i) {
		int index = getIndex(chars[i]);
		if (index != -1) {
			kbListeners[index].push_back(pKbListener);
		}
	}
}

void KeyboardManager::handleKeyboard(Ball& ball)
{
	if (_kbhit()) {
		char k = tolower(_getch());
		int index = getIndex(k);
		if (index != -1) {
			for (auto pKbListener : kbListeners[index]) {
				pKbListener->handleKey(k,ball);
			}
		}
	}
}
