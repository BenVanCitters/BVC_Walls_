//
//  TileSetter.h
//  IOCWall
//
//  Created by Ben Van CItters on 10/10/13.
//
//

#ifndef __BVCWall__TileSetter__
#define __BVCWall__TileSetter__

#include <iostream>
#include "ofMain.h"
#include "TileSetTile.h"

class TileSetter
{
private:
    std::vector<std::vector<TileSetTile> > tiles;
public:
    int mWidth;
    int mHeight;
    ofVec2f mMaxTileSize;
    
    TileSetter();
    TileSetter(int width, int height);
    bool getNewRect(ofVec2f * pos, ofVec2f* sz, std::vector<TileSetTile*>* tilesPieces);
    void findNeighbors();
};

#endif /* defined(__IOCWall__TileSetter__) */
