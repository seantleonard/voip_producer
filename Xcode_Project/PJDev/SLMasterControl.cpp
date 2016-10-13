//
//  SLMasterControl.cpp
//  PJDev
//
//  Created by Sean Leonard on 8/19/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#include "SLMasterControl.hpp"
#include "SLAccount.hpp"
#include "SLSipFrame.hpp"
#include "SLCall.hpp"
#include "SLCallLinePanel.hpp"
#include <wx/wx.h>
#include <thread>

SLMasterControl::SLMasterControl()
{
     startUserAgent();
}

void SLMasterControl::mSetFrame(SLSipFrame *frame)
{
    mainFrame = frame;
}

#pragma mark User Agent
void SLMasterControl::startUserAgent()
{
    
    std::thread pjsipThread([this]{
        Endpoint ep;
        
        try {
            ep.libCreate();
            
            //startPJSUA2(ep);
        } catch (pj::Error & err) {
            std::cout << "Exception: " << err.info() << std::endl;
            // ret = 1;
        }
        
        // Init library
        pj::EpConfig ep_cfg;
        // ep_cfg.medConfig.
        ep_cfg.uaConfig.maxCalls=2;
        ep_cfg.logConfig.level = 2;
        //ep_cfg.uaConfig.mainThreadOnly = true;
        ep.libInit( ep_cfg );
        
        
        // Transport
        pj::TransportConfig tcfg;
        tcfg.port = 5060;
        ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
        
        AudioDevInfoVector devicesAvailable(ep.audDevManager().enumDev());
        
        for(auto it = devicesAvailable.begin(); it != devicesAvailable.end(); ++it)
                {
                    std::cout<< (*it)->name <<" :: "<<"Routes#: "<< (*it)->routes
                    <<" Caps: "<<(*it)->caps<<std::endl;
                }
        ep.audDevManager().setCaptureDev(1);
        ep.audDevManager().setPlaybackDev(0);
        // Start library
        ep.libStart();
        std::cout << "*** PJSUA2 STARTED ***" << std::endl;
        //
        
        std::mutex mtx;
        
        mtx.lock();

        AccountConfig acc_cfg;
        acc_cfg.idUri = "sip:radiojoq@getonsip.com";
        acc_cfg.regConfig.registrarUri = "sip:getonsip.com";
        acc_cfg.sipConfig.proxies.push_back("<sip:sip.onsip.com>");
        acc_cfg.sipConfig.authCreds.push_back( AuthCredInfo("digest", "*",
                                                            "getonsip_radiojoq", 0, "sqHCcMyf76isbZX6") );
        
        this->mAccount = new SLAccount;
        this->mSetPJThread();
        
        mtx.unlock();
     //   mAccount = acc;
        mAccount->create(acc_cfg);

        while(ep.libGetState() == PJSUA_STATE_RUNNING )
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

    });
    pjsipThread.detach();
    
}


#pragma mark Handling

void SLMasterControl::mLineRing(int lineNumber, CallInfo &callInfo)
{
    std::cout<< "INCOMING FROM: "<< callInfo.remoteUri << std::endl;
    
    //Call Panel Update call Line Info
    wxCommandEvent event( wxEVT_COMMAND_TEXT_UPDATED, 100067 );
    event.SetInt(8185903201);  // pass some data along the event, a number in this case
    SLMasterControl::get().mainFrame->mLinePanel->GetEventHandler()->AddPendingEvent( event );
    mainFrame->mLinePanel->activateLine(callInfo);
}

void SLMasterControl::mClearLine(int lineNumber)
{
    mainFrame->mLinePanel->clearLine(lineNumber);
    mActive[lineNumber] = 0;
    mHold[lineNumber] = 0;
    mLocked[lineNumber] = 0;
    
    
}

void SLMasterControl::mHandleLineButton(int lineNumber)
{
    //Check to make sure there is actually a call first
//    if(mAccount->mCallCenter[lineNumber] != NULL && mAccount->mCallCenter.size() > 0)

    if(mAccount->mCallCenter[lineNumber] != NULL)
    {
        if (mActive[lineNumber] == 0)
        {
            if(mHold[lineNumber] == 0)
            {
                mActive[lineNumber] = 1;
                //Answer Call Here
                mAnswerLine(lineNumber);
            }else if (mHold[lineNumber] == 1)
            {
                mActive[lineNumber] = 1;
                mHold[lineNumber] = 0;
                //reset the audio routes
                //update the gui line image
            }
        }else if(mActive[lineNumber] == 1)
        {
            if( mLocked[lineNumber] == 0)
            {
                mLocked[lineNumber] = 1;
                //Send Locked to gui
                //other lock logic
            }else{
                mLocked[lineNumber] = 0;
                // update unlocked to gui
            }
        }
    }
    
    //If there is no call on the line, then do nothing.
    
}

void SLMasterControl::mAnswerLine(int lineNumber)
{
    std::cout<<"Thread Registered: "<<pj_thread_is_registered()<<" Line:"<<lineNumber<<std::endl;

        if (!pj_thread_is_registered()) {
            pj_status_t status;
            pj_thread_desc aPJThreadDesc;
            pj_thread_t *pjThread;
            status = pj_thread_register(NULL, aPJThreadDesc, &pjThread);
            if (status != PJ_SUCCESS) {
                std::cout<<"Error registering thread at PJSUA"<<std::endl;
            }
        }
    CallOpParam prm;
    prm.statusCode = (pjsip_status_code)200;
    
    // maybe we need to do some sort of check/ test here to make sure line is correct.
    
    mAccount->mCallCenter[lineNumber]->answer(prm);
}



void SLMasterControl::mSetPJThread()
{
    mainFrame->mSetPJThread();
    

}

SLMasterControl::~SLMasterControl()
{
    
}
