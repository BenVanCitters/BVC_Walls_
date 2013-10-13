//
//  TileLayer.cpp
//  IOCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#include "TileLayer.h"
#include "ofxJSONElement.h"
//
//#include "threadedObject.h"
//#include "JSONThread1.h"

TileLayer::TileLayer():mTileSetter(200,200)
{
    ofSeedRandom();
//	buildDiamondMesh();
	
//    testURL();
	updateImages(1,false);
    
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
    float tm = ofGetElapsedTimef();
    for(int i=0; i<mTiles.size(); i++)
    {
        mTiles[i].update(tm);
    }
}

void TileLayer::testURL()
{
    ofxJSONElement  response;

    std::string jsonURL = "http://ec2-54-212-34-135.us-west-2.compute.amazonaws.com/recent";

    if (!response.open(jsonURL)) {
        cout  << "Failed to parse JSON\n" << endl;
    }
    
    int fields  =response.size();
    if(fields < 1)
    {
       ofLog(OF_LOG_ERROR, response.getRawString());
    }
    
    for(int i=0; i< fields; i++)
    {
        std::string content  = response[i]["content"].asString();
        std::string real_name  = response[i]["real_name"].asString();
        std::string screen_name  = response[i]["screen_name"].asString();
        uint64 timestamp  = response[i]["timestamp"].asUInt64();
        
        int imageCount = response[i]["images"].size();
//        cout << "content: " << content << endl << " real_name: " << real_name << endl << " screen_name: " << screen_name << endl << " timestamp: " << timestamp << endl;
        for(int j=0; j< imageCount; j++)
        {
            std::string url  = response[i]["images"][j].asString();
            
            cout << url << endl;
            
            int hDivisions = 50;
            int vDivisions = hDivisions*ofGetWindowHeight()/ofGetWindowWidth();
            float tileQuanta = ofGetWindowWidth()/hDivisions;
            
            ofVec2f sz;
            ofVec2f pos;
            bool foundRect = mTileSetter.getNewRect(&pos,&sz);
            
            if(!foundRect)
            {
                DiamondTile tile( ofVec2f(pos.x*tileQuanta,pos.y*tileQuanta),
                                 ofVec2f(tileQuanta*sz.x, tileQuanta*sz.y),
                                 ofVec2f(tileQuanta*sz.x, tileQuanta*sz.y));
                mTiles.push_back(tile);
            }
        }
    }
    
    for(int i = 0; i < mTiles.size(); i++)
    {
        mLoader.loadFromURL(mTiles[i].mImage, mTiles[i].mImgURL);
        mTiles[i].buildDiamondMesh();
    }

}


void TileLayer::updateImages(int queries, bool refresh)
{
    ofxJSONElement response;
    
    for(int j = 0; j < queries; j++)
    {
        int randomYear = 2004+(int)ofRandom(10);
        int randomDay = 1+(int)ofRandom(28);
        int randomMonth = 1+(int)ofRandom(12);
        // 	  std::string url = "http://www.flickr.com/services/rest/?method=flickr.interestingness.getList&api_key=76fee119f6a01912ef7d32cbedc761bb&format=json&nojsoncallback=1&date=";
        std::string jsonURL = "http://api.flickr.com/services/rest/?method=flickr.interestingness.getList&api_key=76fee119f6a01912ef7d32cbedc761bb&format=json&nojsoncallback=1&date=";
        
        std::stringstream sstm;
        sstm <<jsonURL << randomYear << "-";
        if(randomMonth < 10)
            sstm << "0";
        sstm <<  randomMonth << "-";
        if(randomDay < 10)
            sstm <<  "0";
        sstm <<  randomDay;
        if (!response.open(sstm.str()))
        {
            cout  << "Failed to parse JSON\n" << endl;
        }
        
        int numImages =response["photos"]["photo"].size();        
        
        if(numImages < 1)
            ofLog(OF_LOG_NOTICE, response.getRawString());
        
        ofLog(OF_LOG_NOTICE, "numImages %d",numImages);
        for(int i=0; i< numImages; i++)
        {
            int farm = response["photos"]["photo"][i]["farm"].asInt();
            std::string id = response["photos"]["photo"][i]["id"].asString();
            std::string secret = response["photos"]["photo"][i]["secret"].asString();
            std::string server = response["photos"]["photo"][i]["server"].asString();
            std::string url = "http://farm"+ofToString(farm)+".static.flickr.com/"+server+"/"+id+"_"+secret+".jpg";
            //            ofLog(OF_LOG_NOTICE, "url " + url);
//            imgUrlVector.push_back(url);
            
            
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
                tile.mImgURL = url;
            }
            
//            float margin = 200;
//            DiamondTile tile( ofVec3f(ofRandom(ofGetWindowWidth()+margin*2)-margin,ofRandom(ofGetWindowHeight()+margin*2)-margin),
//                              ofVec2f(ofRandom(500),ofRandom(500)),
//                              ofVec2f(ofRandom(700),ofRandom(700)));
//            
//            if(!refresh)
//            {
//                mTiles.push_back(tile);
//                
//            }
            //            ofLog(OF_LOG_NOTICE,"images[%d]: %p",(i+currentSize),&images[i+currentSize]);
            //        string fileName = "snapshot_"+ofToString(10000+i)+".png";
            //		img.saveImage(fileName);
        }
    }
    
    for(int i = 0; i < mTiles.size(); i++)
    {
            cout << "url: " << mTiles[i].mImgURL << endl;
            mLoader.loadFromURL(mTiles[i].mImage, mTiles[i].mImgURL);
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




