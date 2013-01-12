//
//  ofxPhysicalNode.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 08/12/2012.
//
//

#include "ofxPhysicalNode.h"


//--------------------------------------------------------------
ofxPhysicalNode::ofxPhysicalNode() {
    lastUpdateMillis = 0;
}

//--------------------------------------------------------------
void ofxPhysicalNode::resetPhysics() {
    resetTransform();
    posVel.set(0, 0, 0);
    rotVel.set(0, 0, 0);
}


//--------------------------------------------------------------
void ofxPhysicalNode::updatePhysics() {
    float nowMillis = ofGetElapsedTimeMillis();
    float deltaTime = (nowMillis - lastUpdateMillis)/1000.0f;
    lastUpdateMillis = ofGetElapsedTimeMillis();
    
    ofVec3f pos(getPosition());
    if(maxPosVel.x > 0) posVel.x = ofClamp(posVel.x, -maxPosVel.x, maxPosVel.x);
    if(maxPosVel.y > 0) posVel.y = ofClamp(posVel.y, -maxPosVel.y, maxPosVel.y);
    if(maxPosVel.z > 0) posVel.z = ofClamp(posVel.z, -maxPosVel.z, maxPosVel.z);
    pos += posVel * deltaTime;
    setPosition(pos);
    posVel -= posVel * posDrag; // TODO: how to make this fps independent?
    if(posVel.lengthSquared() < 0.00001) posVel.set(0, 0, 0);
    
    ofVec3f rot(getOrientationEuler());
    if(maxRotVel.x > 0) rotVel.x = ofClamp(rotVel.x, -maxRotVel.x, maxRotVel.x);
    if(maxRotVel.y > 0) rotVel.y = ofClamp(rotVel.y, -maxRotVel.y, maxRotVel.y);
    if(maxRotVel.z > 0) rotVel.z = ofClamp(rotVel.z, -maxRotVel.z, maxRotVel.z);
    rot += rotVel * deltaTime;
    setOrientation(rot);
    rotVel -= rotVel * rotDrag; // TODO: how to make this fps independent?
    if(rotVel.lengthSquared() < 0.00001) rotVel.set(0, 0, 0);
}