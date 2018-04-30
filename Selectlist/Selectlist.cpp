// Selectlist.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Selectlist.h"
#include <iostream>
#include <stdlib.h>
void Selectlist::draw() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
	GetConsoleScreenBufferInfo(out, &info);
	SetConsoleCursorPosition(out, this->position);
	for (int i = 0; i < this->list.size(); i++)
		cout << ((list.at(i).selected) ? "[X] " : "[ ] ") << list.at(i).name << ((i == arrow) ? " <=" : "") << endl;
}

void Selectlist::updateLine(int line, int line2 = -1) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(out, &info);
	COORD tmppos = { this->position.X , this->position.Y + line };
	SetConsoleCursorPosition(out, tmppos);
	cout << string(info.dwSize.X, ' ');
	SetConsoleCursorPosition(out, tmppos);
	cout << "\r" << ((list.at(line).selected) ? "[X] " : "[ ] ") << list.at(line).name << ((line == arrow) ? " <=" : "");
	if (line2 >= 0) updateLine(line2);
}
void Selectlist::goUp() {
	int oldArr = arrow;
	if (arrow == 0) arrow = list.size();
	arrow = --arrow % list.size();
	updateLine(arrow, oldArr);
}
void Selectlist::goDown() {
	int oldArr = arrow;
	arrow = ++arrow % list.size();
	updateLine(arrow, oldArr);
}
void Selectlist::choose() {
	list.at(arrow).selected = !list.at(arrow).selected;
	updateLine(arrow);
}
