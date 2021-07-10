#ifndef LOGINDIALOGUE_H_INCLUDED
#define LOGINDIALOGUE_H_INCLUDED

#include <wx/wx.h>
#include <wx/valtext.h>
//#include "Listbox.h"
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/colordlg.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

#if !wxUSE_COMBOCTRL
#error "Please set wxUSE_COMBOCTRL to 1 and rebuild the library."
#endif

#include "wx/image.h"
#include "wx/combo.h"
#include "wx/odcombo.h"

#include "wx/stattext.h"
#include "wx/menu.h"
#include "wx/layout.h"
#include "wx/msgdlg.h"
#include "wx/button.h"
#include "wx/sizer.h"
#include "wx/textctrl.h"
#include "wx/settings.h"

#include "wx/calctrl.h"
#include "wx/splitter.h"
#include "wxsqlite3.h"
#include <vector>

#include "EDLWirelessMain.h"


class UserLoginDialog : public wxDialog
{

    
public:

    void onClickLogin(wxCommandEvent& event);
    void onClickCancel(wxCommandEvent& event);

    UserLoginDialog(const wxString& title);
    ~UserLoginDialog();
    wxSQLite3Database* db;
    wxTextCtrl* ctlUserTxt2;
    wxTextCtrl* ctlPasswordTxt2;
    wxTextCtrl* ctlConfirmPasswordTxt;
     wxString userdbString2;
    wxString passworddbString2;
  
    wxString loggedInAs;

private:


    static const long idButtonLogin2;
    static const long idButtonCancel2;



   




    DECLARE_EVENT_TABLE()

};



class CustomDialog4: public wxDialog
{
public:
    CustomDialog4(wxString& user, wxString& password, const wxString& title);
    ~CustomDialog4();

    UserLoginDialog * UserLogin;
    wxString loggedInAs;
private:

   
    static const long idButtonNewUser;
    static const long idButtonLogin;

    
    void onClickNewUser(wxCommandEvent& event);
    void onClickLogin(wxCommandEvent& event);
   



    DECLARE_EVENT_TABLE()

};


class newUserDialog : public wxDialog
{
public:
    newUserDialog(const wxString& title);
    ~newUserDialog();
    wxSQLite3Database* db;
    wxTextCtrl* ctlUserTxt;
    wxTextCtrl* ctlPasswordTxt;
    wxTextCtrl* ctlConfirmPasswordTxt;

private:

    
    static const long idButtonCreateLogin;
    static const long idButtonCancel;
   
    

    void onClickCreate(wxCommandEvent& event);
    void onClickCancel(wxCommandEvent& event);
    



    DECLARE_EVENT_TABLE()

};








class LoginDlg2 : public wxDialog
{
public:
    LoginDlg2(wxString& user, wxString& password)
        : wxDialog(NULL, wxID_ANY, ("Login"), wxPoint(1100,500), wxSize(340, 330))
    {

        wxPanel* panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(340, 157));
        panel->SetBackgroundColour(wxColor(40, 40, 40));
        
        wxFlexGridSizer* loginInfoSizer = new wxFlexGridSizer(2);
        wxFlexGridSizer* loginImageSizer = new wxFlexGridSizer(1);
        wxFlexGridSizer* loginButtonSizer = new wxFlexGridSizer(3);
        wxFlexGridSizer* testButtonSizer = new wxFlexGridSizer(2);
       
       
        wxPNGHandler* logohandler = new wxPNGHandler;
        wxImage::AddHandler(logohandler);
        wxStaticBitmap* logoimage;

        logoimage = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("loginLogoImage.png", wxBITMAP_TYPE_PNG), wxPoint(35, 5), wxDefaultSize, wxSIMPLE_BORDER);
        loginImageSizer->Add((logoimage), 0, wxALL | wxALIGN_RIGHT, 5);

        wxStaticText* usr = new wxStaticText(this, wxID_ANY, ("Username:"));
        usr->SetForegroundColour(wxColour(0, 38, 153));
        usr->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
        wxStaticText* pw = new wxStaticText(this, wxID_ANY, ("Password:"));
        pw->SetForegroundColour(wxColour(0, 38, 153));
        pw->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

        
        loginInfoSizer->Add((usr), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlUserTxt = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(175, 35));
        ctlUserTxt->SetBackgroundColour(wxColour(228, 228, 240));
       /////////// ctlUserTxt->SetValidator(wxTextValidator(wxFILTER_ALPHANUMERIC | wxFILTER_EMPTY, &user));
        ctlUserTxt->SetValidator(wxTextValidator(wxFILTER_ALPHANUMERIC , &user));
        ctlUserTxt->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
        loginInfoSizer->Add(ctlUserTxt, 0, wxALL, 5);

        loginInfoSizer->Add((pw), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlPasswordTxt = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(175, 35) , wxTE_PASSWORD);
        ctlPasswordTxt->SetBackgroundColour(wxColour(228, 228, 240));
        ctlPasswordTxt->SetValidator(wxTextValidator(wxFILTER_NONE, &password));
        ctlPasswordTxt->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
        loginInfoSizer->Add(ctlPasswordTxt, 0, wxALL, 5);
        

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

      //  static const long idButtonHello;
        
       // wxButton* m_ButtonHello;
       // void onClickHello(wxCommandEvent & event);

       // m_ButtonHello = new wxButton( this, idButtonHello, _T("New User"), wxPoint(200,150), wxDefaultSize, 0);
       // testButtonSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL, 5);
      //  testButtonSizer->Add(m_ButtonHello,  0, wxALL, 5);

        mainSizer->Add(loginImageSizer, 0, wxALL, 5);
        mainSizer->Add(loginInfoSizer, 0, wxALL, 5);
       // mainSizer->Add(testButtonSizer, 0, wxALL, 5);
        mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL, 5);


        /*
        wxBitmapButton* Loginbutton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxT("login.png"),
            wxBITMAP_TYPE_PNG), wxPoint(40, 230), wxSize(-1, -1), wxNO_BORDER);
        wxImage LoginbuttonimgHover("loginh.png");
        Loginbutton->SetBitmapHover(LoginbuttonimgHover);
        wxImage LoginbuttonimgPressed("loginp.png");
        Loginbutton->SetBitmapPressed(LoginbuttonimgPressed);

        wxBitmapButton* NewUserbutton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxT("newlogin.png"),
            wxBITMAP_TYPE_PNG), wxPoint(145, 230), wxSize(-1, -1), wxNO_BORDER);
        wxImage NewUserbuttonimgHover("newloginh.png");
        NewUserbutton->SetBitmapHover(NewUserbuttonimgHover);
        wxImage NewUserbuttonimgPressed("newloginp.png");
        NewUserbutton->SetBitmapPressed(NewUserbuttonimgPressed);

        loginButtonSizer->Add((Loginbutton), 0, wxALL | wxALIGN_RIGHT, 5);
        loginButtonSizer->Add((NewUserbutton), 0, wxALL | wxALIGN_RIGHT, 5);
        mainSizer->Add(loginButtonSizer, 0, wxALL, 5);

        
        */


        SetSizerAndFit(mainSizer);
        Centre();

      

    }
        
};


#endif // LOGINDIALOGUE_H_INCLUDED
