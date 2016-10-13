//
//  SLSipFrame.hpp
//  PJDev
//
//  Created by Sean Leonard on 8/19/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#pragma once

#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/menu.h>
class SLCallLinePanel;

class SLSipFrame : public wxFrame
{
public:
    SLSipFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~SLSipFrame();
    void mSetPJThread();
    SLCallLinePanel *mLinePanel;

    
private:
   // class SLCallLinePanel *mLinePanel;

    
};