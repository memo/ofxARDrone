//
//  ofxARDroneController.cpp
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//

#include "ofxARDroneController.h"
#include "ofxARDrone.h"

namespace ofxARDrone {
    
    
    
    //--------------------------------------------------------------
    Controller::Controller() {
        ofLogVerbose("ofxARDrone::Controller::Controller");
        drone = NULL;
        commandHistory.setMaxLength(0);
        int millisOfLastSend = 0;
        int millisSinceLastSend = 0;
        
        rollAmount = 0;
        pitchAmount = 0;
        liftSpeed = 0;
        spinSpeed = 0;
    }
    
    //--------------------------------------------------------------
    Controller::~Controller() {
        ofLogVerbose("ofxARDrone::Controller::~Controller");
        close();
    }
    
    //--------------------------------------------------------------
    void Controller::setup(Drone* drone) {
        ofLogVerbose("ofxARDrone::Controller::setup - " + ofToString(drone));
        this->drone = drone;

        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }
            
        udpSender.Create();
        udpSender.Connect(drone->commInfo.hostip.c_str(), drone->commInfo.commandPort);
        udpSender.SetNonBlocking(true);
    }
    
    //--------------------------------------------------------------
    void Controller::close() {
        ofLogVerbose("ofxARDrone::Controller::close");
        udpSender.Close();
    }

    
    //--------------------------------------------------------------
    void Controller::update() {
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }
        
        State &state = drone->state;
        
        if(state.isCalibratingHorizontal()) {
            if(state.isFlying()) {
                ofLogWarning("ofxARDrone::Controller::update - shouldn't calibrate horizontal while flying");
                state.setCalibratingHorizontal(false, 0);
            } else {
                Command command;
                command.setName("FTRIM");
                queueCommand(command);
            }
        }
        
        
        if(state.isCalibratingMagnetometer()) {
            if(!state.isFlying()) {
                ofLogWarning("ofxARDrone::Controller::update - should only calibrate magnetometer while flying");
                state.setCalibratingMagnetometer(false, 0);
            } else {
                Command command;
                command.setName("CALIB");
                queueCommand(command);
            }
        }
        
        if(state.isTakingOff() || state.isLanding()) {
            Command command;
            command.setName("REF");
            
            msa::BitField32 bitField;
            bitField.clearAll();
            bitField.setBit(18);
            bitField.setBit(20);
            bitField.setBit(22);
            bitField.setBit(24);
            bitField.setBit(28);
            bitField.setBit(9, state.isTakingOff()); // keep sending until navdata says it's taken off, or landed
            command.addInt(bitField);
            
            queueCommand(command);
        }
        
        rollAmount = ofClamp(rollAmount, -1, 1);
        pitchAmount = ofClamp(pitchAmount, -1, 1);
        liftSpeed = ofClamp(liftSpeed, -1, 1);
        spinSpeed = ofClamp(spinSpeed, -1, 1);
        
        if(state.isFlying()) {
            Command command;
            command.setName("PCMD");
            command.addInt(1);
            command.addFloat(rollAmount);
            command.addFloat(pitchAmount);
            command.addFloat(liftSpeed);
            command.addFloat(spinSpeed);
            
            queueCommand(command);
        }
        
        
        if(commandString.empty() && getMillisSinceLastSend() > 50) resetCommunicationWatchdog();

        
        if(commandString.empty() == false) {
            udpSender.Send(commandString.c_str(), commandString.length());
            commandHistory.push_front(commandString);

            millisOfLastSend = ofGetElapsedTimeMillis();
            this->commandString = "";
        }
    }
    
    //-------------------------------------------------------------- 
//    void Controller::configure(string optionName, string optionValue) {
//        ofLogVerbose("ofxARDrone::Controller::configure - " + optionName + ": " + optionValue);
//        
//        // TODO:
//        Command command;
//        command.setName("CONFIG");
//        queueCommand(command);
//    }
    
    
    //--------------------------------------------------------------
    void Controller::takeOff(bool b, int revertMillis ) {
        ofLogVerbose("ofxARDrone::Controller::takeOff - " + ofToString(b));
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }
        drone->state.setTakingOff(b, revertMillis);
    }
    
    //--------------------------------------------------------------
    void Controller::land(bool b, int revertMillis ) {
        ofLogVerbose("ofxARDrone::Controller::land - " + ofToString(b));
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }
        drone->state.setLanding(b, revertMillis);
    }
    
    
    //--------------------------------------------------------------
    void Controller::emergency(int on) {
        ofLogVerbose("ofxARDrone::Controller::emergency - " + ofToString(on));
        
        Command command;
        command.setName("REF");
        
        msa::BitField32 bitField;
        bitField.clearAll();
        bitField.setBit(18);
        bitField.setBit(20);
        bitField.setBit(22);
        bitField.setBit(24);
        bitField.setBit(28);
        bitField.setBit(8, on);
        command.addInt(bitField);
        
        queueCommand(command);
    }
    
    //--------------------------------------------------------------
    void Controller::animation(animations anim, int speed){
        if(speed == 0){
            speed = AnimationDefaultDurations[anim];
        }
        
        Command command;
        command.setName("CONFIG");
        command.addString("control:flight_anim");
        command.addString(ofToString(anim,0)+","+ofToString(speed,0));
        
        //queueCommand("AT*CONFIG="+ofToString(drone->sequenceNumber++)+",\"control:flight_anim\",\""+ofToString(anim,0)+","+ofToString(speed,0)+"\"");
    }
    
    
    //--------------------------------------------------------------
    void Controller::calibrateHorizontal(bool b, int revertMillis ) {
        ofLogVerbose("ofxARDrone::Controller::calibrateHorizontal - " + ofToString(b));
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }
        drone->state.setCalibratingHorizontal(b, revertMillis);
    }
    
    //--------------------------------------------------------------
    void Controller::calibrateMagnetometer(bool b, int revertMillis ) {
        ofLogVerbose("ofxARDrone::Controller::calibrateMagnetometer - " + ofToString(b));
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }
        drone->state.setCalibratingMagnetometer(b, revertMillis);
    }
    

    //--------------------------------------------------------------
    void Controller::exitBootstrap() {
        ofLogVerbose("ofxARDrone::Controller::exitBootstrap");
        
        Command configCommand;
        configCommand.setName("CONFIG");
        configCommand.addString("general:navdata_demo");
        configCommand.addString("TRUE");
        queueCommand(configCommand);

//        queueCommand("AT*CONFIG="+ofToString(drone->sequenceNumber++)+",\"general:navdata_demo\",\"TRUE\"");
        
        Command command;
        command.setName("CTRL");
        command.addInt(5);
        queueCommand(command);
    }
    
    
    //--------------------------------------------------------------
    void Controller::sendAck() {
        ofLogVerbose("ofxARDrone::Controller::sendAck");
        queueCommand("AT*CTRL=0");
    }

    
    //--------------------------------------------------------------
    void Controller::resetCommunicationWatchdog() {
//        ofLogVerbose("ofxARDrone::Controller::resetCommunicationWatchdog");
        
        queueCommand("AT*COMWDG");
    }

    
    //--------------------------------------------------------------
    void Controller::queueCommand(Command &command) {
        if(drone == NULL) { ofLogError("   Drone is NULL"); return; }

        string commandString = command.getString(drone->sequenceNumber);
        
        queueCommand(commandString);
        drone->sequenceNumber++;
    }
    
    
    //--------------------------------------------------------------
    void Controller::queueCommand(string cs) {
        ofLogVerbose("ofxARDrone::Controller::queueCommand - " + cs);
        
        cs += 0x0D;
        cs += 0x0A; // TODO: is this one needed?
        commandString += cs;
    }
    
    
    //--------------------------------------------------------------
    unsigned long Controller::getMillisSinceLastSend() {
        return ofGetElapsedTimeMillis() - millisOfLastSend;
    }

    

    
}
