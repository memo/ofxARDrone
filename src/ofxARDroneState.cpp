//
//  ofxARDroneState.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 07/12/2012.
//  www.memo.tv
//
//

#include "ofxARDroneState.h"

namespace ofxARDrone {
    
    //--------------------------------------------------------------
    State::State() {
        memset(this, 0, sizeof(*this));
    }
    
    //--------------------------------------------------------------
    //    State::~State() {
    //
    //    }
    
    
    //--------------------------------------------------------------
    void State::setConnected(bool b, int revertMillis){
        ofLogVerbose("ofxARDrone::State::setConnected - " + ofToString(b) + ", " + ofToString(revertMillis));
        bConnected.set(b, revertMillis, true);
    }
    
    //--------------------------------------------------------------
    void State::setTakingOff(bool b, int revertMillis) {
        ofLogVerbose("ofxARDrone::State::setTakingOff - " + ofToString(b) + ", " + ofToString(revertMillis));
        
        bTakingOff.set(b, revertMillis);
        
        if(bTakingOff.get()) {
            setLanding(false, 0);
        }
    }
    
    
    //--------------------------------------------------------------
    void State::setLanding(bool b, int revertMillis) {
        ofLogVerbose("ofxARDrone::State::setLanding - " + ofToString(b) + ", " + ofToString(revertMillis));
        
        bLanding.set(b, revertMillis);
        
        if(bLanding.get()) setTakingOff(false, 0);
    }
    
    //--------------------------------------------------------------
    void State::setCalibratingHorizontal(bool b, int revertMillis) {
        ofLogVerbose("ofxARDrone::State::setCalibratingHorizontal - " + ofToString(b) + ", " + ofToString(revertMillis));
        bCalibratingHorizontal.set(b, revertMillis);
    }
    
    //--------------------------------------------------------------
    void State::setCalibratingMagnetometer(bool b, int revertMillis) {
        ofLogVerbose("ofxARDrone::State::setCalibratingMagnetometer - " + ofToString(b) + ", " + ofToString(revertMillis));
        bCalibratingMagnetometer.set(b, revertMillis);
    }
    
    //--------------------------------------------------------------
    void State::update() {
        bConnected.update();
        bTakingOff.update();
        bLanding.update();
        bCalibratingHorizontal.update();
        bCalibratingMagnetometer.update();
    }
    
    
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    // if revertMillis is nonzero, automatically cancels state after this many milliseconds
    void State::Parameter::set(bool b, int revertMillis, bool resetTimer) {
        if(value != b || resetTimer) {
            value = b;
            changeTimestamp = ofGetElapsedTimeMillis();
            revertTimestamp = revertMillis > 0 ? changeTimestamp + revertMillis : 0;
        }
    }
    
    //--------------------------------------------------------------
    bool State::Parameter::get() {
        return value;
    }
    
    //--------------------------------------------------------------
    int State::Parameter::millisSinceLastChange() {
        return ofGetElapsedTimeMillis() - changeTimestamp;
    }
    
    //--------------------------------------------------------------
    void State::Parameter::update() {
        if(value && revertTimestamp > 0 && ofGetElapsedTimeMillis() > revertTimestamp) {
            set(false, 0);
        }
    }
    

}