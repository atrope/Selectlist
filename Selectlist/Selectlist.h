#pragma once
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;
struct item {
	string name;
	bool selected;
};
class Selectlist {
private:
	COORD position;
	vector<item> list;
	int arrow;
	void updateLine(int line, int line2);
	void hideCursor(HANDLE out);
	void draw();
public:
	Selectlist(COORD pos, int opt = 3) : position(pos), arrow(0) {
		for (int i = 0; i < opt; i++) this->list.push_back({ "Option #" + to_string(i) , false });
		draw();
	};
	void goUp();
	void goDown();
	void choose();
	~Selectlist() {};
};