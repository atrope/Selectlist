// stdafx.cpp : source file that includes just the standard includes
// Selectlist.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information
#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include "Selectlist.h"
#include <string>
#include <iostream>
using namespace std;
int main(int argc, char** argv) {
	const int options = 20;
	const COORD pos = { 0,0 };
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
	Selectlist sl(pos, options);
	INPUT_RECORD ir;
	DWORD count;
	while (ReadConsoleInput(in, &ir, 1, &count)) {
		if (ir.Event.KeyEvent.bKeyDown) {
			if ((GetKeyState(VK_UP) & 0x8000)) sl.goUp();
			else if ((GetKeyState(VK_DOWN) & 0x8000)) sl.goDown();
			else if ((GetKeyState(VK_SPACE) & 0x8000)) sl.choose();
			else if ((GetKeyState(VK_ESCAPE) & 0x8000)) break;
		}
	}
	return 0;
}
