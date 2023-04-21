#include <assert.h>
#include "resource.h"
#include "Board.h"
#include "id.h"

static map<Direction, int> directionBitMapMap = {
	{Direction::NORTH,IDB_ROBOT_NORTH},
	{Direction::SOUTH,IDB_ROBOT_SOUTH},
	{Direction::EAST,IDB_ROBOT_EAST},
	{Direction::WEST,IDB_ROBOT_WEST}
};

CBoard::CBoard(int width, int height) :
	Table(width, height)
{
	_robotTile = nullptr;
}

CBoard::~CBoard()
{
	for (auto& tile : _tiles)
	{
		delete tile;
	}
	_tiles.clear();
}

void CBoard::Create(CWnd* pParent)
{
	int x, y;
	UINT nID = ID_TILE_BUTTON;
	int width = GetWidth();
	int height = GetHeight();
	for (int row = 0; row < width; row++)
	{
		for (int col = (height -1); col >= 0; col--)
		{
			x = 10 + (row * TILE_SIZE);
			y = 10 + ((height -col-1) * TILE_SIZE);

			Coordinate coordinate(row, col);
			CTile* tile = new CTile(pParent, CPoint(x, y), coordinate, nID++);
			_tiles.push_back(tile);
		}
	}
}

void CBoard::DisplayRobot(const Robot& robot)
{
	if (robot.IsPlaced())
	{
		Coordinate coordinate = robot.GetCoordinate();

		// Find tile
		auto vtile = find_if(
			_tiles.begin(),
			_tiles.end(),
			[coordinate](const CTile* tile)
			{
				return tile->GetCoordinate() == coordinate;
			});
		VERIFY(_tiles.end() != vtile);

		Direction direction = robot.GetDirection();
		CTile* tile = (*vtile);

		auto directionBitMap = find_if(
			directionBitMapMap.begin(),
			directionBitMapMap.end(),
			[direction](const auto& it) {
				return it.first == direction;
			});
		VERIFY(directionBitMapMap.end() != directionBitMap);

		CBitmap bmp;
		VERIFY(bmp.LoadBitmap(directionBitMap->second));
		HBITMAP hbmp = HBITMAP(bmp.Detach());

		tile->SetBitmap(hbmp);
		if (nullptr != _robotTile)
		{
			if (!(_robotTile->GetCoordinate() == tile->GetCoordinate()))
			{
				// clear previous tile
				_robotTile->SetBitmap(NULL);
			}
		}
		_robotTile = tile;
	}
}

bool CBoard::IsRobotTileClicked(UINT nID)
{
	bool clicked = false;
	if (nullptr != _robotTile)
	{
		// Find tile
		auto vtile = find_if(
			_tiles.begin(),
			_tiles.end(),
			[nID](const auto tile)
			{
				return tile->GetDlgCtrlID() == nID;
			});
		VERIFY(vtile != _tiles.end());

		CTile* tile = (*vtile);
		if (tile->GetCoordinate() == _robotTile->GetCoordinate())
		{
			clicked = true;
		}
	}
	return clicked;
}
