'	b-PAC 3.0 SDK Component Sample (Print Barcode Label)
'	(C)Copyright Brother Industries, Ltd. 2009
'
'<SCRIPT LANGUAGE="VBScript">

	' Get Item's name & code from arguments list
	set Args = Wscript.Arguments
	If Args.count < 2 Then
		wscript.quit(1)
	End If
	sName = Args(0)
	sCode = Args(1)

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
			ObjDoc.GetObject("objName").Text = sName
			ObjDoc.GetObject("objBarcode").Text = sCode
			' ObjDoc.SetMediaByName ObjDoc.Printer.GetMediaName(), True
			ObjDoc.StartPrint "", 0
			ObjDoc.PrintOut 1, 0
			ObjDoc.EndPrint
			ObjDoc.Close
		End If
		Set ObjDoc = Nothing
	End Sub