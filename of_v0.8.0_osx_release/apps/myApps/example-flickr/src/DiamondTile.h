//
//  DiamondTile.h
//  IOCWall
//
//  Created by Ben Van CItters on 10/8/13.
//
//

#ifndef __IOCWall__DiamondTile__
#define __IOCWall__DiamondTile__

#include <iostream>
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class DiamondTile
{
public:
    ofVboMesh mVboMesh;
    ofImage mImage;
    ofVec3f mPos;
    
    ofVec2f mStartDim;
    ofVec2f mEndDim;
    
    float mAnimDuration;
    float mAnimOffset;
    

    DiamondTile();
    DiamondTile(ofVec3f pos, ofVec2f startDim, ofVec2f endDim);
    void update();
    void buildDiamondMesh();
    void setupDims();
    void updateMouse(int xDim, int yDim);
    void draw(int i);
    void loadImage(ofxThreadedImageLoader* loader, string url);
};

#endif /* defined(__IOCWall__DiamondTile__) */
