//
//  ofxARDroneDataReceiver.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 07/12/2012.
//  www.memo.tv
//
//

#include "ofxARDroneDataReceiver.h"
#include "ofxARDrone.h"

namespace ofxARDrone {

    //--------------------------------------------------------------
    DataReceiver::DataReceiver() {
        ofLogVerbose("ofxARDrone::DataReceiver::DataReceiver");
        drone = NULL;
        commandHistory.setMaxLength(0);
    }
    
    //--------------------------------------------------------------
    DataReceiver::~DataReceiver() {
        ofLogVerbose("ofxARDrone::DataReceiver::~DataReceiver");
        close();
    }
    
    //--------------------------------------------------------------
    void DataReceiver::setup(Drone* drone) {
        ofLogVerbose("ofxARDrone::DataReceiver::setup - " + ofToString(drone));
        this->drone = drone;
        
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }

        udpReceiver.Create();
        udpReceiver.Bind(drone->commInfo.navDataPort);
        udpReceiver.SetNonBlocking(true);
    }
    
    
    //--------------------------------------------------------------
    void DataReceiver::close() {
        ofLogVerbose("ofxARDrone::DataReceiver::close");
        udpReceiver.Close();
    }
    
    //--------------------------------------------------------------
    void DataReceiver::update() {
        char udpMessage[100000];
        udpReceiver.Receive(udpMessage, 100000);
        string message=udpMessage;
        if(message != "") {
            printf("sdfdf");
            commandHistory.push_front(message);
        }
    }
    
    
}