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


namespace ofxARDrone {
    
    class State {
        friend class Drone;
        friend class Controller;
        friend class Receiver;
        
    public:
        State();
        
        bool isFlying()                     { return bFlying.get(); }
        bool isTakingOff()                  { return bTakingOff.get(); }
        bool isLanding()                    { return bLanding.get(); }
        bool isCalibratingHorizontal()      { return bCalibratingHorizontal.get(); }
        bool isCalibratingMagnetometer()    { return bCalibratingMagnetometer.get(); }
        
        int isFlyingMillis()                     { return bFlying.millisSinceLastChange(); }
        int isTakingOffMillis()                  { return bTakingOff.millisSinceLastChange(); }
        int isLandingMillis()                    { return bLanding.millisSinceLastChange(); }
        int isCalibratingHorizontalMillis()      { return bCalibratingHorizontal.millisSinceLastChange(); }
        int isCalibratingMagnetometerMillis()    { return bCalibratingMagnetometer.millisSinceLastChange(); }
        
        void update();
        
    protected:
        // dangerous to play with these, they should only be available to friend classes
        void setFlying(bool b);
        void setTakingOff(bool b, int revertMillis); // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        void setLanding(bool b, int revertMillis);   // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        void setCalibratingHorizontal(bool b, int revertMillis);     // if revertMillis is nonzero, automatically cancels state after this many milliseconds
        void setCalibratingMagnetometer(bool b, int revertMillis);   // if revertMillis is nonzero, automatically cancels state after this many milliseconds

    private:
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        class Parameter {
        public:
            Parameter():value(false), changeTimestamp(0), revertTimestamp(0) {}
            
            // if revertMillis is nonzero, automatically cancels state after this many milliseconds
            void set(bool b, int revertMillis);
            bool get();
            int millisSinceLastChange();
            void update();
            
        protected:
            bool value;
            int changeTimestamp;    // last timestamp at which state changed (in milliseconds)
            int revertTimestamp;    // at what timestamp state should revert to false (if non-zero)
        };
        
        Parameter bFlying;
        Parameter bTakingOff;
        Parameter bLanding;
        Parameter bCalibratingHorizontal;
        Parameter bCalibratingMagnetometer;
    };
}