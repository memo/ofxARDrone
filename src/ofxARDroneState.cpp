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
    void State::setFlying(bool b) {
        ofLogVerbose("ofxARDrone::State::setFlying - " + ofToString(b));
        bFlying.set(b, 0);
    }
    
    //--------------------------------------------------------------
    void State::setTakingOff(bool b, int revertMillis) {
        ofLogVerbose("ofxARDrone::State::setTakingOff - " + ofToString(b) + ", " + ofToString(revertMillis));
        
        bTakingOff.set(b, revertMillis);
        
        // if taking off, assume flying (HACK! TODO: read from navdata)
        if(bTakingOff.get()) {
            setFlying(true);
            setLanding(false, 0);
        }
    }
    
    
    //--------------------------------------------------------------
    void State::setLanding(bool b, int revertMillis) {
        ofLogVerbose("ofxARDrone::State::setLanding - " + ofToString(b) + ", " + ofToString(revertMillis));
        
        // if was landing, and now isn't, assume not flying (HACK! TODO: read from navdata)
        if(bLanding.get() == true && b == false) setFlying(false);
        
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
        bFlying.update();
        bTakingOff.update();
        bLanding.update();
        bCalibratingHorizontal.update();
        bCalibratingMagnetometer.update();
    }
    
    
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    // if revertMillis is nonzero, automatically cancels state after this many milliseconds
    void State::Parameter::set(bool b, int revertMillis) {
        if(value != b) {
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