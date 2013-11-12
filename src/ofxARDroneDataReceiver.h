//
//  ofxARDroneDataHandler.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 07/12/2012.
//  www.memo.tv
//
//

//--------------------------------------------------------------
/*
 
 class to manage receiving data from the Drone and updating the State class
 
 */
//--------------------------------------------------------------


#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

#include "ofxMSABitField.h"
#include "ofxMSAHistory.h"

namespace ofxARDrone {
    
    //----------------------------------------------------------
    typedef struct _navdata_option_t {
        uint16_t tag; /* Tag for a specific option */
        uint16_t size; /* Length of the struct */
        uint8_t data[]; /* Structure complete with the special tag */
    } navdata_option_t;
    //----------------------------------------------------------
    
    
    class Drone;
    
    class DataReceiver {
        friend class Drone;

    public:
        
        DataReceiver();
        ~DataReceiver();
        
        void setup(Drone *drone);
        void close();

        // for viewing and manipulation of command history (for debug purposes)
        msa::HistoryT<string> commandHistory;
        
        void sendDummyPacket();

    protected:
        Drone *drone;
        ofxUDPManager udp;
        
        void update();
    };
    
}