/***************************************************************
 * Name:      EDLWirelessMain.h
 * Purpose:   Defines Application Frame
 * Author:    Alex Moran (alex@edl-inc.com)
 * Created:   2019-03-25
 * Copyright: Alex Moran (www.EDLwireless.com)
 * License:
 **************************************************************/



#ifndef EDLWIRELESSMAIN_H
#define EDLWIRELESSMAIN_H

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#include "wx/timer.h"
#endif

#include "wx/artprov.h"
#include "wx/imaglist.h"
#include "wx/toolbook.h"
#include <wx/app.h>
#include "wx/image.h"


#include "wx/colordlg.h"
#include "wx/image.h"
#include "wx/artprov.h"
#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"
#include "wx/overlay.h"
#include "wx/graphics.h"
#include "wx/filename.h"
#include "wx/metafile.h"
#include "wx/settings.h"

#include <wx/statline.h>
#include <wx/clrpicker.h>

#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include "wx/font.h"
#include <wx/string.h>

#include <string>
#include "wx/radiobox.h"
#include "wx/statbox.h"
#include "wx/font.h"
#include "wx/grid.h"
#include "wx/generic/gridctrl.h"
#include "wx/generic/grideditors.h"
#include <wx/msgdlg.h>
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/button.h>
#include <wx/frame.h>
#include "wxsqlite3.h"
#include <ctime>
#include "wx/artprov.h"
#include "wx/sizer.h"
#include "wx/checkbox.h"
#include "wx/srchctrl.h"
#include "wx/odcombo.h"
#include "wx/choice.h"
#include "wx/timer.h"

#include "dataGrid.h"
#include "SplashScreen.h"
#include "databaseSelection.h"
#include "metrologydb.h"
#include "miscdb.h"
#include "sensordb.h"
#include "digitaldb.h"
#include "Office.h"
#include "Archive.h"

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/charts/wxcharts.h>


#include "WindowIDs.h"

#include <atlstr.h>


#include <PDF/PDFNet.h>
#include <PDF/PDFDoc.h>
#include <PDF/Annot.h>
#include <PDF/Field.h>
#include <PDF/Font.h>
#include <PDF/ElementBuilder.h>
#include <PDF/ElementWriter.h>
#include <PDF/Annots/Widget.h>
#include <PDF/ViewChangeCollection.h>
#include <PDF/Annots/TextWidget.h>
#include <PDF/Annots/CheckBoxWidget.h>
#include <PDF/Annots/ComboBoxWidget.h>
#include <PDF/Annots/ListBoxWidget.h>
#include <PDF/Annots/PushButtonWidget.h>
#include <PDF/Annots/RadioButtonWidget.h>
#include <PDF/Annots/RadioButtonGroup.h>
#include <PDF/Annots/SignatureWidget.h>
#include <iostream>
#include <map>
#include <cmath>

#define TIMER_ID 1000

class EDLWirelessApp : public wxApp
{
    public:
       // EDLWirelessFrame* frame;
      //  virtual bool OnInit();
        bool OnInit() wxOVERRIDE;
};

     wxDECLARE_APP(EDLWirelessApp);

class EDLWirelessFrame: public wxFrame
{
    public:
		EDLWirelessFrame();
        wxStatusBar* statusBar;
        void OnPaint(wxPaintEvent& event);

        void DrawGradients(wxDC& dc);
    virtual ~EDLWirelessFrame();
    // ctor(s)
   // EDLWirelessFrame(const wxString& title,const wxPoint& pos);
	
    
    private:

        wxStatusBar* _statusBar;

        enum
        {
            idMenuQuit = 1000,
            idMenuAbout
        };
      
        DECLARE_EVENT_TABLE()

         enum BookType
    {
        Type_Toolbook,
    }    m_type;

    wxPanel *m_panel; // Panel containing notebook and other controls
    wxPanel* panel;

    wxColour *colour;
    wxBookCtrlBase *m_bookCtrl;
    wxBookCtrlBase* m_bookCtrl2;
    wxBoxSizer *m_sizerFrame;
    wxImageList *m_imageList;
    wxImageList* m_imageList2;
    wxIcon *m_Icon;
  
};

#define LOGIN_PAGE_NAME                 "LOGIN"
#define NERVOSCOPE_PAGE_NAME            "NERVOSCOPE REPAIRS"
#define ANALOG_PAGE_NAME             "ANALOG REPAIRS"
#define DIGITAL_PAGE_NAME               "DIGITAL REPAIRS"
#define SENSOR_PAGE_NAME                "SENSOR REPAIRS"
#define METROLOGY_PAGE_NAME             "METROLOGY REPAIRS"
#define MISC_PAGE_NAME                  "MISC. REPAIRS"
#define OFFICE_PAGE_NAME                  "OFFICE"
#define ARCHIVE_PAGE_NAME                  "ARCHIVE"

#define CASE_TOOLBOOK(x) case Type_Toolbook: x; break;
#define DISPATCH_ON_TYPE(before,toolb,after)       \
    switch ( m_type )                                  \
    {                                                  \
    CASE_TOOLBOOK(before toolb after)                  \
    }

#endif // EDLWIRELESSMAIN_H
