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
//    ofxThreadedImageLoader* mLoader;
    ofVec3f mPos;
    
    DiamondTile();
    DiamondTile(ofVec3f pos);
    void buildDiamondMesh();
    void draw(int i);
    void loadImage(ofxThreadedImageLoader* loader, string url);
};

#endif /* defined(__IOCWall__DiamondTile__) */
