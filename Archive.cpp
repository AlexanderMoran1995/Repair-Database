#include "Archive.h"

#include <wx/clipbrd.h>

using namespace std;




const long ArchivePanel::idButtonGetInfo = ::wxNewId();   //Get Button
const long ArchivePanel::idButtonSearch = ::wxNewId();   //Search Button
const long ArchivePanel::idButtonResetGrid = ::wxNewId();   //Reset Button
const long ArchivePanel::idButtonSortGrid = ::wxNewId();   //Sort Button
const long ArchivePanel::idButtonExcelOutput = ::wxNewId();
const long ArchivePanel::idButtonLogReport = ::wxNewId();
const long ArchivePanel::idButtonFdaSpreadsheet = ::wxNewId();


BEGIN_EVENT_TABLE(ArchivePanel, wxPanel)



EVT_BUTTON(idButtonGetInfo, ArchivePanel::onClickGet) //New User Button
EVT_BUTTON(idButtonSearch, ArchivePanel::onClickSearch) //Login Button
EVT_BUTTON(idButtonResetGrid, ArchivePanel::onClickReset) //Login Button
EVT_BUTTON(idButtonSortGrid, ArchivePanel::onClickSort) //Login Button
EVT_BUTTON(idButtonExcelOutput, ArchivePanel::onClickExcelOutput)
EVT_BUTTON(idButtonLogReport, ArchivePanel::onClickLogReport)
EVT_BUTTON(idButtonFdaSpreadsheet, ArchivePanel::onClickFdaSpreadsheet)

EVT_TIMER(TIMER_ID, ArchivePanel::OnTimer)

EVT_GRID_CELL_LEFT_CLICK(ArchivePanel::OnCellLeftClick)
EVT_GRID_CELL_RIGHT_CLICK(ArchivePanel::OnCellRightClick)

END_EVENT_TABLE()



ArchiveBackgroundPanel::ArchiveBackgroundPanel(wxPanel* parent)
    : wxPanel(parent, -1, wxDefaultPosition,
        wxSize(1207, 707))
{

    ArchiveGP = new ArchivePanel(this);

}


ArchiveBackgroundPanel::~ArchiveBackgroundPanel() {}


ArchivePanel::ArchivePanel(wxPanel* parent)
    : wxPanel(parent, -1, wxDefaultPosition,
        wxSize(1207, 707))
{
    ///PARENT PANEL

    panel = parent;

    wxPanel* panel = new wxPanel(this, wxID_ANY,
        wxPoint(-1, -1), wxSize(1207, 707), wxBORDER_RAISED);
    panel->SetBackgroundColour(wxColour(150, 150, 150));



    ///DATA GRID

    wxPanel* dataGridPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(3, 3), wxSize(1195, 348), wxBORDER_RAISED);
    dataGridPanel->SetBackgroundColour(wxColor(150, 250, 150));


    grid = new wxGrid(dataGridPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(1191, 343));

    grid->CreateGrid(0, 9);

    grid->SetLabelBackgroundColour(wxColor(0, 25, 32));
    grid->SetLabelTextColour(wxColor(0, 173, 234));
    grid->SetGridLineColour(wxColor(0, 173, 234));
    grid->SetDefaultCellTextColour(wxColor(0, 255, 255));
    grid->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    grid->Refresh();

    grid->EnableEditing(false);
    grid->EnableGridLines(true);
    grid->DisableDragColSize();
    grid->DisableDragRowSize();
    grid->EnableDragGridSize(false);

    grid->SetSelectionBackground(wxColor(220, 240, 255));
    grid->SetSelectionForeground(wxColor(0, 0, 0));

    grid->SetRowLabelSize(0);
    grid->SetDefaultCellOverflow(false);

    grid->SetColLabelValue(0, _("ID#"));
    grid->SetColLabelValue(1, _("Contact Name"));
    grid->SetColLabelValue(2, _("Company Name"));
    grid->SetColLabelValue(3, _("Repair Number"));
    grid->SetColLabelValue(4, _("Model Number"));
    grid->SetColLabelValue(5, _("Technician"));
    grid->SetColLabelValue(6, _("Serial Number"));
    grid->SetColLabelValue(7, _("Last Update"));
    grid->SetColLabelValue(8, _("Date Received"));

    grid->SetDefaultCellFont(wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    grid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetDefaultColSize(140);
    grid->SetDefaultRowSize(31);

    grid->SetColSize(0, 56);
    grid->SetColSize(1, 196);
    grid->SetColSize(2, 240);
    grid->SetColSize(3, 115);
    grid->SetColSize(4, 115);
    grid->SetColSize(5, 100);
    grid->SetColSize(6, 160);
    grid->SetColSize(7, 95);
    grid->SetColSize(8, 95);

    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//LogDatabase.db");

    db->Open(testDBName);


    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT);");

    //db->Close();

   // db->Open(testDBName);

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT DISTINCT RepairNumber FROM nodeData WHERE Status = 'Shipped' ORDER BY rowid ASC;");

    std::vector<wxString> repairVector;
    int repairCount = 0;

    while (Res.NextRow())
    {
        repairVector.push_back(Res.GetAsString(0));
        repairCount++;
    }


    Res.Finalize();
    db->Close();

    dbSize = 0;
    int count = 0;

    db->Open(testDBName);
    wxSQLite3ResultSet Res2;

    for (int i = 0; i < repairCount; i++) {

        Res2 = db->ExecuteQuery("SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived, Status FROM nodeData WHERE RepairNumber = '" + repairVector.at(i) + "' ORDER BY Chronology DESC LIMIT 1;");

        if (Res2.GetAsString(9) == "Shipped") {

            grid->AppendRows(1);
            dbSize++;
            grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
            grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));

            for (int i = 0; i < 9; i++) {

                grid->SetCellValue(count, i, wxString::Format(_("%s"), Res2.GetAsString(i)));


            }

            count++;
        }
    }


    Res2.Finalize();
    db->Close();
    repairVector.clear();

    ///PARENT CONTROL PANEL
    wxPanel* controlPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(3, 353), wxSize(224, 310), wxBORDER_NONE);
    controlPanel->SetBackgroundColour(wxColour(150, 150, 150));


    wxPanel* descriptionTitlePanel = new wxPanel(controlPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(224, 37), wxBORDER_RAISED);
    descriptionTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* descriptionTitle = new wxStaticText(descriptionTitlePanel, wxID_ANY, ("Grid Controls"), wxPoint(55, 3), wxSize(-1, -1), wxTE_CENTRE);
    descriptionTitle->SetForegroundColour(wxColor(0, 188, 255));

    descriptionTitle->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* cpsl4 = new wxStaticLine(controlPanel, wxID_ANY, wxPoint(-1, 28),
        wxSize(224, 2));





    /// SEARCH PANEL
    wxPanel* searchPanel = new wxPanel(controlPanel, wxID_ANY,
        wxPoint(-1, 34), wxSize(224, 96), wxBORDER_RAISED);
    searchPanel->SetBackgroundColour(wxColor(33, 33, 57));

    // Create common strings array

    m_fieldarray.Add("Contact Name");
    m_fieldarray.Add("Company Name");
    m_fieldarray.Add("Repair Number");
    m_fieldarray.Add("Model Number");
    m_fieldarray.Add("Technician");
    m_fieldarray.Add("Serial Number");
    m_fieldarray.Add("Last Update");
    m_fieldarray.Add("Date Received");

    m_srchCtrl = new wxSearchCtrl(searchPanel, -1, wxEmptyString, wxPoint(5, 9),
        FromDIP(wxSize(87, -1)));

    odcSearchCategory = new wxOwnerDrawnComboBox(searchPanel, wxID_ANY, "CATEGORIES",
        wxPoint(97, 9), wxDefaultSize,
        m_fieldarray,
        (long)0 | wxCB_READONLY);

    odcSearchCategory->SetBackgroundColour(wxColour(228, 228, 240));

    // Load images from disk
    wxImage imgNormal("dropbutn.png");
    wxImage imgPressed("dropbutp.png");
    wxImage imgHover("dropbuth.png");

    if (imgNormal.IsOk() && imgPressed.IsOk() && imgHover.IsOk())
    {
        wxBitmap bmpNormal(imgNormal);
        wxBitmap bmpPressed(imgPressed);
        wxBitmap bmpHover(imgHover);
        odcSearchCategory->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
    }

    m_srchCtrl->ShowSearchButton(false);
    m_srchCtrl->ShowCancelButton(false);
    m_srchCtrl->SetBackgroundColour(wxColour(228, 228, 240));


    wxBitmapButton* searchButton = new wxBitmapButton(searchPanel, idButtonSearch, wxBitmap(wxT("searchButton.png"),
        wxBITMAP_TYPE_PNG), wxPoint(49, 42), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage searchButtonimgHover("searchButtonh.png");
    searchButton->SetBitmapHover(searchButtonimgHover);
    wxImage searchButtonimgPressed("searchButtonp.png");
    searchButton->SetBitmapPressed(searchButtonimgPressed);




    ///CONTROL AND SORTING PANEL
    wxPanel* sortPanel = new wxPanel(controlPanel, wxID_ANY,
        wxPoint(-1, 132), wxSize(224, 109), wxBORDER_RAISED);
    sortPanel->SetBackgroundColour(wxColour(33, 33, 57));

 

    wxBitmapButton* ResetButton = new wxBitmapButton(sortPanel, idButtonResetGrid, wxBitmap(wxT("resetButton.png"),
        wxBITMAP_TYPE_PNG), wxPoint(68, 12), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage ResetButtonimgHover("resetButtonh.png");
    ResetButton->SetBitmapHover(ResetButtonimgHover);
    wxImage ResetButtonimgPressed("resetButtonp.png");
    ResetButton->SetBitmapPressed(ResetButtonimgPressed);

    m_sortbyarray.Add("Oldest to Newest");
    m_sortbyarray.Add("Newest to Oldest");
    m_sortbyarray.Add("Contact");
    m_sortbyarray.Add("Company");
    m_sortbyarray.Add("Repair #");
    m_sortbyarray.Add("Model #");
    m_sortbyarray.Add("Technician");
    m_sortbyarray.Add("Serial Number");
    m_sortbyarray.Add("Last Updated");
    m_sortbyarray.Add("Date Received");


    odcSortBy = new wxOwnerDrawnComboBox(sortPanel, wxID_ANY, "SORT BY",
        wxPoint(7, 61), wxDefaultSize,
        m_sortbyarray,
        (long)0 | wxCB_READONLY
    );


    if (imgNormal.IsOk() && imgPressed.IsOk() && imgHover.IsOk())
    {
        wxBitmap bmpNormal(imgNormal);
        wxBitmap bmpPressed(imgPressed);
        wxBitmap bmpHover(imgHover);
        odcSortBy->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
    }

    odcSortBy->SetBackgroundColour(wxColour(228, 228, 240));

    wxBitmapButton* SortButton = new wxBitmapButton(sortPanel, idButtonSortGrid, wxBitmap(wxT("sortButton.png"),
        wxBITMAP_TYPE_PNG), wxPoint(140, 54), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage SortButtonimgHover("sortButtonh.png");
    SortButton->SetBitmapHover(SortButtonimgHover);
    wxImage SortButtonimgPressed("sortButtonp.png");
    SortButton->SetBitmapPressed(SortButtonimgPressed);



    ///GET PANEL
    wxPanel* descriptionPanel = new wxPanel(controlPanel, idButtonGetInfo,
        wxPoint(-1, 243), wxSize(224, 67), wxBORDER_RAISED);
    descriptionPanel->SetBackgroundColour(wxColour(33, 33, 57));

    idEntry = new wxTextCtrl(descriptionPanel, -1, wxT(""), wxPoint(28, 15),
        wxSize(70, 27));
    idEntry->SetBackgroundColour(wxColour(228, 228, 240));
    idEntry->SetFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));

    wxBitmapButton* GetButton = new wxBitmapButton(descriptionPanel, idButtonGetInfo, wxBitmap(wxT("getButton.png"),
        wxBITMAP_TYPE_PNG), wxPoint(130, 13), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage GetButtonimgHover("getButtonh.png");
    GetButton->SetBitmapHover(GetButtonimgHover);
    wxImage GetButtonimgPressed("getButtonp.png");
    GetButton->SetBitmapPressed(GetButtonimgPressed);





    ///EXPORT PANEL
    wxPanel* exportPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(230, 353), wxSize(267, 310), wxBORDER_RAISED);
    exportPanel->SetBackgroundColour(wxColour(150, 150, 250));

    wxPanel* exportTitlePanel = new wxPanel(exportPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(267, 30), wxBORDER_NONE);
    exportTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* exportTitle = new wxStaticText(exportTitlePanel, wxID_ANY, ("Form Generator"), wxPoint(60, 3), wxSize(-1, -1), wxTE_CENTRE);
    exportTitle->SetForegroundColour(wxColor(0, 188, 255));

    exportTitle->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* epsl4 = new wxStaticLine(exportPanel, wxID_ANY, wxPoint(-1, 30),
        wxSize(267, 2));


    m_deptarray.Add("Nervo-Scope");
    m_deptarray.Add("Analog");
    m_deptarray.Add("Digital");
    m_deptarray.Add("Sensors");
    m_deptarray.Add("Metrology");
    m_deptarray.Add("Misc.");
    m_deptarray.Add("All");



    odcdept = new wxOwnerDrawnComboBox(exportPanel, wxID_ANY, "DATABASE",
        wxPoint(3, 55), wxSize(110, -1),
        m_deptarray,
        (long)0 | wxCB_READONLY
    );


    if (imgNormal.IsOk() && imgPressed.IsOk() && imgHover.IsOk())
    {
        wxBitmap bmpNormal(imgNormal);
        wxBitmap bmpPressed(imgPressed);
        wxBitmap bmpHover(imgHover);
        odcdept->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
    }

    odcdept->SetBackgroundColour(wxColour(228, 228, 240));


    wxBitmapButton* SpreadsheetButton = new wxBitmapButton(exportPanel, idButtonExcelOutput, wxBitmap(wxT("spreadsheet.png"),
        wxBITMAP_TYPE_PNG), wxPoint(125, 50), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage SpreadsheetButtonimgHover("spreadsheeth.png");
    SpreadsheetButton->SetBitmapHover(SpreadsheetButtonimgHover);
    wxImage SpreadsheetButtonimgPressed("spreadsheetp.png");
    SpreadsheetButton->SetBitmapPressed(SpreadsheetButtonimgPressed);


    odclog = new wxOwnerDrawnComboBox(exportPanel, wxID_ANY, "LOG DB",
        wxPoint(3, 155), wxSize(110, -1),
        m_deptarray,
        (long)0 | wxCB_READONLY
    );

    if (imgNormal.IsOk() && imgPressed.IsOk() && imgHover.IsOk())
    {
        wxBitmap bmpNormal(imgNormal);
        wxBitmap bmpPressed(imgPressed);
        wxBitmap bmpHover(imgHover);
        odclog->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
    }

    wxBitmapButton* LogReportButton = new wxBitmapButton(exportPanel, idButtonLogReport, wxBitmap(wxT("logReport.png"),
        wxBITMAP_TYPE_PNG), wxPoint(134, 150), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage LogReportButtonimgHover("logReporth.png");
    LogReportButton->SetBitmapHover(LogReportButtonimgHover);
    wxImage LogReportButtonimgPressed("logReportp.png");
    LogReportButton->SetBitmapPressed(LogReportButtonimgPressed);

    

    wxBitmapButton* fdaSpreadsheetButton = new wxBitmapButton(exportPanel, idButtonFdaSpreadsheet, wxBitmap(wxT("FDAspreadsheet.png"),
        wxBITMAP_TYPE_PNG), wxPoint(41, 250), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage fdaSpreadsheetButtonimgHover("FDAspreadsheeth.png");
    fdaSpreadsheetButton->SetBitmapHover(fdaSpreadsheetButtonimgHover);
    wxImage fdaSpreadsheetButtonimgPressed("FDAspreadsheetp.png");
    fdaSpreadsheetButton->SetBitmapPressed(fdaSpreadsheetButtonimgPressed);

   


    ///CONTACT INFO PANEL

    wxPanel* contactPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(500, 353), wxSize(420, 310), wxBORDER_RAISED);
    contactPanel->SetBackgroundColour(wxColour(33, 33, 57));

    wxPanel* contactTitlePanel = new wxPanel(contactPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(420, 42), wxBORDER_NONE);
    contactTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* contactTitle = new wxStaticText(contactTitlePanel, wxID_ANY, ("Additional Information"), wxPoint(100, 5), wxSize(-1, -1), wxTE_CENTRE);
    contactTitle->SetForegroundColour(wxColor(0, 188, 255));
    contactTitle->SetFont(wxFont(20, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* copsl1 = new wxStaticLine(contactPanel, wxID_ANY, wxPoint(-1, 43),
        wxSize(420, 2));

    extraDataGrid = new wxGrid(contactPanel, wxID_ANY,
        wxPoint(-1, 45), wxSize(420, 268));

    extraDataGrid->CreateGrid(9, 2);


    extraDataGrid->SetGridLineColour(wxColor(0, 173, 234));
    extraDataGrid->SetDefaultCellTextColour(wxColor(0, 255, 255));
    extraDataGrid->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    extraDataGrid->Refresh();

    extraDataGrid->EnableEditing(false);
    extraDataGrid->EnableGridLines(true);
    extraDataGrid->DisableDragColSize();
    extraDataGrid->DisableDragRowSize();
    extraDataGrid->EnableDragGridSize(false);
    extraDataGrid->SetCellHighlightPenWidth(0);
    extraDataGrid->SetCellHighlightROPenWidth(0);
    extraDataGrid->SetSelectionBackground(extraDataGrid->GetDefaultCellBackgroundColour());
    extraDataGrid->SetSelectionForeground(extraDataGrid->GetDefaultCellTextColour());
    extraDataGrid->SetRowLabelSize(0);
    extraDataGrid->SetColLabelSize(0);


    extraDataGrid->SetDefaultCellFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    extraDataGrid->SetDefaultColSize(208);
    extraDataGrid->SetDefaultRowSize(29);

    extraDataGrid->SetColSize(0, 174);
    extraDataGrid->SetColSize(1, 242);


    extraDataGrid->SetCellValue(0, 0, " ID #:");
    extraDataGrid->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    extraDataGrid->SetCellValue(1, 0, " Contact:");
    extraDataGrid->SetCellAlignment(1, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    extraDataGrid->SetCellValue(2, 0, " Address:");
    extraDataGrid->SetCellAlignment(2, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    extraDataGrid->SetCellValue(3, 0, " Phone Number:");
    extraDataGrid->SetCellAlignment(3, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    extraDataGrid->SetCellValue(4, 0, " Email Address:");
    extraDataGrid->SetCellAlignment(4, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    extraDataGrid->SetCellValue(5, 0, " Model Number:");
    extraDataGrid->SetCellAlignment(5, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    extraDataGrid->SetCellValue(6, 0, " Serial Number:");
    extraDataGrid->SetCellAlignment(6, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    extraDataGrid->SetCellValue(7, 0, " Case:");
    extraDataGrid->SetCellAlignment(7, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    extraDataGrid->SetCellValue(8, 0, " Quantity:");
    extraDataGrid->SetCellAlignment(8, 0, wxALIGN_LEFT, wxALIGN_CENTRE);

    extraDataGrid->SetCellBackgroundColour(0, 1, wxColour(230, 230, 230));
    extraDataGrid->SetCellBackgroundColour(1, 1, wxColour(220, 240, 255));
    extraDataGrid->SetCellBackgroundColour(2, 1, wxColour(230, 230, 230));
    extraDataGrid->SetCellBackgroundColour(3, 1, wxColour(220, 240, 255));
    extraDataGrid->SetCellBackgroundColour(4, 1, wxColour(230, 230, 230));
    extraDataGrid->SetCellBackgroundColour(5, 1, wxColour(220, 240, 255));
    extraDataGrid->SetCellBackgroundColour(6, 1, wxColour(230, 230, 230));
    extraDataGrid->SetCellBackgroundColour(7, 1, wxColour(220, 240, 255));
    extraDataGrid->SetCellBackgroundColour(8, 1, wxColour(230, 230, 230));


    extraDataGrid->SetCellTextColour(0, 1, wxColour(0, 0, 0));
    extraDataGrid->SetCellTextColour(1, 1, wxColour(0, 0, 0));
    extraDataGrid->SetCellTextColour(2, 1, wxColour(0, 0, 0));
    extraDataGrid->SetCellTextColour(3, 1, wxColour(0, 0, 0));
    extraDataGrid->SetCellTextColour(4, 1, wxColour(0, 0, 0));
    extraDataGrid->SetCellTextColour(5, 1, wxColour(0, 0, 0));
    extraDataGrid->SetCellTextColour(6, 1, wxColour(0, 0, 0));
    extraDataGrid->SetCellTextColour(7, 1, wxColour(0, 0, 0));
    extraDataGrid->SetCellTextColour(8, 1, wxColour(0, 0, 0));



    extraDataGrid->SetCellFont(0, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetCellFont(1, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetCellFont(2, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetCellFont(3, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetCellFont(4, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetCellFont(5, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetCellFont(6, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetCellFont(7, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    extraDataGrid->SetCellFont(8, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));


    wxPanel* problemSolutionPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(923, 353), wxSize(275, 315), wxBORDER_NONE);
    problemSolutionPanel->SetBackgroundColour(wxColour(150, 150, 150));



    wxPanel* problemPanel = new wxPanel(problemSolutionPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(275, 153), wxBORDER_RAISED);
    problemPanel->SetBackgroundColour(wxColour(230, 230, 230));


    wxPanel* problemTitlePanel = new wxPanel(problemPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(275, 35), wxBORDER_NONE);
    problemTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* problemTitle = new wxStaticText(problemTitlePanel, wxID_ANY, ("What We Found"), wxPoint(50, 3), wxSize(-1, -1), wxTE_CENTRE);
    problemTitle->SetForegroundColour(wxColor(0, 188, 255));
    problemTitle->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* ppsl1 = new wxStaticLine(problemPanel, wxID_ANY, wxPoint(-1, 35),
        wxSize(420, 2));


    OfficeProblemGrid = new wxGrid(problemPanel, wxID_ANY,
        wxPoint(-1, 38), wxSize(273, 110));

    OfficeProblemGrid->CreateGrid(1, 1);

    OfficeProblemGrid->SetGridLineColour(wxColor(230, 230, 230));
    OfficeProblemGrid->SetDefaultCellTextColour(wxColor(0, 0, 0));
    OfficeProblemGrid->SetDefaultCellBackgroundColour(wxColor(230, 230, 230));
    OfficeProblemGrid->Refresh();

    OfficeProblemGrid->EnableEditing(false);
    OfficeProblemGrid->EnableGridLines(true);
    OfficeProblemGrid->DisableDragColSize();
    OfficeProblemGrid->DisableDragRowSize();
    OfficeProblemGrid->EnableDragGridSize(false);
    OfficeProblemGrid->SetCellHighlightPenWidth(0);
    OfficeProblemGrid->SetCellHighlightROPenWidth(0);
    OfficeProblemGrid->SetSelectionBackground(OfficeProblemGrid->GetDefaultCellBackgroundColour());
    OfficeProblemGrid->SetSelectionForeground(OfficeProblemGrid->GetDefaultCellTextColour());
    OfficeProblemGrid->SetRowLabelSize(0);
    OfficeProblemGrid->SetColLabelSize(0);

    OfficeProblemGrid->SetDefaultCellFont(wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    OfficeProblemGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    OfficeProblemGrid->SetDefaultColSize(269);
    OfficeProblemGrid->SetDefaultRowSize(110);
    OfficeProblemGrid->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_TOP);

    OfficeProblemGrid->SetCellRenderer(0, 0, new wxGridCellAutoWrapStringRenderer);




    wxPanel* solutionPanel = new wxPanel(problemSolutionPanel, wxID_ANY,
        wxPoint(-1, 157), wxSize(275, 153), wxBORDER_RAISED);
    solutionPanel->SetBackgroundColour(wxColour(220, 240, 255));


    wxPanel* solutionTitlePanel = new wxPanel(solutionPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(275, 35), wxBORDER_NONE);
    solutionTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* solutionTitle = new wxStaticText(solutionTitlePanel, wxID_ANY, ("Notes"), wxPoint(100, 3), wxSize(-1, -1), wxTE_CENTRE);
    solutionTitle->SetForegroundColour(wxColor(0, 188, 255));
    solutionTitle->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* spsl1 = new wxStaticLine(solutionPanel, wxID_ANY, wxPoint(-1, 35),
        wxSize(420, 2));

    OfficeCorrectionGrid = new wxGrid(solutionPanel, wxID_ANY,
        wxPoint(-1, 38), wxSize(273, 110));

    OfficeCorrectionGrid->CreateGrid(1, 1);

    OfficeCorrectionGrid->SetGridLineColour(wxColor(220, 240, 255));
    OfficeCorrectionGrid->SetDefaultCellTextColour(wxColor(0, 0, 0));
    OfficeCorrectionGrid->SetDefaultCellBackgroundColour(wxColor(220, 240, 255));
    OfficeCorrectionGrid->Refresh();

    OfficeCorrectionGrid->EnableEditing(false);
    OfficeCorrectionGrid->EnableGridLines(true);
    OfficeCorrectionGrid->DisableDragColSize();
    OfficeCorrectionGrid->DisableDragRowSize();
    OfficeCorrectionGrid->EnableDragGridSize(false);
    OfficeCorrectionGrid->SetCellHighlightPenWidth(0);
    OfficeCorrectionGrid->SetCellHighlightROPenWidth(0);
    OfficeCorrectionGrid->SetSelectionBackground(OfficeCorrectionGrid->GetDefaultCellBackgroundColour());
    OfficeCorrectionGrid->SetSelectionForeground(OfficeCorrectionGrid->GetDefaultCellTextColour());
    OfficeCorrectionGrid->SetRowLabelSize(0);
    OfficeCorrectionGrid->SetColLabelSize(0);

    OfficeCorrectionGrid->SetDefaultCellFont(wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    OfficeCorrectionGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    OfficeCorrectionGrid->SetDefaultColSize(269);
    OfficeCorrectionGrid->SetDefaultRowSize(110);
    OfficeCorrectionGrid->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_TOP);

    OfficeCorrectionGrid->SetCellRenderer(0, 0, new wxGridCellAutoWrapStringRenderer);
    ///LOGIN PANEL

//wxPanel* loginPanel = new wxPanel(panel, wxID_ANY,
  //  wxPoint(3, 3), wxSize(224, 160), wxBORDER_RAISED);
//loginPanel->SetBackgroundColour(wxColour(33, 33, 57));

//  wxPanel* loginTitlePanel = new wxPanel(loginPanel, wxID_ANY,
 //     wxPoint(-1, -1), wxSize(320, 150), wxBORDER_NONE);
//  loginTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

  //wxPNGHandler* logohandler = new wxPNGHandler;
  //wxImage::AddHandler(logohandler);
//wxStaticBitmap* logoimage;

//logoimage = new wxStaticBitmap(loginPanel, wxID_ANY, wxBitmap("loginLogoImage4.png", wxBITMAP_TYPE_PNG), wxPoint(0, 6), wxDefaultSize, wxNO_BORDER);
/*
    wxStaticLine* lopsl1 = new wxStaticLine(loginPanel, wxID_ANY, wxPoint(-1, 150),
        wxSize(320, 3));

    wxStaticText* loginTitle = new wxStaticText(loginPanel, wxID_ANY, ("Logged in as:"), wxPoint(5, 170), wxSize(-1, -1), wxTE_CENTRE);
    loginTitle->SetForegroundColour(wxColor(0, 188, 255));
    loginTitle->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));




    wxTextCtrl* usernameEntry = new wxTextCtrl(loginPanel, -1, wxT(""), wxPoint(160, 170),
        wxSize(140, 35));
    usernameEntry->SetBackgroundColour(wxColour(228, 228, 240));
    usernameEntry->SetFont(wxFont(20, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));


   // db = new wxSQLite3Database();

   // testDBName = wxGetCwd() + wxT("//loginDatabase.db");

   // db->Open(testDBName);

   // wxSQLite3ResultSet Res4 = db->ExecuteQuery("SELECT Username FROM ProcessedLogin;");

   // wxString testInput = Res4.GetAsString(0);


  //  Res4.Finalize();

  //  db->ExecuteQuery("PRAGMA foreign_keys = OFF;");
  //  db->ExecuteQuery("DROP TABLE ProcessedLogin;");
 //   db->ExecuteQuery("PRAGMA foreign_keys = ON;");

  //  db->Close();

   // wxString testInput = Res.GetAsString(0);
  //  usernameEntry->SetValue(Res4.GetAsString(0));

    wxBitmapButton* Loginbutton = new wxBitmapButton(loginPanel, wxID_ANY, wxBitmap(wxT("logout.png"),
        wxBITMAP_TYPE_PNG), wxPoint(85, 225), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage LoginbuttonimgHover("logouth.png");
    Loginbutton->SetBitmapHover(LoginbuttonimgHover);
    wxImage LoginbuttonimgPressed("logoutp.png");
    Loginbutton->SetBitmapPressed(LoginbuttonimgPressed);

    */

   // static const int INTERVAL = 300000; // milliseconds
   // m_timer = new wxTimer(this, TIMER_ID);
   // m_timer->Start(INTERVAL);


    initITT = 0;
}





ArchivePanel::~ArchivePanel() {}




void ArchivePanel::onClickGet(wxCommandEvent& event)
{
    //	wxString idHighlightHolder;
//	testDBName = wxGetCwd() + wxT("//LogDatabase.db");

//	db->Open(testDBName);

//	db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT);");

//	wxSQLite3ResultSet Res4 = db->ExecuteQuery("SELECT Id, RepairNumber FROM nodeData WHERE RepairNumber ='" + getValueS + "';");



//	idHighlightHolder = Res4.GetAsString(0);

//	Res4.Finalize();


//	db->Close();

   // if (cycles >> 0) {


    //    for (int i = 0; i < cellCount; i++) {
        //	cellValue = idHighlightHolder;
    //		cellValue = grid->GetCellValue(i, 0);

      //      if (getValueS == cellValue) {

        //        grid->SetCellBackgroundColour(i, 0, wxColour(0, 25, 32));
          //      grid->SetCellTextColour(i, 0, wxColour(0, 173, 234));

           //     for (int j = 1; j < 10; j++) {

            //        grid->SetCellBackgroundColour(i, j, wxColour(33, 33, 57));
            //        grid->SetCellTextColour(i, j, wxColour(0, 255, 255));

            //    }

         //   }

    //    }



   // }

    wxString logRN;

    getValueS = idEntry->GetValue();

    if (getValueS == "")
    {
        wxString msg = _T("ERROR: No Input Detected For 'GET' Please Try again");
        wxString info = _T("Get ERROR");
        wxMessageBox(msg,
            info,
            wxOK | wxICON_WARNING,
            this);
    }

    else
    {

        wxString idHighlightHolder;
        testDBName = wxGetCwd() + wxT("//LogDatabase.db");

        db->Open(testDBName);

        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

        wxSQLite3ResultSet Res4 = db->ExecuteQuery("SELECT Id, RepairNumber FROM nodeData WHERE RepairNumber ='" + getValueS + "';");



        idHighlightHolder = Res4.GetAsString(1);

        Res4.Finalize();


        db->Close();


        getValueI = wxAtoi(idHighlightHolder);

        cellCount = grid->GetNumberRows();
        idEntry->SetValue(idHighlightHolder);

        testDBName = wxGetCwd() + wxT("//LogDatabase.db");

        db->Open(testDBName);

        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

        wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT Id,ContactName,Address,PhoneNumber,EmailAddress,ModelNumber,SensorSerialNumber,CaseYN,Quantity FROM nodeData WHERE RepairNumber ='" + getValueS + "';");
        wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT WhatWeFound FROM nodeData WHERE RepairNumber ='" + getValueS + "';");
        wxSQLite3ResultSet Res3 = db->ExecuteQuery("SELECT CorrectiveAction FROM nodeData WHERE RepairNumber ='" + getValueS + "';");

        while (Res.NextRow())
        {

            for (int i = 0; i < 9; i++) {

                extraDataGrid->SetCellValue(i, 1, wxString::Format(_("%s"), Res.GetAsString(i)));


            }

        }

        while (Res2.NextRow())
        {

            OfficeProblemGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res2.GetAsString(0)));
        }

        while (Res3.NextRow())
        {

            OfficeCorrectionGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res3.GetAsString(0)));

        }



        Res.Finalize();
        Res2.Finalize();
        Res3.Finalize();


        db->Close();

        for (int i = 0; i < cellCount; i++) {
            cellValue = grid->GetCellValue(i, 3);

            if (getValueI == cellValue) {

                grid->SetCellBackgroundColour(i, 0, wxColour(0, 173, 234));
                grid->SetCellTextColour(i, 0, wxColour(0, 250, 250));

                for (int j = 1; j < 9; j++) {

                    grid->SetCellBackgroundColour(i, j, wxColour(228, 228, 240));
                    grid->SetCellTextColour(i, j, wxColour(0, 0, 0));

                }

            }

        }

        grid->Refresh();

        cycles++;

        idEntry->SetValue("");



    }
}





void ArchivePanel::onClickSearch(wxCommandEvent& event)
{

    getSearchCriteria = m_srchCtrl->GetValue();
    getSearchCategory = odcSearchCategory->GetValue();

    if (getSearchCriteria == "")
    {
        wxString msg = _T("ERROR: No Input Detected For 'SEARCH' Please Try again");
        wxString info = _T("Search ERROR");
        wxMessageBox(msg,
            info,
            wxOK | wxICON_WARNING,
            this);
    }

    else
    {
        int n = 0;
        grid->DeleteRows(n, grid->GetNumberRows() - n);

        testDBName = wxGetCwd() + wxT("//LogDatabase.db");
        db->Open(testDBName);
        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");
     //   db->Close();
       // db->Open(testDBName);

      //  wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT DISTINCT RepairNumber FROM nodeData WHERE Status == 'Shipped' ORDER BY rowid ASC;");

      //  std::vector<wxString> repairVector;
        int repairCount = 0;

       // while (Res.NextRow())
       // {
          //  repairVector.push_back(Res.GetAsString(0));
      //      repairCount++;
      //  }


       // Res.Finalize();
        db->Close();


        dbSize = 0;
        int count = 0;

        db->Open(testDBName);
        wxSQLite3ResultSet Res2;

      //  for (int i = 0; i < repairCount; i++) {

          //  db->Open(testDBName);

            //wxSQLite3ResultSet Res2;

            if (getSearchCategory == "Contact Name") { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE ContactName LIKE '%" + getSearchCriteria + "%' AND Status = 'Shipped' ORDER BY Chronology DESC;"; }
            else if (getSearchCategory == "Company Name") { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived FROM nodeData WHERE CompanyName LIKE '%" + getSearchCriteria + "%' AND Status = 'Shipped' ORDER BY Chronology DESC;"; }
            else if (getSearchCategory == "Repair Number") { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived FROM nodeData WHERE RepairNumber LIKE '%" + getSearchCriteria + "%' AND Status = 'Shipped' ORDER BY Chronology DESC;"; }
            else if (getSearchCategory == "Model Number") { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived FROM nodeData WHERE ModelNumber LIKE '%" + getSearchCriteria + "%' AND Status = 'Shipped' ORDER BY Chronology DESC;"; }
            else if (getSearchCategory == "Technician") { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived FROM nodeData WHERE Technician LIKE '%" + getSearchCriteria + "%' AND Status = 'Shipped' ORDER BY Chronology DESC;"; }
            else if (getSearchCategory == "Serial Number") { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived FROM nodeData WHERE SensorSerialNumber LIKE '%" + getSearchCriteria + "%' AND Status = 'Shipped' ORDER BY Chronology DESC;"; }
            else if (getSearchCategory == "Last Updated") { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived FROM nodeData WHERE DateSent LIKE '%" + getSearchCriteria + "%' AND Status = 'Shipped' ORDER BY Chronology DESC;"; }
            else if (getSearchCategory == "Date Received") { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived FROM nodeData WHERE DateReceived LIKE '%" + getSearchCriteria + "%' AND Status = 'Shipped' ORDER BY Chronology DESC;"; }
            else { dbQuery = "SELECT DISTINCT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY Chronology DESC;"; }


            Res2 = db->ExecuteQuery(dbQuery);


           // if (Res2.GetAsString(6) == "Shipped") {

                while (Res2.NextRow()) {
                  //  if (Res2.GetAsString(6) == "Shipped") {
                    grid->AppendRows(1);
                    dbSize++;
                    grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
                    grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));
                   
                        for (int i = 0; i < 9; i++) {

                            grid->SetCellValue(count, i, wxString::Format(_("%s"), Res2.GetAsString(i)));


                        }

                        count++;
                  //  }
                }
           // }
       // }




        Res2.Finalize();
        db->Close();
      //  repairVector.clear();
        grid->Refresh();
        
    }
    
}



void ArchivePanel::RESET()
{
    int n = 0;
    if (grid->GetNumberRows() >> 0) {

        // if (cntr >> 0) {
        grid->DeleteRows(n, grid->GetNumberRows() - n);
        // }
    }
    // cntr++;

    testDBName = wxGetCwd() + wxT("//LogDatabase.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT DISTINCT RepairNumber FROM nodeData WHERE Status == 'Shipped' ORDER BY rowid ASC;");

    std::vector<wxString> repairVector;
    int repairCount = 0;

    while (Res.NextRow())
    {
        repairVector.push_back(Res.GetAsString(0));
        repairCount++;
    }


    Res.Finalize();
    db->Close();

    dbSize = 0;
    int count = 0;

    db->Open(testDBName);
    wxSQLite3ResultSet Res2;

    for (int i = 0; i < repairCount; i++) {

        Res2 = db->ExecuteQuery("SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, SensorSerialNumber, DateSent, DateReceived, Status FROM nodeData WHERE RepairNumber = '" + repairVector.at(i) + "' ORDER BY Chronology DESC LIMIT 1;");

        if (Res2.GetAsString(9) == "Shipped") {

            grid->AppendRows(1);
            dbSize++;
            grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
            grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));

            for (int i = 0; i < 9; i++) {

                grid->SetCellValue(count, i, wxString::Format(_("%s"), Res2.GetAsString(i)));


            }

            count++;
        }
    }

    Res2.Finalize();
    db->Close();

    grid->Refresh();
}


void ArchivePanel::onClickReset(wxCommandEvent& event)
{
    RESET();
}


void ArchivePanel::OnTimer(wxTimerEvent& event)
{
    RESET();
}



void ArchivePanel::onClickSort(wxCommandEvent& event)
{

    getSortCriteria = odcSortBy->GetValue();

    int n = 0;

    grid->DeleteRows(n, grid->GetNumberRows() - n);

    testDBName = wxGetCwd() + wxT("//LogDatabase.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res;


    if (getSortCriteria == "Newest to Oldest") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY rowid DESC;"; }
    else if (getSortCriteria == "Oldest to Newest") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY rowid ASC;"; }
    else if (getSortCriteria == "Contact") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY ContactName ASC;"; }
    else if (getSortCriteria == "Company") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY CompanyName ASC;"; }
    else if (getSortCriteria == "Repair #") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY RepairNumber ASC;"; }
    else if (getSortCriteria == "Model #") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY ModelNumber ASC;"; }
    else if (getSortCriteria == "Technician") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY Technician ASC;"; }
    else if (getSortCriteria == "Status") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY Status ASC;"; }
    else if (getSortCriteria == "Date Received") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY DateReceived ASC;"; }
    else if (getSortCriteria == "Last Updated") { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY DateSent ASC;"; }
    else { dbQuery = "SELECT Id, ContactName, CompanyName, RepairNumber, ModelNumber, Technician, Status, DateSent, DateReceived FROM nodeData WHERE Status = 'Shipped' ORDER BY rowid ASC;"; }

    Res = db->ExecuteQuery(dbQuery);

    int count = 0;
    while (Res.NextRow())
    {

        grid->AppendRows(1);
        dbSize++;
        grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
        grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));
        for (int i = 0; i < 9; i++) {

            grid->SetCellValue(count, i, wxString::Format(_("%s"), Res.GetAsString(i)));

        }

        count++;
    }


    Res.Finalize();
    db->Close();

    grid->Refresh();


}


bool ChartSampleA::Init()
{
    m_app = wxExcelApplication::CreateInstance();
    if (!m_app)
    {
        wxLogError(_("Failed to create an instance of MS Excel application."));
        return false;
    }

    if (!m_app.IsVersionAtLeast_(wxExcelApplication::evExcel2007))
    {
        wxMessageBox(_("This sample requires Microsoft Excel 2007 or newer."), "Information");
        m_app.Quit();
        return false;
    }

    m_app.SetVisible(true);
    m_app.SetDisplayAlerts(false);

    m_workbook = m_app.GetWorkbooks().Add();
    if (!m_workbook)
    {
        wxLogError(_("Failed to create a new workbook."));
        return false;
    }
    m_workbook.SetAutomationLCID_(wxExcelObject::lcidEnglishUS);


    /*
    m_dataWorksheet = m_workbook.GetWorksheets()[1];
    if (!m_dataWorksheet)
    {
        wxLogError(_("Failed to obtain worksheet number 1."));
        return false;
    }
    m_dataWorksheet.SetName("Data (millions EUR)");

    wxExcelRange range = m_dataWorksheet.GetRange("A1:D1");
    if (!WriteData(range))
        return false;

    m_embeddedChartsWorksheet = m_workbook.GetWorksheets().AddAfterOrBefore(m_dataWorksheet, true);
    if (!m_embeddedChartsWorksheet)
    {
        wxLogError(_("Failed to add a worksheet."));
        return false;
    }
    m_embeddedChartsWorksheet.SetName("Embedded charts");
    */
    m_testWorksheet = m_workbook.GetWorksheets()[1];
    //.AddAfterOrBefore(m_embeddedChartsWorksheet, true);
    if (!m_testWorksheet)
    {
        wxLogError(_("Failed to add a worksheet."));
        return false;
    }
    m_testWorksheet.SetName("test");

    wxExcelRange range = m_testWorksheet.GetRange("A1:V1");
    if (!AddTest(range))
        return false;
    /*
    m_testChartWorksheet = m_workbook.GetWorksheets().AddAfterOrBefore(m_testWorksheet, true);
    if (!m_testChartWorksheet)
    {
        wxLogError(_("Failed to add a worksheet."));
        return false;
    }
    m_testChartWorksheet.SetName("test chart");
    */

    return true;
}

bool ChartSampleA::Init2()
{
    m_app = wxExcelApplication::CreateInstance();
    if (!m_app)
    {
        wxLogError(_("Failed to create an instance of MS Excel application."));
        return false;
    }

    if (!m_app.IsVersionAtLeast_(wxExcelApplication::evExcel2007))
    {
        wxMessageBox(_("This sample requires Microsoft Excel 2007 or newer."), "Information");
        m_app.Quit();
        return false;
    }

    m_app.SetVisible(true);
    m_app.SetDisplayAlerts(false);

    m_workbook2 = m_app.GetWorkbooks().Add();
    if (!m_workbook2)
    {
        wxLogError(_("Failed to create a new workbook."));
        return false;
    }
    m_workbook2.SetAutomationLCID_(wxExcelObject::lcidEnglishUS);


    m_logWorksheet = m_workbook2.GetWorksheets()[1];

    if (!m_logWorksheet)
    {
        wxLogError(_("Failed to add a worksheet."));
        return false;
    }
    m_logWorksheet.SetName("REPAIR LOG");

    wxExcelRange range = m_logWorksheet.GetRange("A1:X1");
    if (!WriteLogData(range))
        return false;


    return true;
}

bool ChartSampleA::Init3()
{
    m_app = wxExcelApplication::CreateInstance();
    if (!m_app)
    {
        wxLogError(_("Failed to create an instance of MS Excel application."));
        return false;
    }

    if (!m_app.IsVersionAtLeast_(wxExcelApplication::evExcel2007))
    {
        wxMessageBox(_("This sample requires Microsoft Excel 2007 or newer."), "Information");
        m_app.Quit();
        return false;
    }

    m_app.SetVisible(true);
    m_app.SetDisplayAlerts(false);

    m_workbook3 = m_app.GetWorkbooks().Add();
    if (!m_workbook3)
    {
        wxLogError(_("Failed to create a new workbook."));
        return false;
    }
    m_workbook3.SetAutomationLCID_(wxExcelObject::lcidEnglishUS);


    m_fdaWorksheet = m_workbook3.GetWorksheets()[1];

    if (!m_fdaWorksheet)
    {
        wxLogError(_("Failed to add a worksheet."));
        return false;
    }
    m_fdaWorksheet.SetName("FDA Spreadsheet");

    wxExcelRange range = m_fdaWorksheet.GetRange("A1:E1");
    if (!WriteFdaData(range))
        return false;


    return true;
}


bool ChartSampleA::WriteData(wxExcelRange& range)
{


    wxVariant variant;

    wxString choice = "Sensors";
    wxString source = choice;
    wxString symbol;
    int hC1, hC2, hC3;
    int cC1, cC2, cC3;


    if (choice == "Sensors")
    {
        testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");
        symbol = "S";
        hC1 = 137;
        hC2 = 1;
        hC3 = 1;
        cC1 = 255;
        cC2 = 51;
        cC3 = 51;
    }

    else if (choice == "Analog")
    {
        testDBName = wxGetCwd() + wxT("//AnalogDatabase.db");
        symbol = "A";
        hC1, hC2, hC3 = 1, 48, 137;
        cC1, cC2, cC3 = 102, 178, 255;
    }

    else if (choice == "Nervo-Scope")
    {
        testDBName = wxGetCwd() + wxT("//nervoDatabase.db");
        symbol = "N";
        hC1, hC2, hC3 = 1, 48, 137;
        cC1, cC2, cC3 = 102, 178, 255;
    }
    else if (choice == "Digital")
    {
        testDBName = wxGetCwd() + wxT("//DigitalDatabase.db");
        symbol = "D";
        hC1 = 1;
        hC2 = 48;
        hC3 = 137;
        cC1 = 102;
        cC2 = 176;
        cC3 = 255;
    }
    else if (choice == "Metrology")
    {
        testDBName = wxGetCwd() + wxT("//CalibratorDatabase.db");
        symbol = "M";
        hC1, hC2, hC3 = 1, 48, 137;
        cC1, cC2, cC3 = 102, 178, 255;
    }

    else if (choice == "Misc.")
    {
        testDBName = wxGetCwd() + wxT("//MiscDatabase.db");
        symbol = "MSC";
        hC1, hC2, hC3 = 1, 48, 137;
        cC1, cC2, cC3 = 102, 178, 255;
    }

    // write sheet headers
    variant.ClearList();

    variant.Append("Date");
    variant.Append("Received");
    variant.Append("Updated");
    variant.Append("Shipped");

    // set cell values
    range.SetValue(variant);

    // set headers to bold
    range.GetFont().SetBold(true);
    // center headers
    range.SetHorizontalAlignment(xlCenter);
    wxExcelFont font = range.GetFont();
    font.SetSize(font.GetSize() * 1.3); // 150% of default size
    range.GetInterior().SetColor(wxColor(hC1, hC2, hC3));
    font.SetColor(wxColor(250, 250, 250));

    //db = new wxSQLite3Database();

    //db->Open(testDBName);

    //db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CustomerName' TEXT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorType' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'AltPhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT);");

    //db->Close();

    //db->Open(testDBName);

    //wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT DateReceived, count(*) as c FROM nodeData GROUP BY DateReceived ORDER BY DateReceived ASC;");
    //wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT DateSent, count(*) as c FROM nodeData GROUP BY DateSent ORDER BY DateSent ASC;");
    //wxSQLite3ResultSet Res3 = db->ExecuteQuery("SELECT DateReceived FROM nodeData ORDER BY DateReceived ASC UNION SELECT DateSent FROM nodeData ORDER BY DateSent ASC;");
    //wxSQLite3ResultSet Res4 = db->ExecuteQuery("SELECT DateSent, count(*) as c FROM nodeData WHERE Status = 'Shipped' GROUP BY DateSent ORDER BY DateSent ASC;");



    //db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'inNOut' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'InDate' TEXT, 'InCount' TEXT, 'UpdateDate' TEXT, 'UpdateCount' TEXT , 'DateRange' TEXT, 'OutDate' TEXT, 'OutCount' TEXT );");

    //db->ExecuteUpdate("INSERT INTO inNOut DEFAULT VALUES;");

    //db->ExecuteUpdate("INSERT INTO inNOut (DateRange) SELECT DateReceived FROM nodeData ORDER BY DateReceived ASC UNION SELECT DateSent FROM nodeData ORDER BY DateSent ASC");



    //db->ExecuteUpdate(wxString::Format(_("INSERT INTO inNOut (InDate,InCount,UpdateDate,UpdateCount,DateRange,OutDate,OutCount) VALUES ('%s','%s','%s','%s','%s','%s','%s')"), nrpCustomer, nrpCompany, nrpContact, nrpType, nrpSerial, nrpLastUpdate, nrpDateRec));
    //db->Close();

    //while (Res.NextRow())
    //{



    //}



    //int count = 1;
    //while (Res.NextRow())
    //{
    //	range = range.GetOffset(1);

    //	if (count % 2 == 0)

    //		range.GetInterior().SetColor(wxColor(225, 225, 225));
    ///	else
    //		range.GetInterior().SetColor(wxColor(cC1, cC2, cC3));
//
    ///	range.SetHorizontalAlignment(xlCenter);
//
    //	variant.ClearList();

    //	variant.Append(Res.GetAsString(0));
    //	variant.Append(Res.GetAsString(1));

    //	range.SetValue(variant);

    //	count++;
//	}

//	Res.Finalize();
//	db->Close();

    // finally, fit the columns to the content
    m_dataWorksheet.GetUsedRange().GetEntireColumn().AutoFit();

    range = m_dataWorksheet.GetUsedRange();
    // add medium-weight borders on the outside and thin-weight on the inside
    wxExcelBorders borders = range.GetBorders();
    borders[xlEdgeTop].SetWeight(xlMedium);
    borders[xlEdgeLeft].SetWeight(xlMedium);
    borders[xlEdgeBottom].SetWeight(xlMedium);
    borders[xlEdgeRight].SetWeight(xlMedium);
    borders[xlInsideHorizontal].SetWeight(xlThin);
    borders[xlInsideVertical].SetWeight(xlThin);



    return range;
}

bool ChartSampleA::WriteLogData(wxExcelRange& range)
{

    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT UpdateID FROM LogSelection;");

    source = Res.GetAsString(0);

    Res.Finalize();
    db->ExecuteQuery("PRAGMA foreign_keys = OFF;");
    db->ExecuteUpdate("DROP TABLE LogSelection;");
    db->ExecuteQuery("PRAGMA foreign_keys = ON;");
    db->Close();


    if (source == "Sensors")
    {

        sourceDB = "Sensors";
        symbol = "S";
        logSource = "sensor";
        hC1 = 191;
        hC2 = 0;
        hC3 = 55;
        cC1 = 255;
        cC2 = 115;
        cC3 = 115;
        LogFormat(range);


    }

    else if (source == "Analog")
    {

        sourceDB = "Analog";
        symbol = "A";
        logSource = "analog";
        hC1 = 4;
        hC2 = 108;
        hC3 = 2;
        cC1 = 157;
        cC2 = 255;
        cC3 = 155;
        LogFormat(range);
    }

    else if (source == "Nervo-Scope")
    {

        sourceDB = "Nervo-Scope";
        symbol = "N";
        logSource = "nervo";
        hC1 = 240;
        hC2 = 104;
        hC3 = 9;
        cC1 = 255;
        cC2 = 178;
        cC3 = 125;
        LogFormat(range);

    }
    else if (source == "Digital")
    {

        sourceDB = "Digital";
        symbol = "D";
        logSource = "digital";
        hC1 = 1;
        hC2 = 48;
        hC3 = 137;
        cC1 = 102;
        cC2 = 176;
        cC3 = 255;
        LogFormat(range);

    }
    else if (source == "Metrology")
    {

        sourceDB = "Metrology";
        symbol = "M";
        logSource = "metrology";
        hC1 = 93;
        hC2 = 0;
        hC3 = 162;
        cC1 = 221;
        cC2 = 177;
        cC3 = 240;
        LogFormat(range);

    }

    else if (source == "Misc.")
    {

        sourceDB = "Misc.";
        symbol = "MSC";
        logSource = "misc";
        hC1 = 47;
        hC2 = 151;
        hC3 = 137;
        cC1 = 182;
        cC2 = 255;
        cC3 = 245;
        LogFormat(range);

    }

    else if (source == "All")
    {


        sourceDB = "Nervo-Scope";
        symbol = "N";
        logSource = "nervo";
        hC1 = 240;
        hC2 = 104;
        hC3 = 9;
        cC1 = 255;
        cC2 = 178;
        cC3 = 125;
        LogFormat(range);
        range = range.GetOffset(5);


        sourceDB = "Analog";
        symbol = "A";
        logSource = "analog";
        hC1 = 4;
        hC2 = 108;
        hC3 = 2;
        cC1 = 157;
        cC2 = 255;
        cC3 = 155;
        LogFormat(range);
        range = range.GetOffset(5);


        sourceDB = "Digital";
        symbol = "D";
        logSource = "digital";
        hC1 = 1;
        hC2 = 48;
        hC3 = 137;
        cC1 = 102;
        cC2 = 176;
        cC3 = 255;
        LogFormat(range);
        range = range.GetOffset(5);


        sourceDB = "Sensors";
        symbol = "S";
        logSource = "sensor";
        hC1 = 191;
        hC2 = 0;
        hC3 = 55;
        cC1 = 255;
        cC2 = 115;
        cC3 = 115;
        LogFormat(range);
        range = range.GetOffset(5);


        sourceDB = "Metrology";
        symbol = "M";
        logSource = "metrology";
        hC1 = 93;
        hC2 = 0;
        hC3 = 162;
        cC1 = 221;
        cC2 = 177;
        cC3 = 240;
        LogFormat(range);
        range = range.GetOffset(5);


        sourceDB = "Misc.";
        symbol = "MSC";
        logSource = "misc";
        hC1 = 47;
        hC2 = 151;
        hC3 = 137;
        cC1 = 182;
        cC2 = 255;
        cC3 = 245;
        LogFormat(range);

    }

    // finally, fit the columns to the content
    m_logWorksheet.GetUsedRange().GetEntireColumn().AutoFit();

    range = m_logWorksheet.GetUsedRange();
    // add medium-weight borders on the outside and thin-weight on the inside
    wxExcelBorders borders = range.GetBorders();
    borders[xlEdgeTop].SetWeight(xlMedium);
    borders[xlEdgeLeft].SetWeight(xlMedium);
    borders[xlEdgeBottom].SetWeight(xlMedium);
    borders[xlEdgeRight].SetWeight(xlMedium);
    borders[xlInsideHorizontal].SetWeight(xlThin);
    borders[xlInsideVertical].SetWeight(xlThin);

    return range;
}

bool ChartSampleA::WriteFdaData(wxExcelRange& range)
{
    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT UpdateID FROM LogSelection;");

    source = Res.GetAsString(0);

    Res.Finalize();
    db->ExecuteQuery("PRAGMA foreign_keys = OFF;");
    db->ExecuteUpdate("DROP TABLE LogSelection;");
    db->ExecuteQuery("PRAGMA foreign_keys = ON;");
    db->Close();


    hC1 = 240;
    hC2 = 104;
    hC3 = 9;
    cC1 = 255;
    cC2 = 178;
    cC3 = 125;
    FdaFormat(range);


    // finally, fit the columns to the content
    m_fdaWorksheet.GetUsedRange().GetEntireColumn().AutoFit();

    range = m_fdaWorksheet.GetUsedRange();
    // add medium-weight borders on the outside and thin-weight on the inside
    wxExcelBorders borders = range.GetBorders();
    borders[xlEdgeTop].SetWeight(xlMedium);
    borders[xlEdgeLeft].SetWeight(xlMedium);
    borders[xlEdgeBottom].SetWeight(xlMedium);
    borders[xlEdgeRight].SetWeight(xlMedium);
    borders[xlInsideHorizontal].SetWeight(xlThin);
    borders[xlInsideVertical].SetWeight(xlThin);

    return range;
}

bool ChartSampleA::AddTest(wxExcelRange& range)
{


    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT UpdateID FROM SpreadsheetSelection;");

    source = Res.GetAsString(0);


    Res.Finalize();

    db->ExecuteQuery("PRAGMA foreign_keys = OFF;");
    db->ExecuteUpdate("DROP TABLE SpreadsheetSelection;");
    db->ExecuteQuery("PRAGMA foreign_keys = ON;");

    db->Close();





    if (source == "Sensors")
    {
        testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");
        sourceDB = "Sensors";
        symbol = "S";
        hC1 = 191;
        hC2 = 0;
        hC3 = 55;
        cC1 = 255;
        cC2 = 115;
        cC3 = 115;

        ChartFormat(range);
    }

    else if (source == "Analog")
    {
        testDBName = wxGetCwd() + wxT("//AnalogDatabase.db");
        sourceDB = "Analog";
        symbol = "A";
        hC1 = 4;
        hC2 = 108;
        hC3 = 2;
        cC1 = 157;
        cC2 = 255;
        cC3 = 155;

        ChartFormat(range);
    }

    else if (source == "Nervo-Scope")
    {
        testDBName = wxGetCwd() + wxT("//nervoDatabase.db");
        sourceDB = "Nervo-Scope";
        symbol = "N";
        hC1 = 240;
        hC2 = 104;
        hC3 = 9;
        cC1 = 255;
        cC2 = 178;
        cC3 = 125;

        ChartFormat(range);
    }
    else if (source == "Digital")
    {
        testDBName = wxGetCwd() + wxT("//DigitalDatabase.db");
        sourceDB = "Digital";
        symbol = "D";
        hC1 = 1;
        hC2 = 48;
        hC3 = 137;
        cC1 = 102;
        cC2 = 176;
        cC3 = 255;

        ChartFormat(range);
    }
    else if (source == "Metrology")
    {
        testDBName = wxGetCwd() + wxT("//CalibratorDatabase.db");
        sourceDB = "Metrology";
        symbol = "M";
        hC1 = 93;
        hC2 = 0;
        hC3 = 162;
        cC1 = 221;
        cC2 = 177;
        cC3 = 240;

        ChartFormat(range);
    }

    else if (source == "Misc.")
    {
        testDBName = wxGetCwd() + wxT("//MiscDatabase.db");
        sourceDB = "Misc.";
        symbol = "MSC";
        hC1 = 47;
        hC2 = 151;
        hC3 = 137;
        cC1 = 182;
        cC2 = 255;
        cC3 = 245;

        ChartFormat(range);
    }

    else if (source == "All")
    {

        testDBName = wxGetCwd() + wxT("//nervoDatabase.db");
        sourceDB = "Nervo-Scope";
        symbol = "N";
        hC1 = 240;
        hC2 = 104;
        hC3 = 9;
        cC1 = 255;
        cC2 = 178;
        cC3 = 125;
        ChartFormat(range);
        range = range.GetOffset(5);

        testDBName = wxGetCwd() + wxT("//AnalogDatabase.db");
        sourceDB = "Analog";
        symbol = "A";
        hC1 = 4;
        hC2 = 108;
        hC3 = 2;
        cC1 = 157;
        cC2 = 255;
        cC3 = 155;
        ChartFormat(range);
        range = range.GetOffset(5);

        testDBName = wxGetCwd() + wxT("//DigitalDatabase.db");
        sourceDB = "Digital";
        symbol = "D";
        hC1 = 1;
        hC2 = 48;
        hC3 = 137;
        cC1 = 102;
        cC2 = 176;
        cC3 = 255;
        ChartFormat(range);
        range = range.GetOffset(5);

        testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");
        sourceDB = "Sensors";
        symbol = "S";
        hC1 = 191;
        hC2 = 0;
        hC3 = 55;
        cC1 = 255;
        cC2 = 115;
        cC3 = 115;
        ChartFormat(range);
        range = range.GetOffset(5);

        testDBName = wxGetCwd() + wxT("//CalibratorDatabase.db");
        sourceDB = "Metrology";
        symbol = "M";
        hC1 = 93;
        hC2 = 0;
        hC3 = 162;
        cC1 = 221;
        cC2 = 177;
        cC3 = 240;
        ChartFormat(range);
        range = range.GetOffset(5);

        testDBName = wxGetCwd() + wxT("//MiscDatabase.db");
        sourceDB = "Misc.";
        symbol = "MSC";
        hC1 = 47;
        hC2 = 151;
        hC3 = 137;
        cC1 = 182;
        cC2 = 255;
        cC3 = 245;
        ChartFormat(range);

    }

    // finally, fit the columns to the content
    m_testWorksheet.GetUsedRange().GetEntireColumn().AutoFit();

    range = m_testWorksheet.GetUsedRange();
    // add medium-weight borders on the outside and thin-weight on the inside
    wxExcelBorders borders = range.GetBorders();
    borders[xlEdgeTop].SetWeight(xlMedium);
    borders[xlEdgeLeft].SetWeight(xlMedium);
    borders[xlEdgeBottom].SetWeight(xlMedium);
    borders[xlEdgeRight].SetWeight(xlMedium);
    borders[xlInsideHorizontal].SetWeight(xlThin);
    borders[xlInsideVertical].SetWeight(xlThin);

    return range;
}


void ChartSampleA::ChartFormat(wxExcelRange& range)
{
    // write sheet headers
    variant.ClearList();

    variant.Append("ID#");
    variant.Append("Company Name");
    variant.Append("Repair Number");
    variant.Append("Serial Number");
    variant.Append("Last Update");
    variant.Append("Date Received");
    variant.Append("Contact");
    variant.Append("Address");
    variant.Append("Phone Number");
    variant.Append("Email Address");
    variant.Append("Model Number");
    variant.Append("Department");
    variant.Append("Technician");
    variant.Append("Status");
    variant.Append("Case");
    variant.Append("Quantity");
    variant.Append("Discrepancy");
    variant.Append("Corrective Action");
    variant.Append("Database Source");
    variant.Append("Group");
    variant.Append("WhatWeFound");
    variant.Append("Level");

    // set cell values
    range.SetValue(variant);

    // set headers to bold
    range.GetFont().SetBold(true);
    // center headers
    range.SetHorizontalAlignment(xlCenter);
    wxExcelFont font = range.GetFont();
    font.SetSize(font.GetSize() * 1.3); // 150% of default size
    range.GetInterior().SetColor(wxColor(hC1, hC2, hC3));
    font.SetColor(wxColor(250, 250, 250));

    db = new wxSQLite3Database();

    db->Open(testDBName);

    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

    db->Close();

    db->Open(testDBName);

    wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT Id, CompanyName, RepairNumber, SensorSerialNumber, DateSent, DateReceived, ContactName, Address, PhoneNumber, EmailAddress, ModelNumber, Department, Technician, Status, CaseYN, Quantity, Discrepancy, CorrectiveAction, GroupNumber, WhatWeFound, Level FROM nodeData WHERE Status IN('Shipped') ORDER BY rowid ASC;");

    int count = 1;
    while (Res2.NextRow())
    {
        range = range.GetOffset(1);

        if (count % 2 == 0)

            range.GetInterior().SetColor(wxColor(225, 225, 225));
        else
            range.GetInterior().SetColor(wxColor(cC1, cC2, cC3));

        range.SetHorizontalAlignment(xlCenter);

        variant.ClearList();

        variant.Append(symbol + Res2.GetAsString(0));
        variant.Append(Res2.GetAsString(1));
        variant.Append(Res2.GetAsString(2));
        variant.Append(Res2.GetAsString(3));
        variant.Append(Res2.GetAsString(4));
        variant.Append(Res2.GetAsString(5));
        variant.Append(Res2.GetAsString(6));
        variant.Append(Res2.GetAsString(7));
        variant.Append(Res2.GetAsString(8));
        variant.Append(Res2.GetAsString(9));
        variant.Append(Res2.GetAsString(10));
        variant.Append(Res2.GetAsString(11));
        variant.Append(Res2.GetAsString(12));
        variant.Append(Res2.GetAsString(13));
        variant.Append(Res2.GetAsString(14));
        variant.Append(Res2.GetAsString(15));
        variant.Append(Res2.GetAsString(16));
        variant.Append(Res2.GetAsString(17));
        variant.Append(sourceDB);
        variant.Append(Res2.GetAsString(18));
        variant.Append(Res2.GetAsString(19));
        variant.Append(Res2.GetAsString(20));


        range.SetValue(variant);

        count++;

    }

    Res2.Finalize();
    db->Close();

}


void ChartSampleA::LogFormat(wxExcelRange& range)
{
    // write sheet headers
    variant.ClearList();

    variant.Append("ID#");
    variant.Append("Company Name");
    variant.Append("Repair Number");
    variant.Append("Serial Number");
    variant.Append("Last Update");
    variant.Append("Date Received");
    variant.Append("Contact");
    variant.Append("Address");
    variant.Append("Phone Number");
    variant.Append("Email Address");
    variant.Append("Model Number");
    variant.Append("Department");
    variant.Append("Technician");
    variant.Append("Status");
    variant.Append("Case");
    variant.Append("Quantity");
    variant.Append("Discrepancy");
    variant.Append("Corrective Action");
    variant.Append("Database Source");
    variant.Append("History");
    variant.Append("Group");
    variant.Append("Chronology");
    variant.Append("What We Found");
    variant.Append("Level");


    // set cell values
    range.SetValue(variant);

    // set headers to bold
    range.GetFont().SetBold(true);
    // center headers
    range.SetHorizontalAlignment(xlCenter);
    wxExcelFont font = range.GetFont();
    font.SetSize(font.GetSize() * 1.3); // 150% of default size
    range.GetInterior().SetColor(wxColor(hC1, hC2, hC3));
    font.SetColor(wxColor(250, 250, 250));

    db = new wxSQLite3Database();
    testDBName = wxGetCwd() + wxT("//LogDatabase.db");
    db->Open(testDBName);
    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");
    db->Close();

    db->Open(testDBName);
    wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT Id, CompanyName, RepairNumber, SensorSerialNumber, DateSent, DateReceived, ContactName, Address, PhoneNumber, EmailAddress, ModelNumber, Department, Technician, Status, CaseYN, Quantity, Discrepancy, CorrectiveAction, History, GroupNumber, Chronology, WhatWeFound, Level FROM nodeData WHERE Source = '" + logSource + "' ORDER BY rowid ASC;");

    int count = 1;
    while (Res2.NextRow())
    {
        range = range.GetOffset(1);

        if (count % 2 == 0)

            range.GetInterior().SetColor(wxColor(225, 225, 225));
        else
            range.GetInterior().SetColor(wxColor(cC1, cC2, cC3));

        range.SetHorizontalAlignment(xlCenter);

        variant.ClearList();

        variant.Append(symbol + Res2.GetAsString(0));
        variant.Append(Res2.GetAsString(1));
        variant.Append(Res2.GetAsString(2));
        variant.Append(Res2.GetAsString(3));
        variant.Append(Res2.GetAsString(4));
        variant.Append(Res2.GetAsString(5));
        variant.Append(Res2.GetAsString(6));
        variant.Append(Res2.GetAsString(7));
        variant.Append(Res2.GetAsString(8));
        variant.Append(Res2.GetAsString(9));
        variant.Append(Res2.GetAsString(10));
        variant.Append(Res2.GetAsString(11));
        variant.Append(Res2.GetAsString(12));
        variant.Append(Res2.GetAsString(13));
        variant.Append(Res2.GetAsString(14));
        variant.Append(Res2.GetAsString(15));
        variant.Append(Res2.GetAsString(16));
        variant.Append(Res2.GetAsString(17));
        variant.Append(sourceDB);
        variant.Append(Res2.GetAsString(18));
        variant.Append(Res2.GetAsString(19));
        variant.Append(Res2.GetAsString(20));

        variant.Append(Res2.GetAsString(21));
        variant.Append(Res2.GetAsString(22));


        range.SetValue(variant);

        count++;

    }

    Res2.Finalize();
    db->Close();

}



void ChartSampleA::FdaFormat(wxExcelRange& range)
{
    // write sheet headers
    variant.ClearList();

    variant.Append("Repair Number");
    variant.Append("Date Received");
    variant.Append("Doctor's Name");
    variant.Append("Model Number");
    variant.Append("Serial Number");


    // set cell values
    range.SetValue(variant);

    // set headers to bold
    range.GetFont().SetBold(true);
    // center headers
    range.SetHorizontalAlignment(xlCenter);
    wxExcelFont font = range.GetFont();
    font.SetSize(font.GetSize() * 1.3); // 150% of default size
    range.GetInterior().SetColor(wxColor(hC1, hC2, hC3));
    font.SetColor(wxColor(250, 250, 250));

    db = new wxSQLite3Database();

    db->Open("nervoDatabase.db");

    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

    db->Close();

    db->Open("nervoDatabase.db");

    wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT RepairNumber,DateReceived,ContactName,ModelNumber,SensorSerialNumber FROM nodeData WHERE ModelNumber IN('ETS-9','ETS-9A' ) AND Status = 'Shipped' ORDER BY rowid ASC;");

    int count = 1;
    while (Res2.NextRow())
    {
        range = range.GetOffset(1);

        if (count % 2 == 0)

            range.GetInterior().SetColor(wxColor(225, 225, 225));
        else
            range.GetInterior().SetColor(wxColor(cC1, cC2, cC3));

        range.SetHorizontalAlignment(xlCenter);

        variant.ClearList();

        variant.Append(Res2.GetAsString(0));
        variant.Append(Res2.GetAsString(1));
        variant.Append(Res2.GetAsString(2));
        variant.Append(Res2.GetAsString(3));
        variant.Append(Res2.GetAsString(4));

        range.SetValue(variant);

        count++;

    }

    Res2.Finalize();
    db->Close();

}

using namespace wxAutoExcel;




void ArchivePanel::onClickExcelOutput(wxCommandEvent& event)
{

    excelDBChoice = odcdept->GetValue();


    if (excelDBChoice == "DATABASE")
    {
        wxString msg = _T("ERROR: No Input Detected For 'SPREADSHEET OUTPUT' Please Try again");
        wxString info = _T("Spreadsheet ERROR");
        wxMessageBox(msg,
            info,
            wxOK | wxICON_WARNING,
            this);
    }

    else
    {

        db = new wxSQLite3Database();

        testDBName = wxGetCwd() + wxT("//tempData.db");

        db->Open(testDBName);

        wxSQLite3ResultSet Res = db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'SpreadsheetSelection' ('UpdateID' TEXT);");

        db->ExecuteUpdate(wxString::Format(_("INSERT INTO SpreadsheetSelection (UpdateID) VALUES ('%s')"), excelDBChoice));

        Res.Finalize();

        db->Close();



        ChartSample sample;

        if (!sample.Init())
            return;

        //sample.AddSparkline();
        //sample.AddChartStacked();
        //sample.AddChartClusteredWithLine();
        //sample.AddChart3D();
        //sample.AddTestChart();


    }

}

void ArchivePanel::onClickLogReport(wxCommandEvent& event)
{

    logDBChoice = odclog->GetValue();


    if (logDBChoice == "LOG DB")
    {
        wxString msg = _T("ERROR: No Input Detected For 'LOG OUTPUT' Please Try again");
        wxString info = _T("Log ERROR");
        wxMessageBox(msg,
            info,
            wxOK | wxICON_WARNING,
            this);
    }

    else
    {

        db = new wxSQLite3Database();

        testDBName = wxGetCwd() + wxT("//tempData.db");

        db->Open(testDBName);

        wxSQLite3ResultSet Res = db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'LogSelection' ('UpdateID' TEXT);");

        db->ExecuteUpdate(wxString::Format(_("INSERT INTO LogSelection (UpdateID) VALUES ('%s')"), logDBChoice));

        Res.Finalize();

        db->Close();



        ChartSample logSample;

        if (!logSample.Init2())
            return;

        //sample.AddSparkline();
        //sample.AddChartStacked();
        //sample.AddChartClusteredWithLine();
        //sample.AddChart3D();
        //sample.AddTestChart();


    }


}

void ArchivePanel::onClickFdaSpreadsheet(wxCommandEvent& event)
{

    excelDBChoice == "Nervo-Scope";

    logDBChoice = odclog->GetValue();


    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res = db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'LogSelection' ('UpdateID' TEXT);");

    db->ExecuteUpdate(wxString::Format(_("INSERT INTO LogSelection (UpdateID) VALUES ('%s')"), logDBChoice));

    Res.Finalize();

    db->Close();



    ChartSample logSample;

    if (!logSample.Init3())
        return;

    //sample.AddSparkline();
    //sample.AddChartStacked();
    //sample.AddChartClusteredWithLine();
    //sample.AddChart3D();
    //sample.AddTestChart();






}

void ArchivePanel::OnCellRightClick(wxGridEvent& ev)
{

    wxString copyId = grid->GetCellValue(ev.GetRow(), 0);
    wxString copyContact = grid->GetCellValue(ev.GetRow(), 1);
    wxString copyCompany = grid->GetCellValue(ev.GetRow(), 2);
    wxString copyRepairNumber = grid->GetCellValue(ev.GetRow(), 3);
    wxString copyModelNumber = grid->GetCellValue(ev.GetRow(), 4);
    wxString copyTechnician  = grid->GetCellValue(ev.GetRow(), 5);
    wxString copySerialNumber = grid->GetCellValue(ev.GetRow(), 6);
    wxString copyLastUpdate = grid->GetCellValue(ev.GetRow(), 7);
    wxString copyDateReceived = grid->GetCellValue(ev.GetRow(), 8);
    

    wxString copyAll = copyId + " , " + copyContact + " , " + copyCompany + " , " + copyRepairNumber + " , " + copyModelNumber + " , " + copyTechnician + " , " + copySerialNumber + " , " + copyLastUpdate + " , " + copyDateReceived;

    if (wxTheClipboard->Open())
    {
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData(new wxTextDataObject(copyAll));
        wxTheClipboard->Close();
    }


}

void ArchivePanel::OnCellLeftClick(wxGridEvent& ev)
{

    wxString clickGet = grid->GetCellValue(ev.GetRow(), 0);


    if (cycles >> 0) {


        for (int i = 0; i < cellCount; i++) {
            cellValue = grid->GetCellValue(i, 0);

            if (getValueS == cellValue) {

                grid->SetCellBackgroundColour(i, 0, wxColour(0, 25, 32));
                grid->SetCellTextColour(i, 0, wxColour(0, 173, 234));

                for (int j = 1; j < 8; j++) {

                    grid->SetCellBackgroundColour(i, j, wxColour(33, 33, 57));
                    grid->SetCellTextColour(i, j, wxColour(0, 255, 255));

                }

            }

        }



    }



    wxString logRN;

    getValueS = clickGet;

    getValueI = wxAtoi(getValueS);

    cellCount = grid->GetNumberRows();

    testDBName = wxGetCwd() + wxT("//logDatabase.db");

    db->Open(testDBName);

    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT Id,ContactName,Address,PhoneNumber,EmailAddress,ModelNumber,SensorSerialNumber,CaseYN,Quantity FROM nodeData WHERE Id ='" + getValueS + "';");
    wxSQLite3ResultSet Res3 = db->ExecuteQuery("SELECT WhatWeFound FROM nodeData WHERE Id ='" + getValueS + "';");
    wxSQLite3ResultSet Res4 = db->ExecuteQuery("SELECT CorrectiveAction FROM nodeData WHERE Id ='" + getValueS + "';");

    while (Res.NextRow())
    {

        for (int i = 0; i < 9; i++) {

            extraDataGrid->SetCellValue(i, 1, wxString::Format(_("%s"), Res.GetAsString(i)));


        }

    }

    while (Res3.NextRow())
    {



        OfficeProblemGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res3.GetAsString(0)));




    }

    while (Res4.NextRow())
    {

        OfficeCorrectionGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res4.GetAsString(0)));

    }



    Res.Finalize();

    Res3.Finalize();
    Res4.Finalize();

    db->Close();

    for (int i = 0; i < cellCount; i++) {
        cellValue = grid->GetCellValue(i, 0);

        if (getValueS == cellValue) {

            grid->SetCellBackgroundColour(i, 0, wxColour(0, 173, 234));
            grid->SetCellTextColour(i, 0, wxColour(0, 250, 250));

            for (int j = 1; j < 8; j++) {

                grid->SetCellBackgroundColour(i, j, wxColour(228, 228, 240));
                grid->SetCellTextColour(i, j, wxColour(0, 0, 0));

            }

        }

    }

    grid->Refresh();

    cycles++;

}