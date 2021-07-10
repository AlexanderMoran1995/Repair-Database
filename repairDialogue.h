#ifndef REPAIRDIALOGUE_H_INCLUDED
#define REPAIRDIALOGUE_H_INCLUDED

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

#include "wx/odcombo.h"

/*
class RepairDlg : public wxDialog
{
public:
    RepairDlg(wxString& contact, wxString& company, wxString& modelNumber, wxString& serialNumber, wxString& repairNumber, wxString& month, wxString& day, wxString& year, wxString& department, wxString& technician, wxString& status)
        : wxDialog(NULL, wxID_ANY, _("Login"))
    {
        wxFlexGridSizer* loginInfoSizer = new wxFlexGridSizer(2);

        wxStaticText* ct = new wxStaticText(this, wxID_ANY, ("&Contact:"));
        ct->SetForegroundColour(wxColour(0, 38, 153));

        wxStaticText* com = new wxStaticText(this, wxID_ANY, ("&Company:"));
        com->SetForegroundColour(wxColour(0, 38, 153));

        wxStaticText* model = new wxStaticText(this, wxID_ANY, ("&Model Number:"));
        model->SetForegroundColour(wxColour(0, 38, 153));

        wxStaticText* serial = new wxStaticText(this, wxID_ANY, ("&Serial Number:"));
        serial->SetForegroundColour(wxColour(0, 38, 153));

        wxStaticText* repair = new wxStaticText(this, wxID_ANY, ("&Repair Number:"));
        repair->SetForegroundColour(wxColour(0, 38, 153));

        wxStaticText* dr = new wxStaticText(this, wxID_ANY, ("&Date Received:"));
        dr->SetForegroundColour(wxColour(0, 38, 153));

        wxStaticText* date = new wxStaticText(this, wxID_ANY, ("&[Month/Day/Year]:"));
        date->SetForegroundColour(wxColour(0, 38, 153));


        wxStaticText* dept = new wxStaticText(this, wxID_ANY, ("&Department:"));
        dept->SetForegroundColour(wxColour(0, 38, 153));

        wxStaticText* tech = new wxStaticText(this, wxID_ANY, ("&Technician:"));
        tech->SetForegroundColour(wxColour(0, 38, 153));

        wxStaticText* stat = new wxStaticText(this, wxID_ANY, ("&Status:"));
        stat->SetForegroundColour(wxColour(0, 38, 153));


        loginInfoSizer->Add((ct), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlContactTxt = new wxTextCtrl(this, wxID_ANY);
        ctlContactTxt->SetBackgroundColour(wxColour(228, 228, 240));
        ctlContactTxt->SetValidator(wxTextValidator(wxFILTER_ALPHANUMERIC | wxFILTER_EMPTY, &contact));
        loginInfoSizer->Add(ctlContactTxt, 0, wxALL, 5);

        loginInfoSizer->Add((com), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlCompanyTxt = new wxTextCtrl(this, wxID_ANY);
        ctlCompanyTxt->SetBackgroundColour(wxColour(228, 228, 240));
        ctlCompanyTxt->SetValidator(wxTextValidator(wxFILTER_NONE, &company));
        loginInfoSizer->Add(ctlCompanyTxt, 0, wxALL, 5);

        loginInfoSizer->Add((model), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlModelNumberTxt = new wxTextCtrl(this, wxID_ANY);
        ctlModelNumberTxt->SetBackgroundColour(wxColour(228, 228, 240));
        ctlModelNumberTxt->SetValidator(wxTextValidator(wxFILTER_ALPHANUMERIC | wxFILTER_EMPTY, &modelNumber));
        loginInfoSizer->Add(ctlModelNumberTxt, 0, wxALL, 5);

        loginInfoSizer->Add((serial), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlSerialNumberTxt = new wxTextCtrl(this, wxID_ANY);
        ctlSerialNumberTxt->SetBackgroundColour(wxColour(228, 228, 240));
        ctlSerialNumberTxt->SetValidator(wxTextValidator(wxFILTER_NONE, &serialNumber));
        loginInfoSizer->Add(ctlSerialNumberTxt, 0, wxALL, 5);

        loginInfoSizer->Add((repair), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlRepairNumberTxt = new wxTextCtrl(this, wxID_ANY);
        ctlRepairNumberTxt->SetBackgroundColour(wxColour(228, 228, 240));
        ctlRepairNumberTxt->SetValidator(wxTextValidator(wxFILTER_ALPHANUMERIC | wxFILTER_EMPTY, &repairNumber));
        loginInfoSizer->Add(ctlRepairNumberTxt, 0, wxALL, 5);


        wxArrayString   m_month;

        m_month.Add("January");
        m_month.Add("February");
        m_month.Add("March");
        m_month.Add("April");
        m_month.Add("May");
        m_month.Add("June");
        m_month.Add("July");
        m_month.Add("August");
        m_month.Add("September");
        m_month.Add("October");
        m_month.Add("November");
        m_month.Add("December");


        wxArrayString   m_day;

        m_day.Add("1");
        m_day.Add("2");
        m_day.Add("3");
        m_day.Add("4");
        m_day.Add("5");
        m_day.Add("6");
        m_day.Add("7");
        m_day.Add("8");
        m_day.Add("9");
        m_day.Add("10");
        m_day.Add("11");
        m_day.Add("12");
        m_day.Add("13");
        m_day.Add("14");
        m_day.Add("15");
        m_day.Add("16");
        m_day.Add("17");
        m_day.Add("18");
        m_day.Add("19");
        m_day.Add("20");
        m_day.Add("21");
        m_day.Add("22");
        m_day.Add("23");
        m_day.Add("24");
        m_day.Add("25");
        m_day.Add("26");
        m_day.Add("27");
        m_day.Add("28");
        m_day.Add("29");
        m_day.Add("30");
        m_day.Add("31");


        wxArrayString   m_Year;

        m_Year.Add("2019");
        m_Year.Add("2020");
        m_Year.Add("2021");
        m_Year.Add("2022");
        m_Year.Add("2023");
        m_Year.Add("2024");
        m_Year.Add("2025");
        m_Year.Add("2026");
        m_Year.Add("2027");
        m_Year.Add("2028");
        m_Year.Add("2029");


        wxArrayString   m_depts;

        m_depts.Add("Analog");
        m_depts.Add("Digital");
        m_depts.Add("Machine Room");
        m_depts.Add("Metrology");
        m_depts.Add("Sensors");
        m_depts.Add("Software");
        m_depts.Add("Calibration");



        wxArrayString   m_techs;

        m_techs.Add("Alex");
        m_techs.Add("Gabbi");
        m_techs.Add("Don");
        m_techs.Add("Dan");
        m_techs.Add("John");
        m_techs.Add("Shawn");
        m_techs.Add("Chris");
        m_techs.Add("Josh");
        m_techs.Add("Angelia");
        m_techs.Add("Hunter");
        m_techs.Add("Algie");
        m_techs.Add("Mike");
        m_techs.Add("Carolyn");
        m_techs.Add("Bo");
        m_techs.Add("Tyler");


        wxFlexGridSizer* dateInfoSizer = new wxFlexGridSizer(3);


        loginInfoSizer->Add((dr), 0, wxALL | wxALIGN_LEFT, 0);
        loginInfoSizer->Add((date), 0, wxALL | wxALIGN_LEFT, 0);



        wxOwnerDrawnComboBox* odcMonth;
        dateInfoSizer->Add(odcMonth = new wxOwnerDrawnComboBox(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, m_month, (long)0));
        odcMonth->SetBackgroundColour(wxColour(228, 228, 240));
        odcMonth->SetValidator(wxTextValidator(wxFILTER_NONE, &month));
        wxOwnerDrawnComboBox* odcDay;
        dateInfoSizer->Add(odcDay = new wxOwnerDrawnComboBox(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, m_day, (long)0));
        odcDay->SetBackgroundColour(wxColour(228, 228, 240));
        odcDay->SetValidator(wxTextValidator(wxFILTER_NONE, &day));

        wxOwnerDrawnComboBox* odcYear;
        dateInfoSizer->Add(odcYear = new wxOwnerDrawnComboBox(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, m_Year, (long)0));
        odcYear->SetBackgroundColour(wxColour(228, 228, 240));
        odcYear->SetValidator(wxTextValidator(wxFILTER_NONE, &year));


        wxFlexGridSizer* loginInfoSizer2 = new wxFlexGridSizer(2);

        wxOwnerDrawnComboBox* odcDept;
        wxInitAllImageHandlers();
        loginInfoSizer2->Add((dept), 0, wxALL | wxALIGN_RIGHT, 5);
        loginInfoSizer2->Add(odcDept = new wxOwnerDrawnComboBox(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, m_depts, (long)0));
        odcDept->SetBackgroundColour(wxColour(228, 228, 240));
        odcDept->SetValidator(wxTextValidator(wxFILTER_NONE, &department));

        wxOwnerDrawnComboBox* odcTech;
        loginInfoSizer2->Add((tech), 0, wxALL | wxALIGN_RIGHT, 5);
        loginInfoSizer2->Add(odcTech = new wxOwnerDrawnComboBox(this, wxID_ANY, wxEmptyString,
            wxDefaultPosition, wxDefaultSize, m_techs, (long)0));
        odcTech->SetBackgroundColour(wxColour(228, 228, 240));
        odcTech->SetValidator(wxTextValidator(wxFILTER_NONE, &technician));


        // Load images from disk
        wxImage imgNormal("dropbutn.png");
        wxImage imgPressed("dropbutp.png");
        wxImage imgHover("dropbuth.png");

        if (imgNormal.IsOk() && imgPressed.IsOk() && imgHover.IsOk())
        {
            wxBitmap bmpNormal(imgNormal);
            wxBitmap bmpPressed(imgPressed);
            wxBitmap bmpHover(imgHover);
            odcDept->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
            odcTech->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
            odcMonth->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
            odcDay->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
            odcYear->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
        }
        else
            wxLogError("Dropbutton images not found");



        loginInfoSizer2->Add((stat), 0, wxALL | wxALIGN_RIGHT, 5);
        wxTextCtrl* ctlStatusTxt = new wxTextCtrl(this, wxID_ANY);
        ctlStatusTxt->SetBackgroundColour(wxColour(228, 228, 240));
        ctlStatusTxt->SetValidator(wxTextValidator(wxFILTER_NONE, &status));
        loginInfoSizer2->Add(ctlStatusTxt, 0, wxALL, 5);

        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        mainSizer->Add(loginInfoSizer, 0, wxALL, 5);
        mainSizer->Add(dateInfoSizer, 0, wxALL, 5);
        mainSizer->Add(loginInfoSizer2, 0, wxALL, 5);
        mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALL, 5);
        SetSizerAndFit(mainSizer);
        Fit();
        Centre();

    }
};

*/

class CustomDialog2 : public wxDialog
{
public:
    CustomDialog2(const wxString& title);

};


#endif // REPAIRDIALOGUE_H_INCLUDED
