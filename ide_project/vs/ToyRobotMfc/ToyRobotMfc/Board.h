#pragma once

#include <map>
#include <vector>
#include "table.hpp"
#include "Tile.h"
#include "robot.hpp"

using namespace std;

class CBoard : public Table
{
public:
	CBoard(int,int);
	virtual ~CBoard();
	void Create(CWnd*);
	void DisplayRobot(const Robot&);
	bool IsRobotTileClicked(UINT);
private:
	vector<CTile*> _tiles;
	CTile* _robotTile; // for clearing
};
