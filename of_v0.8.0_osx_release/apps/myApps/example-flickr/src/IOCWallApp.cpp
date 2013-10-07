#include "IOCWallApp.h"

//------------------------------------------------------------------------------
void IOCWallApp::setup()
{
	ofSetFrameRate(60);

}

//------------------------------------------------------------------------------
void IOCWallApp::draw()
{
    mTileLayer.draw();
}


//--------------------------------------------------------------
void IOCWallApp::keyPressed(int key){
	if(key == ' ') {
		ofToggleFullscreen();
	}
}

void IOCWallApp::mousePressed(int x, int y, int button){
	mTileLayer.updateImages(2,true);
    cout << "mousePressed: " << x << ", " << y << " button: " << button << endl;
}


void IOCWallApp::exit() {
    
    // stop the thread
//    thread.stopThread();
}