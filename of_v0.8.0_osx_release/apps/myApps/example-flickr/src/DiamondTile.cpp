//
//  DiamondTile.cpp
//  IOCWall
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
    
    setupDims();
}

void DiamondTile::update()
{
    
}

void DiamondTile::setupDims()
{
    ofVec3f verts[4] = {ofVec3f(0,0,0),
                        ofVec3f(.5/sqrt(3),.5,0),
                        ofVec3f(-.5/sqrt(3),.5,0),
                        ofVec3f(0,1,0)};
    ofVec3f leg1Dir = verts[1] - verts[0];
    leg1Dir = leg1Dir.normalize() * mStartDim.x;
    ofVec3f leg2Dir = verts[2] - verts[0];
    leg2Dir = leg2Dir.normalize() * mStartDim.y;
    std::vector<ofVec3f> meshVerts = mVboMesh.getVertices();
    if(mVboMesh.getVertices().size() > 3)
    {
        mVboMesh.setVertex(0, ofVec3f(0,0));
        mVboMesh.setVertex(1, leg1Dir);
        mVboMesh.setVertex(2, leg2Dir);
        mVboMesh.setVertex(3, leg1Dir+leg2Dir);
    }
}

void DiamondTile::updateMouse(int xDim, int yDim)
{
//    mStartDim = ofVec2f(xDim,yDim);
    setupDims();
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
    mVboMesh.addTexCoord(ofVec3f(.5,0,0));
    
    mVboMesh.addVertex(scaling*ofVec3f(.5/sqrt(3),.5,0));
    mVboMesh.addTexCoord(ofVec3f(.5+.5/sqrt(3),.5,0));
    
    mVboMesh.addVertex(scaling*ofVec3f(-.5/sqrt(3),.5,0));
    mVboMesh.addTexCoord(ofVec3f(.5-.5/sqrt(3),.5,0));
    
    mVboMesh.addVertex(scaling*ofVec3f(0,1,0));
    mVboMesh.addTexCoord(ofVec3f(.5,1,0));
}

void DiamondTile::loadImage(ofxThreadedImageLoader* loader, string url)
{
//    mLoader = new ofxThreadedImageLoader();
//    cout << mLoader << endl;
    cout << "url: " << url << endl;
//    mLoader->loadFromURL(mImage, url);
    
    loader->loadFromURL(mImage,url);

//    if(!mImage.loadImage(url))
//    {
//        ofLog(OF_LOG_ERROR,"failed to load image!");
//    }
    buildDiamondMesh();
}

void DiamondTile::draw(int i)
{
    setupDims();
    
    ofPushMatrix();
    
    int winWidth = ofGetWindowWidth();
    int winHeight = ofGetWindowWidth();
//    cout << (mImage.width + mImage.height) << ", ";
    if(mImage.width + mImage.height > 0)
    {
        ofTranslate(mPos); // position the current mesh
//        ofTranslate(i*55%winWidth, 200+i*5%winHeight); // position the current mesh
//        ofRotateX((ofGetElapsedTimef() +i)* 30); // slowly rotate the model
//        ofRotateY((ofGetElapsedTimef() +i*1.1)* 10);

//        ofTranslate(mPos); // position the current mesh
//        ofRotateX((ofGetElapsedTimef())* 30); // slowly rotate the model
//        ofRotateY((ofGetElapsedTimef())* 10);
        mImage.bind();
        mVboMesh.draw();
        mImage.unbind();
    }
    ofPopMatrix();
}