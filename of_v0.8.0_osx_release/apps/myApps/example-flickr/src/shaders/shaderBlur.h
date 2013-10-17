/*
 *  shaderBlur.h
 *  openFrameworks
 *
 *  Created by theo on 17/10/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"


class shaderBlur{

	public:
		void setup(int fboW, int fboH);
		
		void beginRender();
		void endRender();
		
        void setBlurParams(int numPasses, float blurDist, float dvAmt);
		void draw(float x, float y, float w, float h, bool useShader);
				
		ofShader shaderH;
		ofShader shaderV;

		ofFbo fbo1, fbo2;
		
        float divAmount;
		float blurDistance;
		int noPasses;
};