#include "sensordb.h"
#include <wx/clipbrd.h>

using namespace std;


const long SensorPanel::idButtonNewRepair = ::wxNewId();   //New Repair Button
const long SensorPanel::idButtonRefreshGrid = ::wxNewId();   //Refresh Button
const long SensorPanel::idButtonGetInfo = ::wxNewId();   //Get Button
const long SensorPanel::idButtonSearch = ::wxNewId();   //Search Button
const long SensorPanel::idButtonUpdateRepair = ::wxNewId();   //Update Repair Button
const long SensorPanel::idButtonResetGrid = ::wxNewId();   //Reset Button
const long SensorPanel::idButtonSortGrid = ::wxNewId();   //Sort Button

const long newRepairDialog::idButtonCreateRepair = ::wxNewId();   //Create Button
const long newRepairDialog::idButtonCancelRepair = ::wxNewId();   //Cancel Button
const long newRepairDialog::idButtonRepairTemplate = ::wxNewId();   //Cancel Button

const long updateRepairDialog::idButtonDoRepairUpdate = ::wxNewId();   //Create Button
const long updateRepairDialog::idButtonCancelRepairUpdate = ::wxNewId();   //Cancel Button
const long updateRepairDialog::idButtonAddNoteTC = ::wxNewId();   //Cancel Button
const long updateRepairDialog::idButtonAddNoteL = ::wxNewId();   //Cancel Button
const long updateRepairDialog::idButtonAddNoteT = ::wxNewId();   //Cancel Button
const long updateRepairDialog::idButtonAddNoteLVL = ::wxNewId();   //Cancel Button


BEGIN_EVENT_TABLE(SensorPanel, wxPanel)

EVT_BUTTON(idButtonNewRepair, SensorPanel::onClickNewRepair) //Login Button
EVT_BUTTON(idButtonRefreshGrid, SensorPanel::onClickRefresh) //Login Button
EVT_BUTTON(idButtonGetInfo, SensorPanel::onClickGet) //New User Button
EVT_BUTTON(idButtonSearch, SensorPanel::onClickSearch) //Login Button
EVT_BUTTON(idButtonUpdateRepair, SensorPanel::onClickUpdateRepair) //Login Button
EVT_BUTTON(idButtonResetGrid, SensorPanel::onClickReset) //Login Button
EVT_BUTTON(idButtonSortGrid, SensorPanel::onClickSort) //Login Button

EVT_TIMER(TIMER_ID, SensorPanel::OnTimer)

EVT_GRID_CELL_LEFT_CLICK(SensorPanel::OnCellLeftClick)
EVT_GRID_CELL_RIGHT_CLICK(SensorPanel::OnCellRightClick)
EVT_GRID_CELL_LEFT_DCLICK(SensorPanel::OnCellLeftDoubleClick)

END_EVENT_TABLE()



BEGIN_EVENT_TABLE(newRepairDialog, wxDialog)

EVT_BUTTON(idButtonCreateRepair, newRepairDialog::onClickCreateRepair) //Login Button
EVT_BUTTON(idButtonCancelRepair, newRepairDialog::onClickCancelRepair)
EVT_BUTTON(idButtonRepairTemplate, newRepairDialog::onClickGetRepairTemplate)

END_EVENT_TABLE()



BEGIN_EVENT_TABLE(updateRepairDialog, wxDialog)

EVT_BUTTON(idButtonDoRepairUpdate, updateRepairDialog::onClickDoRepairUpdate) //Login Button
EVT_BUTTON(idButtonCancelRepairUpdate, updateRepairDialog::onClickCancelRepairUpdate)
EVT_BUTTON(idButtonAddNoteTC, updateRepairDialog::onClickAddNoteTC)
EVT_BUTTON(idButtonAddNoteL, updateRepairDialog::onClickAddNoteL)
EVT_BUTTON(idButtonAddNoteT, updateRepairDialog::onClickAddNoteT)
EVT_BUTTON(idButtonAddNoteLVL, updateRepairDialog::onClickAddLVL)

END_EVENT_TABLE()


BackgroundPanel::BackgroundPanel(wxPanel* parent)
    : wxPanel(parent, -1, wxDefaultPosition,
        wxSize(1207, 707))
{

    SGP = new SensorPanel(this);

}


BackgroundPanel::~BackgroundPanel() {}

SensorPanel::SensorPanel(wxPanel* parent)
    : wxPanel(parent, -1, wxDefaultPosition,
        wxSize(1207,707))
{
    ///PARENT PANEL

    panel = parent;

    wxPanel* panel = new wxPanel(this, wxID_ANY,
        wxPoint(-1, -1), wxSize(1207, 707), wxBORDER_RAISED);
    panel->SetBackgroundColour(wxColour(150, 150, 150));

    wxPanel* searchPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(3, 166), wxSize(224, 130), wxBORDER_RAISED);
    searchPanel->SetBackgroundColour(wxColor(33, 33, 57));

    wxPanel* searchTitlePanel = new wxPanel(searchPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(224, 28), wxBORDER_NONE);
    searchTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));


    wxStaticText* dataTitle = new wxStaticText(searchTitlePanel, wxID_ANY, ("Search Database"), wxPoint(35, 3), wxSize(-1, -1), wxTE_CENTRE);
    dataTitle->SetForegroundColour(wxColor(0, 188, 255));
    dataTitle->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* cpsl1 = new wxStaticLine(searchPanel, wxID_ANY, wxPoint(-1, 29),
        wxSize(224, 2));

      // Create common strings array

    m_fieldarray.Add("Company Name");
    m_fieldarray.Add("Repair Number");
    m_fieldarray.Add("Model Number");
    m_fieldarray.Add("Status");
    m_fieldarray.Add("Last Update");
    m_fieldarray.Add("Date Received");

    m_srchCtrl = new wxSearchCtrl(searchPanel, -1, wxEmptyString, wxPoint(5, 49),
        FromDIP(wxSize(87, -1)));

    
    odcSearchCategory = new wxOwnerDrawnComboBox(searchPanel, wxID_ANY, "CATEGORIES",
        wxPoint(97, 49), wxDefaultSize,
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
        wxBITMAP_TYPE_PNG), wxPoint(49, 82), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage searchButtonimgHover("searchButtonh.png");
    searchButton->SetBitmapHover(searchButtonimgHover);
    wxImage searchButtonimgPressed("searchButtonp.png");
    searchButton->SetBitmapPressed(searchButtonimgPressed);

    wxPanel* formPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(3, 299), wxSize(224, 126), wxBORDER_RAISED);
    formPanel->SetBackgroundColour(wxColour(33, 33, 57));

    wxPanel* formTitlePanel = new wxPanel(formPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(224, 28), wxBORDER_NONE);
    formTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* formTitle = new wxStaticText(formTitlePanel, wxID_ANY, ("Repair Forms"), wxPoint(50, 3), wxSize(-1, -1), wxTE_CENTRE);
    formTitle->SetForegroundColour(wxColor(0, 200, 255));
    formTitle->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* cpsl2 = new wxStaticLine(formPanel, wxID_ANY, wxPoint(-1, 29),
        wxSize(320,2));

    wxBitmapButton* newRepairButton = new wxBitmapButton(formPanel, idButtonNewRepair, wxBitmap(wxT("newRepair.png"),
        wxBITMAP_TYPE_PNG), wxPoint(56, 40), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage newRepairButtonimgHover("newRepairh.png");
    newRepairButton->SetBitmapHover(newRepairButtonimgHover);
    wxImage newRepairButtonimgPressed("newRepairp.png");
    newRepairButton->SetBitmapPressed(newRepairButtonimgPressed);



    updateEntry = new wxTextCtrl(formPanel, -1, wxT(""), wxPoint(7, 87),
        wxSize(63, 24));
    updateEntry->SetBackgroundColour(wxColour(228, 228, 240));
    updateEntry->SetFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));

    wxBitmapButton* updateRepairButton = new wxBitmapButton(formPanel, idButtonUpdateRepair, wxBitmap(wxT("updateRepair.png"),
        wxBITMAP_TYPE_PNG), wxPoint(82, 81), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage updateRepairButtonimgHover("updateRepairh.png");
    updateRepairButton->SetBitmapHover(updateRepairButtonimgHover);
    wxImage updateRepairButtonimgPressed("updateRepairp.png");
    updateRepairButton->SetBitmapPressed(updateRepairButtonimgPressed);

    wxPanel* controlPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(3, 428), wxSize(224, 132), wxBORDER_RAISED);
    controlPanel->SetBackgroundColour(wxColour(33, 33, 57));

    wxPanel* controlTitlePanel = new wxPanel(controlPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(224, 28), wxBORDER_NONE);
    controlTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));


    wxStaticText* controlTitle = new wxStaticText(controlTitlePanel, wxID_ANY, ("D.B. Controls"), wxPoint(55, 3), wxSize(-1, -1), wxTE_CENTRE);
    controlTitle->SetForegroundColour(wxColor(0, 188, 255));
    controlTitle->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* cpsl3 = new wxStaticLine(controlPanel, wxID_ANY, wxPoint(-1, 29),
        wxSize(224, 2));

    wxBitmapButton* RefreshButton = new wxBitmapButton(controlPanel, idButtonRefreshGrid, wxBitmap(wxT("refreshButton.png"),
        wxBITMAP_TYPE_PNG), wxPoint(25, 42), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage RefreshButtonimgHover("refreshButtonh.png");
    RefreshButton->SetBitmapHover(RefreshButtonimgHover);
    wxImage RefreshButtonimgPressed("refreshButtonp.png");
    RefreshButton->SetBitmapPressed(RefreshButtonimgPressed);

    wxBitmapButton* ResetButton = new wxBitmapButton(controlPanel, idButtonResetGrid, wxBitmap(wxT("resetButton.png"),
        wxBITMAP_TYPE_PNG), wxPoint(133, 42), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage ResetButtonimgHover("resetButtonh.png");
    ResetButton->SetBitmapHover(ResetButtonimgHover);
    wxImage ResetButtonimgPressed("resetButtonp.png");
    ResetButton->SetBitmapPressed(ResetButtonimgPressed);

    m_sortbyarray.Add("Oldest to Newest");
    m_sortbyarray.Add("Newest to Oldest");
    m_sortbyarray.Add("Company");
    m_sortbyarray.Add("Repair #");
    m_sortbyarray.Add("Model #");
    m_sortbyarray.Add("Status");
    m_sortbyarray.Add("Last Updated");
    m_sortbyarray.Add("Date Received");


    odcSortBy = new wxOwnerDrawnComboBox(controlPanel, wxID_ANY, "SORT BY",
        wxPoint(7, 91), wxDefaultSize,
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

    wxBitmapButton* SortButton = new wxBitmapButton(controlPanel, idButtonSortGrid, wxBitmap(wxT("sortButton.png"),
        wxBITMAP_TYPE_PNG), wxPoint(140, 84), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage SortButtonimgHover("sortButtonh.png");
    SortButton->SetBitmapHover(SortButtonimgHover);
    wxImage SortButtonimgPressed("sortButtonp.png");
    SortButton->SetBitmapPressed(SortButtonimgPressed);

    wxPanel* descriptionPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(3, 564), wxSize(224, 100), wxBORDER_RAISED);
    descriptionPanel->SetBackgroundColour(wxColour(33, 33, 57));

    wxPanel* descriptionTitlePanel = new wxPanel(descriptionPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(224, 28), wxBORDER_NONE);
    descriptionTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* descriptionTitle = new wxStaticText(descriptionTitlePanel, wxID_ANY, ("Get Description"), wxPoint(40, 3), wxSize(-1, -1), wxTE_CENTRE);
    descriptionTitle->SetForegroundColour(wxColor(0, 188, 255));
    descriptionTitle->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* cpsl4 = new wxStaticLine(descriptionPanel, wxID_ANY, wxPoint(-1, 29),
        wxSize(224, 2));


    idEntry = new wxTextCtrl(descriptionPanel, -1, wxT(""), wxPoint(28, 50),
        wxSize(70, 25),wxTE_PROCESS_ENTER);
    idEntry->SetBackgroundColour(wxColour(228, 228, 240));
    idEntry->SetFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));


    wxBitmapButton* GetButton = new wxBitmapButton(descriptionPanel, idButtonGetInfo, wxBitmap(wxT("getButton.png"),
        wxBITMAP_TYPE_PNG), wxPoint(119, 45), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage GetButtonimgHover("getButtonh.png");
    GetButton->SetBitmapHover(GetButtonimgHover);
    wxImage GetButtonimgPressed("getButtonp.png");
    GetButton->SetBitmapPressed(GetButtonimgPressed);


    ///DATA GRID

    wxPanel* dataGridPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(230, 3), wxSize(968, 362), wxBORDER_RAISED);
    dataGridPanel->SetBackgroundColour(wxColor(150, 250, 150));


    grid = new wxGrid(dataGridPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(964, 360));

    grid->CreateGrid(0, 7);

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
    grid->SetSelectionForeground(wxColor(0,0,0));

    grid->SetRowLabelSize(0);

    grid->SetColLabelValue(0, _("ID#"));
    grid->SetColLabelValue(1, _("Company Name"));
    grid->SetColLabelValue(2, _("Repair Number"));
    grid->SetColLabelValue(3, _("Model Number"));
    grid->SetColLabelValue(4, _("Status"));
    grid->SetColLabelValue(5, _("Last Update"));
    grid->SetColLabelValue(6, _("Date Received"));
    grid->SetDefaultCellOverflow(false);

    grid->SetDefaultCellFont(wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    grid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    grid->SetDefaultColSize(140);
    grid->SetDefaultRowSize(31);

    grid->SetColSize(0, 56);
    grid->SetColSize(1, 240);
    grid->SetColSize(2, 140);
    grid->SetColSize(3, 160);
    grid->SetColSize(4, 160);
    grid->SetColSize(5, 95);
    grid->SetColSize(6, 95);

    db = new wxSQLite3Database();

     testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    db->Open(testDBName);

   
    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

    db->Close();

    db->Open(testDBName);

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY rowid ASC;");
    dbSize = 0;

    int count = 0;
    while (Res.NextRow())
    {
        
        grid->AppendRows(1);
        dbSize++;
        grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
        grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));
        for (int i = 0; i < 7; i++) {

            grid->SetCellValue(count, i, wxString::Format(_("%s"), Res.GetAsString(i)));

        }

        count++;
    }
    

    Res.Finalize();
    db->Close();

    ///LOGIN PANEL

    wxPanel* loginPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(3, 3), wxSize(224, 160), wxBORDER_RAISED);
    loginPanel->SetBackgroundColour(wxColour(33, 33, 57));

    wxStaticBitmap* logoimage;

    logoimage = new wxStaticBitmap(loginPanel, wxID_ANY, wxBitmap("loginLogoImage4.png", wxBITMAP_TYPE_PNG), wxPoint(0, 6), wxDefaultSize, wxNO_BORDER);



    ///CONTACT INFO PANEL

    wxPanel* contactPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(230, 367), wxSize(420, 297), wxBORDER_RAISED);
    contactPanel->SetBackgroundColour(wxColour(33, 33, 57));

    wxPanel* contactTitlePanel = new wxPanel(contactPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(420, 42), wxBORDER_NONE);
    contactTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* contactTitle = new wxStaticText(contactTitlePanel, wxID_ANY, ("Contact Information"), wxPoint(110, 5), wxSize(-1, -1), wxTE_CENTRE);
    contactTitle->SetForegroundColour(wxColor(0, 188, 255));
    contactTitle->SetFont(wxFont(20, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* copsl1 = new wxStaticLine(contactPanel, wxID_ANY, wxPoint(-1, 43),
        wxSize(420, 2));

    contactDataGrid = new wxGrid(contactPanel, wxID_ANY,
        wxPoint(-1, 46), wxSize(420, 249));

    contactDataGrid->CreateGrid(5, 2);


    contactDataGrid->SetGridLineColour(wxColor(0, 173, 234));
    contactDataGrid->SetDefaultCellTextColour(wxColor(0, 255, 255));
    contactDataGrid->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    contactDataGrid->Refresh();

    contactDataGrid->EnableEditing(false);
    contactDataGrid->EnableGridLines(true);
    contactDataGrid->DisableDragColSize();
    contactDataGrid->DisableDragRowSize();
    contactDataGrid->EnableDragGridSize(false);
    contactDataGrid->SetCellHighlightPenWidth(0);
    contactDataGrid->SetCellHighlightROPenWidth(0);
    contactDataGrid->SetSelectionBackground(contactDataGrid->GetDefaultCellBackgroundColour());
    contactDataGrid->SetSelectionForeground(contactDataGrid->GetDefaultCellTextColour());
    contactDataGrid->SetRowLabelSize(0);
    contactDataGrid->SetColLabelSize(0);

   
    contactDataGrid->SetDefaultCellFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    contactDataGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    contactDataGrid->SetDefaultColSize(208);
    contactDataGrid->SetDefaultRowSize(49);

    contactDataGrid->SetColSize(0, 140);
    contactDataGrid->SetColSize(1, 276);


    contactDataGrid->SetCellValue(0, 0, " ID #:");
    contactDataGrid->SetCellAlignment(0,0, wxALIGN_LEFT, wxALIGN_CENTRE);
    contactDataGrid->SetCellValue(1, 0, " Contact:");
    contactDataGrid->SetCellAlignment(1, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    contactDataGrid->SetCellValue(2, 0, " Address:");
    contactDataGrid->SetCellAlignment(2, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    contactDataGrid->SetCellValue(3, 0, " Phone Number:");
    contactDataGrid->SetCellAlignment(3, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    contactDataGrid->SetCellValue(4, 0, " Email Address:");
    contactDataGrid->SetCellAlignment(4, 0, wxALIGN_LEFT, wxALIGN_CENTRE);

    contactDataGrid->SetCellBackgroundColour(0, 1, wxColour(230, 230, 230));
    contactDataGrid->SetCellBackgroundColour(1, 1, wxColour(220, 240, 255));
    contactDataGrid->SetCellBackgroundColour(2, 1, wxColour(230, 230, 230));
    contactDataGrid->SetCellBackgroundColour(3, 1, wxColour(220, 240, 255));
    contactDataGrid->SetCellBackgroundColour(4, 1, wxColour(230, 230, 230));
   

    for (int i = 0; i < 5; i++)
    {
        contactDataGrid->SetCellTextColour(i, 1, wxColour(0, 0, 0));
        contactDataGrid->SetCellFont(i, 1, wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    }

    ///STATUS INFO PANEL
    
    wxPanel* statusPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(655, 367), wxSize(420, 297), wxBORDER_RAISED);
    statusPanel->SetBackgroundColour(wxColour(33, 33, 57));

    wxPanel* statusTitlePanel = new wxPanel(statusPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(420, 42), wxBORDER_NONE);
    statusTitlePanel->SetBackgroundColour(wxColour(28, 28, 43));

    wxStaticText* statusTitle = new wxStaticText(statusTitlePanel, wxID_ANY, ("Status Information"), wxPoint(110, 5), wxSize(-1, -1), wxTE_CENTRE);
    statusTitle->SetForegroundColour(wxColor(0, 188, 255));
    statusTitle->SetFont(wxFont(20, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticLine* spsl1 = new wxStaticLine(statusPanel, wxID_ANY, wxPoint(-1, 43),
        wxSize(420, 2));



    statusDataGrid = new wxGrid(statusPanel, wxID_ANY,
        wxPoint(-1, 45), wxSize(420, 126));

    statusDataGrid->CreateGrid(4, 2);

    statusDataGrid->SetGridLineColour(wxColor(0, 173, 234));
    statusDataGrid->SetDefaultCellTextColour(wxColor(0, 255, 255));
    statusDataGrid->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    statusDataGrid->Refresh();

    statusDataGrid->EnableEditing(false);
    statusDataGrid->EnableGridLines(true);
    statusDataGrid->DisableDragColSize();
    statusDataGrid->DisableDragRowSize();
    statusDataGrid->EnableDragGridSize(false);
    statusDataGrid->SetCellHighlightPenWidth(0);
    statusDataGrid->SetCellHighlightROPenWidth(0);
    statusDataGrid->SetSelectionBackground(statusDataGrid->GetDefaultCellBackgroundColour());
    statusDataGrid->SetSelectionForeground(statusDataGrid->GetDefaultCellTextColour());
    statusDataGrid->SetRowLabelSize(0);
    statusDataGrid->SetColLabelSize(0);


    statusDataGrid->SetDefaultCellFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    statusDataGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    statusDataGrid->SetDefaultColSize(208);
    statusDataGrid->SetDefaultRowSize(31);

    statusDataGrid->SetColSize(0, 163);
    statusDataGrid->SetColSize(1, 252);


    statusDataGrid->SetCellValue(0, 0, " Model #:");
    statusDataGrid->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    
    statusDataGrid->SetCellValue(1, 0, " Department:");
    statusDataGrid->SetCellAlignment(1, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    statusDataGrid->SetCellValue(2, 0, " Technician:");
    statusDataGrid->SetCellAlignment(2, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
    statusDataGrid->SetCellValue(3, 0, " Status:");
    statusDataGrid->SetCellAlignment(3, 0, wxALIGN_LEFT, wxALIGN_CENTRE);

    statusDataGrid->SetCellBackgroundColour(0, 1, wxColour(230, 230, 230));
    statusDataGrid->SetCellBackgroundColour(1, 1, wxColour(220, 240, 255));
    statusDataGrid->SetCellBackgroundColour(2, 1, wxColour(230, 230, 230));
    statusDataGrid->SetCellBackgroundColour(3, 1, wxColour(220, 240, 255));
    

    statusDataGrid->SetCellTextColour(0, 1, wxColour(0, 0, 0));
    statusDataGrid->SetCellTextColour(1, 1, wxColour(0, 0, 0));
    statusDataGrid->SetCellTextColour(2, 1, wxColour(0, 0, 0));
    statusDataGrid->SetCellTextColour(3, 1, wxColour(0, 0, 0));
   

    wxPanel* statusProblemDescriptionPanel = new wxPanel(statusPanel, wxID_ANY,
        wxPoint(-1, 171), wxSize(208, 120), wxSIMPLE_BORDER);
    statusProblemDescriptionPanel->SetBackgroundColour(wxColour(220, 240, 255));

    wxPanel* problemTitlePanel = new wxPanel(statusProblemDescriptionPanel, wxID_ANY,
        wxDefaultPosition, wxSize(208, 25), wxSUNKEN_BORDER);
    problemTitlePanel->SetBackgroundColour(wxColour(28, 28, 32));

    wxStaticText* problemTitle = new wxStaticText(problemTitlePanel, wxID_ANY, ("What We "), wxPoint(35, 1), wxSize(-1, -1), wxTE_CENTRE);
    problemTitle->SetForegroundColour(wxColor(0, 188, 255));
    problemTitle->SetFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));

    wxStaticText* problemTitle2 = new wxStaticText(problemTitlePanel, wxID_ANY, ("Found"), wxPoint(115, 1), wxSize(-1, -1), wxTE_CENTRE);
    problemTitle2->SetForegroundColour(wxColor(0, 188, 255));
    problemTitle2->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, _("MS Sans Serif")));

    statusProblemGrid = new wxGrid(statusProblemDescriptionPanel, wxID_ANY,
        wxPoint(-1, 26), wxSize(206, 93));

    statusProblemGrid->CreateGrid(1, 1);

    statusProblemGrid->SetGridLineColour(wxColor(220, 240, 255));
    statusProblemGrid->SetDefaultCellTextColour(wxColor(0, 0, 0));
    statusProblemGrid->SetDefaultCellBackgroundColour(wxColor(220, 240, 255));
    statusProblemGrid->Refresh();

    statusProblemGrid->EnableEditing(false);
    statusProblemGrid->EnableGridLines(true);
    statusProblemGrid->DisableDragColSize();
    statusProblemGrid->DisableDragRowSize();
    statusProblemGrid->EnableDragGridSize(false);
    statusProblemGrid->SetCellHighlightPenWidth(0);
    statusProblemGrid->SetCellHighlightROPenWidth(0);
    statusProblemGrid->SetSelectionBackground(statusDataGrid->GetDefaultCellBackgroundColour());
    statusProblemGrid->SetSelectionForeground(statusDataGrid->GetDefaultCellTextColour());
    statusProblemGrid->SetRowLabelSize(0);
    statusProblemGrid->SetColLabelSize(0);
    statusProblemGrid->SetDefaultCellOverflow(false);

    statusProblemGrid->SetDefaultCellFont(wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    statusProblemGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    statusProblemGrid->SetDefaultColSize(206);
    statusProblemGrid->SetDefaultRowSize(90);
    statusProblemGrid->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_TOP);

    statusProblemGrid->SetCellRenderer(0, 0, new wxGridCellAutoWrapStringRenderer);

    wxPanel* statusCorrectiveActionPanel = new wxPanel(statusPanel, wxID_ANY,
        wxPoint(208, 171), wxSize(208, 120), wxSIMPLE_BORDER);
    statusCorrectiveActionPanel->SetBackgroundColour(wxColour(230, 230, 230));

    wxPanel* correctiveActionTitlePanel = new wxPanel(statusCorrectiveActionPanel, wxID_ANY,
        wxDefaultPosition, wxSize(208, 25), wxSUNKEN_BORDER);
    correctiveActionTitlePanel->SetBackgroundColour(wxColour(28, 28, 32));

    wxStaticText* correctiveActionTitle = new wxStaticText(correctiveActionTitlePanel, wxID_ANY, ("Notes"), wxPoint(75, 1), wxSize(-1, -1), wxTE_CENTRE);

    correctiveActionTitle->SetForegroundColour(wxColor(0, 188, 255));
    correctiveActionTitle->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, _("MS Sans Serif")));

    statusCorrectionGrid = new wxGrid(statusCorrectiveActionPanel, wxID_ANY,
        wxPoint(-1, 26), wxSize(206, 93));

    statusCorrectionGrid->CreateGrid(1, 1);

    statusCorrectionGrid->SetGridLineColour(wxColor(230, 230, 230));
    statusCorrectionGrid->SetDefaultCellTextColour(wxColor(0, 0, 0));
    statusCorrectionGrid->SetDefaultCellBackgroundColour(wxColor(230, 230, 230));
    statusCorrectionGrid->Refresh();

    statusCorrectionGrid->EnableEditing(false);
    statusCorrectionGrid->EnableGridLines(true);
    statusCorrectionGrid->DisableDragColSize();
    statusCorrectionGrid->DisableDragRowSize();
    statusCorrectionGrid->EnableDragGridSize(false);
    statusCorrectionGrid->SetCellHighlightPenWidth(0);
    statusCorrectionGrid->SetCellHighlightROPenWidth(0);
    statusCorrectionGrid->SetSelectionBackground(statusDataGrid->GetDefaultCellBackgroundColour());
    statusCorrectionGrid->SetSelectionForeground(statusDataGrid->GetDefaultCellTextColour());
    statusCorrectionGrid->SetRowLabelSize(0);
    statusCorrectionGrid->SetColLabelSize(0);

    statusCorrectionGrid->SetDefaultCellFont(wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    statusCorrectionGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    statusCorrectionGrid->SetDefaultColSize(207);
    statusCorrectionGrid->SetDefaultRowSize(90);
    statusCorrectionGrid->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_TOP);
    statusCorrectionGrid->SetCellRenderer(0, 0, new wxGridCellAutoWrapStringRenderer);

    wxPanel* caseAndQtyPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(1078, 367), wxSize(120, 175), wxSIMPLE_BORDER);
    caseAndQtyPanel->SetBackgroundColour(wxColour(230, 230, 230));



    wxPanel* casePanel = new wxPanel(caseAndQtyPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(120, 87), wxSIMPLE_BORDER);
    casePanel->SetBackgroundColour(wxColour(230, 230, 230));

    wxPanel* QtyPanel = new wxPanel(caseAndQtyPanel, wxID_ANY,
        wxPoint(-1, 88), wxSize(120, 87), wxSIMPLE_BORDER);
    QtyPanel->SetBackgroundColour(wxColour(220, 240, 255));

    wxPanel* caseTitlePanel = new wxPanel(casePanel, wxID_ANY,
        wxDefaultPosition, wxSize(120, 25), wxSUNKEN_BORDER);
    caseTitlePanel->SetBackgroundColour(wxColour(28, 28, 32));

    wxStaticText* caseTitle = new wxStaticText(caseTitlePanel, wxID_ANY, ("Case:"), wxPoint(38, 1), wxSize(-1, -1), wxTE_CENTRE);
    caseTitle->SetForegroundColour(wxColor(0, 188, 255));
    caseTitle->SetFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));


    wxPanel* QtyTitlePanel = new wxPanel(QtyPanel, wxID_ANY,
        wxPoint(-1, -1), wxSize(120, 25), wxSUNKEN_BORDER);
    QtyTitlePanel->SetBackgroundColour(wxColour(28, 28, 32));

    wxStaticText* QtyTitle = new wxStaticText(QtyTitlePanel, wxID_ANY, ("Quantity:"), wxPoint(23, 1), wxSize(-1, -1), wxTE_CENTRE);
    QtyTitle->SetForegroundColour(wxColor(0, 188, 255));
    QtyTitle->SetFont(wxFont(12, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));


    caseGrid = new wxGrid(casePanel, wxID_ANY,
        wxPoint(-1, 26), wxSize(130, 80));

    caseGrid->CreateGrid(1, 1);

    caseGrid->SetGridLineColour(wxColor(220, 240, 255));
    caseGrid->SetDefaultCellTextColour(wxColor(0, 0, 0));
    caseGrid->SetDefaultCellBackgroundColour(wxColor(230, 230, 230));
    caseGrid->Refresh();

    caseGrid->EnableEditing(false);
    caseGrid->EnableGridLines(true);
    caseGrid->DisableDragColSize();
    caseGrid->DisableDragRowSize();
    caseGrid->EnableDragGridSize(false);
    caseGrid->SetCellHighlightPenWidth(0);
    caseGrid->SetCellHighlightROPenWidth(0);
    caseGrid->SetSelectionBackground(statusDataGrid->GetDefaultCellBackgroundColour());
    caseGrid->SetSelectionForeground(statusDataGrid->GetDefaultCellTextColour());
    caseGrid->SetRowLabelSize(0);
    caseGrid->SetColLabelSize(0);

    caseGrid->SetDefaultCellFont(wxFont(18, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    caseGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    caseGrid->SetDefaultColSize(117);
    caseGrid->SetDefaultRowSize(59);
    caseGrid->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);

    

    QtyGrid = new wxGrid(QtyPanel, wxID_ANY,
        wxPoint(-1, 26), wxSize(130, 80));

    QtyGrid->CreateGrid(1, 1);

    QtyGrid->SetGridLineColour(wxColor(220, 240, 255));
    QtyGrid->SetDefaultCellTextColour(wxColor(0, 0, 0));
    QtyGrid->SetDefaultCellBackgroundColour(wxColor(220, 240, 255));
    QtyGrid->Refresh();

    QtyGrid->EnableEditing(false);
    QtyGrid->EnableGridLines(true);
    QtyGrid->DisableDragColSize();
    QtyGrid->DisableDragRowSize();
    QtyGrid->EnableDragGridSize(false);
    QtyGrid->SetCellHighlightPenWidth(0);
    QtyGrid->SetCellHighlightROPenWidth(0);
    QtyGrid->SetSelectionBackground(statusDataGrid->GetDefaultCellBackgroundColour());
    QtyGrid->SetSelectionForeground(statusDataGrid->GetDefaultCellTextColour());
    QtyGrid->SetRowLabelSize(0);
    QtyGrid->SetColLabelSize(0);

    QtyGrid->SetDefaultCellFont(wxFont(20, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    QtyGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    QtyGrid->SetDefaultColSize(117);
    QtyGrid->SetDefaultRowSize(58);
    QtyGrid->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);

    
    

    /// LOG PANEL

    wxPanel* logPanel = new wxPanel(panel, wxID_ANY,
        wxPoint(1078, 545), wxSize(120, 120), wxBORDER_RAISED);
    logPanel->SetBackgroundColour(wxColour(228, 228, 240));

    wxPanel* logTitlePanel = new wxPanel(logPanel, wxID_ANY,
        wxDefaultPosition, wxSize(120, 25), wxSUNKEN_BORDER);
    logTitlePanel->SetBackgroundColour(wxColour(28, 28, 32));

    wxStaticText* logTitle = new wxStaticText(logTitlePanel, wxID_ANY, ("LOG"), wxPoint(40, 2), wxSize(-1, -1), wxTE_CENTRE);
    logTitle->SetForegroundColour(wxColor(0, 188, 255));
    logTitle->SetFont(wxFont(10, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));

    wxStaticLine* lpsl1 = new wxStaticLine(logPanel, wxID_ANY, wxPoint(-1, 26),
        wxSize(120, 3));
    logGrid = new wxGrid(logPanel, wxID_ANY,
        wxPoint(-1, 30), wxSize(130, 100));

    logGrid->CreateGrid(5, 3);


    logGrid->SetDefaultCellTextColour(wxColor(0, 255, 255));
    logGrid->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    logGrid->Refresh();

    logGrid->EnableEditing(false);
    logGrid->EnableGridLines(false);
    logGrid->DisableDragColSize();
    logGrid->DisableDragRowSize();
    logGrid->EnableDragGridSize(false);
    logGrid->SetCellHighlightPenWidth(0);
    logGrid->SetCellHighlightROPenWidth(0);
    logGrid->SetSelectionBackground(statusDataGrid->GetDefaultCellBackgroundColour());
    logGrid->SetSelectionForeground(statusDataGrid->GetDefaultCellTextColour());
    logGrid->SetRowLabelSize(0);
    logGrid->SetColLabelSize(0);

    logGrid->SetDefaultCellFont(wxFont(8, wxSWISS, wxBOLD, wxBOLD, false, _("MS Sans Serif")));
    logGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    logGrid->SetDefaultColSize(23);
    logGrid->SetDefaultRowSize(17);

    logGrid->SetColSize(0, 18);
    logGrid->SetColSize(2, 73);

    logGrid->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);

    logGrid->SetCellTextColour(1, 0, wxColor(0, 173, 234));
    logGrid->SetCellTextColour(1, 1, wxColor(0, 173, 234));
    logGrid->SetCellTextColour(1, 2, wxColor(0, 173, 234));

    logGrid->SetCellTextColour(3, 0, wxColor(0, 173, 234));
    logGrid->SetCellTextColour(3, 1, wxColor(0, 173, 234));
    logGrid->SetCellTextColour(3, 2, wxColor(0, 173, 234));


    static const int INTERVAL = 30000; // milliseconds
    m_timer = new wxTimer(this, TIMER_ID);
    m_timer->Start(INTERVAL);

}





SensorPanel::~SensorPanel() {}





void SensorPanel::onClickNewRepair(wxCommandEvent& event)
{

    
    newRepairDialog* NRP = new newRepairDialog(wxT("New Repair"));
    NRP->Show(true);
}





void SensorPanel::REFRESH()
{
    int n = 0;
    if (grid->GetNumberRows() >> 0) {

        // if (cntr >> 0) {
        grid->DeleteRows(n, grid->GetNumberRows() - n);
        // }
    }
    // cntr++;

    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    if (dbQuery == "") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY rowid ASC;"; }


    db->Open(testDBName);
    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

    wxSQLite3ResultSet  Res = db->ExecuteQuery(dbQuery);


    int count = 0;
    while (Res.NextRow())
    {

        grid->AppendRows(1);
        dbSize++;
        grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
        grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));
        for (int i = 0; i < 7; i++) {

            grid->SetCellValue(count, i, wxString::Format(_("%s"), Res.GetAsString(i)));

        }

        count++;
    }


    Res.Finalize();
    db->Close();

    grid->Refresh();

}

void SensorPanel::onClickRefresh(wxCommandEvent& event)
{
    REFRESH();
}


void SensorPanel::OnTimer(wxTimerEvent& event)
{
    REFRESH();
}





void SensorPanel::onClickGet(wxCommandEvent& event)
{
      
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

        for (int i = 0; i < 5; i++)
        {
            logGrid->SetCellValue(i, 0, "");
            logGrid->SetCellValue(i, 1, "");
            logGrid->SetCellValue(i, 2, "");
        }


        getValueI = wxAtoi(getValueS);

        cellCount = grid->GetNumberRows();

        testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

        db->Open(testDBName);

        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

        wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT Id,ContactName,Address,PhoneNumber,EmailAddress FROM nodeData WHERE RepairNumber ='" + getValueS + "';");
        wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT ModelNumber,Department,Technician,Status FROM nodeData WHERE RepairNumber ='" + getValueS + "';");
        wxSQLite3ResultSet Res3 = db->ExecuteQuery("SELECT WhatWeFound FROM nodeData WHERE RepairNumber ='" + getValueS + "';");
        wxSQLite3ResultSet Res4 = db->ExecuteQuery("SELECT CorrectiveAction FROM nodeData WHERE RepairNumber ='" + getValueS + "';");
        wxSQLite3ResultSet Res5 = db->ExecuteQuery("SELECT CaseYN FROM nodeData WHERE RepairNumber ='" + getValueS + "';");
        wxSQLite3ResultSet Res6 = db->ExecuteQuery("SELECT Quantity FROM nodeData WHERE RepairNumber ='" + getValueS + "';");
        wxSQLite3ResultSet Res7 = db->ExecuteQuery("SELECT RepairNumber FROM nodeData WHERE RepairNumber ='" + getValueS + "';");

        while (Res.NextRow())
        {

            for (int i = 0; i < 5; i++) {

                contactDataGrid->SetCellValue(i, 1, wxString::Format(_("%s"), Res.GetAsString(i)));


            }

        }

        while (Res2.NextRow())
        {

            for (int i = 0; i < 4; i++) {

                statusDataGrid->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


            }

        }

        while (Res3.NextRow())
        {

            statusProblemGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res3.GetAsString(0)));

        }

        while (Res4.NextRow())
        {

            statusCorrectionGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res4.GetAsString(0)));

        }

        while (Res5.NextRow())
        {

            caseGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res5.GetAsString(0)));

        }

        while (Res6.NextRow())
        {

            QtyGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res6.GetAsString(0)));

        }

        logRN = Res7.GetAsString(0);


        Res.Finalize();
        Res2.Finalize();
        Res3.Finalize();
        Res4.Finalize();
        Res5.Finalize();
        Res6.Finalize();
        Res7.Finalize();

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

        idEntry->SetValue("");


        testDBName = wxGetCwd() + wxT("//logDatabase.db");
        db->Open(testDBName);
        
        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'Chronology' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

        wxSQLite3ResultSet Res8 = db->ExecuteQuery("SELECT DateSent, History FROM nodeData WHERE RepairNumber = '" + logRN + "' AND Source = 'sensor' ORDER BY Chronology DESC LIMIT 5;");

        int logItt = 0;
        while (Res8.NextRow())
        {
            if (Res8.GetAsString(1) == "CREATED")
            {
                logGrid->SetCellValue(logItt, 0, "C");
            }

            else if (Res8.GetAsString(1) == "UPDATE")
            {
                logGrid->SetCellValue(logItt, 0, "U");
            }


            logGrid->SetCellValue(logItt, 1, "On");
            logGrid->SetCellValue(logItt, 2, wxString::Format(_("%s"), Res8.GetAsString(0)));

            logItt++;

        }

        Res8.Finalize();
        
        db->Close();
    }
}





void SensorPanel::onClickSearch(wxCommandEvent& event)
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


        testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

        db->Open(testDBName);

        wxSQLite3ResultSet Res;

        if (getSearchCategory == "Company Name") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE CompanyName LIKE '%" + getSearchCriteria + "%' AND Status != 'Shipped' ORDER BY rowid DESC;"; }
        else if (getSearchCategory == "Repair Number") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE RepairNumber LIKE '%" + getSearchCriteria + "%' AND Status != 'Shipped' ORDER BY rowid DESC;"; }
        else if (getSearchCategory == "Model Number") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE ModelNumber LIKE '%" + getSearchCriteria + "%' AND Status != 'Shipped' ORDER BY rowid DESC;"; }
        else if (getSearchCategory == "Status") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status LIKE '%" + getSearchCriteria + "%' AND Status != 'Shipped' ORDER BY rowid DESC;"; }
        else if (getSearchCategory == "Last Update") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE DateSent LIKE '%" + getSearchCriteria + "%' AND Status != 'Shipped' ORDER BY rowid DESC;"; }
        else if (getSearchCategory == "Date Received") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE DateReceived LIKE '%" + getSearchCriteria + "%' AND Status != 'Shipped' ORDER BY rowid DESC;"; }
        else { dbQuery = "SELECT Id, CompanyNameName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY rowid ASC;"; }

        Res = db->ExecuteQuery(dbQuery);


        int count = 0;
        while (Res.NextRow())
        {

            grid->AppendRows(1);
            dbSize++;
            grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
            grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));
            for (int i = 0; i < 7; i++) {

                grid->SetCellValue(count, i, wxString::Format(_("%s"), Res.GetAsString(i)));

            }

            count++;
        }


        Res.Finalize();
        db->Close();

        grid->Refresh();

    }
}





void SensorPanel::onClickUpdateRepair(wxCommandEvent& event)
{
    wxString tempUpdate = updateEntry->GetValue();

    if (tempUpdate == "")
    {
        wxString msg = _T("ERROR: No Input Detected For 'UPDATE REPAIR' Please Try again");
        wxString info = _T("Update Repair ERROR");
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

        wxSQLite3ResultSet Res = db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'sensorUpdateData' ('UpdateID' TEXT);");

        db->ExecuteUpdate(wxString::Format(_("INSERT INTO sensorUpdateData (UpdateID) VALUES ('%s')"), tempUpdate));

        Res.Finalize();

        db->Close();


        updateRepairDialog* urdObjPtr = new updateRepairDialog(wxT("Update Repair"));


        updateEntry->SetValue("");

        urdObjPtr->Show(true);
    }
}





void SensorPanel::onClickReset(wxCommandEvent& event)
{

    dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY rowid ASC;";


    int n = 0;
    if (grid->GetNumberRows() >> 0) {

        // if (cntr >> 0) {
        grid->DeleteRows(n, grid->GetNumberRows() - n);
        // }
    }
    // cntr++;

    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    db->Open(testDBName);

    wxSQLite3ResultSet  Res = db->ExecuteQuery("SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY rowid ASC;");



    int count = 0;
    while (Res.NextRow())
    {

        grid->AppendRows(1);
        dbSize++;
        grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
        grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));
        for (int i = 0; i < 7; i++) {

            grid->SetCellValue(count, i, wxString::Format(_("%s"), Res.GetAsString(i)));

        }

        count++;
    }


    Res.Finalize();
    db->Close();

    grid->Refresh();




}





void SensorPanel::onClickSort(wxCommandEvent& event)
{

   
     getSortCriteria = odcSortBy->GetValue();

    int n =0;

    grid->DeleteRows(n, grid->GetNumberRows() - n);

    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res;

    

    if (getSortCriteria == "Newest to Oldest") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY rowid DESC;"; }
    else if (getSortCriteria == "Oldest to Newest") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY rowid ASC;"; }
    else if (getSortCriteria == "Company") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY CompanyName ASC;"; }
    else if (getSortCriteria == "Repair #") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY RepairNumber ASC;"; }
    else if (getSortCriteria == "Serial #") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY ModelNumber ASC;"; }
    else if (getSortCriteria == "Status") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY Status ASC;"; }
    else if (getSortCriteria == "Date Received") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY DateReceived ASC;"; }
    else if (getSortCriteria == "Last Updated") { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY DateSent ASC;"; }
    else { dbQuery = "SELECT Id, CompanyName, RepairNumber, ModelNumber, Status, DateSent, DateReceived FROM nodeData WHERE Status != 'Shipped' ORDER BY rowid ASC;"; }

    Res = db->ExecuteQuery(dbQuery);
 
         int count = 0;
         while (Res.NextRow())
         {

             grid->AppendRows(1);
             dbSize++;
             grid->SetCellBackgroundColour(count, 0, wxColour(0, 25, 32));
             grid->SetCellTextColour(count, 0, wxColour(0, 173, 234));
             for (int i = 0; i < 7; i++) {

                 grid->SetCellValue(count, i, wxString::Format(_("%s"), Res.GetAsString(i)));

             }

             count++;
         }


         Res.Finalize();
         db->Close();

         grid->Refresh();
}




newRepairDialog::newRepairDialog(const wxString& title)
    : wxDialog(NULL, -1, ("Create New Repair"), wxPoint(1100, 500), wxSize(630, 480))
{
    wxPanel* panel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(630, 480));
    panel->SetBackgroundColour(wxColor(33, 33, 57));

    wxPanel* buttonPanel = new wxPanel(panel, -1, wxPoint(10, 387), wxSize(595, 47), wxSIMPLE_BORDER);
    buttonPanel->SetBackgroundColour(wxColor(210, 230, 255));


    m_contact = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(160, 10), wxSize(150, -1), wxTE_PROCESS_ENTER);
    m_contact->SetBackgroundColour(wxColour(228, 228, 240));

    m_company = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(160, 45), wxSize(150, -1), wxTE_PROCESS_ENTER);
    m_company->SetBackgroundColour(wxColour(228, 228, 240));

    


    m_address = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 118), wxSize(185, -1), wxTE_PROCESS_ENTER);
    m_address->SetBackgroundColour(wxColour(228, 228, 240));

    m_city = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 148), wxSize(185, -1), wxTE_PROCESS_ENTER);
    m_city->SetBackgroundColour(wxColour(228, 228, 240));

    m_state = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 178), wxSize(185, -1), wxTE_PROCESS_ENTER);
    m_state->SetBackgroundColour(wxColour(228, 228, 240));

    m_zip = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 208), wxSize(185, -1), wxTE_PROCESS_ENTER);
    m_zip->SetBackgroundColour(wxColour(228, 228, 240));

    m_country = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 238), wxSize(185, -1), wxTE_PROCESS_ENTER);
    m_country->SetBackgroundColour(wxColour(228, 228, 240));




    m_email = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(100, 307), wxSize(185, -1), wxTE_PROCESS_ENTER);
    m_email->SetBackgroundColour(wxColour(228, 228, 240));

    m_phone = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(185, 343), wxSize(100, -1), wxTE_PROCESS_ENTER);
    m_phone->SetBackgroundColour(wxColour(228, 228, 240));

   
    m_model = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(495, 10), wxDefaultSize, wxTE_PROCESS_ENTER);
    m_model->ForceUpper();
    m_model->SetBackgroundColour(wxColour(228, 228, 240));

    m_serial = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(495, 45), wxDefaultSize);
    m_serial->ForceUpper();
    m_serial->SetBackgroundColour(wxColour(228, 228, 240));

    m_repair = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(495, 80), wxDefaultSize, wxTE_PROCESS_ENTER);
    m_repair->ForceUpper();
    m_repair->SetBackgroundColour(wxColour(228, 228, 240));


    m_group = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(320, 200), wxSize(60, -1), wxTE_PROCESS_ENTER);
    m_group->SetBackgroundColour(wxColour(228, 228, 240));

    m_casearray.Add("NO");
    m_casearray.Add("YES");

    odccase = new wxOwnerDrawnComboBox(panel, wxID_ANY, "",
        wxPoint(432, 200), wxDefaultSize,
        m_casearray,
        (long)0 | wxCB_READONLY);

    odccase->SetBackgroundColour(wxColour(228, 228, 240));

    // Load images from disk
    wxImage imgNormal("dropbutn.png");
    wxImage imgPressed("dropbutp.png");
    wxImage imgHover("dropbuth.png");

    if (imgNormal.IsOk() && imgPressed.IsOk() && imgHover.IsOk())
    {
        wxBitmap bmpNormal(imgNormal);
        wxBitmap bmpPressed(imgPressed);
        wxBitmap bmpHover(imgHover);
        odccase->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
    }

    m_quantity = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(525, 200), wxSize(70, -1), wxTE_PROCESS_ENTER);
    m_quantity->SetBackgroundColour(wxColour(228, 228, 240));

    m_multitext = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(350, 265), wxSize(255, 101), wxTE_MULTILINE | wxTE_NO_VSCROLL);
    m_multitext->SetInsertionPoint(0);
    m_multitext->SetForegroundColour(*wxBLACK);
    m_multitext->SetBackgroundColour(wxColour(228, 228, 240));


    wxStaticText* contact = new wxStaticText(panel, wxID_ANY, ("Contact Name:"), wxPoint(10, 10));
    contact->SetForegroundColour(wxColor(0, 255, 255));
    contact->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* company = new wxStaticText(panel, wxID_ANY, ("Company Name:"), wxPoint(10, 45));
    company->SetForegroundColour(wxColor(0, 255, 255));
    company->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

   

   


    wxStaticText* address = new wxStaticText(panel, wxID_ANY, ("Address:"), wxPoint(10, 115));
    address->SetForegroundColour(wxColor(0, 255, 255));
    address->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* city = new wxStaticText(panel, wxID_ANY, ("City:"), wxPoint(10, 145));
    city->SetForegroundColour(wxColor(0, 255, 255));
    city->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* state = new wxStaticText(panel, wxID_ANY, ("State:"), wxPoint(10, 175));
    state->SetForegroundColour(wxColor(0, 255, 255));
    state->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* zip = new wxStaticText(panel, wxID_ANY, ("Zip:"), wxPoint(10, 205));
    zip->SetForegroundColour(wxColor(0, 255, 255));
    zip->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* country = new wxStaticText(panel, wxID_ANY, ("Country:"), wxPoint(10, 235));
    country->SetForegroundColour(wxColor(0, 255, 255));
    country->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));



    wxStaticText* email = new wxStaticText(panel, wxID_ANY, ("Email:"), wxPoint(10, 305));
    email->SetForegroundColour(wxColor(0, 255, 255));
    email->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* phone = new wxStaticText(panel, wxID_ANY, ("Phone Number:"), wxPoint(10, 341));
    phone->SetForegroundColour(wxColor(0, 255, 255));
    phone->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    

    wxStaticText* model = new wxStaticText(panel, wxID_ANY, ("Model Number:"), wxPoint(355, 10));
    model->SetForegroundColour(wxColor(0, 255, 255));
    model->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* serial = new wxStaticText(panel, wxID_ANY, ("Serial Number:"), wxPoint(355, 45));
    serial->SetForegroundColour(wxColor(0, 255, 255));
    serial->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* repair = new wxStaticText(panel, wxID_ANY, ("Repair Number:"), wxPoint(355, 80));
    repair->SetForegroundColour(wxColor(0, 255, 255));
    repair->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

   

    wxStaticText* group = new wxStaticText(panel, wxID_ANY, ("Group:"), wxPoint(320, 175));
    group->SetForegroundColour(wxColor(0, 255, 255));
    group->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* case1 = new wxStaticText(panel, wxID_ANY, ("Case:"), wxPoint(430, 175));
    case1->SetForegroundColour(wxColor(0, 255, 255));
    case1->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* qty = new wxStaticText(panel, wxID_ANY, ("Quantity:"), wxPoint(525, 175));
    qty->SetForegroundColour(wxColor(0, 255, 255));
    qty->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    wxStaticText* desc = new wxStaticText(panel, wxID_ANY, ("Customer Notes:"), wxPoint(420, 235));
    desc->SetForegroundColour(wxColor(0, 255, 255));
    desc->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));


    wxBitmapButton* CreateNewRepairbutton = new wxBitmapButton(buttonPanel, idButtonCreateRepair, wxBitmap(wxT("save.png"),
        wxBITMAP_TYPE_PNG), wxPoint(20, 5), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage CreateNewRepairbuttonimgHover("saveh.png");
    CreateNewRepairbutton->SetBitmapHover(CreateNewRepairbuttonimgHover);
    wxImage CreateNewRepairbuttonimgPressed("savep.png");
    CreateNewRepairbutton->SetBitmapPressed(CreateNewRepairbuttonimgPressed);

    wxBitmapButton* CancelNewRepairbutton = new wxBitmapButton(buttonPanel, idButtonCancelRepair, wxBitmap(wxT("cancel.png"),
        wxBITMAP_TYPE_PNG), wxPoint(160, 5), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage CancelNewRepairbuttonimgHover("cancelh.png");
    CancelNewRepairbutton->SetBitmapHover(CancelNewRepairbuttonimgHover);
    wxImage CancelNewRepairbuttonimgPressed("cancelp.png");
    CancelNewRepairbutton->SetBitmapPressed(CancelNewRepairbuttonimgPressed);


    wxStaticText* LastRepairNumber = new wxStaticText(panel, wxID_ANY, ("Last Repair Number:"), wxPoint(300, 130));
    LastRepairNumber->SetForegroundColour(wxColor(0, 255, 255));
    LastRepairNumber->SetFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));

    m_mostRecentRepair = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(485, 125), wxSize(120, 40), wxTE_PROCESS_ENTER | wxTE_CENTRE | wxTE_READONLY);
    m_mostRecentRepair->SetBackgroundColour(wxColour(0, 30, 120));
    m_mostRecentRepair->SetForegroundColour(wxColour(0, 255, 255));
    m_mostRecentRepair->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));


    db = new wxSQLite3Database();
    wxString testDBName;

    testDBName = wxGetCwd() + wxT("//LogDatabase.db");
    db->Open(testDBName);
    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");
    wxSQLite3ResultSet Res3 = db->ExecuteQuery("SELECT  RepairNumber FROM nodeData ORDER BY RepairNumber DESC LIMIT 1;");
    m_mostRecentRepair->SetValue(Res3.GetAsString(0));
     mostRecentRepair = m_mostRecentRepair->GetValue();
    Res3.Finalize();
    db->Close();


    db = new wxSQLite3Database();

    
    testDBName = wxGetCwd() + wxT("//TemplateDatabase.db");
    db->Open(testDBName);
    
    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'Source' TEXT, unique(CompanyName,ContactName,Address));");
    
    wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT DISTINCT CompanyName FROM nodeData ORDER BY CompanyName ASC;");

    while (Res2.NextRow()) {

        m_templateArray.Add(Res2.GetAsString(0));

    }

    Res2.Finalize();
    
    db->Close();

    odcRepairTemplate = new wxOwnerDrawnComboBox(buttonPanel, wxID_ANY, "TEMPLATES",
        wxPoint(290, 11), wxSize(130, -1),
        m_templateArray,
        (long)0 | wxCB_READONLY);

    odcRepairTemplate->SetBackgroundColour(wxColour(228, 228, 240));

    
    if (imgNormal.IsOk() && imgPressed.IsOk() && imgHover.IsOk())
    {
        wxBitmap bmpNormal(imgNormal);
        wxBitmap bmpPressed(imgPressed);
        wxBitmap bmpHover(imgHover);
        odcRepairTemplate->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);

    }

    wxBitmapButton* NewRepairTemplatebutton = new wxBitmapButton(buttonPanel, idButtonRepairTemplate, wxBitmap(wxT("useTemplate.png"),
        wxBITMAP_TYPE_PNG), wxPoint(450, 5), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage NewRepairTemplatebuttonimgHover("useTemplateh.png");
    NewRepairTemplatebutton->SetBitmapHover(NewRepairTemplatebuttonimgHover);
    wxImage NewRepairTemplatebuttonimgPressed("useTemplatep.png");
    NewRepairTemplatebutton->SetBitmapPressed(NewRepairTemplatebuttonimgPressed);

    Centre();
    ShowModal();

    Destroy();

}





newRepairDialog::~newRepairDialog()
{
}





void newRepairDialog::onClickCreateRepair(wxCommandEvent& event)
{
    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%m/%d/%Y", localtime(&t));

    wxString nrpContact = m_contact->GetValue();
    wxString nrpCompany = m_company->GetValue();
    wxString nrpSerial = m_serial->GetValue();
    wxString nrpLastUpdate = s;
    wxString nrpDateRec = s;
    wxString nrpAddress = m_address->GetValue() + "," + m_city->GetValue() + "," + m_state->GetValue() + "," + m_zip->GetValue() + "," + m_country->GetValue();
    wxString nrpPhone = m_phone->GetValue();
    wxString nrpEmail = m_email->GetValue();
    wxString nrpModel = m_model->GetValue();
    wxString nrpRepair = m_repair->GetValue();
    wxString nrpTech = "";
    wxString nrpDepartment = "Shipping";
    wxString nrpStatus = "Receiving";
    wxString nrpDiscrepancy = m_multitext->GetValue();
    wxString nrpCorrectiveAction = " ";
    wxString nrpCaseYN = odccase->GetValue();
    wxString nrpQuantity = m_quantity->GetValue();
    wxString origin = "sensor";
    wxString history = "CREATED";
    wxString group = m_group->GetValue();
    wxString wWF = "";
    wxString LVL = "";

    if (nrpRepair == "")
    {
        wxString msg = _T("ERROR: No Input Detected For 'Repair Number' Please Try again");
        wxString info = _T("REPAIR NUMBER ERROR");
        wxMessageBox(msg,
            info,
            wxOK | wxICON_WARNING,
            this);
    }


    else if (nrpRepair == mostRecentRepair)
    {
        wxString msg = _T("ERROR: Repair Number Already Used Please Try again");
        wxString info = _T("REPAIR NUMBER ERROR");
        wxMessageBox(msg,
            info,
            wxOK | wxICON_WARNING,
            this);
    }

    else
    {

        db = new wxSQLite3Database();
        wxString testDBName;

        testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");
        db->Open(testDBName);
        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");
        db->ExecuteUpdate(wxString::Format(_("INSERT INTO nodeData (ContactName,CompanyName,SensorSerialNumber,DateSent,DateReceived,Address,PhoneNumber,EmailAddress,ModelNumber,RepairNumber,Department,Technician,Status,Discrepancy,CorrectiveAction,CaseYN,Quantity,GroupNumber,WhatWeFound,Level) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')"), nrpContact, nrpCompany, nrpSerial, nrpLastUpdate, nrpDateRec, nrpAddress, nrpPhone, nrpEmail, nrpModel, nrpRepair, nrpDepartment, nrpTech, nrpStatus, nrpDiscrepancy, nrpCorrectiveAction, nrpCaseYN, nrpQuantity, group, wWF, LVL));
        db->Close();


        testDBName = wxGetCwd() + wxT("//TemplateDatabase.db");
        db->Open(testDBName);
        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'Source' TEXT, unique(CompanyName,ContactName,Address));");
        db->ExecuteUpdate(wxString::Format(_("INSERT OR REPLACE INTO nodeData (ContactName,CompanyName,Address,PhoneNumber,EmailAddress,Source) VALUES ('%s','%s','%s','%s','%s','%s')"), nrpContact, nrpCompany, nrpAddress, nrpPhone, nrpEmail, origin));

        db->Close();


        testDBName = wxGetCwd() + wxT("//LogDatabase.db");
        db->Open(testDBName);
        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");
        db->ExecuteUpdate(wxString::Format(_("INSERT INTO nodeData (ContactName,CompanyName,SensorSerialNumber,DateSent,DateReceived,Address,PhoneNumber,EmailAddress,ModelNumber,RepairNumber,Department,Technician,Status,Discrepancy,CorrectiveAction,CaseYN,Quantity,Source,History,GroupNumber,Chronology) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s', datetime('now', 'localtime'))"), nrpContact, nrpCompany, nrpSerial, nrpLastUpdate, nrpDateRec, nrpAddress, nrpPhone, nrpEmail, nrpModel, nrpRepair, nrpDepartment, nrpTech, nrpStatus, nrpDiscrepancy, nrpCorrectiveAction, nrpCaseYN, nrpQuantity, origin, history, group));
        db->Close();


        wxString msg = _T("Repair Entry For: ") + nrpContact + _T("(") + nrpCompany + _T(") : ") + nrpRepair + _T(" Successfully Created");
        wxString info = _T("Repair Entry Created");
        wxMessageBox(msg,
            info,
            wxOK | wxICON_INFORMATION,
            this);




        wxString rpFormLevel = "";
        wxString repairFile = nrpRepair;

        db = new wxSQLite3Database();

        std::ofstream tf;
        tf.open("PdfGenerator_VB//Temp//name.txt", std::ios::out | std::ios::app);
        tf.close();
        tf.open("PdfGenerator_VB//Temp//name.txt", std::ios::out | std::ios::app);

        if (tf.is_open())
        {
            tf << repairFile;

            tf.close();
        }


        testDBName = wxGetCwd() + wxT("//LogDatabase.db");
        db->Open(testDBName);
        db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");
        db->Close();
        db->Open(testDBName);
        wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT DateReceived, CompanyName, ContactName, EmailAddress, PhoneNumber, Address, Discrepancy FROM nodeData WHERE RepairNumber ='" + repairFile + "' ORDER BY rowid ASC LIMIT 1;");

        nrpDateRec = Res.GetAsString(0);
        nrpCompany = Res.GetAsString(1);
        nrpContact = Res.GetAsString(2);
        nrpEmail = Res.GetAsString(3);
        nrpPhone = Res.GetAsString(4);
        nrpAddress = Res.GetAsString(5);
        nrpDiscrepancy = Res.GetAsString(6);

        Res.Finalize();
        db->Close();

        //rpFormAddress.erase(remove(rpFormAddress.begin(), rpFormAddress.end(), ','), rpFormAddress.end());
        string addressAltered = nrpAddress;
        replace(addressAltered.begin(), addressAltered.end(), ',', '/');

        string notesAltered = nrpDiscrepancy;
        replace(notesAltered.begin(), notesAltered.end(), '\n', ' ');


        std::ofstream fs;
        fs.open("PdfGenerator_VB//Temp//tempForm.csv", std::ios::out | std::ios::app);
        fs.close();
        fs.open("PdfGenerator_VB//Temp//tempForm.csv", std::ios::out | std::ios::app);

        if (fs.is_open())
        {
            fs << nrpDateRec + ",";
            fs << nrpCompany + ",";
            fs << nrpContact + ",";
            fs << nrpEmail + ",";
            fs << nrpPhone + ",";
            fs << addressAltered + ",";
            fs << notesAltered + ".\n";
            fs.close();
        }


        db->Open(testDBName);

        wxSQLite3ResultSet  Res6 = db->ExecuteQuery("SELECT RepairNumber,Quantity,ModelNumber,SensorSerialNumber,CaseYN,Level FROM nodeData WHERE History = 'CREATED' AND DateReceived = '" + nrpDateRec + "' AND CompanyName = '" + nrpCompany + "' AND ContactName = '" + nrpContact + "' AND Address = '" + nrpAddress + "'   ORDER BY Chronology ASC;");



        std::vector<wxString> LVLVector;
        int repairCount = 0;

        while (Res6.NextRow())
        {
            LVLVector.push_back(Res6.GetAsString(0));
            repairCount++;
        }


        int count = 1;
        while (Res6.NextRow())
        {
            nrpRepair = Res6.GetAsString(0);
            nrpQuantity = Res6.GetAsString(1);
            nrpModel = Res6.GetAsString(2);
            nrpSerial = Res6.GetAsString(3);
            nrpCaseYN = Res6.GetAsString(4);
            rpFormLevel = Res6.GetAsString(5);

            string levelAltered = rpFormLevel;
            replace(levelAltered.begin(), levelAltered.end(), ',', '/');

            fs.open("PdfGenerator_VB//Temp//tempForm.csv", std::ios::out | std::ios::app);
            if (fs.is_open())
            {
                fs << nrpRepair + ",";
                fs << nrpQuantity + ",";
                fs << nrpModel + ",";
                fs << nrpSerial + ",";
                fs << nrpCaseYN + ",";
                fs << levelAltered + ",.\n";
                fs.close();
            }
        }


        Res6.Finalize();
        db->Close();

        std::system("\\PdfGenerator_VB\\PdfGenerator_VB.exe");





        Destroy();
    }
}




void newRepairDialog::onClickCancelRepair(wxCommandEvent& event)
{
    Destroy();
}





void newRepairDialog::onClickGetRepairTemplate(wxCommandEvent& event)
{
    std::string fullAddressString;
    wxString templateChoice = odcRepairTemplate->GetValue();

    db = new wxSQLite3Database();

    wxString testDBName;

    testDBName = wxGetCwd() + wxT("//TemplateDatabase.db");

    db->Open(testDBName);

    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'Source' TEXT, unique(CompanyName,ContactName,Address));");

    wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT DISTINCT ContactName, CompanyName, Address, PhoneNumber, EmailAddress  FROM nodeData WHERE CompanyName = '" + templateChoice + "' ORDER BY rowid ASC  LIMIT 1;");

    while (Res2.NextRow()) {

        m_contact->SetValue(Res2.GetAsString(0));
        m_company->SetValue(Res2.GetAsString(1));

        fullAddressString = Res2.GetAsString(2);

        m_phone->SetValue(Res2.GetAsString(3));
        m_email->SetValue(Res2.GetAsString(4));

    }

    Res2.Finalize();

    db->Close();



    string my_str = fullAddressString;
    vector<string> result;
    stringstream s_stream(my_str); //create string stream from the string
    while (s_stream.good()) {
        string substr;
        getline(s_stream, substr, ','); //get first string delimited by comma
        result.push_back(substr);
    }

    wxString addressHolder = result.at(0);
    wxString cityHolder = result.at(1);
    wxString stateHolder = result.at(2);
    wxString zipHolder = result.at(3);
    wxString countryHolder = result.at(4);


    m_address->SetValue(addressHolder);
    m_city->SetValue(cityHolder);
    m_state->SetValue(stateHolder);
    m_zip->SetValue(zipHolder);
    m_country->SetValue(countryHolder);

}




updateRepairDialog::updateRepairDialog(const wxString& title)
    : wxDialog(NULL, -1, ("Update Existing Repair"), wxPoint(1100, 500), wxSize(1200, 764))
{

    wxPanel* parentPanel = new wxPanel(this, -1, wxPoint(-1, -1), wxSize(1200, 764));
    parentPanel->SetBackgroundColour(wxColor(100, 100, 200));

    wxPanel* panel = new wxPanel(parentPanel, -1, wxPoint(-1, 41), wxSize(585, 245));
    panel->SetBackgroundColour(wxColor(200, 200, 200));




    wxPanel* updateRepairTitlePanel = new wxPanel(parentPanel, wxID_ANY,
        wxDefaultPosition, wxSize(1185, 40), wxSUNKEN_BORDER);
    updateRepairTitlePanel->SetBackgroundColour(wxColour(28, 28, 32));


    wxStaticText* updateRepairTitle = new wxStaticText(updateRepairTitlePanel, wxID_ANY, ("Edit Data in Desired Fields, Then Click 'Update Repair' to Save"), wxPoint(320, 5), wxSize(-1, -1), wxTE_CENTRE);
    updateRepairTitle->SetForegroundColour(wxColor(0, 188, 255));
    updateRepairTitle->SetFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));


    updateRepairDataGrid = new wxGrid(panel, wxID_ANY,
        wxPoint(-1, -1), wxSize(590, 245));

    updateRepairDataGrid->CreateGrid(8, 2);

    updateRepairDataGrid->SetGridLineColour(wxColor(0, 173, 234));
    updateRepairDataGrid->SetDefaultCellTextColour(wxColor(0, 255, 255));
    updateRepairDataGrid->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    updateRepairDataGrid->Refresh();


    updateRepairDataGrid->EnableGridLines(true);
    updateRepairDataGrid->DisableDragColSize();
    updateRepairDataGrid->DisableDragRowSize();
    updateRepairDataGrid->EnableDragGridSize(false);
    updateRepairDataGrid->SetCellHighlightPenWidth(0);
    updateRepairDataGrid->SetCellHighlightROPenWidth(0);
    updateRepairDataGrid->SetSelectionBackground(updateRepairDataGrid->GetDefaultCellBackgroundColour());
    updateRepairDataGrid->SetSelectionForeground(updateRepairDataGrid->GetDefaultCellTextColour());
    updateRepairDataGrid->SetRowLabelSize(0);
    updateRepairDataGrid->SetColLabelSize(0);

    updateRepairDataGrid->SetDefaultCellFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid->SetDefaultRowSize(30);
    updateRepairDataGrid->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_CENTER);

    updateRepairDataGrid->SetColSize(0, 190);
    updateRepairDataGrid->SetColSize(1, 390);




    int cbgc;
    for (cbgc = 0; cbgc < 21;)
    {
        updateRepairDataGrid->SetCellBackgroundColour(cbgc, 1, wxColour(230, 230, 230));
        updateRepairDataGrid->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid->SetReadOnly(cbgc, 0);
        updateRepairDataGrid->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
        updateRepairDataGrid->SetCellBackgroundColour(cbgc, 1, wxColour(220, 240, 255));
        updateRepairDataGrid->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid->SetReadOnly(cbgc, 0);
        updateRepairDataGrid->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
    }

    updateRepairDataGrid->SetCellValue(0, 0, " ID #:");
    updateRepairDataGrid->SetCellValue(1, 0, " Contact:");
    updateRepairDataGrid->SetCellValue(2, 0, " Company:");
    updateRepairDataGrid->SetCellValue(3, 0, " Address:");
    updateRepairDataGrid->SetCellValue(4, 0, " Phone Number:");
    updateRepairDataGrid->SetCellValue(5, 0, " Email Address:");
    updateRepairDataGrid->SetCellValue(6, 0, " Last Update:");
    updateRepairDataGrid->SetCellValue(7, 0, " Date Received:");



    updateRepairDataGrid->SetReadOnly(0, 1);
    updateRepairDataGrid->SetReadOnly(6, 1);
    updateRepairDataGrid->SetReadOnly(7, 1);

    // updateRepairDataGrid->SetCellRenderer(15, 1, new wxGridCellAutoWrapStringRenderer);
    // updateRepairDataGrid->SetCellRenderer(16, 1, new wxGridCellAutoWrapStringRenderer);



    // updateRepairDataGrid->SetCellEditor(11, 1, new wxGridCellChoiceEditor(WXSIZEOF(deptChoices), deptChoices));

    // updateRepairDataGrid->SetCellEditor(13, 1, new wxGridCellChoiceEditor(WXSIZEOF(statusChoices), statusChoices));

   //  updateRepairDataGrid->SetCellEditor(17, 1, new wxGridCellChoiceEditor(WXSIZEOF(caseChoices), caseChoices));

    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT UpdateID FROM sensorUpdateData;");

    testInput = Res.GetAsString(0);


    Res.Finalize();



    db->Close();




    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    db->Open(testDBName);

    wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT Id, ContactName, CompanyName, Address, PhoneNumber, EmailAddress, DateSent, DateReceived FROM nodeData WHERE RepairNumber = '" + testInput + "'; ");



    while (Res2.NextRow()) {

        for (int i = 0; i < 8; i++) {

            updateRepairDataGrid->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    Res2.Finalize();

    db->Close();


    ///DEPT GRID///

    wxPanel* panel2 = new wxPanel(parentPanel, -1, wxPoint(-1, 305), wxSize(585, 245));
    panel2->SetBackgroundColour(wxColor(100, 100, 100));

    updateRepairDataGrid2 = new wxGrid(panel2, wxID_ANY,
        wxPoint(-1, -1), wxSize(585, 245));

    updateRepairDataGrid2->CreateGrid(8, 2);

    updateRepairDataGrid2->SetGridLineColour(wxColor(0, 173, 234));
    updateRepairDataGrid2->SetDefaultCellTextColour(wxColor(0, 255, 255));
    updateRepairDataGrid2->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    updateRepairDataGrid2->Refresh();


    updateRepairDataGrid2->EnableGridLines(true);
    updateRepairDataGrid2->DisableDragColSize();
    updateRepairDataGrid2->DisableDragRowSize();
    updateRepairDataGrid2->EnableDragGridSize(false);
    updateRepairDataGrid2->SetCellHighlightPenWidth(0);
    updateRepairDataGrid2->SetCellHighlightROPenWidth(0);
    updateRepairDataGrid2->SetSelectionBackground(updateRepairDataGrid2->GetDefaultCellBackgroundColour());
    updateRepairDataGrid2->SetSelectionForeground(updateRepairDataGrid2->GetDefaultCellTextColour());
    updateRepairDataGrid2->SetRowLabelSize(0);
    updateRepairDataGrid2->SetColLabelSize(0);

    updateRepairDataGrid2->SetDefaultCellFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid2->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid2->SetDefaultRowSize(30);
    updateRepairDataGrid2->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_CENTER);

    updateRepairDataGrid2->SetColSize(0, 190);
    updateRepairDataGrid2->SetColSize(1, 390);

    // int cbgc;
    for (cbgc = 0; cbgc < 21;)
    {
        updateRepairDataGrid2->SetCellBackgroundColour(cbgc, 1, wxColour(230, 230, 230));
        updateRepairDataGrid2->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid2->SetReadOnly(cbgc, 0);
        updateRepairDataGrid2->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
        updateRepairDataGrid2->SetCellBackgroundColour(cbgc, 1, wxColour(220, 240, 255));
        updateRepairDataGrid2->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid2->SetReadOnly(cbgc, 0);
        updateRepairDataGrid2->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
    }



    updateRepairDataGrid2->SetCellValue(0, 0, " Repair Number:");
    updateRepairDataGrid2->SetCellValue(1, 0, " Model Number:");
    updateRepairDataGrid2->SetCellValue(2, 0, " Serial Number:");
    updateRepairDataGrid2->SetCellValue(3, 0, " Department:");
    updateRepairDataGrid2->SetCellValue(4, 0, " Technician:");
  //  updateRepairDataGrid2->SetCellValue(5, 0, " Status:");
    updateRepairDataGrid2->SetCellValue(5, 0, " Case:");
    updateRepairDataGrid2->SetCellValue(6, 0, " Quantity:");
    updateRepairDataGrid2->SetCellValue(7, 0, " Group Number:");


    updateRepairDataGrid2->SetCellAlignment(3, 1, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid2->SetCellAlignment(5, 1, wxALIGN_CENTRE, wxALIGN_CENTRE);
   // updateRepairDataGrid2->SetCellAlignment(6, 1, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid2->SetReadOnly(0, 1);


    const wxString deptChoices[] =
    {
        "Analog",
        "Calibration",
        "Digital",
        "Metrology",
        "Machine Room",
        "Miscellaneous",
        "Sensors",
        "Shipping",
    };



    const wxString caseChoices[] =
    {
        "YES",
        "NO",
    };

    const wxString RepairLevelsTC[] =
    {
        "Thermocouple: Replaced",
        "Thermocouple: Sharpened",
        "Thermocouple: Welded",
        "Thermocouple: Straightened",
        "Thermocouple: Adjusted",
        "Thermocouple: Cleaned",
        "Other"  
    };

    const wxString RepairLevelsL[] =
    {
        "Lead: Cleaned",
        "Lead: Straightened", 
        "Other"   
    };

    const wxString RepairLevelsT[] =
    {
        "Termination: Cleaned",
        "Termination: Adjusted",
        "Termination: Replace Plugs",       
        "Other",
        "Not Repairable/Replacement recommended"
    };


    updateRepairDataGrid2->SetCellEditor(3, 1, new wxGridCellChoiceEditor(WXSIZEOF(deptChoices), deptChoices));

    //updateRepairDataGrid2->SetCellEditor(5, 1, new wxGridCellChoiceEditor(WXSIZEOF(statusChoices), statusChoices));

    updateRepairDataGrid2->SetCellEditor(5, 1, new wxGridCellChoiceEditor(WXSIZEOF(caseChoices), caseChoices));




    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    Res = db->ExecuteQuery("SELECT UpdateID FROM sensorUpdateData;");

    testInput = Res.GetAsString(0);


    Res.Finalize();

   // db->ExecuteQuery("PRAGMA foreign_keys = OFF;");
   // db->ExecuteUpdate("DROP TABLE sensorUpdateData;");
   // db->ExecuteQuery("PRAGMA foreign_keys = ON;");

    db->Close();




    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    db->Open(testDBName);

    Res2 = db->ExecuteQuery("SELECT RepairNumber, ModelNumber, SensorSerialNumber, Department, Technician, CaseYN, Quantity, GroupNumber FROM nodeData WHERE RepairNumber = '" + testInput + "'; ");



    while (Res2.NextRow()) {

        for (int i = 0; i < 8; i++) {

            updateRepairDataGrid2->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    Res2.Finalize();

    db->Close();

    ///STATUS///


    wxPanel* panelSTAT = new wxPanel(parentPanel, -1, wxPoint(-1, 570), wxSize(585, 40));
    panelSTAT->SetBackgroundColour(wxColor(200, 100, 100));

    updateRepairDataGridSTAT = new wxGrid(panelSTAT, wxID_ANY,
        wxPoint(-1, -1), wxSize(585, 40));

    updateRepairDataGridSTAT->CreateGrid(1, 2);

    updateRepairDataGridSTAT->SetGridLineColour(wxColor(255, 51, 51));
    updateRepairDataGridSTAT->SetDefaultCellTextColour(wxColor(255, 51, 51));
    updateRepairDataGridSTAT->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    updateRepairDataGridSTAT->Refresh();


    updateRepairDataGridSTAT->EnableGridLines(true);
    updateRepairDataGridSTAT->DisableDragColSize();
    updateRepairDataGridSTAT->DisableDragRowSize();
    updateRepairDataGridSTAT->EnableDragGridSize(false);
    updateRepairDataGridSTAT->SetCellHighlightPenWidth(0);
    updateRepairDataGridSTAT->SetCellHighlightROPenWidth(0);
    updateRepairDataGridSTAT->SetSelectionBackground(updateRepairDataGridSTAT->GetDefaultCellBackgroundColour());
    updateRepairDataGridSTAT->SetSelectionForeground(updateRepairDataGridSTAT->GetDefaultCellTextColour());
    updateRepairDataGridSTAT->SetRowLabelSize(0);
    updateRepairDataGridSTAT->SetColLabelSize(0);

    updateRepairDataGridSTAT->SetDefaultCellFont(wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGridSTAT->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGridSTAT->SetDefaultRowSize(35);
    updateRepairDataGridSTAT->SetCellAlignment(0, 0, wxALIGN_LEFT, wxALIGN_CENTER);

    updateRepairDataGridSTAT->SetColSize(0, 190);
    updateRepairDataGridSTAT->SetColSize(1, 390);

    // int cbgc;
    for (cbgc = 0; cbgc < 21;)
    {
        updateRepairDataGridSTAT->SetCellBackgroundColour(cbgc, 1, wxColour(230, 230, 230));
        updateRepairDataGridSTAT->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGridSTAT->SetReadOnly(cbgc, 0);
        updateRepairDataGridSTAT->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
        updateRepairDataGridSTAT->SetCellBackgroundColour(cbgc, 1, wxColour(220, 240, 255));
        updateRepairDataGridSTAT->SetCellTextColour(cbgc, 1, wxColour(255, 51, 51));
        updateRepairDataGridSTAT->SetReadOnly(cbgc, 0);
        updateRepairDataGridSTAT->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
    }



    updateRepairDataGridSTAT->SetCellValue(0, 0, " Status:");

    updateRepairDataGridSTAT->SetCellAlignment(0, 1, wxALIGN_CENTRE, wxALIGN_CENTRE);



    const wxString statusChoices[] =
    {
         "Evaluating",
        "Waiting On Office",
        "Working",
        "Calibrating",
        "Finished",
        "Shipped",
    };



    updateRepairDataGridSTAT->SetCellEditor(0, 1, new wxGridCellChoiceEditor(WXSIZEOF(statusChoices), statusChoices));





    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    Res = db->ExecuteQuery("SELECT UpdateID FROM sensorUpdateData;");

    testInput = Res.GetAsString(0);


    Res.Finalize();

    //  db->ExecuteQuery("PRAGMA foreign_keys = OFF;");
    //  db->ExecuteUpdate("DROP TABLE sensorUpdateData;");
    //  db->ExecuteQuery("PRAGMA foreign_keys = ON;");

    db->Close();




    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    db->Open(testDBName);

    Res2 = db->ExecuteQuery("SELECT Status FROM nodeData WHERE RepairNumber = '" + testInput + "'; ");



    while (Res2.NextRow()) {

        for (int i = 0; i < 1; i++) {

            updateRepairDataGridSTAT->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    Res2.Finalize();

    db->Close();





    ///CUSTOMER NOTES///

    wxPanel* panel3 = new wxPanel(parentPanel, -1, wxPoint(600, 40), wxSize(585, 160));
    panel3->SetBackgroundColour(wxColor(100, 100, 160));

    updateRepairDataGrid3 = new wxGrid(panel3, wxID_ANY,
        wxPoint(-1, -1), wxSize(585, 200));

    updateRepairDataGrid3->CreateGrid(1, 2);

    updateRepairDataGrid3->SetGridLineColour(wxColor(0, 173, 234));
    updateRepairDataGrid3->SetDefaultCellTextColour(wxColor(0, 255, 255));
    updateRepairDataGrid3->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    updateRepairDataGrid3->Refresh();


    updateRepairDataGrid3->EnableGridLines(true);
    updateRepairDataGrid3->DisableDragColSize();
    updateRepairDataGrid3->DisableDragRowSize();
    updateRepairDataGrid3->EnableDragGridSize(false);
    updateRepairDataGrid3->SetCellHighlightPenWidth(0);
    updateRepairDataGrid3->SetCellHighlightROPenWidth(0);
    updateRepairDataGrid3->SetSelectionBackground(updateRepairDataGrid3->GetDefaultCellBackgroundColour());
    updateRepairDataGrid3->SetSelectionForeground(updateRepairDataGrid3->GetDefaultCellTextColour());
    updateRepairDataGrid3->SetRowLabelSize(0);
    updateRepairDataGrid3->SetColLabelSize(0);

    updateRepairDataGrid3->SetDefaultCellFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid3->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid3->SetDefaultRowSize(155);
    updateRepairDataGrid3->SetCellAlignment(0, 0, wxALIGN_TOP, wxALIGN_TOP);


   // updateRepairDataGrid3->SetCellAlignment(0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid3->SetCellRenderer(0, 1, new wxGridCellAutoWrapStringRenderer);
    updateRepairDataGrid3->SetCellEditor(0, 1, new wxGridCellAutoWrapStringEditor);


    updateRepairDataGrid3->SetColSize(0, 160);
    updateRepairDataGrid3->SetColSize(1, 420);

    // int cbgc;
    for (cbgc = 0; cbgc < 1;)
    {
        updateRepairDataGrid3->SetCellBackgroundColour(cbgc, 1, wxColour(230, 230, 230));
        updateRepairDataGrid3->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid3->SetReadOnly(cbgc, 0);
        updateRepairDataGrid3->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
        updateRepairDataGrid3->SetCellBackgroundColour(cbgc, 1, wxColour(220, 240, 255));
        updateRepairDataGrid3->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid3->SetReadOnly(cbgc, 0);
        updateRepairDataGrid3->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
    }


    updateRepairDataGrid3->SetCellValue(0, 0, " Customer Notes:");


    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    Res = db->ExecuteQuery("SELECT UpdateID FROM sensorUpdateData;");

    testInput = Res.GetAsString(0);


    Res.Finalize();

    db->ExecuteQuery("PRAGMA foreign_keys = OFF;");
    db->ExecuteUpdate("DROP TABLE sensorUpdateData;");
    db->ExecuteQuery("PRAGMA foreign_keys = ON;");

    db->Close();

    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    db->Open(testDBName);

    Res2 = db->ExecuteQuery("SELECT Discrepancy FROM nodeData WHERE RepairNumber = '" + testInput + "'; ");




    while (Res2.NextRow()) {

        for (int i = 0; i < 1; i++) {

            updateRepairDataGrid3->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    Res2.Finalize();

    db->Close();

    /// REPAIR DROPDOWN \\\

    wxPanel* panel6 = new wxPanel(parentPanel, -1, wxPoint(600, 224), wxSize(493, 40));
    panel6->SetBackgroundColour(wxColor(100, 100, 200));

    updateRepairDataGrid6 = new wxGrid(panel6, wxID_ANY,
        wxPoint(-1, -1), wxSize(493, 40));

    updateRepairDataGrid6->CreateGrid(1, 1);
    updateRepairDataGrid6->SetDefaultCellTextColour(wxColor(0, 0, 0));
    updateRepairDataGrid6->SetDefaultCellBackgroundColour(wxColor(230, 230, 230));
    updateRepairDataGrid6->Refresh();
    updateRepairDataGrid6->DisableDragColSize();
    updateRepairDataGrid6->DisableDragRowSize();
    updateRepairDataGrid6->EnableDragGridSize(false);
    updateRepairDataGrid6->SetCellHighlightPenWidth(0);
    updateRepairDataGrid6->SetCellHighlightROPenWidth(0);
    updateRepairDataGrid6->SetSelectionBackground(updateRepairDataGrid6->GetDefaultCellBackgroundColour());
    updateRepairDataGrid6->SetSelectionForeground(updateRepairDataGrid6->GetDefaultCellTextColour());
    updateRepairDataGrid6->SetRowLabelSize(0);
    updateRepairDataGrid6->SetColLabelSize(0);
    updateRepairDataGrid6->SetDefaultCellFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid6->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid6->SetDefaultRowSize(40);
    updateRepairDataGrid6->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);
    updateRepairDataGrid6->SetCellAlignment(0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid6->SetCellRenderer(0, 0, new wxGridCellAutoWrapStringRenderer);
    updateRepairDataGrid6->SetCellEditor(0, 0, new wxGridCellAutoWrapStringEditor);
    updateRepairDataGrid6->SetColSize(0, 493);
    updateRepairDataGrid6->SetCellEditor(0, 0, new wxGridCellChoiceEditor(WXSIZEOF(RepairLevelsTC), RepairLevelsTC));
    updateRepairDataGrid6->SetCellValue(0, 0, "THERMOCOUPLE:");


    wxPanel* panel9 = new wxPanel(parentPanel, -1, wxPoint(600, 279), wxSize(493, 40));
    panel9->SetBackgroundColour(wxColor(100, 100, 200));

    updateRepairDataGrid7 = new wxGrid(panel9, wxID_ANY,
        wxPoint(-1, -1), wxSize(493, 40));

    updateRepairDataGrid7->CreateGrid(1, 1);
    updateRepairDataGrid7->SetDefaultCellTextColour(wxColor(0, 0, 0));
    updateRepairDataGrid7->SetDefaultCellBackgroundColour(wxColor(230, 230, 230));
    updateRepairDataGrid7->Refresh();
    updateRepairDataGrid7->DisableDragColSize();
    updateRepairDataGrid7->DisableDragRowSize();
    updateRepairDataGrid7->EnableDragGridSize(false);
    updateRepairDataGrid7->SetCellHighlightPenWidth(0);
    updateRepairDataGrid7->SetCellHighlightROPenWidth(0);
    updateRepairDataGrid7->SetSelectionBackground(updateRepairDataGrid7->GetDefaultCellBackgroundColour());
    updateRepairDataGrid7->SetSelectionForeground(updateRepairDataGrid7->GetDefaultCellTextColour());
    updateRepairDataGrid7->SetRowLabelSize(0);
    updateRepairDataGrid7->SetColLabelSize(0);
    updateRepairDataGrid7->SetDefaultCellFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid7->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid7->SetDefaultRowSize(40);
    updateRepairDataGrid7->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);
    updateRepairDataGrid7->SetCellAlignment(0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid7->SetCellRenderer(0, 0, new wxGridCellAutoWrapStringRenderer);
    updateRepairDataGrid7->SetCellEditor(0, 0, new wxGridCellAutoWrapStringEditor);
    updateRepairDataGrid7->SetColSize(0, 493);
    updateRepairDataGrid7->SetCellEditor(0, 0, new wxGridCellChoiceEditor(WXSIZEOF(RepairLevelsL), RepairLevelsL));
    updateRepairDataGrid7->SetCellValue(0, 0, "LEAD:");


    wxPanel* panel8 = new wxPanel(parentPanel, -1, wxPoint(600, 334), wxSize(493, 40));
    panel8->SetBackgroundColour(wxColor(100, 100, 200));

    updateRepairDataGrid8 = new wxGrid(panel8, wxID_ANY,
        wxPoint(-1, -1), wxSize(493, 40));

    updateRepairDataGrid8->CreateGrid(1, 1);
    updateRepairDataGrid8->SetDefaultCellTextColour(wxColor(0, 0, 0));
    updateRepairDataGrid8->SetDefaultCellBackgroundColour(wxColor(230, 230, 230));
    updateRepairDataGrid8->Refresh();
    updateRepairDataGrid8->DisableDragColSize();
    updateRepairDataGrid8->DisableDragRowSize();
    updateRepairDataGrid8->EnableDragGridSize(false);
    updateRepairDataGrid8->SetCellHighlightPenWidth(0);
    updateRepairDataGrid8->SetCellHighlightROPenWidth(0);
    updateRepairDataGrid8->SetSelectionBackground(updateRepairDataGrid8->GetDefaultCellBackgroundColour());
    updateRepairDataGrid8->SetSelectionForeground(updateRepairDataGrid8->GetDefaultCellTextColour());
    updateRepairDataGrid8->SetRowLabelSize(0);
    updateRepairDataGrid8->SetColLabelSize(0);
    updateRepairDataGrid8->SetDefaultCellFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid8->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid8->SetDefaultRowSize(40);
    updateRepairDataGrid8->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);
    updateRepairDataGrid8->SetCellAlignment(0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid8->SetCellRenderer(0, 0, new wxGridCellAutoWrapStringRenderer);
    updateRepairDataGrid8->SetCellEditor(0, 0, new wxGridCellAutoWrapStringEditor);
    updateRepairDataGrid8->SetColSize(0, 493);
    updateRepairDataGrid8->SetCellEditor(0, 0, new wxGridCellChoiceEditor(WXSIZEOF(RepairLevelsT), RepairLevelsT));
    updateRepairDataGrid8->SetCellValue(0, 0, "TERMINATION:");

    wxBitmapButton* CreateAddbutton = new wxBitmapButton(parentPanel, idButtonAddNoteTC, wxBitmap(wxT("add.png"),
        wxBITMAP_TYPE_PNG), wxPoint(1097, 220), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage CreateAddbuttonimgHover("addh.png");
    CreateAddbutton->SetBitmapHover(CreateAddbuttonimgHover);
    wxImage CreateAddbuttonimgPressed("addp.png");
    CreateAddbutton->SetBitmapPressed(CreateAddbuttonimgPressed);

    wxBitmapButton* CreateAddbutton2 = new wxBitmapButton(parentPanel, idButtonAddNoteL, wxBitmap(wxT("add.png"),
        wxBITMAP_TYPE_PNG), wxPoint(1097, 275), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage CreateAddbuttonimgHover2("addh.png");
    CreateAddbutton2->SetBitmapHover(CreateAddbuttonimgHover2);
    wxImage CreateAddbuttonimgPressed2("addp.png");
    CreateAddbutton2->SetBitmapPressed(CreateAddbuttonimgPressed2);

    wxBitmapButton* CreateAddbutton3 = new wxBitmapButton(parentPanel, idButtonAddNoteT, wxBitmap(wxT("add.png"),
        wxBITMAP_TYPE_PNG), wxPoint(1097, 330), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage CreateAddbuttonimgHover3("addh.png");
    CreateAddbutton3->SetBitmapHover(CreateAddbuttonimgHover3);
    wxImage CreateAddbuttonimgPressed3("addp.png");
    CreateAddbutton3->SetBitmapPressed(CreateAddbuttonimgPressed3);



    /// WHAT WE FOUND \\\




    wxPanel* panel4 = new wxPanel(parentPanel, -1, wxPoint(600, 387), wxSize(585, 160));
    panel4->SetBackgroundColour(wxColor(100, 100, 200));

    updateRepairDataGrid4 = new wxGrid(panel4, wxID_ANY,
        wxPoint(-1, -1), wxSize(585, 160));

    updateRepairDataGrid4->CreateGrid(1, 2);

    updateRepairDataGrid4->SetGridLineColour(wxColor(0, 173, 234));
    updateRepairDataGrid4->SetDefaultCellTextColour(wxColor(0, 255, 255));
    updateRepairDataGrid4->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    updateRepairDataGrid4->Refresh();


    updateRepairDataGrid4->EnableGridLines(true);
    updateRepairDataGrid4->DisableDragColSize();
    updateRepairDataGrid4->DisableDragRowSize();
    updateRepairDataGrid4->EnableDragGridSize(false);
    updateRepairDataGrid4->SetCellHighlightPenWidth(0);
    updateRepairDataGrid4->SetCellHighlightROPenWidth(0);
    updateRepairDataGrid4->SetSelectionBackground(updateRepairDataGrid4->GetDefaultCellBackgroundColour());
    updateRepairDataGrid4->SetSelectionForeground(updateRepairDataGrid4->GetDefaultCellTextColour());
    updateRepairDataGrid4->SetRowLabelSize(0);
    updateRepairDataGrid4->SetColLabelSize(0);

    updateRepairDataGrid4->SetDefaultCellFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid4->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid4->SetDefaultRowSize(155);
    updateRepairDataGrid4->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);


    updateRepairDataGrid4->SetCellAlignment(0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid4->SetCellRenderer(0, 1, new wxGridCellAutoWrapStringRenderer);
    updateRepairDataGrid4->SetCellEditor(0, 1, new wxGridCellAutoWrapStringEditor);


    updateRepairDataGrid4->SetColSize(0, 160);
    updateRepairDataGrid4->SetColSize(1, 420);

    // int cbgc;
    for (cbgc = 0; cbgc < 1;)
    {
        updateRepairDataGrid4->SetCellBackgroundColour(cbgc, 1, wxColour(230, 230, 230));
        updateRepairDataGrid4->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid4->SetReadOnly(cbgc, 0);
        updateRepairDataGrid4->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
        updateRepairDataGrid4->SetCellBackgroundColour(cbgc, 1, wxColour(220, 240, 255));
        updateRepairDataGrid4->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid4->SetReadOnly(cbgc, 0);
        updateRepairDataGrid4->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
    }

    updateRepairDataGrid4->SetCellFont(0, 1, wxFont(14, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid4->SetCellValue(0, 0, " What We Found:");

    db->Open(testDBName);

    Res2 = db->ExecuteQuery("SELECT WhatWeFound FROM nodeData WHERE RepairNumber = '" + testInput + "'; ");



    while (Res2.NextRow()) {

        for (int i = 0; i < 1; i++) {

            updateRepairDataGrid4->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    Res2.Finalize();

    db->Close();

    /// NOTES \\\




    wxPanel* panel5 = new wxPanel(parentPanel, -1, wxPoint(600, 565), wxSize(585, 160));
    panel5->SetBackgroundColour(wxColor(100, 100, 200));

    updateRepairDataGrid5 = new wxGrid(panel5, wxID_ANY,
        wxPoint(-1, -1), wxSize(585, 160));

    updateRepairDataGrid5->CreateGrid(1, 2);

    updateRepairDataGrid5->SetGridLineColour(wxColor(0, 173, 234));
    updateRepairDataGrid5->SetDefaultCellTextColour(wxColor(0, 255, 255));
    updateRepairDataGrid5->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    updateRepairDataGrid5->Refresh();


    updateRepairDataGrid5->EnableGridLines(true);
    updateRepairDataGrid5->DisableDragColSize();
    updateRepairDataGrid5->DisableDragRowSize();
    updateRepairDataGrid5->EnableDragGridSize(false);
    updateRepairDataGrid5->SetCellHighlightPenWidth(0);
    updateRepairDataGrid5->SetCellHighlightROPenWidth(0);
    updateRepairDataGrid5->SetSelectionBackground(updateRepairDataGrid5->GetDefaultCellBackgroundColour());
    updateRepairDataGrid5->SetSelectionForeground(updateRepairDataGrid5->GetDefaultCellTextColour());
    updateRepairDataGrid5->SetRowLabelSize(0);
    updateRepairDataGrid5->SetColLabelSize(0);

    updateRepairDataGrid5->SetDefaultCellFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGrid5->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid5->SetDefaultRowSize(155);
    updateRepairDataGrid5->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);


    updateRepairDataGrid5->SetCellAlignment(0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGrid5->SetCellRenderer(0, 1, new wxGridCellAutoWrapStringRenderer);
    updateRepairDataGrid5->SetCellEditor(0, 1, new wxGridCellAutoWrapStringEditor);


    updateRepairDataGrid5->SetColSize(0, 160);
    updateRepairDataGrid5->SetColSize(1, 420);

    // int cbgc;
    for (cbgc = 0; cbgc < 1;)
    {
        updateRepairDataGrid5->SetCellBackgroundColour(cbgc, 1, wxColour(230, 230, 230));
        updateRepairDataGrid5->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid5->SetReadOnly(cbgc, 0);
        updateRepairDataGrid5->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
        updateRepairDataGrid5->SetCellBackgroundColour(cbgc, 1, wxColour(220, 240, 255));
        updateRepairDataGrid5->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGrid5->SetReadOnly(cbgc, 0);
        updateRepairDataGrid5->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
    }


    updateRepairDataGrid5->SetCellValue(0, 0, "          Notes:");


    wxPanel* panelLVL = new wxPanel(parentPanel, -1, wxPoint(-1, 620), wxSize(490, 60));
    panelLVL->SetBackgroundColour(wxColor(100, 100, 200));

    updateRepairDataGridLVL = new wxGrid(panelLVL, wxID_ANY,
        wxPoint(-1, -1), wxSize(490, 60));

    updateRepairDataGridLVL->CreateGrid(1, 2);

    updateRepairDataGridLVL->SetGridLineColour(wxColor(0, 173, 234));
    updateRepairDataGridLVL->SetDefaultCellTextColour(wxColor(0, 255, 255));
    updateRepairDataGridLVL->SetDefaultCellBackgroundColour(wxColor(33, 33, 57));
    updateRepairDataGridLVL->Refresh();


    updateRepairDataGridLVL->EnableGridLines(true);
    updateRepairDataGridLVL->DisableDragColSize();
    updateRepairDataGridLVL->DisableDragRowSize();
    updateRepairDataGridLVL->EnableDragGridSize(false);
    updateRepairDataGridLVL->SetCellHighlightPenWidth(0);
    updateRepairDataGridLVL->SetCellHighlightROPenWidth(0);
    updateRepairDataGridLVL->SetSelectionBackground(updateRepairDataGridLVL->GetDefaultCellBackgroundColour());
    updateRepairDataGridLVL->SetSelectionForeground(updateRepairDataGridLVL->GetDefaultCellTextColour());
    updateRepairDataGridLVL->SetRowLabelSize(0);
    updateRepairDataGridLVL->SetColLabelSize(0);

    updateRepairDataGridLVL->SetDefaultCellFont(wxFont(16, wxSWISS, wxNORMAL, wxNORMAL, false, _("MS Sans Serif")));
    updateRepairDataGridLVL->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGridLVL->SetDefaultRowSize(60);
    updateRepairDataGridLVL->SetCellAlignment(0, 0, wxALIGN_CENTER, wxALIGN_CENTER);


    updateRepairDataGridLVL->SetCellAlignment(0, 0, wxALIGN_CENTRE, wxALIGN_CENTRE);
    updateRepairDataGridLVL->SetCellRenderer(0, 1, new wxGridCellAutoWrapStringRenderer);
    updateRepairDataGridLVL->SetCellEditor(0, 1, new wxGridCellAutoWrapStringEditor);


    updateRepairDataGridLVL->SetColSize(0, 160);
    updateRepairDataGridLVL->SetColSize(1, 330);

    // int cbgc;
    for (cbgc = 0; cbgc < 1;)
    {
        updateRepairDataGridLVL->SetCellBackgroundColour(cbgc, 1, wxColour(230, 230, 230));
       updateRepairDataGridLVL->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGridLVL->SetReadOnly(cbgc, 0);
        updateRepairDataGridLVL->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
        updateRepairDataGridLVL->SetCellBackgroundColour(cbgc, 1, wxColour(220, 240, 255));
        updateRepairDataGridLVL->SetCellTextColour(cbgc, 1, wxColour(0, 0, 0));
        updateRepairDataGridLVL->SetReadOnly(cbgc, 0);
        updateRepairDataGridLVL->SetCellAlignment(cbgc, 0, wxALIGN_LEFT, wxALIGN_CENTRE);
        cbgc++;
    }





    updateRepairDataGridLVL->SetCellValue(0, 0, "         LVL:");


    




    m_LVLarray.Add(">$25");
    m_LVLarray.Add(">$75");
    m_LVLarray.Add("NRP");
    m_LVLarray.Add("Other");
    

   
    odcLVLCategory = new wxOwnerDrawnComboBox(parentPanel, wxID_ANY, "LEVEL",
        wxPoint(495, 617), wxSize(90,25),
        m_LVLarray,
        (long)0 );

    odcLVLCategory->SetBackgroundColour(wxColour(228, 228, 240));

    // Load images from disk
    wxImage imgNormal("dropbutn.png");
    wxImage imgPressed("dropbutp.png");
    wxImage imgHover("dropbuth.png");

    if (imgNormal.IsOk() && imgPressed.IsOk() && imgHover.IsOk())
    {
        wxBitmap bmpNormal(imgNormal);
        wxBitmap bmpPressed(imgPressed);
        wxBitmap bmpHover(imgHover);
        odcLVLCategory->SetButtonBitmaps(bmpNormal, true, bmpPressed, bmpHover);
    }


    wxBitmapButton* AddRepairbutton2 = new wxBitmapButton(parentPanel, idButtonAddNoteLVL, wxBitmap(wxT("add2.png"),
        wxBITMAP_TYPE_PNG), wxPoint(505, 644), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage AddRepairbuttonimgHover("addh2.png");
    AddRepairbutton2->SetBitmapHover(AddRepairbuttonimgHover);
    wxImage AddRepairbuttonimgPressed("addp2.png");
    AddRepairbutton2->SetBitmapPressed(AddRepairbuttonimgPressed);


  //  updateRepairDataGridLVL->SetCellEditor(0, 1, new wxGridCellChoiceEditor(WXSIZEOF(LVLChoices), LVLChoices));


    db->Open(testDBName);

    Res2 = db->ExecuteQuery("SELECT CorrectiveAction FROM nodeData WHERE RepairNumber = '" + testInput + "'; ");



    while (Res2.NextRow()) {

        for (int i = 0; i < 1; i++) {

            updateRepairDataGrid5->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    Res2.Finalize();

    db->Close();



    db->Open(testDBName);

    Res2 = db->ExecuteQuery("SELECT Level FROM nodeData WHERE RepairNumber = '" + testInput + "'; ");




    while (Res2.NextRow()) {

        for (int i = 0; i < 1; i++) {

            updateRepairDataGridLVL->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    Res2.Finalize();

    db->Close();





    /// BUTTONS \\\

    wxPanel* panel7 = new wxPanel(parentPanel, -1, wxPoint(-1, 684), wxSize(585, 40));
    panel7->SetBackgroundColour(wxColor(220, 240, 255));

    wxBitmapButton* CreateNewRepairbutton = new wxBitmapButton(panel7, idButtonDoRepairUpdate, wxBitmap(wxT("updateRepair.png"),
        wxBITMAP_TYPE_PNG), wxPoint(100, 3), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage CreateNewRepairbuttonimgHover("updateRepairh.png");
    CreateNewRepairbutton->SetBitmapHover(CreateNewRepairbuttonimgHover);
    wxImage CreateNewRepairbuttonimgPressed("updateRepairp.png");
    CreateNewRepairbutton->SetBitmapPressed(CreateNewRepairbuttonimgPressed);

    wxBitmapButton* CancelNewRepairbutton = new wxBitmapButton(panel7, idButtonCancelRepairUpdate, wxBitmap(wxT("cancel.png"),
        wxBITMAP_TYPE_PNG), wxPoint(380, 3), wxSize(-1, -1), wxSIMPLE_BORDER);
    wxImage CancelNewRepairbuttonimgHover("cancelh.png");
    CancelNewRepairbutton->SetBitmapHover(CancelNewRepairbuttonimgHover);
    wxImage CancelNewRepairbuttonimgPressed("cancelp.png");
    CancelNewRepairbutton->SetBitmapPressed(CancelNewRepairbuttonimgPressed);

    Centre();
    ShowModal();

    Destroy();



    /*

    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    Res = db->ExecuteQuery("SELECT UpdateID FROM sensorUpdateData;");

    testInput = Res.GetAsString(0);


    Res.Finalize();

    db->ExecuteQuery("PRAGMA foreign_keys = OFF;");
    db->ExecuteUpdate("DROP TABLE sensorUpdateData;");
    db->ExecuteQuery("PRAGMA foreign_keys = ON;");

    db->Close();




    testDBName = wxGetCwd() + wxT("//DigitalDatabase.db");

    db->Open(testDBName);

    Res2 = db->ExecuteQuery("SELECT Id, ContactName, CompanyName, Address, PhoneNumber, EmailAddress, DateSent, DateReceived FROM nodeData WHERE RepairNumber =" + testInput + ";");



    while (Res2.NextRow()) {

        for (int i = 0; i < 8; i++) {

            updateRepairDataGrid2->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    Res2.Finalize();

    db->Close();

    */
}


updateRepairDialog::~updateRepairDialog()
{
}


void updateRepairDialog::onClickDoRepairUpdate(wxCommandEvent& event)
{

    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%m/%d/%Y", localtime(&t));

    wxString fieldID = updateRepairDataGrid->GetCellValue(0, 1);
    wxString fieldC = updateRepairDataGrid->GetCellValue(1, 1);
    wxString fieldCOM = updateRepairDataGrid->GetCellValue(2, 1);
    wxString fieldADD = updateRepairDataGrid->GetCellValue(3, 1);
    wxString fieldPN = updateRepairDataGrid->GetCellValue(4, 1);
    wxString fieldEA = updateRepairDataGrid->GetCellValue(5, 1);
    wxString fieldLU = updateRepairDataGrid->GetCellValue(6, 1);
    wxString fieldDR = updateRepairDataGrid->GetCellValue(7, 1);

    wxString fieldRN = updateRepairDataGrid2->GetCellValue(0, 1);
    wxString fieldMN = updateRepairDataGrid2->GetCellValue(1, 1);
    wxString fieldSN = updateRepairDataGrid2->GetCellValue(2, 1);
    wxString fieldD = updateRepairDataGrid2->GetCellValue(3, 1);
    wxString fieldT = updateRepairDataGrid2->GetCellValue(4, 1);
    wxString fieldCASE = updateRepairDataGrid2->GetCellValue(5, 1);
    wxString fieldQ = updateRepairDataGrid2->GetCellValue(6, 1);
    wxString fieldGN = updateRepairDataGrid2->GetCellValue(7, 1);

    wxString fieldSTAT = updateRepairDataGridSTAT->GetCellValue(0, 1);

    wxString fieldCN = updateRepairDataGrid3->GetCellValue(0, 1);
    wxString fieldWWF = updateRepairDataGrid4->GetCellValue(0, 1);
    wxString fieldNOTE = updateRepairDataGrid5->GetCellValue(0, 1);
    wxString fieldLVL = updateRepairDataGridLVL->GetCellValue(0, 1);
    wxString fieldSOU = "sensor";
    wxString fieldHIS = "UPDATE";


    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");
    db->Open(testDBName);
    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");
    db->ExecuteUpdate("UPDATE nodeData SET Id ='" + fieldID + "',ContactName ='" + fieldC + "',CompanyName ='" + fieldCOM + "', SensorSerialNumber ='" + fieldSN + "' , DateSent ='" + fieldLU + "' , DateReceived ='" + fieldDR + "' , Address ='" + fieldADD + "' , PhoneNumber ='" + fieldPN + "' , EmailAddress ='" + fieldEA + "' , ModelNumber ='" + fieldMN + "' , RepairNumber ='" + fieldRN + "' , Department ='" + fieldD + "' , Technician ='" + fieldT + "' , Status ='" + fieldSTAT + "' , Discrepancy ='" + fieldCN + "' , CorrectiveAction ='" + fieldNOTE + "' , CaseYN ='" + fieldCASE + "' , Quantity = '" + fieldQ + "', GroupNumber = '" + fieldGN + "', WhatWeFound = '" + fieldWWF + "', Level = '" + fieldLVL + "' WHERE RepairNumber ='" + testInput + "';");
    db->Close();


    testDBName = wxGetCwd() + wxT("//LogDatabase.db");
    db->Open(testDBName);
    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");
    db->ExecuteUpdate(wxString::Format(_("INSERT INTO nodeData (ContactName,CompanyName,SensorSerialNumber,DateSent,DateReceived,Address,PhoneNumber,EmailAddress,ModelNumber,RepairNumber,Department,Technician,Status,Discrepancy,CorrectiveAction,CaseYN,Quantity,Source,History,GroupNumber,WhatWeFound,Level,Chronology) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s', datetime('now', 'localtime'))"), fieldC, fieldCOM, fieldSN, fieldLU, fieldDR, fieldADD, fieldPN, fieldEA, fieldMN, fieldRN, fieldD, fieldT, fieldSTAT, fieldCN, fieldNOTE, fieldCASE, fieldQ, fieldSOU, fieldHIS, fieldGN, fieldWWF, fieldLVL));
    db->ExecuteUpdate("UPDATE nodeData SET Level ='" + fieldLVL + "' WHERE RepairNumber ='" + fieldRN + "' AND History = 'CREATED';");
    db->ExecuteUpdate("UPDATE nodeData SET Discrepancy ='" + fieldCN + "' WHERE RepairNumber ='" + fieldRN + "' AND History = 'CREATED';");
    db->Close();

    Destroy();

}





void updateRepairDialog::onClickCancelRepairUpdate(wxCommandEvent& event)
{
    Destroy();
}


void updateRepairDialog::onClickAddNoteTC(wxCommandEvent& event)
{

    wxString note = updateRepairDataGrid6->GetCellValue(0, 0);
    wxString existingNote = updateRepairDataGrid4->GetCellValue(0, 1);
    wxString newNote = existingNote + "\n" + note;
    updateRepairDataGrid4->SetCellValue(0, 1, newNote);


}


void updateRepairDialog::onClickAddNoteL(wxCommandEvent& event)
{

    wxString note = updateRepairDataGrid7->GetCellValue(0, 0);
    wxString existingNote = updateRepairDataGrid4->GetCellValue(0, 1);
    wxString newNote = existingNote + "\n" + note;
    updateRepairDataGrid4->SetCellValue(0, 1, newNote);


}


void updateRepairDialog::onClickAddNoteT(wxCommandEvent& event)
{

    wxString note = updateRepairDataGrid8->GetCellValue(0, 0);
    wxString existingNote = updateRepairDataGrid4->GetCellValue(0, 1);
    wxString newNote = existingNote + "\n" + note;
    updateRepairDataGrid4->SetCellValue(0, 1, newNote);


}

void updateRepairDialog::onClickAddLVL(wxCommandEvent& event)
{

    wxString level = odcLVLCategory->GetValue();
    wxString existingLevel = updateRepairDataGridLVL->GetCellValue(0, 1);
    wxString newLevel; 
    if (existingLevel == "") {
        newLevel = level;
    }
    else {
        newLevel = existingLevel + "," + level;
    }
    updateRepairDataGridLVL->SetCellValue(0, 1, newLevel);


}

void SensorPanel::OnCellRightClick(wxGridEvent& ev)
{

    string copyId = grid->GetCellValue(ev.GetRow(), 0);
    string copyCompany = grid->GetCellValue(ev.GetRow(), 1);
    string copyRepairNumber = grid->GetCellValue(ev.GetRow(), 2);
    string copyModelNumber = grid->GetCellValue(ev.GetRow(), 3);
    string copyStatus = grid->GetCellValue(ev.GetRow(), 4);
    string copyLastUpdate = grid->GetCellValue(ev.GetRow(), 5);
    string copyDateReceived = grid->GetCellValue(ev.GetRow(), 6);

    string copyAll = copyId + " , " + copyCompany + " , " + copyRepairNumber + " , " + copyModelNumber + " , " + copyStatus + " , " + copyLastUpdate + " , " + copyDateReceived;

    if (wxTheClipboard->Open())
    {
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData(new wxTextDataObject(copyAll));
        wxTheClipboard->Close();
    }


}

void SensorPanel::OnCellLeftClick(wxGridEvent& ev)
{

    string clickGet = grid->GetCellValue(ev.GetRow(), 0);


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



    for (int i = 0; i < 5; i++)
    {
        logGrid->SetCellValue(i, 0, "");
        logGrid->SetCellValue(i, 1, "");
        logGrid->SetCellValue(i, 2, "");
    }


    getValueI = wxAtoi(getValueS);

    cellCount = grid->GetNumberRows();

    testDBName = wxGetCwd() + wxT("//sensorDatabase4.db");

    db->Open(testDBName);

    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'GroupNumber' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

    wxSQLite3ResultSet Res = db->ExecuteQuery("SELECT Id,ContactName,Address,PhoneNumber,EmailAddress FROM nodeData WHERE Id ='" + getValueS + "';");
    wxSQLite3ResultSet Res2 = db->ExecuteQuery("SELECT ModelNumber,Department,Technician,Status FROM nodeData WHERE Id ='" + getValueS + "';");
    wxSQLite3ResultSet Res3 = db->ExecuteQuery("SELECT WhatWeFound FROM nodeData WHERE Id ='" + getValueS + "';");
    wxSQLite3ResultSet Res4 = db->ExecuteQuery("SELECT CorrectiveAction FROM nodeData WHERE Id ='" + getValueS + "';");
    wxSQLite3ResultSet Res5 = db->ExecuteQuery("SELECT CaseYN FROM nodeData WHERE Id ='" + getValueS + "';");
    wxSQLite3ResultSet Res6 = db->ExecuteQuery("SELECT Quantity FROM nodeData WHERE Id ='" + getValueS + "';");
    wxSQLite3ResultSet Res7 = db->ExecuteQuery("SELECT RepairNumber FROM nodeData WHERE Id ='" + getValueS + "';");

    while (Res.NextRow())
    {

        for (int i = 0; i < 5; i++) {

            contactDataGrid->SetCellValue(i, 1, wxString::Format(_("%s"), Res.GetAsString(i)));


        }

    }

    while (Res2.NextRow())
    {

        for (int i = 0; i < 4; i++) {

            statusDataGrid->SetCellValue(i, 1, wxString::Format(_("%s"), Res2.GetAsString(i)));


        }

    }

    while (Res3.NextRow())
    {

        statusProblemGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res3.GetAsString(0)));

    }

    while (Res4.NextRow())
    {

        statusCorrectionGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res4.GetAsString(0)));

    }

    while (Res5.NextRow())
    {

        caseGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res5.GetAsString(0)));

    }

    while (Res6.NextRow())
    {

        QtyGrid->SetCellValue(0, 0, wxString::Format(_("%s"), Res6.GetAsString(0)));

    }

    logRN = Res7.GetAsString(0);


    Res.Finalize();
    Res2.Finalize();
    Res3.Finalize();
    Res4.Finalize();
    Res5.Finalize();
    Res6.Finalize();
    Res7.Finalize();

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

    idEntry->SetValue("");


    testDBName = wxGetCwd() + wxT("//logDatabase.db");
    db->Open(testDBName);
    db->ExecuteUpdate("CREATE TABLE IF NOT EXISTS 'nodeData' ( 'Id' INTEGER PRIMARY KEY AUTOINCREMENT, 'CompanyName' TEXT, 'ContactName' TEXT, 'SensorSerialNumber' TEXT, 'DateSent' TEXT, 'DateReceived' TEXT, 'Address' TEXT, 'PhoneNumber' TEXT, 'EmailAddress' TEXT, 'ModelNumber' TEXT, 'RepairNumber' TEXT, 'Department' TEXT, 'Technician' TEXT, 'Status' TEXT, 'Discrepancy' TEXT, 'CorrectiveAction' TEXT, 'CaseYN' TEXT, 'Quantity' TEXT, 'Source' TEXT, 'History' TEXT, 'GroupNumber' TEXT, 'Chronology' TEXT, 'WhatWeFound' TEXT, 'Level' TEXT);");

    wxSQLite3ResultSet Res8 = db->ExecuteQuery("SELECT DateSent, History FROM nodeData WHERE RepairNumber = '" + logRN + "' AND Source = 'nervo' ORDER BY Chronology DESC LIMIT 5;");

    int logItt = 0;
    while (Res8.NextRow())
    {
        if (Res8.GetAsString(1) == "CREATED")
        {
            logGrid->SetCellValue(logItt, 0, "C");
        }

        else if (Res8.GetAsString(1) == "UPDATE")
        {
            logGrid->SetCellValue(logItt, 0, "U");
        }


        logGrid->SetCellValue(logItt, 1, "On");
        logGrid->SetCellValue(logItt, 2, wxString::Format(_("%s"), Res8.GetAsString(0)));

        logItt++;

    }

    Res8.Finalize();

    db->Close();



}


void SensorPanel::OnCellLeftDoubleClick(wxGridEvent& ev)
{
    string clickGet = grid->GetCellValue(ev.GetRow(), 2);

    wxString tempUpdate = clickGet;





    db = new wxSQLite3Database();

    testDBName = wxGetCwd() + wxT("//tempData.db");

    db->Open(testDBName);

    db->ExecuteQuery("CREATE TABLE IF NOT EXISTS 'sensorUpdateData' ('UpdateID' TEXT);");

    db->ExecuteUpdate(wxString::Format(_("INSERT INTO sensorUpdateData ('UpdateID') VALUES ('%s')"), tempUpdate));



    db->Close();


    updateRepairDialog* urdObjPtr = new updateRepairDialog(wxT("Update Repair"));




    urdObjPtr->Show(true);

}