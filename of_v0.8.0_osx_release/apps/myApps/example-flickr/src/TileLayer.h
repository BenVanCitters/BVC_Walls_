//
//  TileLayer.h
//  IOCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#ifndef __IOCWall__TileLayer__
#define __IOCWall__TileLayer__

#include "ofMain.h"
#include "DiamondTile.h"
#include "ofxThreadedImageLoader.h"

#include <iostream>

class TileLayer
{
    std::vector<DiamondTile> mTiles;
    ofxThreadedImageLoader mLoader;
    std::vector<float> mXTerminations;
    std::vector<float> mYTerminations;
    ofVboMesh mVboMesh;

    
public:
    
    TileLayer();
    void testURL();
    void update();
    void draw();
    void updateImages(int queries, bool refresh);
    void loadImages(std::vector<std::string> imgUrlVector);
    void setMouseXY(int x, int y);
};

#endif /* defined(__IOCWall__TileLayer__) */
