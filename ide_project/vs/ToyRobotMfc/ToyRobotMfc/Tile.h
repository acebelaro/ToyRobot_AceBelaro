#pragma once
#include <afxwin.h>
#include <atlimage.h>
#include "coordinate.hpp"

#define TILE_SIZE 80

class CTile :
    public CButton
{
// Construction
public:
    CTile(CWnd*, CPoint&, int, int);
    virtual ~CTile() = default;
    const Coordinate& GetCoordinate() const;
private:
    Coordinate coordinate;
};
