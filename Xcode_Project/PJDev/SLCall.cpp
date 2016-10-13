//
//  SLCall.cpp
//  PJDev
//
//  Created by Sean Leonard on 8/18/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#include "SLCall.hpp"
#include "SLAccount.hpp"
#include "SLMasterControl.hpp"
#include <CoreFoundation/CoreFoundation.h>

SLCall::SLCall(SLAccount &acc, int call_id = PJSUA_INVALID_ID)
:Call(acc, call_id)
{
    mAccount = &acc;
    lineNumber = -1;
}



void SLCall::onCallState(OnCallStateParam &prm)
{
    PJ_UNUSED_ARG(prm);
    
    CallInfo ci = getInfo();
    
    /* DISCONNECTED: Delete the call */
    if (ci.state == PJSIP_INV_STATE_DISCONNECTED) {
//        mAccount->mRemoveCall(this);
        mAccount->removeCallfromCallCenter(this->lineNumber);
        std::cout<<"disconnected"<<std::endl;
        delete this;
    }
}

void SLCall::onCallMediaState(OnCallMediaStateParam &prm)
{
    CallInfo ci = getInfo();

    AudioMedia& cap_med = Endpoint::instance().audDevManager().getCaptureDevMedia();
    AudioMedia *aud_med = NULL;
    //iterate call info for call media and transmit
    for (unsigned i = 0; i < ci.media.size(); i++){
        //gets the pjmedia audio
        if (ci.media[i].type == PJMEDIA_TYPE_AUDIO && getMedia(i)){
            aud_med = (AudioMedia *)getMedia(i);
            break;
        }
    }
    

    //Establish audio transmission with caller.
    //Start up audio player to transmit file upon call answer
    try{
        player = new AudioMediaPlayer;
        player->createPlayer("TelosZingExtend.wav", PJMEDIA_FILE_NO_LOOP);
        player->startTransmit(*aud_med);
    }catch(Error& err){
        std::cout<<"Error Player:"<<&err<<std::endl;
    }
    
    //connect the call audio media to sound device
    AudDevManager& mgr = Endpoint::instance().audDevManager();
//    aud_med->startTransmit(mgr.getPlaybackDevMedia());
    mgr.getCaptureDevMedia().startTransmit(*aud_med);


}
