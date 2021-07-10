#ifndef ARCHIVE_H_INCLUDED
#define ARCHIVE_H_INCLUDED

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "EDLWirelessMain.h"

#include <wx/wx.h>
#include <wx/log.h>
#include <wx/msw/ole/oleutils.h> 
#include <wx/iconbndl.h>

#include <wx/wxAutoExcel.h>
#include "wx/pdfdoc.h"
#include <stdio.h>
#include <process.h>

class wxGrid;


class ArchivePanel : public wxPanel
{
    wxGrid* grid;
    wxGrid* extraDataGrid;
    wxGrid* OfficeProblemGrid;
    wxGrid* OfficeCorrectionGrid;

public:

    ArchivePanel(wxPanel* parent);
    wxPanel* panel;
    wxSQLite3Database* db;
    ~ArchivePanel();

    wxOwnerDrawnComboBox* odcSortBy;
    wxOwnerDrawnComboBox* odcSearchCategory;
    wxOwnerDrawnComboBox* odcdept;
    wxOwnerDrawnComboBox* odcmonth;
    wxOwnerDrawnComboBox* odcday;

    wxOwnerDrawnComboBox* odclog;

    wxString testDBName;
    wxString getSortCriteria;
    wxString dbQuery;
    wxString getValueS;
    wxString cellValue;
    wxString getSearchCriteria;
    wxString getSearchCategory;
    wxString excelDBChoice;
    wxString logDBChoice;
    wxString tagDate;

    int dbSize;
    int newdbSize;
    int getValueI;
    int cycles = 0;
    int cellCount;

    wxTextCtrl* idEntry;
    wxTextCtrl* updateEntry;
    wxTextCtrl* yearEntry;
    wxTextCtrl* rpNumEntry;
    wxTextCtrl* PDFEntry;


    static const long idButtonNewRepair;
    static const long idButtonGetInfo;
    static const long idButtonSearch;
    static const long idButtonUpdateRepair;
    static const long idButtonResetGrid;
    static const long idButtonSortGrid;
    static const long idButtonExcelOutput;
    static const long idButtonLogReport;
    static const long idButtonRepairForm;
    static const long idButtonRepairTag;
    static const long idButtonFdaSpreadsheet;


    void onClickGet(wxCommandEvent& event);
    void onClickSearch(wxCommandEvent& event);
    void onClickReset(wxCommandEvent& event);
    void onClickSort(wxCommandEvent& event);
    void onClickExcelOutput(wxCommandEvent& event);
    void onClickLogReport(wxCommandEvent& event);
    void onClickFdaSpreadsheet(wxCommandEvent& event);

    void OnTimer(wxTimerEvent& event);

    void OnCellRightClick(wxGridEvent&);
    void OnCellLeftClick(wxGridEvent&);


    void RESET();

    //protected:


    wxSearchCtrl* m_srchCtrl;
    wxTextCtrl* m_deptCtrl;

    wxCheckBox* m_searchBtnCheck;
    wxCheckBox* m_cancelBtnCheck;
    wxCheckBox* m_menuBtnCheck;

    wxArrayString   m_fieldarray;
    wxArrayString   m_sortbyarray;
    wxArrayString   m_deptarray;
    wxArrayString   m_montharray;
    wxArrayString   m_dayarray;

    wxString rpTagDate;
    wxString rpTagCompany;
    wxString rpTagModelNum;
    wxString rpTagRepairNum;
    wxString rpTagSerialNum;
    wxString rpTagCase;
    wxString rpTagGroup;

    wxString rpFormDate;
    wxString rpFormCompany;
    wxString rpFormContact;
    wxString rpFormEmail;
    wxString rpFormPhone;
    wxString rpFormAddress;
    wxString rpFormAltPhone;
    wxString rpFormNotes;

    wxString rpFormRepairNum;
    wxString rpFormQuantity;
    wxString rpFormModelNum;
    wxString rpFormSerialNum;
    wxString rpFormCase;

    int initITT;


    //private:
    wxTimer* m_timer;

    DECLARE_EVENT_TABLE()

};


class ArchiveBackgroundPanel : public wxPanel
{


public:
    ArchiveBackgroundPanel(wxPanel* parent);
    ~ArchiveBackgroundPanel();

    ArchivePanel* ArchiveGP;
   

};

using namespace wxAutoExcel;

class ChartSampleA
{
public:
    bool Init();
    bool Init2();
    bool Init3();

    bool AddChartStacked();
    bool AddChartClusteredWithLine();
    bool AddChart3D();
    bool AddSparkline();
    bool AddTestChart();
    void ChartFormat(wxExcelRange& range);
    void LogFormat(wxExcelRange& range);
    void FdaFormat(wxExcelRange& range);
    wxString testDBName;
    wxSQLite3Database* db;

    wxString source;
    wxString sourceDB;
    wxVariant variant;
    wxString symbol;
    wxString logSource;
    wxString fdaSource;
    int hC1, hC2, hC3;
    int cC1, cC2, cC3;

private:
    wxExcelApplication  m_app;
    wxExcelWorkbook     m_workbook;
    wxExcelWorkbook     m_workbook2;
    wxExcelWorkbook     m_workbook3;
    wxExcelWorksheet    m_dataWorksheet;
    wxExcelWorksheet    m_embeddedChartsWorksheet;
    wxExcelWorksheet    m_testWorksheet;
    wxExcelWorksheet    m_testChartWorksheet;
    wxExcelWorksheet    m_logWorksheet;
    wxExcelWorksheet    m_fdaWorksheet;

    bool WriteData(wxExcelRange& range);
    bool WriteLogData(wxExcelRange& range);
    bool WriteFdaData(wxExcelRange& range);
    bool AddTest(wxExcelRange& range);
};

#endif // DATABASESELECTION_H_INCLUDED

