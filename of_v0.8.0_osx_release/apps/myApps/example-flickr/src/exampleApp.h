#pragma once


#include "ofMain.h"
#include "ofxJSONElement.h"
#include "ofxThreadedImageLoader.h"


class exampleApp : public ofBaseApp {
public:
    void setup();
    void draw();
    void buildDiamondMesh(/*ofImage texture*/);
    
    ofxJSONElement  response;
    ofxJSONElement  response2;
    
    
    ofEasyCam cam;
    ofVboMesh vboMesh;
    std::vector<ofImage> images;
    ofxThreadedImageLoader loader;
};
