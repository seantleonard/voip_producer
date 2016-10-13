//
//  SLSipApp.cpp
//  PJDev
//
//  Created by Sean Leonard on 8/19/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#include "SLSipApp.hpp"
#include "SLSipFrame.hpp"
#include "pjsua2.hpp"
#include <iostream>

wxIMPLEMENT_APP(SLSipApp);


bool SLSipApp::OnInit()
{
    if (!pj_thread_is_registered()) {
        pj_status_t status;
        pj_thread_desc guiPJThreadDesc;
        pj_thread_t *pjThreadGui;
        status = pj_thread_register(NULL, guiPJThreadDesc, &pjThreadGui);
        if (status != PJ_SUCCESS) {
            std::cout<<"Error registering thread at GUI"<<std::endl;
        }
    }

    mFrame = new SLSipFrame("SL Producer", wxPoint(-1, -1), wxSize(1250, 600) );
    return true;
}
