//
//  ofxMSABitField.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//

#pragma once

namespace msa {
    
    template <class Type>
    class BitFieldT {
    public:
        Type value;
        
        
        //--------------------------------------------------------------
        BitFieldT() {
            value = (Type)0;
        }
        
        //--------------------------------------------------------------
        operator Type() {
            return value;
        }
        
        //--------------------------------------------------------------
        void fillAll() {
            value = 0xFFFF;
        }
        
        //--------------------------------------------------------------
        void clearAll() {
            value = 0;
        }
        
        //--------------------------------------------------------------
        void setBit(int bitNumber) {
            value |= 1 << bitNumber;
        }
        
        //--------------------------------------------------------------
        void clearBit(int bitNumber) {
            value &= ~(1 << bitNumber);
        }
        
        //--------------------------------------------------------------
        void toggleBit(int bitNumber) {
            value ^= 1 << bitNumber;
        }
        
        //--------------------------------------------------------------
        bool checkBit(int bitNumber) {
            return value & (1 << bitNumber);
        }
        
        //--------------------------------------------------------------
        void setBit(int bitNumber, bool on) {
            if(on) setBit(bitNumber);
            else clearBit(bitNumber);
        }
    };
    
    
    //--------------------------------------------------------------
    //--------------------------------------------------------------
    typedef BitFieldT<uint32_t> BitField32;
}