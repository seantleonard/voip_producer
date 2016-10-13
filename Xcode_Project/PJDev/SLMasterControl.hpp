//
//  SLMasterControl.hpp
//  PJDev
//
//  Created by Sean Leonard on 8/19/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#ifndef SLMasterControl_hpp
#define SLMasterControl_hpp
#include <stdio.h>
#include <iostream>
#include "Singleton.h"
#include "pjsua2.hpp"
#endif /* SLMasterControl_hpp */

using namespace pj;
class SLSipFrame;
class SLAccount;

class SLMasterControl : public Singleton<SLMasterControl>
{
    DECLARE_SINGLETON(SLMasterControl);
public:
    SLMasterControl();
    ~SLMasterControl();
    void mSetPJThread();
    void mSetFrame( SLSipFrame *frame);
    void mLineRing(int lineNumber, CallInfo &callInfo);
    void mAnswerLine(int lineNumber);
    
    
    //Handle the phone lines GUI
    void mHandleLineButton(int lineNumber);
    void mClearLine(int lineNumber);
    
    //Call Center Methods
    void addCall();
    void removeCall();
    
    

    SLSipFrame *mainFrame;
private:  
    void startUserAgent();    
    SLAccount *mAccount;
    
    
    //Line Logic Arrays
    int mActive[4] = {0,0,0,0};
    int mHold[4]   = {0,0,0,0};
    int mLocked[4] = {0,0,0,0};
    
};