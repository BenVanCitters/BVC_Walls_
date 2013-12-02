//
//  TexQuad.cpp
//  ofApp
//
//  Created by Ben Van Citters on 12/2/13.
//
//

#include "TexQuad.h"

TexQuad::TexQuad(ofVec2f pos, ofVec2f sz, ofVec2f vel):mPosition(pos),mStartPosition(pos),mVelocity(vel)
{
    ofVec2f vidSize(320, 240);
    mQuad.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    mQuad.addVertex(pos);
    mQuad.addTexCoord(pos/vidSize);
    
    mQuad.addVertex(ofVec2f(pos.x+sz.x,pos.y));
    mQuad.addTexCoord(ofVec2f(pos.x+sz.x,pos.y)/vidSize);
    
    mQuad.addVertex(ofVec2f(pos.x,pos.y+sz.y));
    mQuad.addTexCoord(ofVec2f(pos.x,pos.y+sz.y)/vidSize);
    
    mQuad.addVertex(pos+sz);
    mQuad.addTexCoord((pos+sz)/vidSize);
}

void TexQuad::resetPosition()
{
    mPosition = mStartPosition;
}

void TexQuad::update()
{
    mPosition += mVelocity;
}

void TexQuad::draw()
{
    //texture should already be bound
    ofPushMatrix();
    ofTranslate(mPosition);
    mQuad.draw();
    ofPopMatrix();
}