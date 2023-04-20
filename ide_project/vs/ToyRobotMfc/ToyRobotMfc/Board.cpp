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

CBoard::CBoard(int size):
	_size(size)
{
	_prevTile = nullptr;
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
	for (int col = 0; col < _size; col++)
	{
		for (int row = (_size-1); row >= 0; row--)
		{
			x = 10 + (col * TILE_SIZE);
			y = 10 + ((_size-row-1) * TILE_SIZE);

			CTile* tile = new CTile(pParent, CPoint(x, y), col, row, nID++);
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

		VERIFY(nullptr  != *vtile);

		Direction direction = robot.GetDirection();
		CTile* tile = (*vtile);

		auto directionBitMap = find_if(
			directionBitMapMap.begin(),
			directionBitMapMap.end(),
			[direction](const auto& it) {
				return it.first == direction;
			});
		VERIFY(directionBitMap != directionBitMapMap.end());

		CBitmap bmp;
		VERIFY(bmp.LoadBitmap(directionBitMap->second));
		HBITMAP hbmp = HBITMAP(bmp.Detach());

		tile->SetBitmap(hbmp);
		if (nullptr != _prevTile)
		{
			if (!(_prevTile->GetCoordinate() == tile->GetCoordinate()))
			{
				// clear previous tile
				_prevTile->SetBitmap(NULL);
			}
		}
		_prevTile = tile;
	}
}

bool CBoard::IsRobotTileClicked(UINT nID)
{
	bool clicked = false;
	if (nullptr != _prevTile)
	{
		// Find tile
		auto vtile = find_if(
			_tiles.begin(),
			_tiles.end(),
			[nID](const CTile* tile)
			{
				return tile->GetDlgCtrlID() == nID;
			});
		VERIFY(nullptr != *vtile);

		CTile* tile = (*vtile);
		if (tile->GetCoordinate() == _prevTile->GetCoordinate())
		{
			clicked = true;
		}
	}
	return clicked;
}
