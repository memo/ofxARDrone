//
//  ofxARDroneCommand.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//

//--------------------------------------------------------------
/*
 
 INTERNAL CLASS
 A single control command sent to a Drone
 
 */
//--------------------------------------------------------------


#pragma once

#include "ofMain.h"
#include <assert.h>

namespace ofxARDrone {
    
    class Command {
    public:
        void setName(string commandName);
        void addInt(uint32_t i);
        void addFloat(float f);
        void reset();
        
        string getString(uint32_t sequenceNumber);
        
    protected:
        string commandName;
        vector<uint32_t> params; // parameters EXCLUDING sequence number
    };
    
}
