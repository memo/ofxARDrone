//
//  ofxMSAHistory.h
//  ofxARDrone Example
//
//  Created by Memo Akten on 06/12/2012.
//  www.memo.tv
//
//

#pragma once

namespace msa {
    
    template <class Type>
    class HistoryT {
    public:
        
        //--------------------------------------------------------------
        HistoryT() {
            // arbitrary init
            setMaxLength(10);
        }
        
        //--------------------------------------------------------------
        void push_back(Type &t) {
            if(maxLength) {
                history.push_back(t);
                if(history.size()>maxLength) history.pop_front();
            }
        }
        
        //--------------------------------------------------------------
        void push_front(Type &t) {
            if(maxLength) {
                history.push_front(t);
                if(history.size()>maxLength) history.pop_back();
            }
        }
        
        //--------------------------------------------------------------
        void pop_front(Type &t) {
            history.pop_front();
        }

        //--------------------------------------------------------------
        void pop_back(Type &t) {
            history.pop_back();
        }

        //--------------------------------------------------------------
        int getLength() {
            return history.size();
        }

        //--------------------------------------------------------------
        int getMaxLength() {
            return maxLength;
        }
        
        //--------------------------------------------------------------
        void setMaxLength(int i) {
            maxLength = i;
            clear();
        }
        
        //--------------------------------------------------------------
        string getAsString(string separator = "") {
            string t;
            for(typename list<Type>::iterator it=history.begin(); it!=history.end(); ++it) {
                t += ofToString(*it) + separator;
            }
            return t;
            
        }
        
        //--------------------------------------------------------------
        list<Type>& getAsList() {
            return history;
        }

        //--------------------------------------------------------------
        void clear() {
            history.clear();
        }
        
    protected:
        list<Type> history;
        int maxLength;
    };
    
}