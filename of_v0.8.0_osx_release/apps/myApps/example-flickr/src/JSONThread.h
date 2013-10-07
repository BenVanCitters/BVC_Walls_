#ifndef _THREADED_OBJECT
#define _THREADED_OBJECT

#include "ofMain.h"
#include "IOCWallApp.h"

// this is not a very exciting example yet
// but ofThread provides the basis for ofNetwork and other
// operations that require threading.
//
// please be careful - threading problems are notoriously hard
// to debug and working with threads can be quite difficult

class JSONThread : public ofThread{

	public:
        IOCWallApp* iocWallApp;

	    int count;  // threaded fucntions that share data need to use lock (mutex)
	                // and unlock in order to write to that data
	                // otherwise it's possible to get crashes.
	                //
	                // also no opengl specific stuff will work in a thread...
	                // threads can't create textures, or draw stuff on the screen
	                // since opengl is single thread safe

		//--------------------------
		JSONThread(){
			count = 0;
		}

		void start(){
            startThread(true, false);   // blocking, verbose
        }

        void stop(){
            stopThread();
        }

    void threadedFunction(){
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
        

        
        //call the completion callback with our url
        iocWallApp->loadImages(imgUrlVector);
        // done
        unlock();
    }
};

#endif
