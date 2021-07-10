/***************************************************************
 * Name:      EDLWirelessMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alex Moran (alex@edl-inc.com)
 * Created:   2019-03-25
 * Copyright: Alex Moran (www.EDLwireless.com)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "EDLWirelessMain.h"



// Standard DC supports drawing with alpha on OSX and GTK3.
#if defined(__WXOSX__) || defined(__WXGTK3__)
#define wxDRAWING_DC_SUPPORTS_ALPHA 1
#else
#define wxDRAWING_DC_SUPPORTS_ALPHA 0
#endif // __WXOSX__ || __WXGTK3__
//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


BEGIN_EVENT_TABLE(EDLWirelessFrame, wxFrame)

END_EVENT_TABLE()


wxPanel* CreateOfficePage(wxBookCtrlBase* parent)
{
    wxString user, password;
    wxPanel* panel = new wxPanel(parent);

    OfficePanel* m_OP;

    m_OP = new OfficePanel(panel);

    return panel;
}



wxPanel* CreateNervoscopePage(wxBookCtrlBase* parent)
{

    wxPanel* panel = new wxPanel(parent);

    NervoPanel* m_NGP;

    m_NGP = new NervoPanel(panel);

    return panel;
}

wxPanel* CreateAnalogPage(wxBookCtrlBase* parent)
{

    wxPanel* panel = new wxPanel(parent);

    AnalogPanel* m_AGP;

    m_AGP = new AnalogPanel(panel);

    return panel;
}


wxPanel* CreateDigitalPage(wxBookCtrlBase* parent)
{

    wxPanel* panel = new wxPanel(parent);

    DigitalPanel* m_DGP;

    m_DGP = new DigitalPanel(panel);

    return panel;
}


wxPanel* CreateSensorPage(wxBookCtrlBase* parent)
{

    wxPanel* panel = new wxPanel(parent);

    BackgroundPanel* m_BGP;

    m_BGP = new BackgroundPanel(panel);

    return panel;
}

wxPanel* CreateMetrologyPage(wxBookCtrlBase* parent)
{

    wxPanel* panel = new wxPanel(parent);

    MetrologyPanel* m_MGP;

    m_MGP = new MetrologyPanel(panel);

    return panel;
}

wxPanel* CreateMiscPage(wxBookCtrlBase* parent)
{

    wxPanel* panel = new wxPanel(parent);

    MiscPanel* m_MiscGP;

    m_MiscGP = new MiscPanel(panel);

    return panel;
}

wxPanel* CreateArchivePage(wxBookCtrlBase* parent)
{

    wxPanel* panel = new wxPanel(parent);

    ArchivePanel* m_ArchiveGP;

    m_ArchiveGP = new ArchivePanel(panel);

    return panel;
}



int GetIconIndex(wxBookCtrlBase* bookCtrl)
{
    if (bookCtrl && bookCtrl->GetImageList())
    {
       int nImages = bookCtrl->GetImageList()->GetImageCount();
       if (nImages > 0)
       {
           return bookCtrl->GetPageCount() % nImages;
       }
    }

    return -1;
}

void CreateInitialPages(wxBookCtrlBase *parent)
{
     //Create and add some panels to the notebook

    wxPanel *panel;

    panel = CreateOfficePage(parent);
    parent->AddPage(panel, OFFICE_PAGE_NAME, false, GetIconIndex(parent));

    panel = CreateNervoscopePage(parent);
    parent->AddPage(panel, NERVOSCOPE_PAGE_NAME, false, GetIconIndex(parent));

    panel = CreateAnalogPage(parent);
    parent->AddPage(panel, ANALOG_PAGE_NAME, false, GetIconIndex(parent));

    panel = CreateDigitalPage(parent);
    parent->AddPage(panel, DIGITAL_PAGE_NAME, false, GetIconIndex(parent));
  
    panel = CreateSensorPage(parent);
    parent->AddPage(panel, SENSOR_PAGE_NAME, false, GetIconIndex(parent));

    panel = CreateMetrologyPage(parent);
    parent->AddPage(panel, METROLOGY_PAGE_NAME, false, GetIconIndex(parent));

    panel = CreateMiscPage(parent);
    parent->AddPage(panel, MISC_PAGE_NAME, false, GetIconIndex(parent));

    panel = CreateArchivePage(parent);
    parent->AddPage(panel, ARCHIVE_PAGE_NAME, false, GetIconIndex(parent));

 
    parent->SetSelection(0);
}

wxPanel *CreatePage(wxBookCtrlBase *parent, const wxString&pageName)
{
   
    if ( pageName == NERVOSCOPE_PAGE_NAME )
        return CreateNervoscopePage(parent);

    if ( pageName == ANALOG_PAGE_NAME )
        return CreateAnalogPage(parent);

    if (pageName == DIGITAL_PAGE_NAME)
        return CreateDigitalPage(parent);

    if (pageName == SENSOR_PAGE_NAME)
        return CreateSensorPage(parent);

    if (pageName == METROLOGY_PAGE_NAME)
        return CreateMetrologyPage(parent);

    if (pageName == MISC_PAGE_NAME)
        return CreateMiscPage(parent);

    if (pageName == OFFICE_PAGE_NAME)
        return CreateOfficePage(parent);

    if (pageName == ARCHIVE_PAGE_NAME)
        return CreateArchivePage(parent);

      return NULL;
}


EDLWirelessFrame::EDLWirelessFrame()
    : wxFrame(NULL, wxID_ANY, wxString("Repair Database"),
                                 wxPoint(500,175), wxSize(-1, -1),
                                 wxDEFAULT_FRAME_STYLE)
{

    EdlSplashScreen SplSc;
    SplSc.EDLMakeSplashScreen();
   
      m_type = Type_Toolbook;
      m_panel    = NULL;

    // create a dummy image list with a few icons
    const wxSize imageSize(32,32);

    m_imageList = new wxImageList(imageSize.GetWidth(), imageSize.GetHeight());

    m_imageList->Add(wxICON(hhhh), imageSize);
    m_imageList->Add(wxICON(cccc), imageSize);
    m_imageList->Add(wxICON(dddd), imageSize);
    m_imageList->Add(wxICON(dddd), imageSize);
    m_imageList->Add(wxICON(eeee), imageSize);
    m_imageList->Add(wxICON(ffff), imageSize);
    m_imageList->Add(wxICON(gggg), imageSize);
    m_imageList->Add(wxICON(iiii), imageSize);
    
    
    m_panel = new wxPanel(this);

    m_panel->SetBackgroundColour(wxColour(28, 28, 43));
    

    // Set sizers
    m_sizerFrame = new wxBoxSizer(wxVERTICAL);

    int flags;
    flags = wxTBK_HORZ_LAYOUT;

    m_bookCtrl = NULL;
    DISPATCH_ON_TYPE(m_bookCtrl = new,wxToolbook,(m_panel, wxID_ANY, wxDefaultPosition, wxSize(1209,714), wxBK_TOP| wxTBK_HORZ_LAYOUT));
    if (!m_bookCtrl)
        return;
  
    m_bookCtrl->Show();
    m_bookCtrl->SetImageList(m_imageList);
 
    CreateInitialPages(m_bookCtrl);

    m_sizerFrame->Insert(0, m_bookCtrl, wxSizerFlags(flags).Expand().Border());
    m_sizerFrame->Show(m_bookCtrl);
    m_sizerFrame->Layout();

    m_panel->SetSizer(m_sizerFrame);
    m_panel->Layout();

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_panel, wxSizerFlags(500).Expand());
    SetSizerAndFit(sizer);

  
  Center();

  
}

EDLWirelessFrame::~EDLWirelessFrame()
{
  delete m_imageList;
}


bool EDLWirelessApp::OnInit()
{

    if (!wxApp::OnInit())
        return false;

    EdlSplashScreen SplSc;
    SplSc.EDLMakeSplashScreen();

    EDLWirelessFrame* frame = new EDLWirelessFrame();

   
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show(true);

#if !defined(__WXGTK20__)
    // we don't need it at least on wxGTK with GTK+ 2.12.9
    wxYield();
#endif

    return true;

}


IMPLEMENT_APP(EDLWirelessApp);
