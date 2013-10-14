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
    DiamondTile::DiamondTile(ofVec3f(200,200),ofVec3f(200,200),ofVec3f(200,200));
}

DiamondTile::DiamondTile(ofVec3f pos, ofVec2f startDim, ofVec2f endDim)
{
    mPos = pos;
    mStartDim = startDim;
    mEndDim = endDim;
    mAnimDuration = 4.f;
    mAnimOffset = ofRandom(mAnimDuration);
    
//    setupDims();
    update(0);
}

void DiamondTile::update(float tm)
{
    float myTm = tm+mAnimOffset;
    float tween = (cos(TWO_PI* myTm/mAnimDuration) + 1)/2;
    ofVec2f dim = tween*mStartDim + (1-tween)*mEndDim;
    setupDims(dim);
}

void DiamondTile::checkTexCoords()
{
    
    if(mImage.width+mImage.height > 0)
    {
        float startArea = (leg1Dir*mStartDim.x).crossed(leg2Dir*mStartDim.y).length();
        float startW = abs((leg1Dir*mStartDim.x - leg2Dir*mStartDim.y).x);
        float startH = (leg1Dir*mStartDim.x+leg2Dir*mStartDim.y).length();
        float startVWToH = startW/startH;

        float endArea = (leg1Dir*mEndDim.x).crossed(leg2Dir*mEndDim.y).length();
        float endW = abs((leg1Dir*mEndDim.x - leg2Dir*mEndDim.y).x);
        float endH = (leg1Dir*mEndDim.x+leg2Dir*mEndDim.y).length();
        float endVWToH = (mEndDim.x*leg1Dir).length()/(mEndDim.y*leg2Dir).length();
        
        float imgWToH = mImage.width*1.f/mImage.height;
        
        if (startVWToH < 1 && endVWToH < 1)
        {
//            max
        }
        
        
        mVboMesh.setTexCoord(0, ofVec3f(0,0));
        mVboMesh.setTexCoord(1, leg1Dir*mStartTexPos[0].x);
        mVboMesh.setTexCoord(2, leg2Dir*mStartTexPos[0].y);
        mVboMesh.setTexCoord(3, (leg1Dir*mStartTexPos[0].x+leg2Dir*mStartTexPos[0].y));
    }
}


ofVec3f const DiamondTile::verts[4] = {ofVec3f(0.f,0.f,0.f),
                                       ofVec3f(1.f,0.f,0.f),
                                       ofVec3f(0.f,1.f,0.f),
                                       ofVec3f(1.f,1.f,0.f)};
ofVec3f DiamondTile::leg1Dir = (verts[1] - verts[0]).normalize();
ofVec3f DiamondTile::leg2Dir = (verts[2] - verts[0]).normalize();


void DiamondTile::setupDims(ofVec2f currentDim)
{
    
//    std::vector<ofVec3f> meshVerts = mVboMesh.getVertices();
    if(mVboMesh.getVertices().size() > 3)
    {
        mVboMesh.setVertex(0, ofVec3f(0,0));
        mVboMesh.setVertex(1, leg1Dir*currentDim.x);
        mVboMesh.setVertex(2, leg2Dir*currentDim.y);
        mVboMesh.setVertex(3, (leg1Dir*currentDim.x+leg2Dir*currentDim.y));
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

void DiamondTile::buildDiamondMesh()
{
	// OF_PRIMITIVE_TRIANGLES means every three vertices create a triangle
	mVboMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	
    //	int width = texture.getWidth();
    //	int height = texture.getHeight();
    //	ofVec2f imageSize(width,height);
    
    float scaling = 300;
    mVboMesh.addVertex(scaling*ofVec3f(0,0,0));
    mVboMesh.addTexCoord(ofVec3f(0,0,0));
    
    mVboMesh.addVertex(scaling*ofVec3f(1,0,0));
    mVboMesh.addTexCoord(ofVec3f(1,0,0));
    
    mVboMesh.addVertex(scaling*ofVec3f(1,1,0));
    mVboMesh.addTexCoord(ofVec3f(0,1,0));
    
    mVboMesh.addVertex(scaling*ofVec3f(0,1,0));
    mVboMesh.addTexCoord(ofVec3f(1,1,0));
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
//        ofRotateY((ofGetElapsedTimef() +i*1.1)* 10);

//        ofTranslate(mPos); // position the current mesh
//        ofRotateX((ofGetElapsedTimef())* 30); // slowly rotate the model
//        ofRotateY((ofGetElapsedTimef())* 10);
        //mImage.bind();
        mVboMesh.draw();
        //mImage.unbind();
    }
    ofPopMatrix();
}