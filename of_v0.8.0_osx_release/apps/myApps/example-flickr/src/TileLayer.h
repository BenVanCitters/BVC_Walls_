//
//  TileLayer.h
//  BVCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#ifndef __BVCWall__TileLayer__
#define __BVCWall__TileLayer__

#include "ofMain.h"
#include "DiamondTile.h"
#include "ofxThreadedImageLoader.h"
#include "TileSetter.h"
#include "shaderBlur.h"

#include <iostream>

class TileLayer
{
    std::vector<DiamondTile> mTiles;
    ofxThreadedImageLoader mLoader;
    ofVboMesh mVboMesh;
    TileSetter mTileSetter;
    ofVideoGrabber vidGrabber;
    ofTexture videoTexture;
    shaderBlur blur;

    ofVec2f mMouseXY;
    
    bool mRedOrYellow;
public:
    
    TileLayer();
    void testURL();
    void update();
    void draw();
    void generateTiles();
    void setMouseXY(int x, int y);
    void startRandomTileSpin();
};

#endif /* defined(__BVCWall__TileLayer__) */
