//
//  SLAccount.hpp
//  PJDev
//
//  Created by Sean Leonard on 8/18/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#ifndef SLAccount_hpp
#define SLAccount_hpp
#include <stdio.h>
#include <iostream>
#include <pjsua2.hpp>
#endif /* SLAccount_hpp */

class SLCall;
using namespace pj;

class SLAccount : public Account
{
    
public:
    SLAccount();
    ~SLAccount();
    
    void onRegState(OnRegStateParam &prm);
    void onRegStarted(OnRegStartedParam &prm);
    void onIncomingCall(OnIncomingCallParam &iprm);
    void mRemoveCall(SLCall *call);
    std::vector<Call *> mCalls;

    void addCallfromCallCenter(SLCall* incomingCall);
    void removeCallfromCallCenter(int lineNumber);
    

    SLCall *mCallCenter[8];
private:
    std::mutex callCenterMutex;
    
};