#include "resource.h"
#include "Tile.h"
#include <sstream>

#define TILE_DWORD_STYLE ( WS_CHILD | WS_VISIBLE | SS_CENTER | BS_BITMAP | SS_CENTERIMAGE )

CTile::CTile(CWnd* pParent, CPoint& pos, int row, int col):
	coordinate(row,col)
{
	Create(NULL, TILE_DWORD_STYLE, CRect(pos, CSize(TILE_SIZE, TILE_SIZE)), pParent, 1000);
}

const Coordinate& CTile::GetCoordinate() const
{
	return coordinate;
}
