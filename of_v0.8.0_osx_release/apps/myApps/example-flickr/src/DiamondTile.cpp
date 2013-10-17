//
//  DiamondTile.cpp
//  BVCWall
//
//  Created by Ben Van CItters on 10/8/13.
//
//

#include "DiamondTile.h"

DiamondTile::DiamondTile()
{
    DiamondTile::DiamondTile(ofVec3f(200,200),ofVec3f(200,200));
}

DiamondTile::DiamondTile(ofVec3f pos, ofVec2f startDim)
{
    mPos = pos;
    mStartDim = startDim;
//    mEndDim = endDim;
    mAnimDuration = 4.f;
    mAnimOffset = ofRandom(mAnimDuration);
    setupMesh(mStartDim);
}

void DiamondTile::update(float tm)
{
//    float myTm = tm+mAnimOffset;
//    float tween = (cos(TWO_PI* myTm/mAnimDuration) + 1)/2;
//    ofVec2f dim = tween*mStartDim + (1-tween)*mEndDim;
//    setupMesh(mStartDim);
}


ofVec3f const DiamondTile::verts[4] = {ofVec3f(0.f,0.f,0.f),
                                       ofVec3f(1.f,0.f,0.f),
                                       ofVec3f(0.f,1.f,0.f),
                                       ofVec3f(1.f,1.f,0.f)};
ofVec3f DiamondTile::leg1Dir = (verts[1] - verts[0]).normalize();
ofVec3f DiamondTile::leg2Dir = (verts[2] - verts[0]).normalize();


void DiamondTile::setupMesh(ofVec2f currentDim)
{
    mVboMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    ofVec2f wxh(ofGetWindowWidth(),ofGetWindowHeight());
    
    ofVec2f pos[4] = {(-leg1Dir*currentDim.x - leg2Dir*currentDim.y)/2,
                      (leg1Dir*currentDim.x - leg2Dir*currentDim.y)/2,
                      (-leg1Dir*currentDim.x+leg2Dir*currentDim.y)/2,
                      (leg2Dir*currentDim.y + leg1Dir*currentDim.x)/2};
    //set verticies & texture coords
    for(int i = 0; i < 4; i++)
    {
        mVboMesh.addVertex(pos[i]);
        pos[i] += mPos;
        //convert screen-space to normalized texture-space.
        mVboMesh.addTexCoord(ofVec2f(pos[i].x/wxh.x, pos[i].y/wxh.y));
        mVboMesh.addNormal(ofVec3f(0,0,1));
    }
}

void DiamondTile::updateMouse(int xDim, int yDim)
{
//    mStartDim = ofVec2f(xDim,yDim);
//    setupDims();
}

void DiamondTile::setTexCoords(ofVec2f* coords)
{
    for(int i = 0; i < 4; i++)
    {
        mVboMesh.setTexCoord(i, coords[i]);
    }
}


void DiamondTile::draw(int i)
{
//    setupDims();
    
    ofPushMatrix();
    
    int winWidth = ofGetWindowWidth();
    int winHeight = ofGetWindowWidth();
//    cout << (mImage.width + mImage.height) << ", ";
    //if(mImage.width + mImage.height > 0)
    {
        ofTranslate(mPos); // position the current mesh
//        ofTranslate(i*55%winWidth, 200+i*5%winHeight); // position the current mesh
//        ofRotateX((ofGetElapsedTimef() +i)* 30); // slowly rotate the model
        ofRotateZ((ofGetElapsedTimef() +i*1.1)* 10);

//        ofTranslate(mPos); // position the current mesh
//        ofRotateX((ofGetElapsedTimef())* 30); // slowly rotate the model
//        ofRotateY((ofGetElapsedTimef())* 10);
        mVboMesh.draw();
    }
    ofPopMatrix();
}