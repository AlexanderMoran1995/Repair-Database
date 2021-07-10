'	b-PAC 3.0 SDK Component Sample (Print Barcode Label)
'	(C)Copyright Brother Industries, Ltd. 2009
'
'<SCRIPT LANGUAGE="VBScript">

	' Get Item's name & code from arguments list
	set Args = Wscript.Arguments
	If Args.count < 7 Then
		wscript.quit(1)
	End If
	sRepNum = Args(0)
	sDate = Args(1)
	sCompany = Args(2)
	sCase = Args(3)
	sModelNum = Args(4)
	sSerialNum = Args(5)
	sGroupNum = Args(6)

	' Data Folder
	Const sDataFolder = "C:\Program Files\Brother bPAC3 SDK\Templates\"
	
	' Print
	DoPrint(sDataFolder & "BcdItem2.lbx")


	'*******************************************************************
	'	Print Module
	'*******************************************************************
    Sub DoPrint(strFilePath)
		Set ObjDoc = CreateObject("bpac.Document")
		bRet = ObjDoc.Open(strFilePath)
		If (bRet <> False) Then
			ObjDoc.GetObject("objRepNum").Text = sRepNum
			ObjDoc.GetObject("objDate").Text = sDate
            ObjDoc.GetObject("objCompany").Text = sCompany
            ObjDoc.GetObject("objCase").Text = sCase
            ObjDoc.GetObject("objModelNum").Text = sModelNum
            ObjDoc.GetObject("objSerialNum").Text = sSerialNum
			ObjDoc.GetObject("objGroupNum").Text = sGroupNum
			
			' ObjDoc.SetMediaByName ObjDoc.Printer.GetMediaName(), True
			ObjDoc.StartPrint "", 0
			ObjDoc.PrintOut 1, 0
			ObjDoc.EndPrint
			ObjDoc.Close
		End If
		Set ObjDoc = Nothing
	End Sub