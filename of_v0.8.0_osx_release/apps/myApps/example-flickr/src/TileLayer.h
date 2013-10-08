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
    ofVboMesh mVboMesh;
    std::vector<ofImage> mImages;
    ofxThreadedImageLoader mLoader;
    std::vector<float> mXTerminations;
    std::vector<float> mYTerminations;
    
public:
    
    TileLayer();
    void testURL();
    
    void draw();
    void updateImages(int queries, bool refresh);
    void loadImages(std::vector<std::string> imgUrlVector);
    void buildDiamondMesh(/*ofImage texture*/);
    void finishedLoadingURLs(std::vector<std::string> imgUrlVector);
};

#endif /* defined(__IOCWall__TileLayer__) */
