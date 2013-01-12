//
//  ofxPhysicalNode.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 08/12/2012.
//
//



#pragma once

#include "ofMain.h"

class ofxPhysicalNode : public ofNode {
public:

    ofxPhysicalNode();

    void resetPhysics();
    void updatePhysics();
    
protected:
    ofVec3f posVel;
    ofVec3f rotVel;
    
    ofVec3f posDrag;
    ofVec3f rotDrag;
    
    ofVec3f maxPosVel;
    ofVec3f maxRotVel;
    
    unsigned long lastUpdateMillis;
    
};