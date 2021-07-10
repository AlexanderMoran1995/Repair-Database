#ifndef DATABASESELECTION_H_INCLUDED
#define DATABASESELECTION_H_INCLUDED

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "EDLWirelessMain.h"

class wxGrid;


class NervoPanel : public wxPanel
{
    wxGrid* grid;
    wxGrid* contactDataGrid;
    wxGrid* statusDataGrid;
    wxGrid* statusProblemGrid;
    wxGrid* statusCorrectionGrid;
    wxGrid* caseGrid;
    wxGrid* QtyGrid;
    wxGrid* logGrid;

public:

    NervoPanel(wxPanel* parent);
    wxPanel* panel;
    wxSQLite3Database* db;
    ~NervoPanel();
   
    wxOwnerDrawnComboBox* odcSortBy;
    wxOwnerDrawnComboBox* odcSearchCategory;

    wxString testDBName;
    wxString getSortCriteria;
    wxString dbQuery;
    wxString getValueS;
    wxString cellValue;
    wxString getSearchCriteria;
    wxString getSearchCategory;

    int dbSize;
    int newdbSize;
    int getValueI;
    int cycles = 0;
    int cellCount;

    wxTextCtrl* idEntry;
    wxTextCtrl* updateEntry;


    static const long idButtonNewRepair;
    static const long idButtonRefreshGrid;
    static const long idButtonGetInfo;
    static const long idButtonSearch;
    static const long idButtonUpdateRepair;
    static const long idButtonResetGrid;
    static const long idButtonSortGrid;


    void onClickNewRepair(wxCommandEvent& event);
    void onClickRefresh(wxCommandEvent& event);
    void onClickGet(wxCommandEvent& event);
    void onClickSearch(wxCommandEvent& event);
    void onClickUpdateRepair(wxCommandEvent& event);
    void onClickReset(wxCommandEvent& event);
    void onClickSort(wxCommandEvent& event);

    void OnTimer(wxTimerEvent& event);

    void OnCellRightClick(wxGridEvent& );
    void OnCellLeftClick(wxGridEvent& );
    void OnCellLeftDoubleClick(wxGridEvent&);

    void REFRESH();

    //protected:


    wxSearchCtrl* m_srchCtrl;
    wxTextCtrl* m_deptCtrl;

    wxCheckBox* m_searchBtnCheck;
    wxCheckBox* m_cancelBtnCheck;
    wxCheckBox* m_menuBtnCheck;

    wxArrayString   m_fieldarray;
    wxArrayString   m_sortbyarray;

    //private:
    wxTimer *m_timer;

    DECLARE_EVENT_TABLE()

   

};




class NervonewRepairDialog : public wxDialog
{
public:
    NervonewRepairDialog(const wxString& title);
    ~NervonewRepairDialog();

    wxOwnerDrawnComboBox* odccase;
    wxArrayString   m_casearray;

    wxTextCtrl* m_customer;
    wxTextCtrl* m_company;
    wxTextCtrl* m_type;
    wxTextCtrl* m_dateSent;
    wxTextCtrl* m_dateRec;

    wxTextCtrl* m_model;
    wxTextCtrl* m_serial;
    wxTextCtrl* m_repair;
    wxTextCtrl* m_tech;
    wxTextCtrl* m_multitext;

    wxTextCtrl* m_contact;
    wxTextCtrl* m_phone;
    wxTextCtrl* m_altPhone;
    wxTextCtrl* m_email;
    wxTextCtrl* m_address;
    wxTextCtrl* m_city;
    wxTextCtrl* m_state;
    wxTextCtrl* m_zip;
    wxTextCtrl* m_country;


    wxTextCtrl* m_case;
    wxTextCtrl* m_quantity;
    wxTextCtrl* m_group;
    wxTextCtrl* m_mostRecentRepair;

    wxString mostRecentRepair;

    wxOwnerDrawnComboBox* odcRepairTemplate;
    wxArrayString   m_templateArray;

    wxString rpFormRepairNum;
    wxString rpFormQuantity;
    wxString rpFormModelNum;
    wxString rpFormSerialNum;
    wxString rpFormCase;
    wxString rpFormLevel;
    wxString rpFormRPHolder;
    wxString rpFormLevelHolder;

    static const long idButtonCreateRepair;
    static const long idButtonCancelRepair;
    static const long idButtonRepairTemplate;



    void onClickCreateRepair(wxCommandEvent& event);
    void onClickCancelRepair(wxCommandEvent& event);
    void onClickGetRepairTemplate(wxCommandEvent& event);

    wxSQLite3Database* db;

    //private:

    DECLARE_EVENT_TABLE()

};




class NervoupdateRepairDialog : public wxDialog
{

    wxGrid* updateRepairDataGrid;
    wxGrid* updateRepairDataGrid2;
    wxGrid* updateRepairDataGrid3;
    wxGrid* updateRepairDataGrid4;
    wxGrid* updateRepairDataGrid5;
    wxGrid* updateRepairDataGrid6;
    wxGrid* updateRepairDataGrid7;
    wxGrid* updateRepairDataGrid8;
    wxGrid* updateRepairDataGridSTAT;
    wxGrid* updateRepairDataGridLVL;


public:
    NervoupdateRepairDialog(const wxString& title);
    ~NervoupdateRepairDialog();



    wxTextCtrl* m_customer;
    wxTextCtrl* m_company;
    wxTextCtrl* m_type;
    wxTextCtrl* m_dateSent;
    wxTextCtrl* m_dateRec;

    wxTextCtrl* m_model;
    wxTextCtrl* m_serial;
    wxTextCtrl* m_repair;
    wxTextCtrl* m_multitext;

    wxTextCtrl* m_contact;
    wxTextCtrl* m_phone;
    wxTextCtrl* m_altPhone;
    wxTextCtrl* m_email;
    wxTextCtrl* m_address;

    wxTextCtrl* oldDataEntry;
    wxTextCtrl* newDataEntry;

    wxString testInput;

    static const long idButtonDoRepairUpdate;
    static const long idButtonCancelRepairUpdate;
    static const long idButtonAddNote;
    static const long idButtonSelect;


    void onClickDoRepairUpdate(wxCommandEvent& event);
    void onClickCancelRepairUpdate(wxCommandEvent& event);
    void onClickAddNote(wxCommandEvent& event);
    void onClickSelect(wxCommandEvent& event);


    wxSQLite3Database* db;
    wxString testDBName;

    wxString updateID;

    //private:

    DECLARE_EVENT_TABLE()

};

class NervoBackgroundPanel : public wxPanel
{


public:
    NervoBackgroundPanel(wxPanel* parent);
    ~NervoBackgroundPanel();

    NervoPanel* NGP;
    NervonewRepairDialog* NRPD;
    NervoupdateRepairDialog* URD;

};



#endif // DATABASESELECTION_H_INCLUDED

