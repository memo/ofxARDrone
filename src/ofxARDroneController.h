//
//  ofxARDroneController.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//

//--------------------------------------------------------------
/*
 
 class to manage sending data to the Drone and controlling it
 
 */
//--------------------------------------------------------------

#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

#include "ofxMSABitField.h"
#include "ofxMSAHistory.h"

#include "ofxARDroneConstants.h"
#include "ofxARDroneCommand.h"


namespace ofxARDrone {
    
    class Drone;

    // sends control messages to a Drone
    class Controller {
        friend class Drone;
        
    public:
        
        Controller();
        ~Controller();
        
        void setup(Drone *drone);
        void close();
        
        void update();
        
        
        void takeOff(bool b, int revertMillis);  // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        void land(bool b, int revertMillis); // if revertMillis is nonzero, automatically cancels state after this many milliseconds

        // calibrate horizontal plane, MUST BE SENT WHILE NOT FLYING
        void calibrateHorizontal(bool b, int revertMillis);  // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        
        // calibrate magnetometer, MUST BE SENT WHILE FLYING
        void calibrateMagnetometer(bool b, int revertMillis);    // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        
        void emergency(int on);
        
        // Perform premade animation. Set speed to 0 to use default duration.
        void animation(animations anim, int speed);
        
        
        //--------------------------------------------------------------
        // MOVING
        // you can write to the these variables directly as many times as you want per frame
        // when update() is called, it will send these variables to the Drone
        // they are all in the range -1...1
        
        // tilt and move left / right
        // values in the range -1...1, -ve: left, +ve: right
        float rollAmount;

        // tilt and move forward / backward
        // values in the range -1...1, -ve: front, +ve: back
        float pitchAmount;

        // move up and down
        // values in the range -1...1, -ve: down, +ve: right
        float liftSpeed;

        // spin around horizontally
        // values in the range -1...1, -ve: left, +ve: right
        float spinSpeed;

      
        //--------------------------------------------------------------
        // ADVANCED FUNCTIONS
        
        void exitBootstrap();
        
        void sendAck();
        
        // send if ARDRONE_COM_WATCHDOG_MASK is set (no traffic for >50ms)
        void resetCommunicationWatchdog();
        
        
        void queueCommand(Command &command);
        void queueCommand(string commandString);
        
        unsigned long getMillisSinceLastSend();
        
        // for viewing and manipulation of command history (for debug purposes)
        msa::HistoryT<string> commandHistory;
        
    protected:
        Drone *drone;
        ofxUDPManager udpSender;
        string commandString;
        
        unsigned long millisOfLastSend;
        unsigned long millisSinceLastSend;
    };
}
