//
//  ofxARDroneSimulator.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 07/12/2012.
//  www.memo.tv
//
//


#include "ofxARDroneSimulator.h"

#include "ofxARDrone.h"

namespace ofxARDrone {
    
    //--------------------------------------------------------------
    Simulator::Simulator() {
        ofLogVerbose("ofxARDrone::Simulator::Simulator");
        drone = NULL;
        
        rollRotMult = -10;
        pitchRotMult = 10;
        rollVelMult = -10;
        pitchVelMult = 10;
        liftVelMult = 10;
        spinVelMult = -5;
        
        // physics parameters
        posDrag.set(0.05, 0.1, 0.05);
        rotDrag.set(0.01, 0.04, 0.01);
    }
    
    //--------------------------------------------------------------
    Simulator::~Simulator() {
        ofLogVerbose("ofxARDrone::Simulator::~Simulator");
    }
    
    //--------------------------------------------------------------
    void Simulator::setup(Drone *drone) {
        ofLogVerbose("ofxARDrone::Simulator::setup - " + ofToString(drone));
        this->drone = drone;
    }

    //--------------------------------------------------------------
    void Simulator::reset() {
        resetTransform();
        resetPhysics();
    }
    
    //--------------------------------------------------------------
    void Simulator::update() {
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }
        
        posVel += -drone->controller.rollAmount * rollVelMult * getXAxis();
        posVel += drone->controller.liftSpeed * liftVelMult * getYAxis();
        posVel += drone->controller.pitchAmount * pitchVelMult * getZAxis();
  
        ofVec3f rot(getOrientationEuler());
        rotVel.y += drone->controller.spinSpeed * spinVelMult;
        // TODO: do pitch and tilt as well
        
        updatePhysics();
    }
    
    //--------------------------------------------------------------
    void Simulator::customDraw() {
        // all units in cm
        float bladeLength = 20;

        ofPushStyle();
        
        // draw body
        ofSetColor(100);
        ofPushMatrix();
        ofScale(5, 5, 15);
        ofBox(1);
        ofPopMatrix();
        
        // draw head
        ofSetColor(180);
        ofBox(0, 0, -10, 5);
        
        // draw cross frames
        ofSetColor(50);
        for(int i=0; i<2; i++) {
            ofPushMatrix();
            ofRotateY(45 + i * 90);
            ofScale(bladeLength * 1.4f, 1, 1);
            ofBox(0, 3, 0, 1);
            ofPopMatrix();
        }
        
        
        // draw blades
        ofSetColor(150);
        for(int i=0; i<2; i++) {
            for(int j=0; j<2; j++) {
                ofPushMatrix();
                float x = (i-0.5) * bladeLength;
                float z = (j-0.5) * bladeLength;
                ofTranslate(x, 3, z);

                float rot = i * 73 + j * 130;
                if(drone->state.isFlying() || drone->state.isTakingOff()) {
                    int sign = (i+j)%2 ? 1 : -1;
                    rot +=  ofGetElapsedTimeMillis() * 100;
                    rot *= sign;
                }
                ofRotateY(rot);
                ofScale(20, 1, 2);
                ofBox(1);
                ofPopMatrix();
            }
        }
        
//        ofDrawAxis(30);
        
        ofPopStyle();
    }
    
};