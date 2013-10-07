//
//  TileLayer.cpp
//  IOCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#include "TileLayer.h"
#include "ofxJSONElement.h"

#include "threadedObject.h"
#include "JSONThread1.h"

TileLayer::TileLayer()
{
	buildDiamondMesh();
	// this load font loads the non-full character set
	// (ie ASCII 33-128), at size "32"
	
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
	for(int i=0; i<images.size(); i++) {
        if(images[i].width + images[i].height > 0)
        {
            //            images[i].draw(i*55%winWidth, i*30%winHeight);
            ofPushMatrix();
            
            ofTranslate(i*55%winWidth, i*5%winHeight); // position the current mesh
            ofRotateX((ofGetElapsedTimef() +i)* 30); // slowly rotate the model
            ofRotateY((ofGetElapsedTimef() +i*1.1)* 10);
            images[i].bind();
            vboMesh.draw();
            images[i].unbind();
            ofPopMatrix();
        }
    }
    ofDisableDepthTest();
    
    // draw the framerate in the top left corner
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
}

void TileLayer::updateImages(int queries, bool refresh)
{
    ofxJSONElement  response;
    int currentSize = 0;
    
    std::vector<std::string> imgUrlVector;
    for(int j = 0; j < queries; j++)
    {
        int randomYear = 2004+(int)ofRandom(10);
        int randomDay = 1+(int)ofRandom(28);
        int randomMonth = 1+(int)ofRandom(12);
        // 	  std::string url = "http://www.flickr.com/services/rest/?method=flickr.interestingness.getList&api_key=76fee119f6a01912ef7d32cbedc761bb&format=json&nojsoncallback=1&date=";
        std::string url = "http://api.flickr.com/services/rest/?method=flickr.interestingness.getList&api_key=76fee119f6a01912ef7d32cbedc761bb&format=json&nojsoncallback=1&date=";
        
        std::stringstream sstm;
        sstm <<url << randomYear << "-";
        if(randomMonth < 10)
            sstm << "0";
        sstm <<  randomMonth << "-";
        if(randomDay < 10)
            sstm <<  "0";
        sstm <<  randomDay;
        url = sstm.str();
        if (!response.open(url)) {
            cout  << "Failed to parse JSON\n" << endl;
        }
        
        int numImages =response["photos"]["photo"].size();
        
        
        if(numImages < 1)
            ofLog(OF_LOG_NOTICE, response.getRawString());
        
        ofLog(OF_LOG_NOTICE, "numImages %d",numImages);
        for(int i=0; i< numImages; i++) {
            //            ofImage img;
            
            int farm = response["photos"]["photo"][i]["farm"].asInt();
            std::string id = response["photos"]["photo"][i]["id"].asString();
            std::string secret = response["photos"]["photo"][i]["secret"].asString();
            std::string server = response["photos"]["photo"][i]["server"].asString();
            std::string url = "http://farm"+ofToString(farm)+".static.flickr.com/"+server+"/"+id+"_"+secret+".jpg";
            //            ofLog(OF_LOG_NOTICE, "url " + url);
            imgUrlVector.push_back(url);
            ofImage img;
            if(!refresh)
                images.push_back(img);
            
            //            ofLog(OF_LOG_NOTICE,"images[%d]: %p",(i+currentSize),&images[i+currentSize]);
            //        string fileName = "snapshot_"+ofToString(10000+i)+".png";
            //		img.saveImage(fileName);
        }
        currentSize+=numImages;
    }
    for(int i = 0; i < imgUrlVector.size(); i++)
    {
        if(refresh)
        {
            int randIndex = (int)ofRandom(images.size());
            loader.loadFromURL(images[randIndex],imgUrlVector[i]);
        }else{
            loader.loadFromURL(images[i],imgUrlVector[i]);
        }
    }
}

void TileLayer::finishedLoadingURLs(std::vector<std::string> imgUrlVector)
{
    ofLog(OF_LOG_NOTICE,"finishedLoadingURLs");
}

void TileLayer::loadImages(std::vector<std::string> imgUrlVector)
{
    for(int i = 0; i < imgUrlVector.size(); i++)
    {
        ofImage img;
        images.push_back(img);
    }
    
    for(int i = 0; i < imgUrlVector.size(); i++)
    {
        //        if(refresh)
        {
            
            //            int randIndex = (int)ofRandom(images.size());
            loader.loadFromURL(images[i],imgUrlVector[i]);
            //        }else{
            //            loader.loadFromURL(images[i],imgUrlVector[i]);
        }
    }
}

void TileLayer::buildDiamondMesh(/*ofImage texture*/)
{
    ofMesh mesh;
	// OF_PRIMITIVE_TRIANGLES means every three vertices create a triangle
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //	int skip = 10;	// this controls the resolution of the mesh
	
    //	int width = texture.getWidth();
    //	int height = texture.getHeight();
    //	ofVec2f imageSize(width,height);
    
	ofVec3f zero(0, 0, 0);
    
    
    float scaling = 300;
    mesh.addVertex(ofVec3f(0,0,0));
    mesh.addTexCoord(ofVec3f(.5,0,0));
    
    mesh.addVertex(ofVec3f(scaling*.5/sqrt(3),scaling*.5,0));
    mesh.addTexCoord(ofVec3f(.5+.5/sqrt(3),.5,0));
    
    mesh.addVertex(ofVec3f(scaling*-.5/sqrt(3),scaling*.5,0));
    mesh.addTexCoord(ofVec3f(.5-.5/sqrt(3),.5,0));
    
    mesh.addVertex(ofVec3f(0,scaling*1,0));
    mesh.addTexCoord(ofVec3f(.5,1,0));
    
	vboMesh = mesh;
}



