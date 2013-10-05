#pragma once


#include "ofMain.h"
#include "ofxJSONElement.h"
#include "ofxThreadedImageLoader.h"


class IOCWallApp : public ofBaseApp {
public:
    void setup();
    void draw();
    void buildDiamondMesh(/*ofImage texture*/);
    void keyPressed(int key);
    void updateImages(int queries, bool refresh);
    void mousePressed(int x, int y, int button);
    void exit();
    
    ofxJSONElement  response;
    
    
    ofEasyCam cam;
    ofVboMesh vboMesh;
    std::vector<ofImage> images;
    ofxThreadedImageLoader loader;
};

class FlickrJSONThread : public ofThread
{
    std::vector<ofImage>* images;
    bool refresh;
    ofxJSONElement  response;
    int queries;
    ofxThreadedImageLoader loader;
    
    
    // the thread function
//    void /*FlickrJSONThread::*/threadedFunction()
//    {
//        // start
//        int currentSize = 0;
//        std::vector<ofImage>* images;
//        std::vector<std::string> imgUrlVector;
//        for(int j = 0; j < queries; j++)
//        {
//            int randomYear = 2004+(int)ofRandom(10);
//            int randomDay = 1+(int)ofRandom(28);
//            int randomMonth = 1+(int)ofRandom(12);
////            std::string url = "http://www.flickr.com/services/rest/?method=flickr.interestingness.getList&api_key=76fee119f6a01912ef7d32cbedc761bb&format=json&nojsoncallback=1&date=";
//            std::string url = "http://api.flickr.com/services/rest/?method=flickr.interestingness.getList&api_key=e3b3f4b8eaaada75c02b27cffb9ec025&format=json&nojsoncallback=1&date=";
//            
//            std::stringstream sstm;
//            sstm <<url << randomYear << "-";
//            if(randomMonth < 10)
//                sstm << "0";
//            sstm <<  randomMonth << "-";
//            if(randomDay < 10)
//                sstm <<  "0";
//            sstm <<  randomDay;
//            url = sstm.str();
//            if (!response.open(url)) {
//                cout  << "Failed to parse JSON\n" << endl;
//            }
//            
//            int numImages =response["photos"]["photo"].size();// MAX(5,response["photos"]["photo"].size());
//            
//            //            images.resize(200);//images.size()+numImages2);
//            
//            ofLog(OF_LOG_NOTICE, "numImages %d",numImages);
//            for(int i=0; i< numImages; i++) {
//                //            ofImage img;
//                
//                int farm = response["photos"]["photo"][i]["farm"].asInt();
//                std::string id = response["photos"]["photo"][i]["id"].asString();
//                std::string secret = response["photos"]["photo"][i]["secret"].asString();
//                std::string server = response["photos"]["photo"][i]["server"].asString();
//                std::string url = "http://farm"+ofToString(farm)+".static.flickr.com/"+server+"/"+id+"_"+secret+".jpg";
//                //            ofLog(OF_LOG_NOTICE, "url " + url);
//                imgUrlVector.push_back(url);
//                ofImage img;
//                if(!refresh)
//                    images->push_back(img);
//                
//                //            ofLog(OF_LOG_NOTICE,"images[%d]: %p",(i+currentSize),&images[i+currentSize]);
//                //        string fileName = "snapshot_"+ofToString(10000+i)+".png";
//                //		img.saveImage(fileName);
//            }
//            currentSize+=numImages;
//        }
//        for(int i = 0; i < imgUrlVector.size(); i++)
//        {
////            lock();
//            if(refresh)
//            {
//                int randIndex = (int)ofRandom(images->size());
//                loader.loadFromURL((*images)[randIndex],imgUrlVector[i]);
//            }else{
//                loader.loadFromURL((*images)[i],imgUrlVector[i]);
//            }
////            unlock();
//        }
//        
//        // done
//    }
public:
//    void loadThreaded(//std::vector<ofImage>* images,
//                      bool refrsh,
//                      ofxJSONElement  rsponse,
//                      int quries,
//                      ofxThreadedImageLoader lder)
//    {
//        this->images = images;
//        refresh = refrsh;
//        response = rsponse;
//        queries = quries;
//        loader = lder;
//        threadedFunction();
//    }
};
