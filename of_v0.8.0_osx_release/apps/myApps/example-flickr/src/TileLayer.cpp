//
//  TileLayer.cpp
//  BVCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#include "TileLayer.h"
//


TileLayer::TileLayer():mTileSetter(200,200)
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
    

    
	ofBackground(0);
    vidGrabber.draw(10,10);
    ofEnableNormalizedTexCoords();
    
    int winWidth = ofGetWindowWidth();
    int winHeight = ofGetWindowWidth();
	
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].draw(i);
    }
    
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
        int numImages =0;
        
        
        
        ofLog(OF_LOG_NOTICE, "numImages %d",numImages);
        for(int i=0; i< numImages; i++)
        {
                        ofVec2f sz;
            ofVec2f pos;
            bool foundRect = mTileSetter.getNewRect(&pos,&sz);
            
            if(foundRect)
            {
                int hDivisions = 50;
                int vDivisions = hDivisions*ofGetWindowHeight()/ofGetWindowWidth();
                float tileQuanta = ofGetWindowWidth()/hDivisions;
                
                cout << "pos: " << pos << "sz: " << sz << endl;
                DiamondTile tile(ofVec2f(pos.x*tileQuanta,pos.y*tileQuanta),
                                 ofVec2f(tileQuanta*sz.x, tileQuanta*sz.y),
                                 ofVec2f(tileQuanta*sz.x, tileQuanta*sz.y));
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




