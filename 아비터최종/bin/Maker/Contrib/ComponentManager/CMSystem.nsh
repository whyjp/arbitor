/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * NSIS Component Management Platform -                      *
 * A powerful way to manage the many components included     *
 * with today's programs.  Uses the NSIS Compile-Time File   *
 * Manipulation Utility, a way of writing to files from the  *
 * command line.  CM features installation repair,           *
 * modification, and more.                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
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

!macro SET S V
  !ifdef ${S}
    !undef ${S}
  !endif
  !define ${S} `${V}`
!macroend

!macro DEFAULT S V
  !ifndef ${S}
    !define ${S} `${V}`
  !endif
!macroend

!macro UNSET S
  !ifdef ${S}
    !undef ${S}
  !endif
!macroend

; Check NSIS version
!define NSIS_VCHECK_${NSIS_VERSION}
!ifdef NSIS_VCHECK_v2.0 | NSIS_VCHECK_v2.01 | NSIS_VCHECK_v2.02 | NSIS_VCHECK_v2.03 | NSIS_VCHECK_v2.04 | NSIS_VCHECK_v2.05 | NSIS_VCHECK_v2.06 | NSIS_VCHECK_v2.07 | NSIS_VCHECK_v2.08 | NSIS_VCHECK_v2.09 | NSIS_VCHECK_v2.10
  !ifndef CM_USE_EXT_FILE_WRITER
    !define CM_USE_EXT_FILE_WRITER
  !endif
!endif

!macro FILEOPEN F
  !ifdef CM_USE_EXT_FILE_WRITER
    !execute '"${CM_SYSDIR}\FileManip\Fileman.exe" /Special:Init $%TEMP%\${F}'
  !else
    !tempfile "${F}"
  !endif
!macroend

!macro FILECLOSE F
  !ifdef CM_USE_EXT_FILE_WRITER
    !execute '"${CM_SYSDIR}\FileManip\Fileman.exe" /Special:Fini $%TEMP%\${F}'
  !else
    !delfile "${${F}}"
  !endif
!macroend

!macro FILEWRITE F C
  !ifdef CM_USE_EXT_FILE_WRITER
    !execute '"${CM_SYSDIR}\FileManip\Fileman.exe" $%TEMP%\${F} /Text:${C}'
  !else
    !appendfile "${${F}}" `${C}$\r$\n`
  !endif
!macroend

!macro CM_INCLUDE F
  !ifdef CM_USE_EXT_FILE_WRITER
    !include `$%TEMP%\${F}`
  !else
    !include `${${F}}`
  !endif
!macroend

; Include in generated scripts
!macro CM_INCLUDE_ALT F
  !ifdef CM_USE_EXT_FILE_WRITER
    !include `$%TEMP%\${F}`
  !else
    !include `${${F}}`
  !endif
!macroend

!define FileOpen "!insertmacro FILEOPEN"
!define FileClose "!insertmacro FILECLOSE"
!define FileWrite "!insertmacro FILEWRITE"
!define CMInclude "!insertmacro CM_INCLUDE"
!define CMIncludeAlt "!insertmacro CM_INCLUDE_ALT"

!define Set "!insertmacro SET"
!define Default "!insertmacro DEFAULT"
!define Unset "!insertmacro UNSET"

; Defaults
${Default} CM_VERBOSE 1
${Default} CM_USEUI XPUI
${Default} CM_SYSDIR "${NSISDIR}\Contrib\ComponentManager"

Var CM_UNINST_FULL

!verbose push
!verbose ${CM_VERBOSE}
${FileOpen} CompList
${FileOpen} InstList
${FileOpen} DescList
${FileOpen} LabelList
${FileOpen} ReadModifyList
${FileOpen} GenModifyList
${FileOpen} UncheckList
${FileOpen} FileList
${FileOpen} DirList
${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini Settings NumFields 1`
${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field 1" Type Label`
${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field 1" Left 0`
${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field 1" Right -1`
${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field 1" Top 0`
${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field 1" Bottom 10`
${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field 1" Text "Please select which components of $(^Name) should be installed:"`
${FileWrite} GenModifyList `StrCpy $0 0`
${FileWrite} GenModifyList `StrCpy $1 10`
${FileWrite} GenModifyList `StrCpy $R8 1`
${FileWrite} ReadModifyList `StrCpy $R8 1`
!verbose pop

!macro SECTION NAME ID DESC

  Var "C_${ID}"
  
  !verbose push
  !verbose 4
  !echo "CM: Section: ${NAME} (ID: ${ID})"
  !verbose ${CM_VERBOSE}
  ${FileWrite} GenModifyList `IntOp $0 $0 + 15`
  ${FileWrite} GenModifyList `IntOp $1 $1 + 15`
  ${FileWrite} GenModifyList `IntOp $R8 $R8 + 1`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Settings" NumFields $R8`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Type Checkbox`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Left 6`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Right -1`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Top $0`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Bottom $1`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Text "${NAME}"`
  ${FileWrite} GenModifyList `${CMIncludeAlt} CompList`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" State $C_${ID}`
  ${FileWrite} ReadModifyList `IntOp $R8 $R8 + 1`
  ${FileWrite} ReadModifyList `ReadINIStr $C_${ID} $PLUGINSDIR\Modify.ini "Field $R8" State`
  ${FileWrite} DescList `!insertmacro ${CM_USEUI}_DESCRIPTION_TEXT "${${ID}}" "${DESC}"`
  ${FileWrite} CompList `ReadINIStr $C_${ID} "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" "$(^Name)" "${ID}"`
  ${FileWrite} InstList `StrCmp $C_${ID} 1 0 +2`
  ${FileWrite} InstList `Call :.InstallComponent${ID}`
  ${FileWrite} LabelList `Call :.InstallComponent${ID}`
  ${FileWrite} UncheckList `WriteINIStr "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" "$(^Name)" "${ID}" 0`
  
  !ifndef CM_SEC_INSERTED

    !define CM_SEC_INSERTED

  Section -pre

  .cmPre:
  Push $R0
    System::Call 'kernel32::GetModuleFileNameA(i 0, t .R0, i 1024) i r1'
    CopyFiles $R0 "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe"
    IfFileExists "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe" +2
    CopyFiles $CMDLINE "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe"
  Pop $R0

  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "DisplayName" $(^Name)
  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "UninstallString" $INSTDIR\Uninst.exe
  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "InstallDir" $INSTDIR
  IfFileExists "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe" "" +2
  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "ModifyPath" "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe"

  IfFileExists "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" NoCreateDB
    CreateDirectory "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini"
    FileOpen $R9 "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" w
    FileClose $R9
  NoCreateDB:

  WriteUninstaller $INSTDIR\Uninst.exe

  ; Remove all components from the database
  Call CM_Uncheck
  SectionEnd

  !endif

  Section `${NAME}` ${ID}

  .InstallComponent${ID}:

  WriteINIStr '$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini' "$(^Name)" "${ID}" 1
  
  !verbose pop

!macroend

!macro SECTION_RO NAME ID DESC

  Var "C_${ID}"

  !verbose push
  !verbose 4
  !echo "CM: Read-only Section: ${NAME} (ID: ${ID})"
  !verbose ${CM_VERBOSE}
  ${FileWrite} GenModifyList `IntOp $0 $0 + 15`
  ${FileWrite} GenModifyList `IntOp $1 $1 + 15`
  ${FileWrite} GenModifyList `IntOp $R8 $R8 + 1`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Settings" NumFields $R8`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Type Checkbox`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Left 6`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Right -1`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Top $0`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Bottom $1`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Text "${NAME}"`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" Flags "DISABLED"`
  ${FileWrite} GenModifyList `${CMIncludeAlt} CompList`
  ${FileWrite} GenModifyList `WriteINIStr $PLUGINSDIR\Modify.ini "Field $R8" State $C_${ID}`
  ${FileWrite} ReadModifyList `IntOp $R8 $R8 + 1`
  ${FileWrite} ReadModifyList `ReadINIStr $C_${ID} $PLUGINSDIR\Modify.ini "Field $R8" State`
  ${FileWrite} DescList `!insertmacro ${CM_USEUI}_DESCRIPTION_TEXT "${${ID}}" "${DESC}"`
  ${FileWrite} CompList `ReadINIStr $C_${ID} "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" "$(^Name)" "${ID}"`
  ${FileWrite} InstList `StrCmp $C_${ID} 1 0 +2`
  ${FileWrite} InstList `Call :.InstallComponent${ID}`
  ${FileWrite} LabelList `Call :.InstallComponent${ID}`
  ${FileWrite} UncheckList `WriteINIStr "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" "$(^Name)" "${ID}" 0`

  !ifndef CM_SEC_INSERTED

    !define CM_SEC_INSERTED

  Section -pre

  .cmPre:
  Push $R0
    System::Call 'kernel32::GetModuleFileNameA(i 0, t .R0, i 1024) i r1'
    CopyFiles $R0 "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe"
    IfFileExists "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe" +2
    CopyFiles $CMDLINE "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe"
  Pop $R0

  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "DisplayName" $(^Name)
  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "UninstallString" $INSTDIR\Uninst.exe
  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "InstallDir" $INSTDIR
  IfFileExists "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe" "" +2
  WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "ModifyPath" "$PROGRAMFILES\Common Files\NSIS Installation Data\$(^Name).exe"

  IfFileExists "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" NoCreateDB
    CreateDirectory "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini"
    FileOpen $R9 "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" w
    FileClose $R9
  NoCreateDB:

  WriteUninstaller $INSTDIR\Uninst.exe

  ; Remove all components from the database
  Call CM_Uncheck
  SectionEnd

  !endif

  Section `${NAME}` ${ID}

  .InstallComponent${ID}:
  SectionIn RO

  WriteINIStr '$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini' "$(^Name)" "${ID}" 1
  
  !verbose pop

!macroend

!macro SECTIONEND
  SectionEnd
!macroend

!macro OUTPATH DIR

  !verbose push
  !verbose 4
  !echo "CM: SetOutPath: ${DIR}"
  !verbose ${CM_VERBOSE}

  ${FileWrite} DirList `RMDir "${DIR}"`
  ${Set} OUTDIR "${DIR}"
  SetOutPath "${DIR}"
  
  !verbose pop

!macroend

!macro FILE O F

  !verbose push
  !verbose 4
  !echo "CM: File: ${F} -> ${OUTDIR}\${O}"
  !verbose ${CM_VERBOSE}

  !ifndef OUTDIR
    !verbose 4
    !error "You did not use $${SetOutPath}.  You need to use $${SetOutPath} before using $${File}."
  !endif

  ${FileWrite} FileList `Delete "${OUTDIR}\${O}"`
  File "/oname=$OUTDIR\${O}" "${F}"
  
  !verbose pop
  
!macroend

!macro SER_REG N P

  DetailPrint "Register Service: ${P} as ${N}"
  SetDetailsPrint none
  Push $OUTDIR
  SetOutPath $PLUGINSDIR
  File "${NSISDIR}\Contrib\Nopey\Nopey.exe"
  nsExec::Exec `"$PLUGINSDIR\Nopey.exe" ser install ${N} "${P}"`
  Pop $OUTDIR
  SetDetailsPrint both
  
!macroend

!macro SER_REM N

  DetailPrint "Remove Service: ${N}"
  SetDetailsPrint none
  Push $OUTDIR
  SetOutPath $PLUGINSDIR
  File "${NSISDIR}\Contrib\Nopey\Nopey.exe"
  nsExec::Exec `"$PLUGINSDIR\Nopey.exe" ser remove ${N}`
  Pop $OUTDIR
  SetDetailsPrint both

!macroend

!macro SER_START N

  DetailPrint "Start Service: ${N}"
  SetDetailsPrint none
  Push $OUTDIR
  SetOutPath $PLUGINSDIR
  File "${NSISDIR}\Contrib\Nopey\Nopey.exe"
  nsExec::Exec `"$PLUGINSDIR\Nopey.exe" ser start ${N}`
  Pop $OUTDIR
  SetDetailsPrint both

!macroend

!macro SER_STOP N

  DetailPrint "Stop Service: ${N}"
  SetDetailsPrint none
  Push $OUTDIR
  SetOutPath $PLUGINSDIR
  File "${NSISDIR}\Contrib\Nopey\Nopey.exe"
  nsExec::Exec `"$PLUGINSDIR\Nopey.exe" ser stop ${N}`
  Pop $OUTDIR
  SetDetailsPrint both

!macroend

!macro COPY_FILE IN OUT

  !ifndef OUTDIR
    !error "You did not use $${SetOutPath}.  You need to use $${SetOutPath} before using $${CopyFiles}."
  !endif

  ${FileWrite} FileList `Delete "${OUTDIR}\${OUT}"`
  CopyFiles `${IN}` `${OUTDIR}\${OUT}`
!macroend

!macro WRITE_REGSTR ROOT KEY VALNAME VAL
  ${FileWrite} FileList `DeleteRegValue ${ROOT} "${KEY}" "${VALNAME}"`
  WriteRegStr "${ROOT}" `${KEY}` `${VALNAME}` `${VAL}`
!macroend

!macro SHORTCUT_START PageID Var

  !define CM_STARTMENU_VAR "${Var}"
  !define CM_STARTMENU_ID  "${PageID}"
  
  !ifdef CM_STARTMENU_REG_ROOT & CM_STARTMENU_REG_KEY & CM_STARTMENU_REG_VALUE
    !define CM_${PageID}_STARTMENU_REG_ROOT `${CM_STARTMENU_REG_ROOT}`
    !define CM_${PageID}_STARTMENU_REG_KEY `${CM_STARTMENU_REG_KEY}`
    !define CM_${PageID}_STARTMENU_REG_VALUE `${CM_STARTMENU_REG_VALUE}`
    !undef CM_STARTMENU_REG_ROOT
    !undef CM_STARTMENU_REG_KEY
    !undef CM_STARTMENU_REG_VALUE
    ${FileWrite} FileList `ReadRegStr $0 "${CM_${PageID}_STARTMENU_REG_ROOT}" "${CM_${PageID}_STARTMENU_REG_KEY}" "${CM_${PageID}_STARTMENU_REG_VALUE}"`
    ${WriteRegStr} `${CM_${PageID}_STARTMENU_REG_ROOT}` `${CM_${PageID}_STARTMENU_REG_KEY}` `${CM_${PageID}_STARTMENU_REG_VALUE}` `${CM_STARTMENU_VAR}`
  !endif
  
  !insertmacro ${CM_USEUI}_STARTMENU_WRITE_BEGIN ${PageID}
  CreateDirectory "$SMPROGRAMS\${CM_STARTMENU_VAR}"
  
!macroend

!macro SHORTCUT_END

  !ifdef CM_${CM_STARTMENU_ID}_STARTMENU_REG_ROOT & CM_${CM_STARTMENU_ID}_STARTMENU_REG_KEY & CM_${CM_STARTMENU_ID}_STARTMENU_REG_VALUE
    ${FileWrite} FileList `RMDir "$SMPROGRAMS\$0"`
  !endif

  !insertmacro ${CM_USEUI}_STARTMENU_WRITE_END
  !undef CM_STARTMENU_VAR
  !undef CM_STARTMENU_ID
!macroend

!macro MAKE_SHORTCUT NAME CMDLINE
  !ifdef CM_${CM_STARTMENU_ID}_STARTMENU_REG_ROOT & CM_${CM_STARTMENU_ID}_STARTMENU_REG_KEY & CM_${CM_STARTMENU_ID}_STARTMENU_REG_VALUE
    ${FileWrite} FileList `Delete "$SMPROGRAMS\$0\${NAME}.lnk"`
  !endif

  CreateShortcut `$SMPROGRAMS\${CM_STARTMENU_VAR}\${NAME}.lnk` `${CMDLINE}`
!macroend

!define Section "!insertmacro SECTION"
!define SectionRO "!insertmacro SECTION_RO"
!define SectionEnd "!insertmacro SECTIONEND"
!define SetOutPath "!insertmacro OUTPATH"
!define File "!insertmacro FILE"
!define RegisterService "!insertmacro SER_REG"
!define RemoveService "!insertmacro SER_REM"
!define StartService "!insertmacro SER_START"
!define StopService "!insertmacro SER_STOP"
!define CopyFiles "!insertmacro COPY_FILE"
!define WriteRegStr "!insertmacro WRITE_REGSTR"
!define StartMenu "!insertmacro SHORTCUT_START"
!define StartMenuEnd "!insertmacro SHORTCUT_END"
!define CreateShortcut "!insertmacro MAKE_SHORTCUT"

!macro CM_SYSTEM

    !insertmacro ${CM_USEUI}_FUNCTION_DESCRIPTION_BEGIN
      ${CMInclude} DescList
    !insertmacro ${CM_USEUI}_FUNCTION_DESCRIPTION_END
    
    Function CM_Uninst
      Delete $INSTDIR\Uninst.exe
      ${CMInclude} "FileList"
      ${CMInclude} "DirList"
      DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
      DeleteINISec "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" "$(^Name)"
      !ifmacrodef CM_UNINST
        !insertmacro CM_UNINST
      !endif
    FunctionEnd
    
    Function un.CM_Uninst
      Delete $INSTDIR\Uninst.exe
      ${CMInclude} "FileList"
      ${CMInclude} "DirList"
      DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
      DeleteINISec "$PROGRAMFILES\Common Files\NSIS Installation Data\ComponentDatabase.ini" "$(^Name)"
      !ifmacrodef CM_UNINST
        !insertmacro CM_UNINST
      !endif
    FunctionEnd
    
  Section "Uninstall"
    StrCmp $INSTDIR $WINDIR DirBad DirGood
    StrCmp $INSTDIR $SYSDIR DirBad DirGood
    StrCmp $INSTDIR $PROGRAMFILES DirBad DirGood
    StrCmp $INSTDIR $SMPROGRAMS DirBad DirGood
      DirBad:
      MessageBox MB_OK "Setup cannot uninstall $(^Name) because $(^Name) was installed in a system folder.$\r$\n$\r$\nPlease click OK to exit Setup."
      Abort
    DirGood:
    StrCpy $CM_UNINST_FULL 1
    Call un.CM_Uninst
  SectionEnd
  
  Page custom cm_maint cm_maint_finish
  Page custom cm_modify cm_modify_finish
  Page custom cm_confirm cm_confirm_finish
  Var CM_MAINTMODE
  
  Function cm_maint
    ReadRegStr $0 HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) UninstallString
    IfFileExists $0 +3
    StrCpy $CM_MAINTMODE 3
    Abort
    !ifdef XPUI_VERSION
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_EXTRACT_AS "${CM_SYSDIR}\res\Maint_XPUI.ini" "Maint.ini"
    !else
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_EXTRACT_AS "${CM_SYSDIR}\res\Maint.ini" "Maint.ini"
    !endif
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_EXTRACT_AS "${CM_SYSDIR}\res\Modify.ico" "Modify.ico"
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_EXTRACT_AS "${CM_SYSDIR}\res\Repair.ico" "Repair.ico"
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_EXTRACT_AS "${CM_SYSDIR}\res\Remove.ico" "Remove.ico"
    WriteINIStr $PLUGINSDIR\Maint.ini "Field 11" Text "This option allows you to change which components of $(^Name) are installed."
    WriteINIStr $PLUGINSDIR\Maint.ini "Field 10" Text "Repairing restores all of the files, settings, shortcuts, and Registry entries that were installed initially.  Use this option if your installation of $(^Name) has become corrupted or stops working."
    WriteINIStr $PLUGINSDIR\Maint.ini "Field 9" Text "This action removes all of $(^Name)'s files, settings, shortcuts, and registry entries from your computer."
    WriteINIStr $PLUGINSDIR\Maint.ini "Field 12" Text "This option runs Setup as usual.  Use this if you are upgrading an existing installation of $(^Name)."
    WriteINIStr $PLUGINSDIR\Maint.ini "Field 5" Text $PLUGINSDIR\Modify.ico
    WriteINIStr $PLUGINSDIR\Maint.ini "Field 6" Text $PLUGINSDIR\Repair.ico
    WriteINIStr $PLUGINSDIR\Maint.ini "Field 7" Text $PLUGINSDIR\Remove.ico
    GetDlgItem $0 $HWNDPARENT 1
    EnableWindow $0 0
    !insertmacro ${CM_USEUI}_HEADER_TEXT "Installation Maintenance" "Modify, repair, or remove $(^Name)."
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_DISPLAY Maint.ini
  FunctionEnd
  
  Function cm_maint_finish
    ReadINIStr $0 $PLUGINSDIR\Maint.ini Settings State
    StrCmp $0 1 Next
    StrCmp $0 2 Next
    StrCmp $0 3 Next
    StrCmp $0 4 Next
    Goto CreateCM
    Next:
    GetDlgItem $0 $HWNDPARENT 1
    EnableWindow $0 1
    Abort
    CreateCM:
    ReadINIStr $0 $PLUGINSDIR\Maint.ini "Field 1" State
    StrCmp $0 1 0 +3
    StrCpy $CM_MAINTMODE 0
    Goto Done
    ReadINIStr $0 $PLUGINSDIR\Maint.ini "Field 2" State
    StrCmp $0 1 0 +3
    StrCpy $CM_MAINTMODE 1
    Goto Done
    ReadINIStr $0 $PLUGINSDIR\Maint.ini "Field 3" State
    StrCmp $0 1 0 +3
    StrCpy $CM_MAINTMODE 2
    Goto Done
    StrCpy $CM_MAINTMODE 3
    Done:
  FunctionEnd
  
  Function cm_modify
    StrCmp $CM_MAINTMODE 0 +2
    Abort
    ${CMInclude} GenModifyList
    !ifdef XPUI_VERSION
      !insertmacro ${CM_USEUI}_HEADER_TEXT "$(${CM_USEUI}_COMPONENTSPAGE_TITLE)" "$(${CM_USEUI}_COMPONENTSPAGE_SUBTITLE)"
    !else
      !insertmacro ${CM_USEUI}_HEADER_TEXT "$(${CM_USEUI}_TEXT_COMPONENTS_TITLE)" "$(${CM_USEUI}_TEXT_COMPONENTS_SUBTITLE)"
    !endif
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_DISPLAY modify.ini
  FunctionEnd
  
  Function cm_modify_finish
    StrCmp $CM_MAINTMODE 0 "" NoMod
    NoMod:
  FunctionEnd
  
  Function cm_confirm
    StrCmp $CM_MAINTMODE 0 Confirm
    StrCmp $CM_MAINTMODE 1 Confirm
    StrCmp $CM_MAINTMODE 2 Confirm
    Abort
    Confirm:
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_EXTRACT_AS "${CM_SYSDIR}\res\Confirm.ini" Confirm.ini
    StrCmp $CM_MAINTMODE 0 Mod
    StrCmp $CM_MAINTMODE 1 Rep
    StrCmp $CM_MAINTMODE 2 Rem
    Abort
    Mod:
    StrCpy $3 "You are about to modify $(^Name)."
    StrCpy $4 "All of the components of $(^Name) that you selected will be replaced.  If you un-selected a component that was previously selected, that component will be removed.  Do you really want to continue?"
    Goto Show
    Rep:
    StrCpy $3 "You are about to repair $(^Name)."
    StrCpy $4 "All of the components of $(^Name) that are currently installed will be replaced.  Do you really want to continue?"
    Goto Show
    Rem:
    StrCpy $3 "You are about to remove $(^Name)."
    StrCpy $4 "All of the components of $(^Name) that are currently installed will be removed.  Do you really want to continue?"
    Show:
    GetDlgItem $0 $HWNDPARENT 1
    SendMessage $0 0xC 0 STR:Yes
    GetDlgItem $0 $HWNDPARENT 2
    SendMessage $0 0xC 0 "STR:No, exit Setup"
    GetDlgItem $0 $HWNDPARENT 3
    SendMessage $0 0xC 0 "STR:No, go back"
    !insertmacro ${CM_USEUI}_INSTALLOPTIONS_INITDIALOG Confirm.ini
    Pop $1
    GetDlgItem $0 $1 1201
    CreateFont $2 Tahoma 8 700
    SendMessage $0 0x30 $2 0
    SendMessage $0 0xC 0 STR:$3
    GetDlgItem $0 $1 1202
    CreateFont $2 Tahoma 8 350
    SendMessage $0 0x30 $2 0
    SendMessage $0 0xC 0 STR:$4
    !insertmacro ${CM_USEUI}_HEADER_TEXT "Confirm Action" "Please confirm the selected action."
    InstallOptions::show
  FunctionEnd
  
  Var CM_DONE

  Function cm_confirm_finish
    StrCmp $${CM_USEUI}_ABORTED 1 "" +2
    Return
    StrCmp $CM_DONE 1 CloseSetup
    StrCmp $CM_MAINTMODE 0 "" NoModify
    GetDlgItem $0 $1 1201
    SendMessage $0 0xC 0 "STR:Please wait..."
    GetDlgItem $0 $1 1202
    SendMessage $0 0xC 0 "STR:Please wait while Setup performs the selected action on $(^Name)."
    Call :.cmPre
    StrCpy $CM_UNINST_FULL 0
    Call CM_Uninst
    ${CMInclude} "ReadModifyList"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
    WriteUninstaller $INSTDIR\Uninst.exe
    WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "DisplayName" $(^Name)
    WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "UninstallString" $INSTDIR\Uninst.exe
    WriteRegStr HKLM Software\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name) "InstallDir" $INSTDIR
    Call CM_Uncheck
    ${CMInclude} "InstList"
    GetDlgItem $0 $1 1201
    SendMessage $0 0xC 0 "STR:$(^Name) has been modified successfully."
    GetDlgItem $0 $1 1202
    SendMessage $0 0xC 0 "STR:Any components of $(^Name) that were not installed before but were checked on the previous page have been installed.  Also, any components of $(^Name) that were installed before but were unchecked on the previous page have been uninstalled.$\n$\nPlease click Finish to exit Setup."
    GetDlgItem $0 $HWNDPARENT 1
    SendMessage $0 0xC 0 STR:Finish
    GetDlgItem $0 $HWNDPARENT 2
    SendMessage $0 0xC 0 STR:Cancel
    EnableWindow $0 0
    GetDlgItem $0 $HWNDPARENT 3
    SendMessage $0 0xC 0 STR:Back
    EnableWindow $0 0
    !insertmacro ${CM_USEUI}_HEADER_TEXT "Action Complete" "The requested action was performed successfully."
    StrCpy $CM_DONE 1
    Abort
    NoModify:
    StrCmp $CM_MAINTMODE 1 "" NoRepair
    GetDlgItem $0 $1 1201
    SendMessage $0 0xC 0 "STR:Please wait..."
    GetDlgItem $0 $1 1202
    SendMessage $0 0xC 0 "STR:Please wait while Setup performs the selected action on $(^Name)."
    StrCpy $CM_UNINST_FULL 0
    Call InstallAll
    GetDlgItem $0 $1 1201
    SendMessage $0 0xC 0 "STR:$(^Name) has been repaired successfully."
    GetDlgItem $0 $1 1202
    SendMessage $0 0xC 0 "STR:All of the components of $(^Name) that were installed have been restored to their original states.$\n$\nPlease click Finish to exit Setup."
    GetDlgItem $0 $HWNDPARENT 1
    SendMessage $0 0xC 0 STR:Finish
    GetDlgItem $0 $HWNDPARENT 2
    SendMessage $0 0xC 0 STR:Cancel
    EnableWindow $0 0
    GetDlgItem $0 $HWNDPARENT 3
    SendMessage $0 0xC 0 STR:Back
    EnableWindow $0 0
    !insertmacro ${CM_USEUI}_HEADER_TEXT "Action Complete" "The requested action was performed successfully."
    StrCpy $CM_DONE 1
    Abort
    NoRepair:
    StrCmp $CM_MAINTMODE 2 "" NoRemove
    GetDlgItem $0 $1 1201
    SendMessage $0 0xC 0 "STR:Please wait..."
    GetDlgItem $0 $1 1202
    SendMessage $0 0xC 0 "STR:Please wait while Setup performs the selected action on $(^Name)."
    
    Call :.cmPre
    StrCpy $CM_UNINST_FULL 1
    Call CM_Uninst
    Sleep 2000
    
    GetDlgItem $0 $1 1201
    SendMessage $0 0xC 0 "STR:$(^Name) has been uninstalled successfully."
    GetDlgItem $0 $1 1202
    SendMessage $0 0xC 0 "STR:All of the components of $(^Name) that were installed have been removed.  In addition, any hidden or required components, registry entries, Start Menu groups, and shortcuts related to $(^Name) have been removed.$\n$\nPlease click Finish to exit Setup."
    GetDlgItem $0 $HWNDPARENT 1
    SendMessage $0 0xC 0 STR:Finish
    GetDlgItem $0 $HWNDPARENT 2
    SendMessage $0 0xC 0 STR:Cancel
    EnableWindow $0 0
    GetDlgItem $0 $HWNDPARENT 3
    SendMessage $0 0xC 0 STR:Back
    EnableWindow $0 0
    !insertmacro ${CM_USEUI}_HEADER_TEXT "Action Complete" "The requested action was performed successfully."
    StrCpy $CM_DONE 1
    Abort
    CloseSetup:
    !ifdef XPUI_INCLUDED
    Call .onGUIend
    !endif
    Quit
    NoRemove:
  FunctionEnd
  
  Function CM_Uncheck
    ${CMInclude} UncheckList
  FunctionEnd
  
  Function InstallAll
    ${CMInclude} CompList
    Call CM_Uninst
    Call :.cmPre
    ${CMInclude} InstList
  FunctionEnd
  
  ${FileClose} CompList
  ${FileClose} InstList
  ${FileClose} DescList
  ${FileClose} LabelList
  ${FileClose} ReadModifyList
  ${FileClose} GenModifyList
  ${FileClose} UncheckList
  ${FileClose} FileList
  ${FileClose} DirList
  
!macroend