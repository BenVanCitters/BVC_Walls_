//
//  TileLayer.cpp
//  BVCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#include "TileLayer.h"
//


TileLayer::TileLayer():mTileSetter(20,15)
{
    ofSeedRandom();
//	buildDiamondMesh();
	
//    testURL();
	updateImages(1,false);
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setVerbose(true);
    vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(640,480);
}


void TileLayer::draw()
{
    ofEnableDepthTest();
    
	ofBackground(255,255,255);
    //vidGrabber.draw(10,10);
    ofEnableNormalizedTexCoords();
    
    int winWidth = ofGetWindowWidth();
    int winHeight = ofGetWindowWidth();
	
    vidGrabber.getTextureReference().bind();
//    videoTexture.bind();
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].draw(i);
    }
//    videoTexture.unbind();
    vidGrabber.getTextureReference().unbind();
    ofDisableDepthTest();
    ofDisableNormalizedTexCoords();
    // draw the framerate in the top left corner
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
}

void TileLayer::update()
{
    vidGrabber.update();
    
    float tm = ofGetElapsedTimef();
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].update(tm);
    }
}


void TileLayer::updateImages(int queries, bool refresh)
{
    for(int j = 0; j < queries; j++)
    {
        int numImages =600;
        
        ofLog(OF_LOG_NOTICE, "numImages %d",numImages);
        for(int i=0; i< numImages; i++)
        {
                        ofVec2f sz;
            ofVec2f pos;
            bool foundRect = mTileSetter.getNewRect(&pos,&sz);
            
            if(foundRect)
            {
                int hDivisions = mTileSetter.mWidth;
                int vDivisions = mTileSetter.mHeight;
                float tileWQuanta = ofGetWindowWidth()/hDivisions;
                float tileHQuanta = ofGetWindowHeight()/vDivisions;
                
                cout << "pos: " << pos << "sz: " << sz << endl;
                DiamondTile tile(ofVec2f(pos.x*tileWQuanta,pos.y*tileHQuanta),
                                 ofVec2f(tileWQuanta*sz.x, tileHQuanta*sz.y),
                                 ofVec2f(tileWQuanta*sz.x, tileHQuanta*sz.y));
                mTiles.push_back(tile);
            }
        }
    }
    
    for(int i = 0; i < mTiles.size(); i++)
    {
        mTiles[i].buildDiamondMesh();
    }
}

void TileLayer::loadImages(std::vector<std::string> imgUrlVector)
{

}

void TileLayer::setMouseXY(int x, int y)
{
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].updateMouse(x, y);
    }
}




