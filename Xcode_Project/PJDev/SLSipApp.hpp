//
//  SLSipApp.hpp
//  PJDev
//
//  Created by Sean Leonard on 8/19/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//
#if !wxUSE_ANIMATIONCTRL
#error Cannot compile this sample if wxAnimationCtrl is not enabled
#endif
//#define wxUSE_ANIMATIONCTRL 1

#pragma once
#include <wx/wx.h>
#include <wx/app.h>


class SLSipApp : public wxApp
{
public:
    virtual bool OnInit();
private:
    class SLSipFrame* mFrame;
};
