#pragma once

#include <map>
#include <vector>
#include "Tile.h"
#include "robot.hpp"

using namespace std;

class CBoard
{
public:
	CBoard(int);
	~CBoard();
	void Create(CWnd*);
	void DisplayRobot(const Robot&);
private:
	int _size;
	vector<CTile*> _tiles;
	CTile* _prevTile; // for clearing
};
