//
//  ofxARDroneConstants.h
//  ofxARDrone Example
//
//  Created by Jonas Jongejan on 02/11/13.
//
//

#pragma once 

namespace ofxARDrone {
    
    
    struct DRONE_STATUS {
        uint32_t header;
        uint32_t droneState;
        uint32_t sequenceNumber;
        uint32_t visionFlag;
    };
    
    
    typedef enum {
        ARDRONE_FLY_MASK            = 1U << 0,  /*!< FLY MASK : (0) ardrone is landed, (1) ardrone is flying */
        ARDRONE_VIDEO_MASK          = 1U << 1,  /*!< VIDEO MASK : (0) video disable, (1) video enable */
        ARDRONE_VISION_MASK         = 1U << 2,  /*!< VISION MASK : (0) vision disable, (1) vision enable */
        ARDRONE_CONTROL_MASK        = 1U << 3,  /*!< CONTROL ALGO : (0) euler angles control, (1) angular speed control */
        ARDRONE_ALTITUDE_MASK       = 1U << 4,  /*!< ALTITUDE CONTROL ALGO : (0) altitude control inactive (1) altitude control active */
        ARDRONE_USER_FEEDBACK_START = 1U << 5,  /*!< USER feedback : Start button state */
        ARDRONE_COMMAND_MASK        = 1U << 6,  /*!< Control command ACK : (0) None, (1) one received */
        ARDRONE_CAMERA_MASK         = 1U << 7,  /*!< CAMERA MASK : (0) camera not ready, (1) Camera ready */
        ARDRONE_TRAVELLING_MASK     = 1U << 8,  /*!< Travelling mask : (0) disable, (1) enable */
        ARDRONE_USB_MASK            = 1U << 9,  /*!< USB key : (0) usb key not ready, (1) usb key ready */
        ARDRONE_NAVDATA_DEMO_MASK   = 1U << 10, /*!< Navdata demo : (0) All navdata, (1) only navdata demo */
        ARDRONE_NAVDATA_BOOTSTRAP   = 1U << 11, /*!< Navdata bootstrap : (0) options sent in all or demo mode, (1) no navdata options sent */
        ARDRONE_MOTORS_MASK  	      = 1U << 12, /*!< Motors status : (0) Ok, (1) Motors problem */
        ARDRONE_COM_LOST_MASK       = 1U << 13, /*!< Communication Lost : (1) com problem, (0) Com is ok */
        ARDRONE_SOFTWARE_FAULT      = 1U << 14, /*!< Software fault detected - user should land as quick as possible (1) */
        ARDRONE_VBAT_LOW            = 1U << 15, /*!< VBat low : (1) too low, (0) Ok */
        ARDRONE_USER_EL             = 1U << 16, /*!< User Emergency Landing : (1) User EL is ON, (0) User EL is OFF*/
        ARDRONE_TIMER_ELAPSED       = 1U << 17, /*!< Timer elapsed : (1) elapsed, (0) not elapsed */
        ARDRONE_MAGNETO_NEEDS_CALIB = 1U << 18, /*!< Magnetometer calibration state : (0) Ok, no calibration needed, (1) not ok, calibration needed */
        ARDRONE_ANGLES_OUT_OF_RANGE = 1U << 19, /*!< Angles : (0) Ok, (1) out of range */
        ARDRONE_WIND_MASK 		  = 1U << 20, /*!< WIND MASK: (0) ok, (1) Too much wind */
        ARDRONE_ULTRASOUND_MASK     = 1U << 21, /*!< Ultrasonic sensor : (0) Ok, (1) deaf */
        ARDRONE_CUTOUT_MASK         = 1U << 22, /*!< Cutout system detection : (0) Not detected, (1) detected */
        ARDRONE_PIC_VERSION_MASK    = 1U << 23, /*!< PIC Version number OK : (0) a bad version number, (1) version number is OK */
        ARDRONE_ATCODEC_THREAD_ON   = 1U << 24, /*!< ATCodec thread ON : (0) thread OFF (1) thread ON */
        ARDRONE_NAVDATA_THREAD_ON   = 1U << 25, /*!< Navdata thread ON : (0) thread OFF (1) thread ON */
        ARDRONE_VIDEO_THREAD_ON     = 1U << 26, /*!< Video thread ON : (0) thread OFF (1) thread ON */
        ARDRONE_ACQ_THREAD_ON       = 1U << 27, /*!< Acquisition thread ON : (0) thread OFF (1) thread ON */
        ARDRONE_CTRL_WATCHDOG_MASK  = 1U << 28, /*!< CTRL watchdog : (1) delay in control execution (> 5ms), (0) control is well scheduled */
        ARDRONE_ADC_WATCHDOG_MASK   = 1U << 29, /*!< ADC Watchdog : (1) delay in uart2 dsr (> 5ms), (0) uart2 is good */
        ARDRONE_COM_WATCHDOG_MASK   = 1U << 30, /*!< Communication Watchdog : (1) com problem, (0) Com is ok */
        ARDRONE_EMERGENCY_MASK      = 1U << 31  /*!< Emergency landing : (0) no emergency, (1) emergency */
    } status_mask;
    
    
    
    struct NAVDATA {
        uint16_t    tag;					  /*!< Navdata block ('option') identifier */
        uint16_t    size;					  /*!< set this to the size of this structure */
        
        uint32_t    ctrl_state;             /*!< Flying state (landed, flying, hovering, etc.) defined in CTRL_STATES enum. */
        uint32_t    vbat_flying_percentage; /*!< battery voltage filtered (mV) */
        
        float   theta;                  /*!< UAV's pitch in milli-degrees */
        float   phi;                    /*!< UAV's roll  in milli-degrees */
        float   psi;                    /*!< UAV's yaw   in milli-degrees */
        
        int32_t     altitude;               /*!< UAV's altitude in centimeters */
        
        float   vx;                     /*!< UAV's estimated linear velocity */
        float   vy;                     /*!< UAV's estimated linear velocity */
        float   vz;                     /*!< UAV's estimated linear velocity */
        
        uint32_t    num_frames;			  /*!< streamed frame index */ // Not used -> To integrate in video stage.
        
        // Camera parameters compute by detection
        ofMatrix3x3  detection_camera_rot;   /*!<  Deprecated ! Don't use ! */
        ofVec3f  detection_camera_trans; /*!<  Deprecated ! Don't use ! */
        uint32_t	  detection_tag_index;    /*!<  Deprecated ! Don't use ! */
        
        uint32_t	  detection_camera_type;  /*!<  Type of tag searched in detection */
        
        // Camera parameters compute by drone
        ofMatrix3x3  drone_camera_rot;		  /*!<  Deprecated ! Don't use ! */
        ofVec3f  drone_camera_trans;	  /*!<  Deprecated ! Don't use ! */
        
    };
    
    
    
    static const int32_t AnimationDefaultDurations[20] = {
        1000,  // ARDRONE_ANIM_PHI_M30_DEG
        1000,  // ARDRONE_ANIM_PHI_30_DEG
        1000,  // ARDRONE_ANIM_THETA_M30_DEG
        1000,  // ARDRONE_ANIM_THETA_30_DEG
        1000,  // ARDRONE_ANIM_THETA_20DEG_YAW_200DEG
        1000,  // ARDRONE_ANIM_THETA_20DEG_YAW_M200DEG
        5000,  // ARDRONE_ANIM_TURNAROUND
        5000,  // ARDRONE_ANIM_TURNAROUND_GODOWN
        2000,  // ARDRONE_ANIM_YAW_SHAKE
        5000,  // ARDRONE_ANIM_YAW_DANCE
        5000,  // ARDRONE_ANIM_PHI_DANCE
        5000,  // ARDRONE_ANIM_THETA_DANCE
        5000,  // ARDRONE_ANIM_VZ_DANCE
        5000,  // ARDRONE_ANIM_WAVE
        5000,  // ARDRONE_ANIM_PHI_THETA_MIXED
        5000,  // ARDRONE_ANIM_DOUBLE_PHI_THETA_MIXED
        15,  // ARDRONE_ANIM_FLIP_AHEAD
        15,  // ARDRONE_ANIM_FLIP_BEHIND
        15,  // ARDRONE_ANIM_FLIP_LEFT
        15,  // ARDRONE_ANIM_FLIP_RIGHT
    };
    
    // Mayday scenarii
    typedef enum {
        ARDRONE_ANIM_PHI_M30_DEG= 0,
        ARDRONE_ANIM_PHI_30_DEG,
        ARDRONE_ANIM_THETA_M30_DEG,
        ARDRONE_ANIM_THETA_30_DEG,
        ARDRONE_ANIM_THETA_20DEG_YAW_200DEG,
        ARDRONE_ANIM_THETA_20DEG_YAW_M200DEG,
        ARDRONE_ANIM_TURNAROUND,
        ARDRONE_ANIM_TURNAROUND_GODOWN,
        ARDRONE_ANIM_YAW_SHAKE,
        ARDRONE_ANIM_YAW_DANCE,
        ARDRONE_ANIM_PHI_DANCE,
        ARDRONE_ANIM_THETA_DANCE,
        ARDRONE_ANIM_VZ_DANCE,
        ARDRONE_ANIM_WAVE,
        ARDRONE_ANIM_PHI_THETA_MIXED,
        ARDRONE_ANIM_DOUBLE_PHI_THETA_MIXED,
        ARDRONE_ANIM_FLIP_AHEAD,
        ARDRONE_ANIM_FLIP_BEHIND,
        ARDRONE_ANIM_FLIP_LEFT,
        ARDRONE_ANIM_FLIP_RIGHT,
        ARDRONE_NB_ANIM_MAYDAY
    } animations;

}