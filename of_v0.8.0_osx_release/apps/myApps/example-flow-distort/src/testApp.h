#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
    ofVec2f** vecs;
    
	ofVideoGrabber cam;
	ofxCv::FlowFarneback flow;
	ofMesh mesh;
	int stepSize, xSteps, ySteps;
};