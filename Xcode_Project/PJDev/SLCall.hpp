//
//  SLCall.hpp
//  PJDev
//
//  Created by Sean Leonard on 8/18/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#ifndef SLCall_hpp
#define SLCall_hpp
#include <stdio.h>
#include <iostream>
#endif /* SLCall_hpp */
#include "pjsua2.hpp"

using namespace pj;
class SLAccount;

class SLCall: public Call
{
public:
    SLCall(SLAccount &acc, int call_id);
    
    void onCallState(OnCallStateParam &prm);
    void onCallMediaState(OnCallMediaStateParam &prm);
    
    int lineNumber;
    
private:
    SLAccount *mAccount;
    AudioMediaPlayer *player;

};