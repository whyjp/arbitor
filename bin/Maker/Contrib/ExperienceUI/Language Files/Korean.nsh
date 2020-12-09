;NSIS ExperienceUI - Language File
;Compatible with ExperienceUI 1.09

;Language: Korean (1042)
;By Hell Master, http://jgh0721.egloos.com

;--------------------------------

!insertmacro XPUI_LANGUAGEFILE_BEGIN "Korean"

; Use only ASCII characters (if this is not possible, use the English name)
!insertmacro XPUI_UNSET XPUI_LANGNAME
!insertmacro XPUI_DEFAULT XPUI_LANGNAME "Korean"

; BUTTONS
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_NEXT   다음
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_BACK   이전
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_CANCEL 취소
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_CLOSE  닫기

!insertmacro XPUI_DEFAULT XPUI_ABORTWARNING_TEXT "설치를 중단하려고 합니다.$\n$\n지금 종료하면, $(^Name) 는 설치되지 않습니다.$\n$\n계속 하시겠습니까?"

; +---------+
; | INSTALL |
; +---------+

; WELCOME PAGE
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TEXT_TOP "$(^Name) 설치 마법사를 시작합니다."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TEXT "설치마법사는 $(^Name) 의 설치를 안내합니다.\r\n\r\n설치를 시작하기 전에 모든 다른 프로그램을 종료하는 것을 권장합니다. 그러면 컴퓨터를 재부팅하지 않고 관련된 시스템 파일을 업데이트할 수 있습니다.\r\n\r\n"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TITLE "환영합니다"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_SUBTITLE "$(^Name) 를 설치하는 것을 환영합니다."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_CAPTION " "

!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TEXT_TOP "$(^Name) 설치제거 마법사를 시작합니다."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TEXT "설치마법사는 $(^Name) 설치제거를 안내합니다.\r\n\r\n설치제거를 시작하기 전에 모든 프로그램을 종료하는 것을 권장합니다. 그러면 커뮤터를 재부팅하지 않고 관련된 시스템 파일을 업데이트할 수 있습니다.\r\n\r\n"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TITLE "환영합니다"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_SUBTITLE "$(^Name) 를 설치제거를 시작합니다."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_CAPTION " "

; WELCOME PAGE STYLE 2
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_TEXT_TOP "$(^Name) NSIS 설치 마법사를 시작합니다."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_TEXT "$(^Name) NSIS 설치 마법사를 시작합니다. 이 설치마법사는 이 컴퓨터에 $(^Name) 를 설치합니다."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_TITLE "환영합니다"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_SUBTITLE "$(^Name) 를 설치하는 것을 환영합니다."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_CAPTION " "

!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_TEXT_TOP "$(^Name) NSIS 설치제거 마법사를 시작합니다."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_TEXT "$(^Name) NSIS 설치 마법사를 시작합니다. 이 설치마법사는 이 컴퓨터에서 $(^Name) 를 설치제거합니다."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_TITLE "환영합니다"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_SUBTITLE "$(^Name) 를 설치제거를 시작합니다."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_CAPTION " "

; LICENSE PAGE
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_CAPTION ": 라이센스 동의문"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_RADIOBUTTONS_TEXT_ACCEPT "나는 위의 라이센스에 동의합니다"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_RADIOBUTTONS_TEXT_DECLINE "나는 위의 라이센스에 동의하지 않습니다"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_CHECKBOX "나는 위의 라이센스에 동의합니다"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_SUBTITLE "$(^Name) 를 설치하기 전에 라이센스를 살펴보십시요."
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TITLE "라이센스 동의문"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_TOP "라이센스 동의문의 나머지를 보려면 Page Down 키를 누르십시요."
!ifndef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "내용에 동의하셨다면 동의합니다를 선택하십시요. $(^Name) 설치하기 위해서는 반드시 내용에 동의하셔야 합니다."
  !endif
!endif
!ifndef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifdef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "내용에 동의하셨다면 아래 선택상자를 선택해 주세요. $(^Name) 설치하기 위해서는 반드시 내용에 동의하셔야 합니다."
  !endif
!endif
!ifdef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "내용에 동의하셨다면 첫 번째 사항을 선택해 주세요. $(^Name) 설치하기 위해서는 반드시 내용에 동의하셔야 합니다."
  !endif
!endif

!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_CAPTION ": 라이센스 동의문"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_RADIOBUTTONS_TEXT_ACCEPT "나는 위의 라이센스에 동의합니다"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_RADIOBUTTONS_TEXT_DECLINE "나는 위의 라이센스에 동의하지 않습니다"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_CHECKBOX "나는 위의 라이센스에 동의합니다"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_SUBTITLE "$(^Name) 를 설치제거하기 전에 라이센스를 살펴보십시요."
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TITLE "라이센스 동의문"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_TOP "라이센스 동의문의 나머지를 보려면 Page Down 키를 누르십시요."
!ifndef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "내용에 동의하셨다면 동의합니다를 선택하십시요. $(^NameDA) 설치제거하기 위해서는 반드시 내용에 동의하셔야 합니다."
  !endif
!endif
!ifndef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifdef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "내용에 동의하셨다면 아래 선택상자를 선택해 주세요. $(^NameDA) 설치제거하기 위해서는 반드시 내용에 동의하셔야 합니다."
  !endif
!endif
!ifdef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "내용에 동의하셨다면 첫 번째 사항을 선택해 주세요. $(^NameDA) 설치제거하기 위해서는 반드시 내용에 동의하셔야 합니다."
  !endif
!endif

; COMPONENTS PAGE
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_CAPTION ": 구성요소 선택"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_SUBTITLE "설치할 $(^Name) 의 구성요소를 선택합니다."
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TITLE "구성요소 선택"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TEXT_DESCRIPTION_TITLE "설명"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TEXT_DESCRIPTION_INFO  "설명을 보려는 컴포넌트 위로 마우스를 이동시키십시요"

!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_CAPTION ": 구성요소 선택"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_SUBTITLE "설치제거하려는 $(^Name) 의 구성요소를 선택합니다."
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TITLE "구성요소 선택"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TEXT_DESCRIPTION_TITLE "설명"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TEXT_DESCRIPTION_INFO  "설명을 보려는 컴포넌트 위로 마우스를 이동시키십시요"

; DIRECTORY PAGE
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_CAPTION ": 설치 폴더 선택"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_TOP "설치마법사는 아래 폴더에 $(^Name) 을 설치합니다.\r\n\r\n기본 폴더에 설치하려면 아래 폴더를 그대로 설치하십시요. 다른 폴더에 설치하려면 찾아보기 버튼을 누르십시요. $_CLICK"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_DESTINATION "설치 디렉토리"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_BROWSE "찾아보기"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_BROWSEDIALOG "폴더를 선택해 주세요 :"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TITLE "설치 위치 선택"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_SUBTITLE "$(^Name) 을 설치할 폴더를 선택합니다."

!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_CAPTION ": 설치 폴더 선택"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_TOP "설치마법사는 아래폴더로부터 $(^Name) 을 설치제거합니다.\r\n\r\n이 폴더로부터 설치제거하려면 다음을 누르십시요. 다른 폴더로부터 설치제거하려면 찾아보기 버튼을 누르십시요."
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_DESTINATION "설치 디렉토리"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_BROWSE "찾아보기"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_BROWSEDIALOG "폴더를 선택해 주세요 :"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TITLE "설치 위치 선택"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_SUBTITLE "$(^Name) 를 설치제거할 폴더를 선택합니다."

; START MENU PAGE
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_CAPTION    ": 시작 메뉴 폴더"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_TITLE      "시작 메뉴 폴더 선택"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_SUBTITLE   "$(^Name) 에 대한 시작 메뉴 단축아이콘을 만들 폴더를 선택하세요 : "
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_TEXT       "$(^Name) 에 대한 시작 메뉴 단축아이콘을 폴더를 선택하세요 :"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_CHECKBOX   "시작 메뉴 폴더를 만들지 않습니다"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_FOLDER     "$(^Name)"

!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_CAPTION  ": 시작 메뉴 폴더"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_TITLE    "시작 메뉴 폴더 선택"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_SUBTITLE "시작 메뉴 단축아이콘을 삭제할 폴더를 선택하세요 :"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_TEXT     "시작 메뉴 단축아이콘을 삭제할 폴더를 선택하세요 :"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_CHECKBOX "시작 메뉴 폴더를 삭제하지 않습니다"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_FOLDER   "$(^Name)"

; INSTALL CONFIRM PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_CAPTION ": 설치 확인"
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_SUBTITLE "설치마법사는 $(^Name) 설치를 위한 준비를 끝마쳤습니다."
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TITLE "설치 확인"
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TEXT_TOP "설치마법사는 $(^Name) 를 설치할 준비가 되었습니다."
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TEXT_BOTTOM "$_CLICK"

!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_CAPTION ": 설치제거 확인"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_SUBTITLE "설치마법사는 $(^Name) 설치제거를 위한 준비를 끝마쳤습니다."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TITLE "설치제거 확인"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TEXT_TOP "설치마법사는 $(^Name) 를 설치제거할 준비가 되었습니다."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TEXT_BOTTOM "계속하려면 다음을 누르세요."

; INSTFILES PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_CAPTION ": 파일 복사"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_SUBTITLE "$(^Name) 를 설치하는 동안 기다려주세요."
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_TITLE "설치중..."
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_DONE_TITLE "설치 완료"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_DONE_SUBTITLE "$(^Name) 의 모든 구성요소가 성공적으로 복사되었습니다."

!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_CAPTION ": 파일 삭제"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_SUBTITLE "$(^Name) 를 설치제거하는 동안 기다려주세요."
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_TITLE "설치제거중..."
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_DONE_TITLE "설치제거 완료"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_DONE_SUBTITLE "$(^Name) 의 모든 구성요소가 성공적으로 제거되었습니다."
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_FAIL_TITLE "설치 실패"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_FAIL_SUBTITLE "$(^Name) 설치가 성공적으로 완료되지 못하였습니다.."
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_FAIL_TITLE "설치제거 실패"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_FAIL_SUBTITLE "$(^Name) 설치제거가 실패하였습니다."

; INSTALL SUCCESS PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_CAPTION ": 설치 성공"
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_SUBTITLE "$(^Name) 를 성공적으로 설치하였습니다."
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TITLE "설치완료"
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TEXT_TOP    "$(^Name) 가 성공적으로 설치되었습니다."
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TEXT_BOTTOM "종료하려면 닫기를 누르세요."

!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_CAPTION ": 설치제거 성공"
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_SUBTITLE "$(^Name) 를 성공적으로 설치제거하였습니다."
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TITLE "설치제거 완료"
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TEXT_TOP    "$(^Name) 를 성공적으로 설치제거하였습니다."
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TEXT_BOTTOM "종료하려면 닫기를 누르세요."

; FINISH PAGE

!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TITLE "설치 완료"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_SUBTITLE "$(^Name) 를 성공적으로 설치하였습니다."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CAPTION ": 설치 완료"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_TOP "$(^Name) 설치완료중"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_TOP_ALT "NSIS 설치마법사 완료"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_RUN "$(^Name) 를 성공적으로 설치하였습니다.\r\n\r\n어떤 작업을 하시겠습니까?"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_REBOOT "설치마법사는 파일을 복사하였습니다.\r\n\r\n설치를 완료하려면 컴퓨터를 재부팅해야합니다. 지금 컴퓨터를 재부팅하시겠습니까?"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT "$(^Name) 설치를 성공적으로 완료하였습니다.\r\n\r\n설치마법사를 종료하려면 $(XPUI_BUTTONTEXT_CLOSE) 를 누르세요."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CHECKBOX_RUN "지금 $(^Name) 실행합니다"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CHECKBOX_DOCS "$(^Name) 에 대한 문서를 봅니다"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_RADIOBUTTON_REBOOT "예, 지금 리부팅합니다."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_RADIOBUTTON_NOREBOOT "아니오, 나중에 하겠습니다."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_REBOOT_MESSAGEBOX "설치마법사는 컴퓨터를 재부팅하려고 합니다.$\r$\n$\r$\n작업을 저장하고 확인을 누르면 컴푸퓨터를 재부팅합니다."

!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TITLE "설치제거 완료"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_SUBTITLE "$(^Name) 를 성공적으로 설치제거하였습니다."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_CAPTION ": 설치제거 완료"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_TOP "$(^Name) 설치제거완료중"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_TOP_ALT "NSIS 설치마법사 완료"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_REBOOT "설치마법사는 파일을 제거하였습니다.\r\n\r\n설치제거를 완료하려면 컴퓨터를 재부팅해야합니다. 지금 컴퓨터를 재부팅하시겠습니까?"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_RUN "설치마법사는 $(^Name) 를 성공적으로 제거하였습니다.\r\n\r\n어떤 작업을 하시겠습니까?"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT "설치마법사는 $(^Name) 를 성공적으로 제거하였습니다.\r\n\r\n설치마법사를 종료하려면 $(XPUI_BUTTONTEXT_CLOSE) 를 누르세요."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_RADIOBUTTON_REBOOT "예, 지금 리부팅합니다."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_RADIOBUTTON_NOREBOOT "아니오, 나중에 하겠습니다."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_CHECKBOX_RUN "${XPUI_FINISHPAGE_CHECKBOX_RUN}"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_CHECKBOX_DOCS "${XPUI_FINISHPAGE_CHECKBOX_DOCS}"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_REBOOT_MESSAGEBOX "${XPUI_FINISHPAGE_REBOOT_MESSAGEBOX}"

; ABORT PAGE
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TEXT_TOP "NSIS 설치마법사 완료"
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TEXT "$(^Name) 설치가 사용자에의해 완료되지 못했습니다.\r\n\r\n시스템이 변경되지 않았습니다. 나중에 설치하려면 이 마법사를 실행하세요.\r\n\r\n\r\n\r\n\r\n설치마법사를 종료하려면 닫기를 누르세요."
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TITLE "설치가 중단되었습니다."
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_SUBTITLE "$(^Name) 설치가 완료되지 않았습니다."
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_CAPTION ": 설치가 취소되었습니다"

!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TEXT_TOP "NSIS 설치제거마법사 완료"
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TEXT "$(^Name) 설치제거가 사용자에의해 완료되지 못했습니다.\r\n\r\n시스템이 변경되지 않았습니다. 나중에 설치제거하려면 이 마법사를 실행하세요.\r\n\r\n\r\n\r\n\r\n설치마법사를 종료하려면 닫기를 누르세요."
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TITLE "설치제거가 완료되지 않았습니다"
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_SUBTITLE "$(^Name) 설치제거가 완료되지 않았습니다."
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_CAPTION ": 설치제거가 취소되었습니다"

; +-----------+
; | UNINSTALL |
; +-----------+

; MOST OF THE UNINSTALL PAGES ARE TAKEN CARE OF USING THE PAGE MODE SYSTEM
; THE XPUI CONFIRM, UNINSTFILES, AND SUCCESS PAGES USE THE PAGE MODE SYSTEM,
; BUT THE NSIS-STYLE UNINSTALL CONFIRM PAGE SIMPLY USES A NON-PAGE-MODE METHOD.

; UNINST CONFIRM PAGE (NSIS)
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_CAPTION ": 설치제거 확인"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_SUBTITLE "$(^Name) 를 삭제합니다"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TITLE "$(^Name) 설치제거"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TEXT_TOP "아래 폴더에서 $(^Name) 는 삭제됩니다. 설치제거를 시작하려면 설치제거를 누르세요."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TEXT_FOLDER "설치제거 폴더 :"

!insertmacro XPUI_LANGUAGEFILE_END
