/*
 *  shaderBlur.cpp
 *  openFrameworks
 *
 *  Created by theo on 17/10/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "shaderBlur.h"

//--------------------------------------------------------------
void shaderBlur::setup(int fboW, int fboH){	
	
	ofBackground(255,255,255);	
	ofSetVerticalSync(true);
	
	fbo1.allocate(fboW, fboH);//, GL_RGB16F_ARB);
	fbo2.allocate(fboW, fboH);//, GL_RGB16F_ARB);
    // need to figure out filenames
	shaderH.load("shaders/simpleBlurHorizontal.vert",
                 "shaders/simpleBlurHorizontal.frag");
	shaderV.load("shaders/simpleBlurVertical.vert",
                 "shaders/simpleBlurVertical.frag");

	noPasses = 1;
	blurDistance = 2.0;
}

//--------------------------------------------------------------
void shaderBlur::beginRender(){
	fbo1.bind();
}

//--------------------------------------------------------------
void shaderBlur::endRender(){
	fbo1.unbind();
}

//--------------------------------------------------------------
void shaderBlur::setBlurParams(int numPasses, float blurDist, float dvAmt){
	noPasses		= ofClamp(numPasses, 1, 100000);
	blurDistance	= blurDist;
//    cout << "blurDist: " << blurDist << endl;

    divAmount = dvAmt;
//    cout << "divAmount: " << divAmount << endl;
}

//--------------------------------------------------------------
void shaderBlur::draw(float x, float y, float w, float h, bool useShader){
	
	ofFbo * src, * dst;
	src = &fbo1;
	dst = &fbo2;

	if( useShader ){
				
		for(int i = 0; i < noPasses; i++){
			float blurPer =  blurDistance * ofMap(i, 0, noPasses, 1.0/noPasses, 1.0);
			
			//first the horizontal shader
			dst->begin();
            shaderH.begin();
            shaderH.setUniform1f("blurAmnt", blurDistance);
            shaderH.setUniform1f("divAmt", divAmount);
			src->draw(0, 0);
			shaderH.end();
			dst->end();
            
             //now the vertical shader
			src->begin();
			shaderV.begin();
            shaderV.setUniform1f("divAmt", divAmount);
			shaderV.setUniform1f("blurAmnt", blurDistance);
			dst->draw(0,0);
			shaderV.end();
			src->end();
            
			ofFbo  * tmp = src;
			src = dst;
			dst = tmp;
		}
	}
	
	ofEnableAlphaBlending();	
	ofSetColor(255, 255, 255, 255);
	src->draw(x, y, w, h);	

}



