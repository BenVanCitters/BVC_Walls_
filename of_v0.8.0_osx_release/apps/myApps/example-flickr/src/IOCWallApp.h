#pragma once


#include "ofMain.h"
#include "TileLayer.h"

#include "ofxThreadedImageLoader.h"


class IOCWallApp : public ofBaseApp {
public:
//    void buildDiamondMesh(/*ofImage texture*/);
//    void loadImages(std::vector<std::string> imgUrlVector);
//    void finishedLoadingURLs(std::vector<std::string> imgUrlVector);
    
    //openframeworks app functions
    void setup();
    void draw();
    void keyPressed(int key);
    void updateImages(int queries, bool refresh);
    void mousePressed(int x, int y, int button);
    void exit();
    
    TileLayer tileLayer;
//    ofVboMesh vboMesh;
//    std::vector<ofImage> images;
//    ofxThreadedImageLoader loader;
};
