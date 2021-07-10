#include "loginDialogue.h"

using namespace std;

struct loginData
{
    wxString dbusr;
    wxString dbpw;
};




const long CustomDialog4::idButtonLogin = ::wxNewId();   //Login Button
const long CustomDialog4::idButtonNewUser = ::wxNewId();   //New User Button
const long newUserDialog::idButtonCreateLogin = ::wxNewId();   //Create Button
const long newUserDialog::idButtonCancel = ::wxNewId();   //Cancel Button
const long UserLoginDialog::idButtonLogin2 = ::wxNewId();   //Create Button
const long UserLoginDialog::idButtonCancel2 = ::wxNewId();   //Cancel Button



BEGIN_EVENT_TABLE(CustomDialog4, wxDialog)

EVT_BUTTON(idButtonLogin, CustomDialog4::onClickLogin) //Login Button
EVT_BUTTON(idButtonNewUser, CustomDialog4::onClickNewUser) //New User Button
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(newUserDialog, wxDialog)

EVT_BUTTON(idButtonCreateLogin, newUserDialog::onClickCreate) //Create Button
EVT_BUTTON(idButtonCancel, newUserDialog::onClickCancel) //Cancel Button
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(UserLoginDialog, wxDialog)

EVT_BUTTON(idButtonLogin2, UserLoginDialog::onClickLogin) //Create Button
EVT_BUTTON(idButtonCancel2, UserLoginDialog::onClickCancel) //Cancel Button
END_EVENT_TABLE()


CustomDialog4::CustomDialog4(wxString& user, wxString& password, const wxString& title)
    : wxDialog(NULL, -1, ("Login"), wxPoint(1100, 500), wxSize(340, 330))
{
    wxPanel* panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(340, 330));
    panel->SetBackgroundColour(wxColor(40, 40, 40));

    wxFlexGridSizer* loginImageSizer = new wxFlexGridSizer(1);
    wxFlexGridSizer* loginButtonSizer = new wxFlexGridSizer(3);
    
    wxPNGHandler* logohandler = new wxPNGHandler;
    wxImage::AddHandler(logohandler);
    wxStaticBitmap* logoimage;

    logoimage = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("loginLogoImage2.png", wxBITMAP_TYPE_PNG), wxPoint(35, 5), wxDefaultSize, wxSIMPLE_BORDER);
    loginImageSizer->Add((logoimage), 0, wxALL | wxALIGN_RIGHT, 5);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(loginImageSizer, 0, wxALL, 5);
   
    wxBitmapButton* Loginbutton = new wxBitmapButton(panel, idButtonLogin, wxBitmap(wxT("login.png"),
        wxBITMAP_TYPE_PNG), wxPoint(40, 230), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage LoginbuttonimgHover("loginh.png");
    Loginbutton->SetBitmapHover(LoginbuttonimgHover);
    wxImage LoginbuttonimgPressed("loginp.png");
    Loginbutton->SetBitmapPressed(LoginbuttonimgPressed);

    wxBitmapButton* NewUserbutton = new wxBitmapButton(panel, idButtonNewUser, wxBitmap(wxT("newlogin.png"),
        wxBITMAP_TYPE_PNG), wxPoint(145, 230), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage NewUserbuttonimgHover("newloginh.png");
    NewUserbutton->SetBitmapHover(NewUserbuttonimgHover);
    wxImage NewUserbuttonimgPressed("newloginp.png");
    NewUserbutton->SetBitmapPressed(NewUserbuttonimgPressed);

  
    loginButtonSizer->Add((Loginbutton), 0, wxALL | wxALIGN_RIGHT, 5);
    loginButtonSizer->Add((NewUserbutton), 0, wxALL | wxALIGN_RIGHT, 5);
   
    mainSizer->Add(loginButtonSizer, 0, wxALL, 5);

    SetSizerAndFit(mainSizer);

    Centre();
    ShowModal();

    Destroy();
}


CustomDialog4::~CustomDialog4()
{
}



void CustomDialog4::onClickNewUser(wxCommandEvent& event)
{
    newUserDialog* NewUser = new newUserDialog(wxT(""));
    NewUser->Show(true);
}

void CustomDialog4::onClickLogin(wxCommandEvent& event)
{
    UserLogin = new UserLoginDialog(wxT(""));
    UserLogin->Show(true);
}


newUserDialog::newUserDialog(const wxString& title)
    : wxDialog(NULL, -1, ("Create Login"), wxPoint(1100, 500), wxSize(340, 330))
{
    wxPanel* panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(370, 380));
    panel->SetBackgroundColour(wxColor(40, 40, 40));

    wxFlexGridSizer* newLoginImageSizer = new wxFlexGridSizer(1);
    wxFlexGridSizer* newLoginInfoSizer = new wxFlexGridSizer(2);
    wxFlexGridSizer* newLoginButtonSizer = new wxFlexGridSizer(3);

    //wxPNGHandler* logohandler = new wxPNGHandler;
   // wxImage::AddHandler(logohandler);
    wxStaticBitmap* logoimage;

    logoimage = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("loginLogoImage.png", wxBITMAP_TYPE_PNG), wxPoint(100, 5), wxDefaultSize, wxSIMPLE_BORDER);
    newLoginImageSizer->Add((logoimage), 0, wxALL | wxALIGN_RIGHT, 10);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(newLoginImageSizer, 0,  wxLEFT, 22);



    wxStaticText* newUsr = new wxStaticText(this, wxID_ANY, ("Username:"));
    newUsr->SetForegroundColour(wxColour(50, 255, 255));
    newUsr->SetBackgroundColour(wxColour(40,40,40));
    newUsr->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    wxStaticText* newPw = new wxStaticText(this, wxID_ANY, ("Password:"));
    newPw->SetForegroundColour(wxColour(50, 255, 255));
    newPw->SetBackgroundColour(wxColour(40, 40, 40));
    newPw->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    wxStaticText* confirmNewPw = new wxStaticText(this, wxID_ANY, ("Retype Password:"));
    confirmNewPw->SetForegroundColour(wxColour(50, 255, 255));
    confirmNewPw->SetBackgroundColour(wxColour(40, 40, 40));
    confirmNewPw->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));


    newLoginInfoSizer->Add((newUsr), 0, wxALL | wxALIGN_RIGHT, 5);
     ctlUserTxt = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(175, 35));
    ctlUserTxt->SetBackgroundColour(wxColour(228, 228, 240)); 
    ctlUserTxt->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    newLoginInfoSizer->Add(ctlUserTxt, 0, wxALL, 5);

    newLoginInfoSizer->Add((newPw), 0, wxALL | wxALIGN_RIGHT, 5);
     ctlPasswordTxt = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(175, 35), wxTE_PASSWORD);
    ctlPasswordTxt->SetBackgroundColour(wxColour(228, 228, 240));
    ctlPasswordTxt->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    newLoginInfoSizer->Add(ctlPasswordTxt, 0, wxALL, 5);

    newLoginInfoSizer->Add((confirmNewPw), 0, wxALL | wxALIGN_RIGHT, 5);
     ctlConfirmPasswordTxt = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(175, 35), wxTE_PASSWORD);
    ctlConfirmPasswordTxt->SetBackgroundColour(wxColour(228, 228, 240));
    ctlConfirmPasswordTxt->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    newLoginInfoSizer->Add(ctlConfirmPasswordTxt, 0, wxALL, 5);

    mainSizer->Add(newLoginInfoSizer, 0, wxALL, 5);



    wxBitmapButton* CreateLoginbutton = new wxBitmapButton(panel, idButtonCreateLogin, wxBitmap(wxT("createUser.png"),
        wxBITMAP_TYPE_PNG), wxPoint(40, 230), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage LoginbuttonimgHover("createUserh.png");
    CreateLoginbutton->SetBitmapHover(LoginbuttonimgHover);
    wxImage LoginbuttonimgPressed("createUserp.png");
    CreateLoginbutton->SetBitmapPressed(LoginbuttonimgPressed);

    wxBitmapButton* Cancelbutton = new wxBitmapButton(panel, idButtonCancel, wxBitmap(wxT("cancel.png"),
        wxBITMAP_TYPE_PNG), wxPoint(145, 230), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage NewUserbuttonimgHover("cancelh.png");
    Cancelbutton->SetBitmapHover(NewUserbuttonimgHover);
    wxImage NewUserbuttonimgPressed("cancelp.png");
    Cancelbutton->SetBitmapPressed(NewUserbuttonimgPressed);


    newLoginButtonSizer->Add((CreateLoginbutton), 0, wxLEFT | wxALIGN_RIGHT, 50);
    newLoginButtonSizer->Add((Cancelbutton), 0, wxLEFT | wxALIGN_RIGHT, 10);

    mainSizer->Add(newLoginButtonSizer, 0, wxALL, 10);

    SetSizerAndFit(mainSizer);

    Centre();
    ShowModal();

    Destroy();
}


newUserDialog::~newUserDialog()
{
}

void newUserDialog::onClickCreate(wxCommandEvent& event)
{

    wxString userdbString = ctlUserTxt->GetValue();
    wxString passworddbString = ctlPasswordTxt->GetValue();
    wxString passwordConfirmationString = ctlConfirmPasswordTxt->GetValue();

   int userCharCount = userdbString.size();
   int pwCharCount = passworddbString.size();
   int pwcCharCount = passwordConfirmationString.size();

   int pwresult = strcmp(passworddbString, passwordConfirmationString);


   if (userCharCount >> 0)
   {

       if (pwCharCount >= 6)
       {


           if (pwresult == 0)
           {

               db = new wxSQLite3Database();

               wxString testDBName = wxGetCwd() + wxT("/loginDatabase.db");

               db->Open(testDBName);

                db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'Logins' ('Username' TEXT, 'Password' TEXT, 'Id' INTEGER PRIMARY KEY AUTOINCREMENT );");

               //db->Close();

               //db->Open(testDBName);

               db->ExecuteUpdate(wxString::Format(_("INSERT INTO Logins (Username,Password) VALUES ('%s','%s')"), userdbString, passworddbString));

               db->Close();


               wxString msg = _T("Login for: ") + userdbString + _T(" Successfully Created") + "\nUsername: " + userdbString + "\nPassword: " + passworddbString;
               wxString info = _T("Login Created");
               wxMessageBox(msg,
                   info,
                   wxOK | wxICON_INFORMATION,
                   this);

               Destroy();

           }

           else
           {
               wxString msg = _T("Login Creation Failed:\n Password and Password Confirmation Must Match! ");
               wxString info = _T("Invalid Login");
               wxMessageBox(msg,
                   info,
                   wxOK | wxICON_ERROR,
                   this);

           }

       }

       else
       {
           wxString msg = _T("Login Creation Failed:\n Password Must Contain At Least 6 Characters! ");
           wxString info = _T("Invalid Login");
           wxMessageBox(msg,
               info,
               wxOK | wxICON_ERROR,
               this);

       }

   }

   else
   {
       wxString msg = _T("Login Creation Failed:\n Username Cannot be Blank! ");
       wxString info = _T("Invalid Login");
       wxMessageBox(msg,
           info,
           wxOK | wxICON_ERROR,
           this);

   }

}


void newUserDialog::onClickCancel(wxCommandEvent& event)
{
    Destroy();
}



UserLoginDialog::UserLoginDialog(const wxString& title)
    : wxDialog(NULL, -1, ("Login"), wxPoint(1100, 500), wxSize(340, 380))
{
    wxPanel* panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(340, 330));
    panel->SetBackgroundColour(wxColor(40, 40, 40));

    wxFlexGridSizer* loginInfoSizer = new wxFlexGridSizer(2);
    wxFlexGridSizer* loginImageSizer = new wxFlexGridSizer(1);
    wxFlexGridSizer* loginButtonSizer = new wxFlexGridSizer(2);
   


    //wxPNGHandler* logohandler = new wxPNGHandler;
    //wxImage::AddHandler(logohandler);
    wxStaticBitmap* logoimage;

    logoimage = new wxStaticBitmap(panel, wxID_ANY, wxBitmap("loginLogoImage.png", wxBITMAP_TYPE_PNG), wxPoint(35, 5), wxDefaultSize, wxSIMPLE_BORDER);
    loginImageSizer->Add((logoimage), 0, wxALL | wxALIGN_RIGHT, 5);

    wxStaticText* usr = new wxStaticText(panel, wxID_ANY, ("Username:"));
    usr->SetForegroundColour(wxColour(50, 255, 255));
    usr->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    wxStaticText* pw = new wxStaticText(panel, wxID_ANY, ("Password:"));
    pw->SetForegroundColour(wxColour(50, 255, 255));
    pw->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));


    loginInfoSizer->Add((usr), 0, wxALL | wxALIGN_RIGHT, 5);
     ctlUserTxt2 = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(175, 35));
    ctlUserTxt2->SetBackgroundColour(wxColour(228, 228, 240));
    ctlUserTxt2->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    loginInfoSizer->Add(ctlUserTxt2, 0, wxALL, 5);

    loginInfoSizer->Add((pw), 0, wxALL | wxALIGN_RIGHT, 5);
     ctlPasswordTxt2 = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(175, 35), wxTE_PASSWORD);
    ctlPasswordTxt2->SetBackgroundColour(wxColour(228, 228, 240));
    ctlPasswordTxt2->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    loginInfoSizer->Add(ctlPasswordTxt2, 0, wxALL, 5);
  
    wxBitmapButton* Loginbutton = new wxBitmapButton(panel, idButtonLogin2, wxBitmap(wxT("login.png"),
        wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage LoginbuttonimgHover("loginh.png");
    Loginbutton->SetBitmapHover(LoginbuttonimgHover);
    wxImage LoginbuttonimgPressed("loginp.png");
    Loginbutton->SetBitmapPressed(LoginbuttonimgPressed);

    wxBitmapButton* NewUserbutton = new wxBitmapButton(panel, idButtonCancel2, wxBitmap(wxT("cancel.png"),
        wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage NewUserbuttonimgHover("cancelh.png");
    NewUserbutton->SetBitmapHover(NewUserbuttonimgHover);
    wxImage NewUserbuttonimgPressed("cancelp.png");
    NewUserbutton->SetBitmapPressed(NewUserbuttonimgPressed);

    loginButtonSizer->Add((Loginbutton), 0, wxALL | wxALIGN_RIGHT, 5);
    loginButtonSizer->Add((NewUserbutton), 0, wxALL | wxALIGN_RIGHT, 5);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(loginImageSizer, 0, wxALL, 5);
    mainSizer->Add(loginInfoSizer, 0, wxALL, 5);
    mainSizer->Add(loginButtonSizer, 0, wxALL, 5);
   
    SetSizerAndFit(mainSizer);
    

    Centre();
    ShowModal();

    Destroy();

    
}


UserLoginDialog::~UserLoginDialog()
{
}


void UserLoginDialog::onClickLogin(wxCommandEvent& event)
{
    // loggedInAs = ctlUserTxt2->GetValue();
   // wxString loggedInAs;
   
    // EDLWirelessFrame* frame = new EDLWirelessFrame();

   

    //return true;

   
   //  EDLWirelessFrame* frame = new EDLWirelessFrame();
    /// userdbString2 = ctlUserTxt2->GetValue();
   //  passworddbString2 = ctlPasswordTxt2->GetValue();

    
    //int userresult = 0;
  //  int pwresult = 0;


   
   
             //   db = new wxSQLite3Database();

            //    wxString testDBName = wxGetCwd() + wxT("/loginDatabase.db");

             //    db->Open(testDBName);

             //    db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'ProcessedLogin' ('Username' TEXT);");
             //    db->ExecuteUpdate(wxString::Format(_("INSERT INTO ProcessedLogin (Username) VALUES ('%s')"), userdbString2));

                 //db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'LoginAttempt' ('Username' TEXT, 'Password' TEXT);");
               //  db->ExecuteUpdate(wxString::Format(_("INSERT INTO LoginAttempt (Username,Password) VALUES ('%s','%s')"), userdbString2, passworddbString2));

               //  db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'Logins' ('Username' TEXT, 'Password' TEXT, 'Id' INTEGER PRIMARY KEY AUTOINCREMENT );");
               //  wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT Username FROM Logins WHERE Username ="+ userdbString2 +";");
               //  wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT Password FROM Logins WHERE Password =" + passworddbString2 + ";");

               //  Res.Finalize();
               //  Res2.Finalize();

            //     db->Close();

              //   EDLWirelessFrame* frame = new EDLWirelessFrame();

            //     EDLWirelessFrame* frame = new EDLWirelessFrame();

           //      frame = new EDLWirelessFrame();

             //    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
//      frame->Show(true);

          /*

                 if (Res.IsNull("Username")==true)
                 {
                     if (Res2.IsNull("Password") == true)
                     {

                         wxString msg = _T("Username ") + userdbString2 + _T(" Is Invalid") + _T("\n\n") + _T("& Password ") + passworddbString2 + _T(" Is Invalid");
                         wxString info = _T("Login Failed");
                         wxMessageBox(msg,
                             info,
                             wxOK | wxICON_INFORMATION,
                             this);

                        

                     }

                     else
                     {

                        

                         wxString msg = _T("Password ") + passworddbString2 + " Is Invalid";
                         wxString info = _T("Login Failed");
                         wxMessageBox(msg,
                             info,
                             wxOK | wxICON_INFORMATION,
                             this);

                     }



                 }

                 if (Res2.IsNull("Password") == false)
                 {


                     if (Res.IsNull("Username") == true)
                     {

                         wxString msg = _T("Username ") + userdbString2 + _T(" Is Invalid");
                         wxString info = _T("Login Failed");
                         wxMessageBox(msg,
                             info,
                             wxOK | wxICON_INFORMATION,
                             this);



                     }

                     else if (Res.IsNull("Username") == false)
                     {


                          frame = new EDLWirelessFrame();

                          frame->SetIcon(wxICON(aaaa)); // To Set App Icon

                          frame->Show(true);

                        //  Destroy();
                        

                     }


                 }

              

             
             */

              
                


}




void UserLoginDialog::onClickCancel(wxCommandEvent& event)
{
    Destroy();
}
