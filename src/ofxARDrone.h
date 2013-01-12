//
//  ofxARDrone.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//

//--------------------------------------------------------------
/* 

 This is an openFrameworks addon to interface with and control the Parrot AR.Drone and AR.Drone2 Quadrotor (http://ardrone2.parrot.com/)
 It does NOT use the official SDK in any way.
 Instead it re-implements the open network communication protocol (as outlined in the official documentation) using the standard openFrameworks ofxNetwork addon.
 As such, ofxARDrone addon has no dependencies and will compile and run on any platform that can compile and run ofxNetwork (i.e. currently all openFrameworks platforms).
 

 TODO:
 LOW-LEVEL:
 - read and interpret navdata
 - send configuration data
 - read video streams
 
 HIGH-LEVEL:
 - somehow track absolute position and orientation of Drone
    - cameras on Drone read AR Markers in space
    - cameras in space track Drone
 - AI to hold Drone in position
 - AI to drive Drones along path
 
 */
//--------------------------------------------------------------

#pragma once

#include "ofMain.h"

#include "ofxARDroneController.h"
#include "ofxARDroneDataReceiver.h"
#include "ofxARDroneState.h"
#include "ofxARDroneSimulator.h"

namespace ofxARDrone {

    // An instance of a Drone
    class Drone {
        friend class Controller;
        friend class DataReceiver;
        
    public:
        
        Drone();
        ~Drone();
        
        void connect();
        void disconnect();
        
        void update();
        
        // for sending commands to the Drone
        Controller controller;
        
        // for receiving data from the Drone
        DataReceiver dataReceiver;
        
        // contains information on state
        State state;
        
        
        //--------------------------------------------------------------
        // ADVANCED FUNCTIONS
        // the struct below is filled with defaults
        // over-ride if need be (e.g. if you hack your Drone to listen or send on different ports)
        // WRITE-ONLY
        struct {
            string hostip;
            int commandPort;   // UDP port on which to send commands to the Drone
            int navDataPort;    // UDP port on which navdata comms is made
            int videoPort;      // TODO: TCP/UDP port on which video comms is made
            int controlPort;    // TODO: TCP port for critical comms
        } commInfo;
        
        uint32_t getSequenceNumber();

        void resetSequenceNumber();
        
    protected:
        uint32_t sequenceNumber;
        
    };
    
}
