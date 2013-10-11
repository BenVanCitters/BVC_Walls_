//
//  TileSetter.h
//  IOCWall
//
//  Created by Ben Van CItters on 10/10/13.
//
//

#ifndef __IOCWall__TileSetter__
#define __IOCWall__TileSetter__

#include <iostream>
#include "ofMain.h"
#include "TileSetTile.h"

class TileSetter
{
private:
    std::vector<std::vector<TileSetTile> > tiles;
public:
    TileSetter();
    TileSetter(int width, int height);
    bool getNewRect(ofVec2f* pos, ofVec2f* sz);
};

#endif /* defined(__IOCWall__TileSetter__) */
