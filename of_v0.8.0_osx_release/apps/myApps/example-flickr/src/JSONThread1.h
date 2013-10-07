//
//  JSONThread.h
//  example-flickr
//
//  Created by Ben Van Citters on 10/4/13.
//
//

#include "ofMain.h"
#include "TileLayer.h"

#ifndef __example_flickr__JSONThread__
#define __example_flickr__JSONThread__

#include <iostream>
class JSONThread1 : public ofThread
{
public:
    
    TileLayer* tileLayer;
    void start()
    {
        startThread(true, false);   // blocking, verbose
    }
    
    void stop()
    {
        stopThread();
    }
    
    // the thread function
    void threadedFunction()
    {
        cout  << "calling my own threadedFunction\n" << endl;
        
        lock();
        std::string url;
        // start
        
        int currentSize = 0;
        
        std::vector<std::string> imgUrlVector;
        //    for(int j = 0; j < queries; j++)
        {
            ofxJSONElement  response;
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
                //
                imgUrlVector.push_back(url);
            }
            currentSize+=numImages;
        }
        
        // done
        unlock();
        
        //call the completion callback with our url
        tileLayer->loadImages(imgUrlVector);
    }
    
};
#endif /* defined(__example_flickr__JSONThread__) */
