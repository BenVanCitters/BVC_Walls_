//
//  TileLayer.h
//  IOCWall
//
//  Created by Ben Van CItters on 10/7/13.
//
//

#ifndef __IOCWall__TileLayer__
#define __IOCWall__TileLayer__

#include "ofMain.h"

#include "ofxThreadedImageLoader.h"
#include <iostream>

class TileLayer
{
    ofVboMesh vboMesh;
    std::vector<ofImage> images;
    ofxThreadedImageLoader loader;
    
public:
    TileLayer();
    void draw();
    void updateImages(int queries, bool refresh);
    void loadImages(std::vector<std::string> imgUrlVector);
    void buildDiamondMesh(/*ofImage texture*/);
    void finishedLoadingURLs(std::vector<std::string> imgUrlVector);
};

#endif /* defined(__IOCWall__TileLayer__) */
