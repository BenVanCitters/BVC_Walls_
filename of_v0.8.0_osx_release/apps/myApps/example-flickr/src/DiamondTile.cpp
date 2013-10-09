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
    DiamondTile::DiamondTile(ofVec3f(200,200));    
}

DiamondTile::DiamondTile( ofVec3f pos)
{
    mPos = pos;
}


void DiamondTile::buildDiamondMesh()
{
    ofMesh mesh;
	// OF_PRIMITIVE_TRIANGLES means every three vertices create a triangle
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	
    //	int width = texture.getWidth();
    //	int height = texture.getHeight();
    //	ofVec2f imageSize(width,height);
    
    float scaling = 300;
    mesh.addVertex(scaling*ofVec3f(0,0,0));
    mesh.addTexCoord(ofVec3f(.5,0,0));
    
    mesh.addVertex(scaling*ofVec3f(.5/sqrt(3),.5,0));
    mesh.addTexCoord(ofVec3f(.5+.5/sqrt(3),.5,0));
    
    mesh.addVertex(scaling*ofVec3f(-.5/sqrt(3),.5,0));
    mesh.addTexCoord(ofVec3f(.5-.5/sqrt(3),.5,0));
    
    mesh.addVertex(scaling*ofVec3f(0,1,0));
    mesh.addTexCoord(ofVec3f(.5,1,0));
    
	mVboMesh = mesh;
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
    ofPushMatrix();
    
    int winWidth = ofGetWindowWidth();
    int winHeight = ofGetWindowWidth();
//    cout << (mImage.width + mImage.height) << ", ";
    if(mImage.width + mImage.height > 0)
    {
        ofTranslate(i*55%winWidth, i*5%winHeight); // position the current mesh
        ofRotateX((ofGetElapsedTimef() +i)* 30); // slowly rotate the model
        ofRotateY((ofGetElapsedTimef() +i*1.1)* 10);

//        ofTranslate(mPos); // position the current mesh
//        ofRotateX((ofGetElapsedTimef())* 30); // slowly rotate the model
//        ofRotateY((ofGetElapsedTimef())* 10);
        mImage.bind();
        mVboMesh.draw();
        mImage.unbind();
    }
    ofPopMatrix();
}