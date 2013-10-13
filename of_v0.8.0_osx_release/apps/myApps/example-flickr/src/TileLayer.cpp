//
//  TileLayer.cpp
//  IOCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#include "TileLayer.h"
//
//#include "threadedObject.h"
//#include "JSONThread1.h"

TileLayer::TileLayer()
{
    
//	buildDiamondMesh();
	
//    testURL();
	updateImages(3,false);
    
    //    JSONThread1 fJS;
    ////    fJS.loadThreaded(/*&images,*/ false, response, 5, loader);
    //    fJS.startThread();
    ////    threadedObject to;
    ////    to.start();
    //    threadedObject thread;
    //    thread.iocWallApp = this;
    ////    thread.callBack = &IOCWallApp::loadImages;
    //    thread.start();
}


void TileLayer::draw()
{
    ofEnableDepthTest();
    
	ofBackground(0);
    ofEnableNormalizedTexCoords();
    
    int winWidth = ofGetWindowWidth();
    int winHeight = ofGetWindowWidth();
	
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].draw(i);
    }
    
    ofDisableDepthTest();
    
    // draw the framerate in the top left corner
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
}

void TileLayer::update()
{
    
}



void TileLayer::updateImages(int queries, bool refresh)
{
//    ofxJSONElement response;
//    int currentSize = 0;
    
    std::vector<std::string> imgUrlVector;
    for(int j = 0; j < queries; j++)
    {
        int numImages =0;
        
        ofLog(OF_LOG_NOTICE, "numImages %d",numImages);
        for(int i=0; i< numImages; i++)
        {
            std::string url = "sdkjhfkaj";

            DiamondTile tile( ofVec3f(ofRandom(ofGetWindowWidth()),ofRandom(ofGetWindowWidth())),
                              ofVec2f(ofRandom(500),ofRandom(500)),
                              ofVec2f(ofRandom(700),ofRandom(700)));
            
            mTiles.push_back(tile);
            //            ofLog(OF_LOG_NOTICE,"images[%d]: %p",(i+currentSize),&images[i+currentSize]);
            //        string fileName = "snapshot_"+ofToString(10000+i)+".png";
            //		img.saveImage(fileName);
        }
//        currentSize+=numImages;
    }
    
    for(int i = 0; i < imgUrlVector.size(); i++)
    {
//        mTiles[i].loadImage(&mLoaders[i],imgUrlVector[i]);
//        if(refresh)
//        {
//            int randIndex = (int)ofRandom(mTiles());
////            mLoader.loadFromURL(mTiles[randIndex].mImage,imgUrlVector[i]);
//        }else{
            cout << "url: " << imgUrlVector[i] << endl;
            mLoader.loadFromURL(mTiles[i].mImage, imgUrlVector[i]);
            mTiles[i].buildDiamondMesh();
//        }
    }
}

void TileLayer::setMouseXY(int x, int y)
{
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].updateMouse(x, y);
    }
}




