; NSIS Component Manager - File Manipulation System
; Used to control temporary script creation at compile time
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

!define NSIS_STRLEN_CHECK_${NSIS_MAX_STRLEN}
!ifndef  NSIS_STRLEN_CHECK_8192
  !warning "It is highly recommended that you compile this program with a special build of NSIS that allows 8,192 character strings or higher!"
!endif

Caption "NSIS Compile-time File Manipulation agent"
OutFile FileMan.exe
Icon Icon.ico
SilentInstall Silent
Section
Call GetParameters
  Pop $0
  StrCpy $1 $0 13
  StrCmp $1 /Special:Init init
  StrCmp $1 /Special:Fini close
  Push $0
  Push "/Text:"
  Call StrStr
  Pop $0
  StrCpy $0 $0 "" 6
  StrCmp $0 "" "" Found
  MessageBox MB_OK|MB_ICONEXCLAMATION "File manipulation: cannot open stored file!"
  SetErrorLevel 1
  Quit
  Found:
  ; $0 contains the text to write
  Call GetParameters
  Pop $2
  StrLen $1 $0
  IntOp $1 $1 + 7
  StrLen $3 $2
  IntOp $3 $3 - $1
  StrCpy $2 $2 $3
  ;MessageBox MB_OK `Text: "$0"$\nFile: "$2"`
  StrCpy $3 ""
  FileOpen $4 $2 r
    FileRead $4 $3 ${NSIS_MAX_STRLEN}
    StrCpy $5 $3
    ;MessageBox MB_OK $5
    readloop:
    FileRead $4 $3
    StrCpy $5 $5$3
    IfErrors "" readloop
    ;MessageBox MB_OK $5
  FileClose $4
  FileOpen $2 $2 w
    StrCpy $4 $0
    StrCmp $5 "" +2
    StrCpy $4 $5$\r$\n$0
    FileWrite $2 "$4"
    ;MessageBox MB_OK "$$0: $0$\n$$1: $1$\n$$2: $2$\n$$3: $3$\n$$5: $5"
  FileClose $2
  Return
  Init:
  StrCpy $0 $0 "" 14
  Delete $0
  FileOpen $1 "$0" w
  FileClose $1
  Return
  Close:
  StrCpy $0 $0 "" 14
  Delete $0
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

 Function StrStr
   Exch $R1 ; st=haystack,old$R1, $R1=needle
   Exch    ; st=old$R1,haystack
   Exch $R2 ; st=old$R1,old$R2, $R2=haystack
   Push $R3
   Push $R4
   Push $R5
   StrLen $R3 $R1
   StrCpy $R4 0
   ; $R1=needle
   ; $R2=haystack
   ; $R3=len(needle)
   ; $R4=cnt
   ; $R5=tmp
   loop:
     StrCpy $R5 $R2 $R3 $R4
     StrCmp $R5 $R1 done
     StrCmp $R5 "" done
     IntOp $R4 $R4 + 1
     Goto loop
 done:
   StrCpy $R1 $R2 "" $R4
   Pop $R5
   Pop $R4
   Pop $R3
   Pop $R2
   Exch $R1
 FunctionEnd
