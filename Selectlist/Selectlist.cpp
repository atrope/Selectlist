// Selectlist.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Selectlist.h"
#include <iostream>
#include <stdlib.h>
void Selectlist::draw() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	hideCursor(out);
	SetConsoleCursorPosition(out, this->position);
	for (size_t  i = 0; i < this->list.size(); i++)
		cout << ((list.at(i).selected) ? "[X] " : "[ ] ") << list.at(i).name << ((i == arrow) ? " <=" : "") << endl;
}

void Selectlist::hideCursor(HANDLE out) { // Hide the cursor as we dont use it
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Selectlist::updateLine(int line, int line2 = -1) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info); // Get the number of cols so we can clear it
	COORD tmppos = { static_cast<short>(this->position.X), static_cast<short>(this->position.Y + line) };
	SetConsoleCursorPosition(out, tmppos); 
	cout << string(info.dwSize.X, ' '); // Clear line
	SetConsoleCursorPosition(out, tmppos); //refresh Cursor position so we can write in  right place
	cout << "\r" << ((list.at(line).selected) ? "[X] " : "[ ] ") << list.at(line).name << ((line == arrow) ? " <=" : "");
	if (line2 >= 0) updateLine(line2); // If we received 2 lines, send it to update also
}
void Selectlist::goUp() { //Move arrow up
	int oldArr = arrow;
	if (arrow == 0) arrow = list.size();
	arrow = --arrow % list.size();
	updateLine(arrow, oldArr);
}
void Selectlist::goDown() { // move arrow down
	int oldArr = arrow;
	arrow = ++arrow % list.size();
	updateLine(arrow, oldArr);
}
void Selectlist::choose() { // choose option
	list.at(arrow).selected = !list.at(arrow).selected;
	updateLine(arrow);
}
