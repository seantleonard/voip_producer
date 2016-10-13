//
//  SLAccount.cpp
//  PJDev
//
//  Created by Sean Leonard on 8/18/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#include "SLAccount.hpp"
#include "SLSipFrame.hpp"
#include "SLCall.hpp"
#include "SLCallLinePanel.hpp"

#include "SLMasterControl.hpp"
#include <wx/wx.h>
//#include "EventID.hpp"

SLAccount::SLAccount()
{
    for(int i =0; i<8; i++)
    {
        mCallCenter[i] = NULL;
    }
}

SLAccount::~SLAccount()
{
    std::cout << "*** Account is being deleted ***"<< std::endl;
}

void SLAccount::onRegState(OnRegStateParam &prm)
{
    AccountInfo ai = getInfo();
    std::cout << (ai.regIsActive? "*** onRegister: code=" : "*** onUnregister: code=")
    << prm.code << std::endl;
    
    PresenceStatus ps;
    ps.status = PJSUA_BUDDY_STATUS_ONLINE;
    
    if(ai.regIsActive)
    {
        setOnlineStatus(ps);
    }
    else
    {
        std::cout<<"wtf"<<std::endl;
    }
}

void SLAccount::onRegStarted(OnRegStartedParam &prm)
{
    AccountInfo ai = getInfo();
    std::cout << (ai.regIsActive? "*** StartRegister: code=": "*** StartUnregister: code=")
    <<std::endl;
}

void SLAccount::onIncomingCall(OnIncomingCallParam &iprm)
{
    SLCall *call = new SLCall(*this, iprm.callId);
    CallInfo ci = call->getInfo();
    CallOpParam prm;
    
    std::cout<< "*** Incoming Call: "<< ci.remoteUri <<" ["<<ci.stateText<<"]"<<std::endl;
    
//    mCalls.push_back(call);
//    prm.statusCode = (pjsip_status_code)200;
//    
//    SLMasterControl::get().mLineRing(1, ci);
//    
    
    addCallfromCallCenter(call);
}

void SLAccount::mRemoveCall(SLCall *call)
{
    for (std::vector<Call *>::iterator callIterator = mCalls.begin();
         callIterator != mCalls.end(); ++callIterator)
    {
        if (*callIterator == call) {
            mCalls.erase(callIterator);
            break;
        }
    }
}

void SLAccount::addCallfromCallCenter(SLCall* incomingCall)
{
    callCenterMutex.lock();
    
    //Cycle through all the lines in the array
    for(int i=0; i<8; i++)
    {
        //empty line? we add here. Fill in next available line
        //we don't always need to add to the end.
        if(mCallCenter[i] == NULL)
        {
            mCallCenter[i] = incomingCall;
            //add line number to call, so upon destruction/disconnect
            //Call->Account knows what line to delete.
            incomingCall->lineNumber = i;
            break; //once we add a call once, that's it.
        }
    }
    //Right now, no else. because PJSIP allows for max calls.
    //so that means any additional past 8, they'll get busy signal
    callCenterMutex.unlock();
    wxCommandEvent *event;
    
    switch(incomingCall->lineNumber){
        case 0:
            event = new wxCommandEvent(wxEVT_COMMAND_TEXT_UPDATED,100);
            break;
        case 1:
            event = new wxCommandEvent(wxEVT_COMMAND_TEXT_UPDATED, 101 );
            break;
        case 2:
            event = new wxCommandEvent(ID_LineThreeButton, 102 );
            break;
        case 3:
            event = new wxCommandEvent(ID_LineFourButton, 100067 );
            break;
        case 4:
            event = new wxCommandEvent(ID_LineFiveButton, 100067 );
            break;
        case 5:
            event = new wxCommandEvent(ID_LineSixButton, 100067 );
            break;
        case 6:
            event = new wxCommandEvent(ID_LineSevenButton, 100067 );
            break;
        case 7:
            event = new wxCommandEvent(ID_LineEightButton, 100067 );
            break;
        default:
            break;
    }
    
    //Now we can signal the GUI the line number to activate.
    SLMasterControl::get().mainFrame->mLinePanel->GetEventHandler()->AddPendingEvent( *event );
    
    // maybe add "access" for mainfram event handler in slmastercontrol.

}

void SLAccount::removeCallfromCallCenter(int lineNumber)
{
    callCenterMutex.lock();
    mCallCenter[lineNumber] = NULL;
    SLMasterControl::get().mClearLine(lineNumber);
    callCenterMutex.unlock();

}