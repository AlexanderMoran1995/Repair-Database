#ifndef OFFICE_H_INCLUDED
#define OFFICE_H_INCLUDED

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

class OfficePanel : public wxPanel
{
    wxGrid* grid;
    wxGrid* extraDataGrid;
    wxGrid* OfficeProblemGrid;
    wxGrid* OfficeCorrectionGrid;

public:

    OfficePanel(wxPanel* parent);
    wxPanel* panel;
    wxSQLite3Database* db;
    ~OfficePanel();

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
    void onClickRepairForm(wxCommandEvent& event);
    void onClickRepairTag(wxCommandEvent& event);
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
	wxString rpFormLevel;
	wxString rpFormRPHolder;
	wxString rpFormLevelHolder;

	int initITT;
	

	//private:
	wxTimer* m_timer;

    DECLARE_EVENT_TABLE()

};

class OfficeBackgroundPanel : public wxPanel
{

public:
    OfficeBackgroundPanel(wxPanel* parent);
    ~OfficeBackgroundPanel();

    OfficePanel* OP;
  
};



using namespace wxAutoExcel;

class ChartSample 
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


class PdfTuto2 : public wxPdfDocument
{
	// Page header
	void Header()
	{
		// Logo
	//	SetFont(wxS("Helvetica"), wxS("B"), 12);
		//Cell(10, 10, (wxS("Electronic Development Labs, Inc. "));
		
	//	Image(wxS("pdflogo.png"), 150, 5, 45);
		// Helvetica bold 15
	//	SetFont(wxS("Helvetica"), wxS("B"), 18);
		// Move to the right
		//Cell(10);
		//Ln(25);
		// Title
		//Cell(200, 10, wxS("Customer Repair Form"), wxPDF_BORDER_FRAME, 0, wxPDF_ALIGN_CENTER);

		// Line break
	//	Ln(20);
	}

	// Page footer
	void Footer()
	{
		// Position at 1.5 cm from bottom
		SetY(-15);
		// Helvetica italic 8
		SetFont(wxS("Helvetica"), wxS("I"), 8);
		// Page number
		Cell(0, 10, wxString::Format(wxS("Page %d/{nb}"), PageNo()), 0, 0, wxPDF_ALIGN_CENTER);
	}
};

#endif // OFFICE_H_INCLUDED
