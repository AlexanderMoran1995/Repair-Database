#include "SplashScreen.h"

void EdlSplashScreen::EDLMakeSplashScreen()
{
   wxImage::AddHandler(new wxPNGHandler);
    wxBitmap bitmap;
    bitmap.LoadFile("rpdbsplash70%.png", wxBITMAP_TYPE_PNG);
    EDLDecorateSplashScreen(bitmap);

    //Destroy();

new wxSplashScreen(bitmap,
            wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
            1000, NULL, wxID_ANY, wxDefaultPosition, wxDefaultSize,
            wxSIMPLE_BORDER|wxSTAY_ON_TOP);
}

// Draws artwork onto our splashscreen at runtime
void EdlSplashScreen::EDLDecorateSplashScreen(wxBitmap& bmp)
{
    // use a memory DC to draw directly onto the bitmap
    wxMemoryDC memDc(bmp);

    // draw border box (with  outline) at the bottom of the splashscreen.
    // this box will be 10% of the height of the bitmap, and be at the bottom.
    const wxRect bannerRect(wxPoint(0, (bmp.GetHeight() / 9.35)*8.6),
                            wxPoint(bmp.GetWidth(), bmp.GetHeight()));
    wxDCBrushChanger bc(memDc, wxBrush(wxColour(40,40,40)));
    memDc.DrawRectangle(bannerRect);
    memDc.DrawLine(bannerRect.GetTopLeft(), bannerRect.GetTopRight());

    // dynamically get the wxWidgets version to display
    wxString description = wxString::Format("EDL  -RPDB %s", " v0.9.4");
    // create a copyright notice that uses the year that this file was compiled
    wxString year(__DATE__);
    wxString copyrightLabel = wxString::Format("%s%s Electronic Development Labs. %s",
        wxString::FromUTF8("\xc2\xa9"), year.Mid(year.Length() - 4),
        "All rights reserved.");

    memDc.SetTextForeground(wxColour(235,255,255));
     
    
    memDc.DrawLabel(description, bannerRect.Deflate(5, 0), wxALIGN_CENTRE_VERTICAL|wxALIGN_LEFT);

    // draw the copyright label on the right side
    memDc.SetFont(wxFontInfo(8));
    memDc.DrawLabel(copyrightLabel, bannerRect.Deflate(5, 0), wxALIGN_CENTRE_VERTICAL | wxALIGN_RIGHT);
}
