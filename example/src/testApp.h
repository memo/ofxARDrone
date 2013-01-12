//
//  testApp.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//


#pragma once

#include "ofMain.h"
#include "ofxARDrone.h"
#include "ofxARDroneOscBridge.h"

class testApp : public ofBaseApp {
public:

    ofxARDrone::Drone drone;                // the main big daddy class
    ofxARDrone::Simulator droneSimulator;   // for displaying on screen (OPTIONAL)
    ofxARDrone::OscBridge droneOsc;         // for sending/receiving OSC between another app (OPTIONAL)
    
    ofEasyCam easyCam;
    
    bool doPause;
    
    bool keys[65535];

    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
};
