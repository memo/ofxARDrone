//
//  ofxARDroneState.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 07/12/2012.
//  www.memo.tv
//
//

//--------------------------------------------------------------
/*
 
 class to manage the State of the Drone
 
 */
//--------------------------------------------------------------

#pragma once

#include "ofMain.h"

#include "ofxARDroneConstants.h"




namespace ofxARDrone {
    
    class State {
        friend class Drone;
        friend class Controller;
        friend class DataReceiver;
        
    public:
        State();
        
        bool isConnected()                  { return bConnected.get(); }
        bool isTakingOff()                  { return bTakingOff.get(); }
        bool isLanding()                    { return bLanding.get(); }
        bool isCalibratingHorizontal()      { return bCalibratingHorizontal.get(); }
        bool isCalibratingMagnetometer()    { return bCalibratingMagnetometer.get(); }
        
        int isTakingOffMillis()                  { return bTakingOff.millisSinceLastChange(); }
        int isLandingMillis()                    { return bLanding.millisSinceLastChange(); }
        int isCalibratingHorizontalMillis()      { return bCalibratingHorizontal.millisSinceLastChange(); }
        int isCalibratingMagnetometerMillis()    { return bCalibratingMagnetometer.millisSinceLastChange(); }
        
        void update();
        
        bool isFlying()                     { return getState(ARDRONE_FLY_MASK); }
        bool inEmergencyMode()              { return !getState(ARDRONE_EMERGENCY_MASK); }
        uint32_t getBatteryPercentage()     { return getNavData().vbat_flying_percentage; }

        //Milli degrees
        float getPitch()                    { return getNavData().theta; }
        float getRoll()                     { return getNavData().phi; }
        float getYaw()                      { return getNavData().psi; }
        
        //Centimeters
        int getAltitude()                   { return getNavData().altitude; }
        
        float getVx()                       { return getNavData().vx; }
        float getVy()                       { return getNavData().vy; }
        float getVz()                       { return getNavData().vz; }
        
        
        //Advanced states. See ofxARDroneConstants to see possible data
        bool getState(status_mask mask)     { return bDroneStatus.droneState & mask ? TRUE : FALSE; };
        NAVDATA getNavData()                { return bNavData; };
        

    protected:
        // dangerous to play with these, they should only be available to friend classes
        void setTakingOff(bool b, int revertMillis); // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        void setLanding(bool b, int revertMillis);   // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        void setCalibratingHorizontal(bool b, int revertMillis);     // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        void setCalibratingMagnetometer(bool b, int revertMillis);   // if revertMillis is nonzero, automatically cancels state after this many milliseconds

        void setConnected(bool b, int revertMillis);
        
        
        DRONE_STATUS bDroneStatus;
        NAVDATA bNavData;

    private:
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class Parameter {
        public:
            Parameter():value(false), changeTimestamp(0), revertTimestamp(0) {}
            
            // if revertMillis is nonzero, automatically cancels state after this many milliseconds
            void set(bool b, int revertMillis, bool resetTimer = false);
            bool get();
            int millisSinceLastChange();
            void update();
            
        protected:
            bool value;
            int changeTimestamp;    // last timestamp at which state changed (in milliseconds)
            int revertTimestamp;    // at what timestamp state should revert to false (if non-zero)
        };
        
        Parameter bConnected;
        Parameter bTakingOff;
        Parameter bLanding;
        Parameter bCalibratingHorizontal;
        Parameter bCalibratingMagnetometer;
    };
}