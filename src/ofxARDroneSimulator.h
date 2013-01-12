//
//  ofxARDroneSimulator.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 07/12/2012.
//  www.memo.tv
//
//


//--------------------------------------------------------------
/*
 
 (Very VERY crude) class to create a simulation of a Drone (so you can test without killing people)
 TODO: update based on real data read back from drone
 
 */
//--------------------------------------------------------------


#pragma once

#include "ofMain.h"

#include "ofxPhysicalNode.h"


namespace ofxARDrone {
    
    class Drone;
    
    class Simulator : public ofxPhysicalNode {
    public:
        // made up arbitrary multipliers
        float rollRotMult;  // how the -1...1 rollAmount maps to angle
        float pitchRotMult; // how the -1...1 pitchAmount maps to angle
        float rollVelMult;  // how the -1...1 rollAmount maps to velocity
        float pitchVelMult; // how the -1...1 pitchAmount maps to velocity
        float liftVelMult;     // how the -1...1 liftSpeed maps to velocity
        float spinVelMult;     // how the -1...1 spinSpeed maps to velocity

        float vertDrag;
        float horzDrag;
        float angularDrag;
        
        Simulator();
        ~Simulator();
        
        void setup(Drone *drone);
        void update();
        void reset();
        
        void customDraw();
        
    protected:
        Drone *drone;
    };
}