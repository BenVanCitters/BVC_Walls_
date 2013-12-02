#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
	ofSetVerticalSync(true);

	ofSetFrameRate(120);
    ofDisableArbTex();
    ofEnableNormalizedTexCoords();
	cam.initGrabber(320, 240);
	
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	stepSize = 4;
	ySteps = cam.getHeight() / stepSize;
	xSteps = cam.getWidth() / stepSize;
    
    vecs = new ofVec2f*[ySteps];
	for(int y = 0; y < ySteps; y++) {
        vecs[y] = new ofVec2f[xSteps];
		for(int x = 0; x < xSteps; x++) {
            quads.push_back(TexQuad(ofVec2f(x* stepSize,y* stepSize),ofVec2f(stepSize*2,stepSize*2),ofVec2f::zero()));
			mesh.addVertex(ofVec2f(x * stepSize, y * stepSize));
			mesh.addTexCoord(ofVec2f(x * stepSize, y * stepSize));
		}
	}
	for(int y = 0; y + 1 < ySteps; y++) {
		for(int x = 0; x + 1 < xSteps; x++) {
			int nw = y * xSteps + x;
			int ne = nw + 1;
			int sw = nw + xSteps;
			int se = sw + 1;
			mesh.addIndex(nw);
			mesh.addIndex(ne);
			mesh.addIndex(se);
			mesh.addIndex(nw);
			mesh.addIndex(se);
			mesh.addIndex(sw);
		}
	}
    ofSetBackgroundAuto(false);
}

void testApp::update() {

	cam.update();
	if(cam.isFrameNew()) {
		flow.setWindowSize(8);
		flow.calcOpticalFlow(cam);
        
        for(int i = 0; i < quads.size();i++)
        {
            
            ofRectangle area(quads[i].mPosition - ofVec2f(stepSize, stepSize) / 2, stepSize, stepSize);
            if(area.x > 0 && area.y > 0 && area.getRight() < 320 && area.getBottom() < 240)
            {
                ofVec2f vel =flow.getAverageFlowInRegion(area);
                quads[i].mVelocity = (quads[i].mVelocity+vel) *.4;
            
            }
            quads[i].update();
        }
        
//		int i = 0;
//		float distortionStrength = 4;
//		for(int y = 1; y + 1 < ySteps; y++) {
//			for(int x = 1; x + 1 < xSteps; x++) {
//                
//				int i = y * xSteps + x;
//				ofVec2f position(x * stepSize, y * stepSize);
//				ofRectangle area(position - ofVec2f(stepSize, stepSize) / 2, stepSize, stepSize);
//                vecs[y][x] =flow.getAverageFlowInRegion(area);
//				ofVec2f offset = vecs[y][x];
//				mesh.setVertex(i, position + distortionStrength * offset);
//				i++;
//			}
//		}
	}
}

void testApp::draw() {
//	ofBackground(0,0,0,0);
//	ofScale(2, 2);
    
    cam.getTextureReference().bind();
    for(int i = 0; i < quads.size();i++)
    {
//        ofRectangle area(quads[i].mPosition - ofVec2f(stepSize, stepSize) / 2, stepSize, stepSize);
        quads[i].draw();
    }
    cam.getTextureReference().unbind();
//    
//    for(int y = 1; y + 1 < ySteps; y++) {
//        for(int x = 1; x + 1 < xSteps; x++) {
//            ofVec2f position(x * stepSize, y * stepSize);
//            ofLine(position, position+vecs[y][x]);
//        }
//    }
//	cam.getTextureReference().bind();
//	mesh.draw();
//	cam.getTextureReference().unbind();
	if(ofGetMousePressed()) {
		mesh.drawWireframe();
	}
}