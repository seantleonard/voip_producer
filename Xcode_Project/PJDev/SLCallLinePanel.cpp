//
//  SLCallLinePanel.cpp
//  PJDev
//
//  Created by Sean Leonard on 8/19/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#include "SLCallLinePanel.hpp"
#include "SLMasterControl.hpp"
#include "EventID.hpp"
#include <wx/dcclient.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/wfstream.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/image.h>

//wxDEFINE_EVENT(ID_LineOneStatus, wxCommandEvent);

BEGIN_EVENT_TABLE(SLCallLinePanel, wxPanel)
EVT_PAINT(SLCallLinePanel::PaintEvent)
EVT_BUTTON(ID_LineOneButton, SLCallLinePanel::handleLineButton)
EVT_BUTTON(ID_LineTwoButton, SLCallLinePanel::handleLineButton)
//EVT_COMMAND  (ID_LineOneButton, wxEVT_COMMAND_TEXT_UPDATED, SLCallLinePanel::handleLine)
EVT_COMMAND  (100, wxEVT_COMMAND_TEXT_UPDATED,SLCallLinePanel::handleLineStatus)
EVT_COMMAND  (101, wxEVT_COMMAND_TEXT_UPDATED,SLCallLinePanel::handleLineStatus)
EVT_COMMAND  (102, wxEVT_COMMAND_TEXT_UPDATED,SLCallLinePanel::handleLineStatus)


END_EVENT_TABLE()


SLCallLinePanel::SLCallLinePanel(wxFrame* parent)
:wxPanel(parent)
{
    wxImage::AddHandler(new wxPNGHandler);

    mSetPJThread();
    
    wxBoxSizer *allElements = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *infoColumn = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *infoRow = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *controlColumn = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *controlRow = new wxBoxSizer(wxHORIZONTAL);
    
    
    //NAME COLUMN
    wxBoxSizer *infoCol1 = new wxBoxSizer(wxVERTICAL);
    wxStaticText *strName =  new wxStaticText(this, wxID_ANY,
                                              wxT("Name"));
    wxTextCtrl *ctrlName1 = new wxTextCtrl(this, wxID_ANY, wxT(""),
                                           wxPoint(-1, -1), wxSize(100, -1), wxTE_LEFT);
    
    infoCol1->Add(strName, 0,  wxEXPAND | wxBOTTOM, 20);
    infoCol1->Add(ctrlName1, 0,  wxEXPAND | wxLEFT, 0);
    
    //CITY COLUMN
    wxBoxSizer *infoCol2 = new wxBoxSizer(wxVERTICAL);
    wxStaticText *strCity =  new wxStaticText(this, wxID_ANY,
                                              wxT("City"));
    wxTextCtrl *ctrlCity1 = new wxTextCtrl(this, wxID_ANY, wxT(""),
                                           wxPoint(-1, -1), wxSize(100, -1), wxTE_LEFT);
    
    infoCol2->Add(strCity, 0, wxEXPAND | wxBOTTOM, 20);
    infoCol2->Add(ctrlCity1, 0,  wxEXPAND | wxBOTTOM, 0);
    
    //COMMENT COLUMN
    wxBoxSizer *infoCol3 = new wxBoxSizer(wxVERTICAL);
    wxStaticText *strComment =  new wxStaticText(this, wxID_ANY,
                                                 wxT("Comment"));
    wxTextCtrl *ctrlComment1 = new wxTextCtrl(this, wxID_ANY, wxT(""),
                                              wxPoint(-1, -1), wxSize(200, -1), wxTE_LEFT);
    
    infoCol3->Add(strComment, 0, wxEXPAND | wxBOTTOM, 20);
    infoCol3->Add(ctrlComment1, 0, wxEXPAND | wxBOTTOM, 0);
    
    //NUMBER COLUMN
    wxBoxSizer *infoCol4 = new wxBoxSizer(wxVERTICAL);
    wxStaticText *strNumber =  new wxStaticText(this, wxID_ANY,
                                                wxT("Number"));
    mNumberLabelWX.Create(this, wxID_ANY,wxT(""),wxDefaultPosition,wxSize(250,-1), 0, wxT(""));
    infoCol4->Add(strNumber, 0, wxEXPAND | wxBOTTOM, 20);
    infoCol4->Add(&mNumberLabelWX, 0, wxEXPAND | wxLEFT, 0);
    
    //Add labels to the vertical box
    infoRow->Add(infoCol1, 1,  wxLEFT | wxRIGHT, 10);
    infoRow->Add(infoCol2, 1,  wxLEFT | wxRIGHT, 10);
    infoRow->Add(infoCol3, 1,  wxLEFT | wxRIGHT, 10);
    infoRow->Add(infoCol4, 1,  wxLEFT | wxRIGHT, 10);
    
    infoColumn->Add(infoRow, 1, wxEXPAND| wxALL, 10);
    
    //Add Buttons to the Control Column
    //Control Column title
    
    wxBoxSizer *controlRow0 = new wxBoxSizer(wxHORIZONTAL);
    controlRow0->Add(new wxStaticText(this, -1, wxT("Line Button")), 1, wxEXPAND | wxBOTTOM, 20);
    
    //Control Column Button 01
    wxBoxSizer *controlRow1 = new wxBoxSizer(wxHORIZONTAL);
    line01Button = new wxButton(this, ID_LineOneButton, wxT("( 1 )"), wxPoint(-1, -1), wxDefaultSize, 10);
    line01Button->SetLabel("( 1 )");
    
    //Control Column Status 01
    lineOneStatus = new wxAnimationCtrl(this, wxID_ANY,wxNullAnimation,wxDefaultPosition,wxDefaultSize,wxAC_DEFAULT_STYLE  );
    lineOneStatus->LoadFile("Ring4sm.gif", wxANIMATION_TYPE_GIF);
    lineOneStatus->SetInactiveBitmap( wxBitmap(wxImage(wxT("IDLE_sm.png")), wxBITMAP_DEFAULT_TYPE));
    controlRow1->Add(lineOneStatus, 1, wxLEFT | wxRIGHT, 0);
    //lineOneStatus->Play();
    controlRow1->Add(line01Button, 1, wxLEFT | wxRIGHT, 0);
    

    //Control Column Button 02
    wxBoxSizer *controlRow2 = new wxBoxSizer(wxHORIZONTAL);
    line02Button = new wxButton(this, ID_LineTwoButton, wxT("( 2 )"), wxPoint(-1, -1), wxDefaultSize, 10);
    line02Button->SetLabel("( 2 )");
    
    //Control Column Status 02
    lineTwoStatus = new wxAnimationCtrl(this, wxID_ANY,wxNullAnimation,wxDefaultPosition,wxDefaultSize,wxAC_DEFAULT_STYLE  );
    lineTwoStatus->LoadFile("Ring4sm.gif", wxANIMATION_TYPE_GIF);
    lineTwoStatus->SetInactiveBitmap( wxBitmap(wxImage(wxT("IDLE_sm.png")), wxBITMAP_DEFAULT_TYPE));
    controlRow2->Add(lineTwoStatus, 1, wxLEFT | wxRIGHT, 0);
    //lineOneStatus->Play();
    controlRow2->Add(line02Button, 1, wxLEFT | wxRIGHT, 0);
    
    //Add rows to the Control Column
    controlColumn->Add(controlRow0, 0, wxLEFT, 10);
    controlColumn->Add(controlRow1, 0, wxLEFT | wxTOP, 10);
    controlColumn->Add(controlRow2, 0, wxLEFT | wxTOP, 10);

    
    allElements->Add(infoColumn, 0, wxLEFT | wxTOP, 10);
    allElements->Add(controlColumn, 0,   wxTOP, 20);
    
    this->SetSizer(allElements);
    Show(this);

}

void SLCallLinePanel::handleLineButton(wxCommandEvent &event)
{

    EventID id = static_cast<EventID>(event.GetId());
    switch(id)
    {
        //Cases Button Press. 
        case ID_LineOneButton:
            SLMasterControl::get().mHandleLineButton(0);
            break;
        case ID_LineTwoButton:
            SLMasterControl::get().mHandleLineButton(1);
            break;
        default:
            std::cout<<"we couldn't encounter your event ID"<<std::endl;

    }
    
}

void SLCallLinePanel::handleLineStatus(wxCommandEvent &event)
{
    
    EventID id = static_cast<EventID>(event.GetId());
    switch(id)
    {
            //Case Incoming Call Set Animation
        case 100:
            lineOneStatus->Play();
            break;
        case 101:
            lineTwoStatus->Play();
            break;

        default:
            std::cout<<"we didn't encounter your event ID"<<std::endl;
            
    }
    
}

void SLCallLinePanel::PaintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    Render(dc);
}

void SLCallLinePanel::PaintNow()
{
    wxClientDC dc(this);
    Render(dc);
}

void SLCallLinePanel::Render(wxDC& dc)
{
    // Clear
    //dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    
    // Draw the grid
    DrawPanel(dc);
}

void SLCallLinePanel::DrawPanel(wxDC& dc)
{
//    
//    mNameLabel = "Name";
//    
//    dc.DrawText(mNameLabel, 20, 10);
//    dc.DrawText("City", 100, 10);
//    dc.DrawText("Comment", 180, 10);
//    dc.DrawText("Phone Number", 500, 10);
//    dc.DrawText(mNumberLabel, 500, 50);
//
//    
//
//    
}

void SLCallLinePanel::activateLine(CallInfo &info)
{
    mNumberLabelWX.SetLabel(info.remoteUri);

}

void SLCallLinePanel::clearLine(int lineNumber)
{
    switch(lineNumber)
    {
        case 0:
            mNumberLabelWX.SetLabel("");
            lineOneStatus->Stop();
            break;
        case 1:
            mNumberLabelWX.SetLabel("");
            lineTwoStatus->Stop();
            break;
        default:
            std::cout<<"cannot find what you are looking for"<<std::endl;
    }
   
    
}


void SLCallLinePanel::SetModel(std::shared_ptr<class LineModel> model)
{
    mModel = model;
}

void SLCallLinePanel::SetupBitmap()
{
    mBitmap.Create(GetSize());
}

void SLCallLinePanel::answerLine(wxCommandEvent& event)
{
   // SLMasterControl::get().mAnswerLine();
}

void SLCallLinePanel::updateLineRing()
{
   // lineOneStatus->Play();

}

void SLCallLinePanel::mSetPJThread()
{
    std::cout<<pj_thread_is_registered()<<std::endl;
    if (!pj_thread_is_registered()) {
        pj_status_t status;
        pj_thread_desc panelPJThreadDesc;
        pj_thread_t *pjPanelThread;
        status = pj_thread_register(NULL, panelPJThreadDesc, &pjPanelThread);
        if (status != PJ_SUCCESS) {
            std::cout<<"Error registering thread at PJSUA"<<std::endl;
        }
    }
}
