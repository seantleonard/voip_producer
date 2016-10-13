//
//  SLSipFrame.cpp
//  PJDev
//
//  Created by Sean Leonard on 8/19/16.
//  Copyright © 2016 Sean Leonard. All rights reserved.
//

#include "SLSipFrame.hpp"
#include "SLCallLinePanel.hpp"
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/wfstream.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include "SLMasterControl.hpp"

SLSipFrame::SLSipFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    SetMaxSize(size);
    SetMinSize(size);

    //SLMasterControl controlTower();
    SLMasterControl::get().mSetFrame(this);
    
    //Prep the Panel
    mLinePanel = new SLCallLinePanel(this);
    Show(true);
    
    
    
    
//    
//    wxPanel *panel = new wxPanel(this, -1);
//    wxBoxSizer *allElements = new wxBoxSizer(wxHORIZONTAL);
//    wxBoxSizer *infoColumn = new wxBoxSizer(wxVERTICAL);
//    wxBoxSizer *controlColumn = new wxBoxSizer(wxVERTICAL);
//    wxBoxSizer *infoRow = new wxBoxSizer(wxHORIZONTAL);
//    
//    
//    //NAME COLUMN
//    wxBoxSizer *infoCol1 = new wxBoxSizer(wxVERTICAL);
//    wxStaticText *strName =  new wxStaticText(panel, wxID_ANY,
//                                              wxT("Name"));
//    wxTextCtrl *ctrlName1 = new wxTextCtrl(panel, wxID_ANY, wxT(""),
//                                          wxPoint(-1, -1), wxSize(-1, -1), wxTE_LEFT);
//
//    infoCol1->Add(strName, 0, wxEXPAND|  wxBOTTOM, 20);
//    infoCol1->Add(ctrlName1, 0, wxEXPAND | wxLEFT, 0);
//
//    //CITY COLUMN
//    wxBoxSizer *infoCol2 = new wxBoxSizer(wxVERTICAL);
//    wxStaticText *strCity =  new wxStaticText(panel, wxID_ANY,
//                                              wxT("City"));
//    wxTextCtrl *ctrlCity1 = new wxTextCtrl(panel, wxID_ANY, wxT(""),
//                                           wxPoint(-1, -1), wxSize(-1, -1), wxTE_LEFT);
//
//    infoCol2->Add(strCity, 0, wxEXPAND | wxBOTTOM, 20);
//    infoCol2->Add(ctrlCity1, 0, wxEXPAND | wxBOTTOM, 0);
//
//    //COMMENT COLUMN
//    wxBoxSizer *infoCol3 = new wxBoxSizer(wxVERTICAL);
//    wxStaticText *strComment =  new wxStaticText(panel, wxID_ANY,
//                                                 wxT("Comment"));
//    wxTextCtrl *ctrlComment1 = new wxTextCtrl(panel, wxID_ANY, wxT(""),
//                                           wxPoint(-1, -1), wxSize(-1, -1), wxTE_LEFT);
//    
//    infoCol3->Add(strComment, 0, wxEXPAND | wxBOTTOM, 20);
//    infoCol3->Add(ctrlComment1, 0, wxEXPAND | wxBOTTOM, 0);
//    
//    //NUMBER COLUMN
//    wxBoxSizer *infoCol4 = new wxBoxSizer(wxVERTICAL);
//    wxStaticText *strNumber =  new wxStaticText(panel, wxID_ANY,
//                                                wxT("Number"));
//    infoCol4->Add(strNumber, 0, wxLEFT, 0);
//    
//    //Add labels to the vertical box
//    infoRow->Add(infoCol1, 1,  wxEXPAND | wxLEFT | wxRIGHT, 10);
//    infoRow->Add(infoCol2, 1,  wxEXPAND | wxLEFT | wxRIGHT, 10);
//    infoRow->Add(infoCol3, 1,  wxLEFT | wxRIGHT, 10);
//    infoRow->Add(infoCol4, 1,  wxLEFT | wxRIGHT, 10);
//
//    infoColumn->Add(infoRow, 1, wxEXPAND| wxALL, 10);
//
//    allElements->Add(infoColumn, 0, wxLEFT | wxTOP, 10);
//    allElements->Add(controlColumn, 0, wxLEFT | wxTOP, 10);
//    
//    panel->SetSizer(allElements);
//    Show(panel);

}

void SLSipFrame::mSetPJThread()
{
    if (!pj_thread_is_registered()) {
        pj_status_t status;
        pj_thread_desc aPJThreadDesc;
        pj_thread_t *pjThread;
        status = pj_thread_register(NULL, aPJThreadDesc, &pjThread);
        if (status != PJ_SUCCESS) {
            std::cout<<"Error registering thread at PJSUA"<<std::endl;
        }
    }
}

SLSipFrame::~SLSipFrame()
{
    
}
