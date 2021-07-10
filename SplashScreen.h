#ifndef SPLASHSCREEN_H_INCLUDED
#define SPLASHSCREEN_H_INCLUDED

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/image.h"
#include "wx/splash.h"
#include "wx/mediactrl.h"


// Define a new application type, each program should derive a class from wxApp
class EdlSplashScreen : public wxSplashScreen
{
public:


    void EDLMakeSplashScreen();
    void EDLDecorateSplashScreen(wxBitmap& bmp);
};

#endif // SPLASHSCREEN_H_INCLUDED
