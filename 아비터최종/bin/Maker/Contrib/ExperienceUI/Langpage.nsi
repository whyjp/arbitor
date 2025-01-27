!VERBOSE 1
!define XPUI_VERBOSE 1
!define XPUI_SILENT
!define XPUI_INSTALLOPTIONS_MAXFIELD 4
!ifndef XPUI_LANGINI_LIST_B
  !error "This script should only be compiled through the ExperienceUI's internal multi-language support system!"
!endif

SetCompress off

Name "Select Language"
Caption " "
OutFile "${NSISDIR}\Contrib\ExperienceUI\LangDialog.exe"

MiscButtonText "" "" "" OK
!define XPUI_DISABLEBG
!define XPUI_ABORTPAGE_TEXT "The wizard was interrupted before the program could be installed.\r\n\r\nYour system has not been modified.  To install the program at a later time, please run this setup wizard again.\r\n\r\n\r\n\r\n\r\nPlease click $\"$(XPUI_BUTTONTEXT_CLOSE)$\" to exit the NSIS installation wizard."
!define XPUI_ABORTPAGE_SUBTITLE "Setup did not complete successfully."
!define XPUI_ABORTPAGE_CAPTION " "
!include XPUI.nsh
!VERBOSE 1

Page custom LangSelect LangSelectFin ""
;Page custom CancelConfirm CancelConfirmFin ""
!insertmacro XPUI_PAGE_ABORT

Function LangSelect
Call GetParameters
Pop $0
StrCmp $0 "/CancelDialog" 0 +2
Abort
SetOutPath $PLUGINSDIR
File "${NSISDIR}\Contrib\ExperienceUI\INI\LangDlg.ini"
WriteINIStr "$PLUGINSDIR\LangDlg.ini" "Field 1" ListItems "${XPUI_LANGINI_LIST_B}"
StrCpy $XPUI_TEMP1 "${XPUI_LANGINI_LIST_B}"
StrCpy $XPUI_HWND 0
PipeLoop:
StrCpy $XPUI_TEMP2 $XPUI_TEMP1 1 $XPUI_HWND
StrCmp $XPUI_TEMP2 | foundPipe
IntOp $XPUI_HWND $XPUI_HWND + 1
Goto PipeLoop
FoundPipe:
StrCpy $XPUI_TEMP1 $XPUI_TEMP1 $XPUI_HWND
WriteINIStr "$PLUGINSDIR\LangDlg.ini" "Field 1" State "$XPUI_TEMP1"
InstallOptions::initDialog /NOUNLOAD $PLUGINSDIR\LangDlg.ini
Pop $XPUI_HWND
!insertmacro XPUI_CONTROL_SKIN $XPUI_HWND
GetDlgItem $XPUI_TEMP1 $XPUI_HWND 1200
!insertmacro XPUI_CONTROL_SKIN $XPUI_TEMP1
GetDlgItem $XPUI_TEMP1 $XPUI_HWND 1201
!insertmacro XPUI_CONTROL_SKIN $XPUI_TEMP1
CreateFont $XPUI_TEMP2 "Tahoma" 8 700
SendMessage $XPUI_TEMP1 0x30 $XPUI_TEMP2 0
GetDlgItem $XPUI_TEMP1 $XPUI_HWND 1202
!insertmacro XPUI_CONTROL_SKIN $XPUI_TEMP1
CreateFont $XPUI_TEMP2 "Tahoma" 8 350
SendMessage $XPUI_TEMP1 0x30 $XPUI_TEMP2 0
!insertmacro XPUI_HEADER_TEXT "Select Language" "Please select which language to use in the installer."
InstallOptions::show
FunctionEnd

Function LangSelectFin

Call GetParameters
Pop $0
StrCmp $0 "/CancelDialog" 0 +2
Return

; Reset everything
StrCpy $XPUI_HWND 0
StrCpy $XPUI_TEMP1 0
StrCpy $XPUI_TEMP2 0

ReadINIStr $XPUI_NOABORTWARNING $PLUGINSDIR\LangDlg.ini "Field 1" State
!include `${CHECKLIST}`
/*

; First, find out if user selected first language...
StrCpy $XPUI_TEMP1 "${XPUI_LANGINI_LIST_B}"
StrCpy $XPUI_HWND 0
PipeLoop1:
StrCpy $XPUI_TEMP2 $XPUI_TEMP1 1 $XPUI_HWND
StrCmp $XPUI_TEMP2 | foundPipe1
IntOp $XPUI_HWND $XPUI_HWND + 1
Goto PipeLoop1
FoundPipe1:
StrCpy $XPUI_TEMP1 $XPUI_TEMP1 $XPUI_HWND
ReadINIStr $XPUI_NOABORTWARNING $PLUGINSDIR\LangDlg.ini "Field 1" State
StrCmp $XPUI_TEMP1 $NOABORTWARNING "" PipeLoop2
StrCpy $XPUI_TEMP1 0
Goto Done

PipeLoop2:

; Reset everything
StrCpy $XPUI_HWND 0
StrCpy $XPUI_TEMP1 0
StrCpy $XPUI_TEMP2 0

PipeLoop:
StrCpy $XPUI_TEMP2 "${XPUI_LANGINI_LIST_B}" 1 $XPUI_HWND
StrCmp $XPUI_TEMP2 "" Done
StrCmp $XPUI_TEMP2 | foundPipe
IntOp $XPUI_HWND $XPUI_HWND + 1
Goto PipeLoop
FoundPipe:
IntOp $XPUI_TEMP1 $XPUI_TEMP1 + 1
IntOp $XPUI_HWND $XPUI_HWND + 1
ReadINIStr $XPUI_NOABORTWARNING $PLUGINSDIR\LangDlg.ini "Field 1" State
StrLen $XPUI_TEMP2 "$NOABORTWARNING"
StrCpy $XPUI_TEMP2 "${XPUI_LANGINI_LIST_B}" $XPUI_TEMP2 $XPUI_HWND
StrCmp $XPUI_TEMP2 $NOABORTWARNING Done PipeLoop
Goto PipeLoop
Done:
IntOp $XPUI_TEMP1 $XPUI_TEMP1 * 4
StrCpy $0 "${XPUI_LANGIDLIST_LIST_B}" 4 $XPUI_TEMP1
SetErrorLevel $0       */
MessageBox MB_OK|MB_ICONEXCLAMATION "The language page system could not detect the language ID.  The installer will use the first language inserted in the script file."
SetErrorLevel 0
FunctionEnd

/*
Function CancelConfirm
Call GetParameters
Pop $0
StrCmp $0 "/CancelDialog" +2
Abort
SetOutPath $PLUGINSDIR
File "${NSISDIR}\Contrib\ExperienceUI\Ini\CancelConfirm.ini"
!insertmacro XPUI_INSTALLOPTIONS_DISPLAY "CancelConfirm.ini"
FunctionEnd

Function CancelConfirmFin
  ReadINIStr $0 $PLUGINSDIR\CancelConfirm.ini "Field 2" State
  StrCmp $0 1 "" ResumeOnLogin
  SetErrorLevel 5
  Return
  ResumeOnLogin:
  ReadINIStr $0 $PLUGINSDIR\CancelConfirm.ini "Field 3" State
  StrCmp $0 1 "" Resume
  SetErrorLevel 6
  Return
  Resume:
  SetErrorLevel 7
FunctionEnd */

Function .onUserAbort
StrCmp $XPUI_ABORTED 1 Done
MessageBox MB_YESNO|MB_ICONQUESTION "You are about to quit setup.$\n$\nIf you quit now, the program will not be installed.$\n$\nDo you want to continue?" IDNO CancelQuit
!insertmacro XPUI_USERABORT
CancelQuit:
Abort
Done:
SetErrorLevel 1
FunctionEnd

Section
SectionEnd

 Function GetParameters

   Push $R0
   Push $R1
   Push $R2
   Push $R3

   StrCpy $R2 1
   StrLen $R3 $CMDLINE

   ;Check for quote or space
   StrCpy $R0 $CMDLINE $R2
   StrCmp $R0 '"' 0 +3
     StrCpy $R1 '"'
     Goto loop
   StrCpy $R1 " "

   loop:
     IntOp $R2 $R2 + 1
     StrCpy $R0 $CMDLINE 1 $R2
     StrCmp $R0 $R1 get
     StrCmp $R2 $R3 get
     Goto loop

   get:
     IntOp $R2 $R2 + 1
     StrCpy $R0 $CMDLINE 1 $R2
     StrCmp $R0 " " get
     StrCpy $R0 $CMDLINE "" $R2

   Pop $R3
   Pop $R2
   Pop $R1
   Exch $R0

 FunctionEnd

 !insertmacro XPUI_LANGUAGE English

!VERBOSE 1