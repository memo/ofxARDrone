//
//  ofxARDroneCommand.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//

#include "ofxARDroneCommand.h"

namespace ofxARDrone {
    
#define MAX_COMMAND_LENGTH      1024
    
    //--------------------------------------------------------------
    void Command::setName(string commandName) {
        this->commandName = commandName;
    }
    
    //--------------------------------------------------------------
    void Command::addInt(uint32_t i) {
        params.push_back(i);
    }
    
    //--------------------------------------------------------------
    void Command::addFloat(float f) {
        // floats are stored in int memory space, as ints
        assert(sizeof(uint32_t)==sizeof(float));
        params.push_back(*(uint32_t*)(&f));
    }
    
    //--------------------------------------------------------------
    void Command::reset() {
        params.clear();
    }
    
    //--------------------------------------------------------------
    string Command::getString(uint32_t sequenceNumber) {
        string s = "AT*";
        s += commandName;
        s += "=";
        s +=  ofToString(sequenceNumber);
        for(int i=0; i<params.size(); i++) {
            s += ",";
            s += ofToString(params[i]);
        }
//        s += char(0x0A);
        
        if(s.length()>=MAX_COMMAND_LENGTH) ofLogError("Drone::makeATCommand - length of ATCommand too long " + s.length());
        return s;
    }

}