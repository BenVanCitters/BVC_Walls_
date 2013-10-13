//
//  TileSetTile.h
//  IOCWall
//
//  Created by Ben Van CItters on 10/10/13.
//
//

#ifndef __IOCWall__TileSetTile__
#define __IOCWall__TileSetTile__

#include <iostream>

class TileSetTile
{
public:
    TileSetTile* tileAbove;
    TileSetTile* tileBelow;
    TileSetTile* tileLeft;
    TileSetTile* tileRight;
    bool isOccupied;
};

#endif /* defined(__IOCWall__TileSetTile__) */
