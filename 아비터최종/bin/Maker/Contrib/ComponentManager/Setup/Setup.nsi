; NSIS Component Manager - Installation script
; Copyright (c) 2005 Dan Fuhry/Dashboard Software, Inc.

; This script SDK (including any additional scripts in this package)
; is free software; you can redistribute it and/or modify it under
; the terms of the GNU Lesser General Public License as published
; by the Free Software Foundation; either version 2.1 of the License,
; or (at your option) any later version.

; This script SDK is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; Lesser General Public License for more details.

; You should have received a copy of the GNU Lesser General Public
; License along with this library; if not, write to the Free Software
; Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

; Didn't these FSF guys used to be down in Mississippi?

!define NAME "Component Manager"
!define VERSION "0.2"
!define CM_USEUI XPUI
;!define XPUI_VERBOSE 4 # for debugging XPUI
!define XPUI_COMPONENTSPAGE_TEXT_DESCRIPTION_INFO "Note: you must select all components if you wish to recompile $(^Name) as a custom distro."
!define CM_STARTMENU_REG_ROOT HKLM
!define CM_STARTMENU_REG_KEY  "Software\NSIS\ComponentManager"
!define CM_STARTMENU_REG_VALUE "StartMenuDir"
!include CM.nsh

Name "${NAME}"
Caption "${NAME} ${VERSION} Setup"
OutFile "..\ComponentManager${VERSION}.exe"
SetCompressor /SOLID /FINAL lzma
;ChangeUI IDD_INST "${NSISDIR}\Contrib\ExperienceUI\UIs\HeaderUI.exe"

; ExperienceUI stuff
!define XPUI_BOTTOMIMAGE
!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "NSIS\$(^Name)"
!define XPUI_STARTMENUPAGE_FOLDER "NSIS\$(^Name)"
!include XPUI.nsh
!insertmacro MUI_LANGUAGE English
!insertmacro XPUI_PAGE_STARTMENU_INIT App $R4
;!insertmacro MUI_LANGUAGE PortugueseBR

Function .onInit
ReadRegStr $0 HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\NSIS UninstallString
StrCpy $0 $0 "" 1
StrLen $1 $0
IntOp $1 $1 - 17
StrCpy $INSTDIR $0 $1
IfFileExists $INSTDIR\MakeNSIS.exe FoundNSIS
MessageBox MB_OK|MB_ICONEXCLAMATION "Setup could not find NSIS on your system.  $(^Name) is an extension for the NSIS Installer SDK, and it requires NSIS in order to work.  Please download NSIS at http://nsis.sourceforge.net/ and run this installer again."
Abort
FoundNSIS:
FunctionEnd

${SectionRO} "Component Manager Base Files" Sec1 "The files required for $(^Name) to work"
  ${SetOutPath} $INSTDIR\Contrib\ComponentManager
  ${File} CMSystem.nsh ..\CMSystem.nsh
  ${File} License.rtf ..\License.rtf
  ${SetOutPath} $INSTDIR\Contrib\ComponentManager\Res
  ${File} Confirm.ini ..\Res\Confirm.ini
  ${File} Maint.ini ..\Res\Maint.ini
  ${File} Maint_XPUI.ini ..\Res\Maint_XPUI.ini
  ${File} Repair.ico ..\Res\Repair.ico
  ${File} Modify.ico ..\Res\Modify.ico
  ${File} Remove.ico ..\Res\Remove.ico
  ${SetOutPath} $INSTDIR\Contrib\ComponentManager\FileManip
  ${File} FileMan.exe ..\FileManip\FileMan.exe
  ${File} FileMan.nsi ..\FileManip\FileMan.nsi
  ${File} Icon.ico ..\FileManip\Icon.ico
  ${SetOutPath} $INSTDIR\Contrib\ComponentManager\Setup
  ${File} Setup.nsi Setup.nsi
  FileOpen $0 $INSTDIR\Include\CM.nsh w
    FileWrite $0 `!include "$INSTDIR\Contrib\ComponentManager\CMSystem.nsh"`
  FileClose $0
${SectionEnd}

${Section} "Documentation" Docs "Information on how to use $(^Name)"
  ${SetOutPath} $INSTDIR\Docs\ComponentManager
  ${File} index.htm "..\..\..\Docs\ComponentManager\index.htm"
  ${File} top.gif   "..\..\..\Docs\ComponentManager\top.gif"
  Call MakeShortcuts
${SectionEnd}

${Section} "Example script" Sec2 "An example script to get you started"
  ${SetOutPath} $INSTDIR\Examples\ComponentManager
  ${File} Example.nsi "..\..\..\Examples\ComponentManager\Example.nsi"
  ${SetOutPath} $INSTDIR\Examples\ComponentManager\Data
  ${CopyFiles} "$PROGRAMFILES\Windows NT\Accessories\Mswrd6.wpc" "Mswrd6.wpc"
  ${CopyFiles} "$PROGRAMFILES\Windows NT\Accessories\Mswrd8.wpc" "Mswrd8.wpc"
  ${CopyFiles} "$PROGRAMFILES\Windows NT\Accessories\Write.wpc" Write.wpc
  ${CopyFiles} "$PROGRAMFILES\Windows NT\Accessories\Wordpad.exe" Wordpad.exe
  ${CopyFiles} $WINDIR\Notepad.exe Notepad.exe
  ${File} LGPL.htm "..\..\..\Examples\ComponentManager\Data\LGPL.htm"
${SectionEnd}

Function MakeShortcuts

  ${StartMenu} App $R4
    ${CreateShortcut} Documentation '"$INSTDIR\Docs\ComponentManager\index.htm"'
  ${StartMenuEnd}

FunctionEnd

!macro CM_UNINST
  ReadRegStr $0 HKLM Software\NSIS\ComponentManager StartMenuCreated
  StrCmp $0 1 "" NoSM
    ReadRegStr $0 HKLM Software\NSIS\ComponentManager StartMenuDir
    Delete $SMPROGRAMS\$0\Documentation.lnk
    RMDir $SMPROGRAMS\$0
  NoSM:
!macroend

!insertmacro CM_SYSTEM
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE ..\License.rtf
!insertmacro MUI_PAGE_COMPONENTS
!ifdef XPUI_INCLUDED
  !insertmacro XPUI_PAGE_STARTMENU_SHOW App
!else
  !insertmacro MUI_PAGE_STARTMENU
!endif
!ifdef XPUI_VERSION
  !insertmacro XPUI_PAGE_INSTCONFIRM
!endif
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!ifdef XPUI_VERSION
!insertmacro UMUI_PAGE_ABORT
!endif
!ifdef UMUI_INCLUDED
!insertmacro UMUI_PAGE_ABORT
!endif
!ifndef XPUI_VERSION & UMUI_INCLUDED
!insertmacro MUI_PAGE_ABORT
!endif

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH
!ifdef XPUI_VERSION
!insertmacro UMUI_PAGE_ABORT
!endif
