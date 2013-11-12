//
//  testApp.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//


// '1' to exit bootstrap mode
// '2' to send acknowledgement

// 't' to start taking off
// 't' to stop taking off and enter flight mode

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // clear all keys
    memset(keys, 0, sizeof(*keys));
    
    // setup viewport camera
    easyCam.orbit(10, -20, 100);
    easyCam.setDistance(300);
    
    doPause = false;

    
    // connect to the drone (yes, it's that easy)
    drone.connect();
    
    // setup command history lengths for debugging and dumping onscreen (OPTIONAL)
    drone.controller.commandHistory.setMaxLength(30);
    drone.dataReceiver.commandHistory.setMaxLength(30);
    
    // setup the simulator so we have a display in the viewport (OPTIONAL)
    droneSimulator.setup(&drone);
    
    // setup osc so we can send & receive commands from another app to this one, to forward onto the drone (OPTIONAL)
    droneOsc.setup(&drone, 8000, 9000);
}

//--------------------------------------------------------------
void testApp::update() {
    if(doPause) return;

    {
        float s = 0.02;
        
        if(keys[OF_KEY_UP]) drone.controller.pitchAmount -= s;
        else if(keys[OF_KEY_DOWN]) drone.controller.pitchAmount += s;

        if(keys['a']) drone.controller.rollAmount -= s;
        else if(keys['d']) drone.controller.rollAmount += s;

        if(keys['w']) drone.controller.liftSpeed += s;
        else if(keys['s']) drone.controller.liftSpeed -= s;
        
        if(keys[OF_KEY_LEFT]) drone.controller.spinSpeed -= s;
        else if(keys[OF_KEY_RIGHT]) drone.controller.spinSpeed += s;

    }
    
    // update the drone (process and send queued commands to drone, receive commands from drone and update state
    drone.update();
    
    // update position of simulator (OPTIONAL)
    droneSimulator.update();
    
    // receive and send relevant osc commands to any other apps (OPTIONAL)
    droneOsc.update();
}

void drawBar(int x, int y, int w, int h, float t, bool doVertical) {
    ofPushStyle();
    ofFill();
    ofSetColor(250, 0, 0);
    if(doVertical) ofRect(x, y + h/2, w, ofMap(t, -1, 1, h/2, -h/2));
    else ofRect(x + w/2, y, ofMap(t, -1, 1, -w/2, w/2), h);
    
    ofNoFill();
    ofSetColor(100);
    ofSetLineWidth(1);
    ofRect(x, y, w, h);
    if(doVertical) ofLine(x, y - y/2, x + w, y + y/2);
    else ofLine(x + w/2, y, x + w/2, y + h);
    ofPopStyle();
}


//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    ofEnableAlphaBlending();
    glEnable(GL_DEPTH_TEST);
    
    // draw bars
    {
        int x = 155;
        int y = 140;
        int w = 150;
        int h = 14;
        int yinc = 14;
        
        drawBar(x, y, w, h, drone.controller.rollAmount, false); y+= yinc;
        drawBar(x, y, w, h, drone.controller.pitchAmount, false); y+= yinc;
        drawBar(x, y, w, h, drone.controller.liftSpeed, false); y+= yinc;
        drawBar(x, y, w, h, drone.controller.spinSpeed, false); y+= yinc;
    }
    
    // draw simulator
    easyCam.begin();
    ofPushStyle();
    // draw axis
    ofSetLineWidth(1);
    ofDrawAxis(100);
    
    // draw thrust line
    ofSetColor(255, 0, 0);
    ofSetLineWidth(3);
    ofSetColor(50);
    ofLine(ofVec3f(0, 0, 0), droneSimulator.getPosition());
    
    droneSimulator.draw();
    ofPopStyle();
    easyCam.end();
    
    // draw debug strings
    string controllerString = "fps: " + ofToString(ofGetFrameRate()) + "\n";
    controllerString += "millisSinceLastSend: " + ofToString(drone.controller.getMillisSinceLastSend()) + "\n";
    controllerString += "\n";
    controllerString += "takeOff (t)\n";
    controllerString += "land (l)\n";
    controllerString += "calibrateHorizontal (c)\n";
    controllerString += "calibrateMagnetometer (m)\n";
    controllerString += "EMERGENCY (E)\n";
    controllerString += "\n";
    controllerString += "roll (a/d)        : " + ofToString(drone.controller.rollAmount) + "\n";
    controllerString += "pitch (up/down)   : " + ofToString(drone.controller.pitchAmount) + "\n";
    controllerString += "lift (w/s)        : " + ofToString(drone.controller.liftSpeed) + "\n";
    controllerString += "spin (left/right) : " + ofToString(drone.controller.spinSpeed) + "\n";
    controllerString += "\n";
    controllerString += "reset droneSimulator (r)\n";
    controllerString += "debug history (h)\n";
    controllerString += "fullscreen (f)\n";
    controllerString += "PAUSE (p)\n";
    
    ofxARDrone::State &state = drone.state;
    string stateString = "";
    stateString += "isFlying : " + ofToString(state.isFlying()) + "\n";
    stateString += "isTakingOff : " + ofToString(state.isTakingOff()) + ", " + ofToString(state.isTakingOffMillis()) + "\n";
    stateString += "isLanding : " + ofToString(state.isLanding()) + ", " + ofToString(state.isLandingMillis()) + "\n";
    stateString += "isCalibratingHorizontal : " + ofToString(state.isCalibratingHorizontal()) + ", " + ofToString(state.isCalibratingHorizontalMillis()) + "\n";
    stateString += "isCalibratingMagnetometer : " + ofToString(state.isCalibratingMagnetometer()) + ", " + ofToString(state.isCalibratingMagnetometerMillis()) + "\n";

    
    stateString += "\n\nisConnected: " + ofToString(state.isConnected()) + ", " + ofToString(state.isCalibratingMagnetometerMillis()) + "\n";
    stateString += "altitude: "+ ofToString(state.getAltitude())+"\n";
    stateString += "emergency state: "+ ofToString(state.inEmergencyMode())+"\n";
    stateString += "battery level: "+ ofToString(state.getBatteryPercentage())+"%\n";
    stateString += "vx: "+ ofToString(state.getVx())+" vy: "+ ofToString(state.getVy())+" vz: "+ ofToString(state.getVz())+"\n";
    
    ofSetColor(0, 200, 0);
    ofDrawBitmapString(controllerString, 10, 30);
    ofDrawBitmapString(stateString, ofGetWidth()-300, 30);
    
    ofDrawBitmapString(drone.controller.commandHistory.getAsString(), 10, 280);
    ofDrawBitmapString(drone.dataReceiver.commandHistory.getAsString("\n"), ofGetWidth()-300, 280);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key) {
        case '1': drone.controller.exitBootstrap(); break;
        case '2': drone.controller.sendAck(); break;
        case '3': drone.dataReceiver.sendDummyPacket(); break;
        case '0': drone.controller.resetCommunicationWatchdog(); break;

        case 't': drone.controller.takeOff(!drone.state.isTakingOff(), 3000); break;
        case 'l': drone.controller.land(!drone.state.isLanding(), 3000); break;
        case 'c': drone.controller.calibrateHorizontal(!drone.state.isCalibratingHorizontal(), 3000); break;
        case 'm': drone.controller.calibrateMagnetometer(!drone.state.isCalibratingMagnetometer(), 3000); break;
        case 'p': doPause ^= true; break;
            
        case 'e': drone.controller.emergency(0); break;
        case 'E': drone.controller.emergency(1); break;

        case 'r': droneSimulator.reset(); break;
        case 'R': drone.resetSequenceNumber(); break;
            
        case 'h':
            drone.controller.commandHistory.setMaxLength(drone.controller.commandHistory.getMaxLength() ? 0 : (ofGetHeight()-280)/14);
            drone.dataReceiver.commandHistory.setMaxLength(drone.controller.commandHistory.getMaxLength());
            break;
            
        case 'f': ofToggleFullscreen(); break;
    }
    
    keys[key] = true;
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    keys[key] = false;
    
    switch(key) {
        case OF_KEY_UP:
        case OF_KEY_DOWN:
            drone.controller.pitchAmount = 0;
            break;
            
        case OF_KEY_LEFT:
        case OF_KEY_RIGHT:
            drone.controller.spinSpeed = 0;
            break;

        case 'w':
        case 's':
            drone.controller.liftSpeed = 0;
            break;
            
        case 'a':
        case 'd':
            drone.controller.rollAmount = 0;
            break;
            
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    mousePressed(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
//    drone.controller.rollAmount = ofMap(mouseX, 0, ofGetWidth(), -1, 1, true);
//    drone.controller.pitchAmount = ofMap(mouseY, 0, ofGetHeight(), -1, 1, true);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
//    drone.controller.rollAmount = 0;
//    drone.controller.pitchAmount = 0;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    if(drone.controller.commandHistory.getMaxLength()) {
        drone.controller.commandHistory.setMaxLength((ofGetHeight()-280)/14);
        drone.dataReceiver.commandHistory.setMaxLength(drone.controller.commandHistory.getMaxLength());
    }
}
