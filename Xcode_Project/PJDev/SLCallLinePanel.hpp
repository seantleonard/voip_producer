//
//  SLCallLinePanel.hpp
//  PJDev
//
//  Created by Sean Leonard on 8/19/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//
#pragma once
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/bitmap.h>
#include <wx/stattext.h>
#include <wx/animate.h>
#include <wx/mediactrl.h>
#include "EventID.hpp"

#include "pjsua2.hpp"
using namespace pj;

class SLCallLinePanel : public wxPanel
{
public:
    SLCallLinePanel(wxFrame* parent);
    void updateLineRing();
    void updateLineHold();
    void updateLineActive();
    void answerLine(wxCommandEvent& event);
    void handleLineButton(wxCommandEvent& event);
    void handleLineStatus(wxCommandEvent& event);

    void activateLine(CallInfo &info);

    void mSetPJThread();
    
    void SetupBitmap();
    
    void clearLine(int lineNumber);

    //Buffer that stores current drawing as bitmap
    wxBitmap mBitmap;
    void SetModel(std::shared_ptr<class LineModel> model);

    //Shared ptr
    std::shared_ptr<class LineModel> mModel;
    
protected:
    void PaintNow();
    void PaintEvent(wxPaintEvent & evt);
    void Render(wxDC& dc);
    void DrawPanel(wxDC& dc);
    
    std::string mNameLabel;
    std::string mCityLabel;
    std::string mCommentLabel;
    std::string mNumberLabel;
    
    wxStaticText mNumberLabelWX;
   
    //Control Column  Button | Status
    wxButton *line01Button;
    wxAnimationCtrl *lineOneStatus;
    
    wxButton *line02Button;
    wxAnimationCtrl *lineTwoStatus;
    
    wxButton *line03Button;
    wxAnimationCtrl *lineThreeStatus;

    DECLARE_EVENT_TABLE()

};

enum
{
    BUTTON_Line01 = wxID_HIGHEST+1
};