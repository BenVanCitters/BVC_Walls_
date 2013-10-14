#include "BVCWallApp.h"

//------------------------------------------------------------------------------
void BVCWallApp::setup()
{
	ofSetFrameRate(60);
    ofSeedRandom();
}

void BVCWallApp::update()
{
    mTileLayer.update();
}

//------------------------------------------------------------------------------
void BVCWallApp::draw()
{
    mTileLayer.draw();
}


//--------------------------------------------------------------
void BVCWallApp::keyPressed(int key)
{
	if(key == ' ') {
		ofToggleFullscreen();
	}
}

void BVCWallApp::mousePressed(int x, int y, int button)
{
	mTileLayer.updateImages(2,true);
    cout << "mousePressed: " << x << ", " << y << " button: " << button << endl;
}

void BVCWallApp::mouseMoved(int x, int y)
{
    mTileLayer.setMouseXY(x,y);
}

void BVCWallApp::exit()
{
    // stop the thread
//    thread.stopThread();
}