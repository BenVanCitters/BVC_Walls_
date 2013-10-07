#pragma once


#include "ofMain.h"
#include "TileLayer.h"

#include "ofxThreadedImageLoader.h"


class IOCWallApp : public ofBaseApp {
public:
    TileLayer mTileLayer;

    //openframeworks app functions
    void setup();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    void exit();
};
