//
//  DiamondTile.h
//  BVCWall
//
//  Created by Ben Van CItters on 10/8/13.
//
//

#ifndef __BVCWall__DiamondTile__
#define __BVCWall__DiamondTile__

#include <iostream>
#include "ofMain.h"
#include "ofxThreadedImageLoader.h"

class DiamondTile
{
private:
    static const ofVec3f verts[4];
    static ofVec3f leg1Dir;
    static ofVec3f leg2Dir;

public:
    ofVboMesh mVboMesh;
    ofImage mImage;
    ofVec3f mPos;
    
    ofVec2f mStartDim;
    ofVec2f mEndDim;
    
    ofVec2f mStartTexPos[4];
    ofVec2f mEndTexPos[4];
    
    float mAnimDuration;
    float mAnimOffset;
    
    DiamondTile();
    DiamondTile(ofVec3f pos, ofVec2f startDim, ofVec2f endDim);
    void update(float tm);
    void buildDiamondMesh();
    void setupDims(ofVec2f currentDim);
    void updateMouse(int xDim, int yDim);
    void draw(int i);
    void checkTexCoords();
    void setTexCoords(ofVec2f* coords);
};

#endif /* defined(__IOCWall__DiamondTile__) */
