//
//  TileSetTile.h
//  BVCWall
//
//  Created by Ben Van CItters on 10/10/13.
//
//

#ifndef __BVCWall__TileSetTile__
#define __BVCWall__TileSetTile__

#include <iostream>
#include "DiamondTile.h"

class TileSetTile
{
public:
    TileSetTile* tileAbove;
    TileSetTile* tileBelow;
    TileSetTile* tileLeft;
    TileSetTile* tileRight;
    bool isOccupied;
    DiamondTile* mOwnerTile;
};

#endif /* defined(__IOCWall__TileSetTile__) */
