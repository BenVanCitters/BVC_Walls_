//
//  TileLayer.cpp
//  BVCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#include "TileLayer.h"
#include "TileSetTile.h"


TileLayer::TileLayer():mTileSetter(20,25)
{
    ofSetWorkingDirectoryToDefault();
    ofSeedRandom();

	generateTiles();
    
    vidGrabber.setDeviceID(0);
    vidGrabber.setVerbose(true);
    vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(1280,720);
    blur.setup(1024, 768);
}


void TileLayer::draw()
{
    blur.setBlurParams(4, (float)mMouseXY.x / 100, 25.f);//(float)mMouseXY.y / 10);
//	blur.beginRender();
    
    ofEnableDepthTest();
    
	
    //vidGrabber.draw(10,10);
    ofEnableNormalizedTexCoords();
    
    int winWidth = ofGetWindowWidth();
    int winHeight = ofGetWindowWidth();
	
    vidGrabber.getTextureReference().bind();
//    videoTexture.bind();
    ofSetColor(255,255,255,255);
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].draw(i);
    }
    ofPushMatrix();
    vidGrabber.getTextureReference().unbind();
    
    ofTranslate(0,0,-200);
    ofSetColor(255,0,0,255);
    if(mRedOrYellow)
        ofSetColor(255,255,0,255);
    mRedOrYellow = !mRedOrYellow;
//    ofFill();
    ofRect(-1000, -1000, 2999, 2000);
    ofPopMatrix();
//    ofBackground(255,0,0);
//    videoTexture.unbind();
    
    ofDisableDepthTest();
    ofDisableNormalizedTexCoords();
//    blur.endRender();
//	blur.draw(0, 0, 1024, 768, true);
    
    
    // draw the framerate in the top left corner
//	ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
}

void TileLayer::update()
{
    vidGrabber.update();
    
    float tm = ofGetElapsedTimef();
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].update(tm);
    }
    
    if(ofRandom(2*60) < 1)
        startRandomTileSpin();
}


void TileLayer::generateTiles()
{
    int hDivisions = mTileSetter.mWidth;
    int vDivisions = mTileSetter.mHeight;
    float tileWQuanta = ofGetWindowWidth()*1.f/hDivisions;
    float tileHQuanta = ofGetWindowHeight()*1.f/vDivisions;
    
    ofVec2f sz;
    ofVec2f pos;
    std::vector<TileSetTile*> tilePieces;

    while(mTileSetter.getNewRect(&pos,&sz,&tilePieces))//(int i=0; i< numImages; i++)
    {
//            cout << "pos: " << pos << "sz: " << sz << endl;
        DiamondTile tile(ofVec2f(pos.x*tileWQuanta,pos.y*tileHQuanta),
                         ofVec2f(tileWQuanta*sz.x, tileHQuanta*sz.y));
        tile.mTilePieces = tilePieces;
        mTiles.push_back(tile);
        
        tilePieces.clear();
    }
    
    for(int i = 0; i < mTiles.size(); i++)
    {
        for(int j = 0; j < mTiles[i].mTilePieces.size(); j++)
        {
            mTiles[i].mTilePieces[j]->mOwnerTile = &mTiles[i];
        }
    }
    
    //we filled the rect now determine neighbors
    mTileSetter.findNeighbors();
}

void TileLayer::startRandomTileSpin()
{
//    mSpinDuration = ;
//    mReSpinWait = ;
//    mNeighborActivationDelay = orRandom(.1;
    
    mTiles[(int)(ofRandom(mTiles.size()))].startSpin( (int)ofRandom(2),
                                                     .1+ofRandom(8),
                                                     ofRandom(1.5),
                                                     ofRandom(.2));
}

void TileLayer::setMouseXY(int x, int y)
{
    mMouseXY = ofVec2f(x,y);
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].updateMouse(x, y);
    }
}




