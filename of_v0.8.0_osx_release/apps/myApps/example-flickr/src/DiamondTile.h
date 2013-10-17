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
//#include "TileSetTile.h"

class TileSetTile;
enum DiamondTileState { tileStateWaiting, tileStateActivated, tileStateSpinning };

class DiamondTile
{
private:
    static const ofVec3f verts[4];
    static ofVec3f leg1Dir;
    static ofVec3f leg2Dir;

public:
    ofVboMesh mVboMesh;
    ofVec3f mPos;
    ofVec3f mCurRotation;
    DiamondTileState mCurrentState;
    float mSpinDuration;
    float mCurSpinStartTime;
    float mCurSpinFinishTime;
    
    float mReSpinWait;
    float mSpinWaitStartTime;
    float mSpinWaitFinishTime;
    int mRotationIndex;
    
    float mNeighborActivationDelay;
    bool mTriggeredNeighbors;
    
    ofVec2f mStartDim;
    
    ofVec2f mStartTexPos[4];
    ofVec2f mEndTexPos[4];
    
    float mAnimDuration;
    float mAnimOffset;
    
    std::vector<TileSetTile*> mTilePieces;
    std::set<DiamondTile*> mNeighborTiles;
    
    DiamondTile();
    DiamondTile(ofVec3f pos, ofVec2f startDim);
    void update(float tm);
    void setupMesh(ofVec2f currentDim);
    void updateMouse(int xDim, int yDim);
    void draw(int i);
//    void checkTexCoords();
    void setTexCoords(ofVec2f* coords);
    void startSpin(int rotationIndex, float duration, float wait, float activationDelay);

    
};

#endif /* defined(__IOCWall__DiamondTile__) */
