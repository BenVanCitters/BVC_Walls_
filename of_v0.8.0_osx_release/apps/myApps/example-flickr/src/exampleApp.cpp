#include "exampleApp.h"

//------------------------------------------------------------------------------
void exampleApp::setup()
{
	ofSetFrameRate(60);
	buildDiamondMesh();
	// this load font loads the non-full character set
	// (ie ASCII 33-128), at size "32"
	
	std::string url1 = "http://www.flickr.com/services/rest/?method=flickr.interestingness.getList&api_key=76fee119f6a01912ef7d32cbedc761bb&format=json&nojsoncallback=1";

    if (!response.open(url1)) {
		cout  << "Failed to parse JSON\n" << endl;
	}
    
	int numImages =response["photos"]["photo"].size();// MAX(5,response["photos"]["photo"].size());
    
    std::string url2 = "http://api.flickr.com/services/rest/?method=flickr.interestingness.getList&api_key=0ba85adbb9e348398f58099fe79932f7&date=2005-09-01&format=json&nojsoncallback=1";
    if (!response2.open(url2)) {
		cout  << "Failed to parse JSON\n" << endl;
	}
    
	int numImages2 =response2["photos"]["photo"].size();// MAX(5,response["photos"]["photo"].size());
	
    
//    total = 24;
	images.resize(numImages+numImages2);
	for(int i=0; i< numImages; i++) {
		int farm = response["photos"]["photo"][i]["farm"].asInt();
		std::string id = response["photos"]["photo"][i]["id"].asString();
		std::string secret = response["photos"]["photo"][i]["secret"].asString();
		std::string server = response["photos"]["photo"][i]["server"].asString();
		std::string url = "http://farm"+ofToString(farm)+".static.flickr.com/"+server+"/"+id+"_"+secret+".jpg";
    
        loader.loadFromURL(images[i],url);
//        string fileName = "snapshot_"+ofToString(10000+i)+".png";
//		img.saveImage(fileName);
	}
	for(int i=0; i< numImages2; i++) {
		int farm = response2["photos"]["photo"][i]["farm"].asInt();
		std::string id = response2["photos"]["photo"][i]["id"].asString();
		std::string secret = response2["photos"]["photo"][i]["secret"].asString();
		std::string server = response2["photos"]["photo"][i]["server"].asString();
		std::string url = "http://farm"+ofToString(farm)+".static.flickr.com/"+server+"/"+id+"_"+secret+".jpg";
//        ofLog(OF_LOG_NOTICE, "url " + url);
        loader.loadFromURL(images[i+numImages],url);
        //        string fileName = "snapshot_"+ofToString(10000+i)+".png";
        //		img.saveImage(fileName);
	}
}

//------------------------------------------------------------------------------
void exampleApp::draw()
{
//    cam.begin();
	ofEnableDepthTest();
    
	ofBackground(0);
    ofEnableNormalizedTexCoords();
    
    int winWidth = ofGetWindowWidth();
    int winHeight = ofGetWindowWidth();
	for(int i=0; i<images.size(); i++) {
//		images[i].draw(i*55%winWidth, i*30%winHeight);
        ofPushMatrix();
        
        ofTranslate(i*55%winWidth, i*5%winHeight); // position the current mesh
        ofRotateX((ofGetElapsedTimef() +i)* 30); // slowly rotate the model
//        ofScale(100, 100);
        images[i].bind();
        vboMesh.draw();
        images[i].unbind();
        ofPopMatrix();
    }
    ofDisableDepthTest();
//	cam.end();
    
//    img.bind(); // bind the image to begin texture mapping
//	int n = 55; // make a 5x5 grid
//	ofVec2f spacing(img.getWidth(), img.getHeight()); // spacing between meshes
//	ofTranslate(-spacing.x * n / 2, -spacing.y * n / 2, 0); // center the grid
//	for(int i = 0; i < n; i++) { // loop through the rows
//		for(int j = 0; j < n; j++) { // loop through the columns
//			ofPushMatrix();
//			ofTranslate(i * spacing.x, j * spacing.y); // position the current mesh
//			ofTranslate(spacing.x / 2, spacing.y / 2); // center the mesh
//			if(ofGetKeyPressed()) {
//				vboMesh.draw(); // draw a vboMesh (faster) when a key is pressed
//			} else {
//				mesh.draw(); // draw an ofMesh (slower) when no key is pressed
//			}
//			ofPopMatrix();
//		}
//	}
//	img.unbind();
    
    
    // draw the framerate in the top left corner
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()) + " fps", 10, 20);
}


void exampleApp::buildDiamondMesh(/*ofImage texture*/)
{
    ofMesh mesh;
	// OF_PRIMITIVE_TRIANGLES means every three vertices create a triangle
	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//	int skip = 10;	// this controls the resolution of the mesh
	
//	int width = texture.getWidth();
//	int height = texture.getHeight();
//	ofVec2f imageSize(width,height);
    
	ofVec3f zero(0, 0, 0);
    
    /*
     texCoords = new float[][]{{.5,0},
     {.5+.5/sqrt(3),.5},
     {.5,1},
     {.5-.5/sqrt(3),.5}};
     
     posCoords = new float[][]{{0,0},
     {.5/sqrt(3),.5},
     {0,1},
     {-.5/sqrt(3),.5}};
     */
//
    float scaling = 300;
    mesh.addVertex(ofVec3f(0,0,0));
    mesh.addTexCoord(ofVec3f(.5,0,0));
    
    mesh.addVertex(ofVec3f(scaling*.5/sqrt(3),scaling*.5,0));
    mesh.addTexCoord(ofVec3f(.5+.5/sqrt(3),.5,0));
    
    mesh.addVertex(ofVec3f(scaling*-.5/sqrt(3),scaling*.5,0));
    mesh.addTexCoord(ofVec3f(.5-.5/sqrt(3),.5,0));
    
    mesh.addVertex(ofVec3f(0,scaling*1,0));
    mesh.addTexCoord(ofVec3f(.5,1,0));

	vboMesh = mesh;
}

//--------------------------------------------------------------
void exampleApp::keyPressed(int key){
	if(key == ' ') {
		ofToggleFullscreen();
	}
}

