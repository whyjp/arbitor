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
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_NEXT   ����
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_BACK   ����
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_CANCEL ���
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_CLOSE  �ݱ�

!insertmacro XPUI_DEFAULT XPUI_ABORTWARNING_TEXT "��ġ�� �ߴ��Ϸ��� �մϴ�.$\n$\n���� �����ϸ�, $(^Name) �� ��ġ���� �ʽ��ϴ�.$\n$\n��� �Ͻðڽ��ϱ�?"

; +---------+
; | INSTALL |
; +---------+

; WELCOME PAGE
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TEXT_TOP "$(^Name) ��ġ �����縦 �����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TEXT "��ġ������� $(^Name) �� ��ġ�� �ȳ��մϴ�.\r\n\r\n��ġ�� �����ϱ� ���� ��� �ٸ� ���α׷��� �����ϴ� ���� �����մϴ�. �׷��� ��ǻ�͸� ��������� �ʰ� ���õ� �ý��� ������ ������Ʈ�� �� �ֽ��ϴ�.\r\n\r\n"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TITLE "ȯ���մϴ�"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_SUBTITLE "$(^Name) �� ��ġ�ϴ� ���� ȯ���մϴ�."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_CAPTION " "

!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TEXT_TOP "$(^Name) ��ġ���� �����縦 �����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TEXT "��ġ������� $(^Name) ��ġ���Ÿ� �ȳ��մϴ�.\r\n\r\n��ġ���Ÿ� �����ϱ� ���� ��� ���α׷��� �����ϴ� ���� �����մϴ�. �׷��� Ŀ���͸� ��������� �ʰ� ���õ� �ý��� ������ ������Ʈ�� �� �ֽ��ϴ�.\r\n\r\n"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TITLE "ȯ���մϴ�"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_SUBTITLE "$(^Name) �� ��ġ���Ÿ� �����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_CAPTION " "

; WELCOME PAGE STYLE 2
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_TEXT_TOP "$(^Name) NSIS ��ġ �����縦 �����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_TEXT "$(^Name) NSIS ��ġ �����縦 �����մϴ�. �� ��ġ������� �� ��ǻ�Ϳ� $(^Name) �� ��ġ�մϴ�."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_TITLE "ȯ���մϴ�"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_SUBTITLE "$(^Name) �� ��ġ�ϴ� ���� ȯ���մϴ�."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGESTYLE2_CAPTION " "

!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_TEXT_TOP "$(^Name) NSIS ��ġ���� �����縦 �����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_TEXT "$(^Name) NSIS ��ġ �����縦 �����մϴ�. �� ��ġ������� �� ��ǻ�Ϳ��� $(^Name) �� ��ġ�����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_TITLE "ȯ���մϴ�"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_SUBTITLE "$(^Name) �� ��ġ���Ÿ� �����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGESTYLE2_CAPTION " "

; LICENSE PAGE
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_CAPTION ": ���̼��� ���ǹ�"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_RADIOBUTTONS_TEXT_ACCEPT "���� ���� ���̼����� �����մϴ�"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_RADIOBUTTONS_TEXT_DECLINE "���� ���� ���̼����� �������� �ʽ��ϴ�"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_CHECKBOX "���� ���� ���̼����� �����մϴ�"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_SUBTITLE "$(^Name) �� ��ġ�ϱ� ���� ���̼����� ���캸�ʽÿ�."
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TITLE "���̼��� ���ǹ�"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_TOP "���̼��� ���ǹ��� �������� ������ Page Down Ű�� �����ʽÿ�."
!ifndef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "���뿡 �����ϼ̴ٸ� �����մϴٸ� �����Ͻʽÿ�. $(^Name) ��ġ�ϱ� ���ؼ��� �ݵ�� ���뿡 �����ϼž� �մϴ�."
  !endif
!endif
!ifndef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifdef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "���뿡 �����ϼ̴ٸ� �Ʒ� ���û��ڸ� ������ �ּ���. $(^Name) ��ġ�ϱ� ���ؼ��� �ݵ�� ���뿡 �����ϼž� �մϴ�."
  !endif
!endif
!ifdef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "���뿡 �����ϼ̴ٸ� ù ��° ������ ������ �ּ���. $(^Name) ��ġ�ϱ� ���ؼ��� �ݵ�� ���뿡 �����ϼž� �մϴ�."
  !endif
!endif

!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_CAPTION ": ���̼��� ���ǹ�"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_RADIOBUTTONS_TEXT_ACCEPT "���� ���� ���̼����� �����մϴ�"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_RADIOBUTTONS_TEXT_DECLINE "���� ���� ���̼����� �������� �ʽ��ϴ�"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_CHECKBOX "���� ���� ���̼����� �����մϴ�"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_SUBTITLE "$(^Name) �� ��ġ�����ϱ� ���� ���̼����� ���캸�ʽÿ�."
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TITLE "���̼��� ���ǹ�"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_TOP "���̼��� ���ǹ��� �������� ������ Page Down Ű�� �����ʽÿ�."
!ifndef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "���뿡 �����ϼ̴ٸ� �����մϴٸ� �����Ͻʽÿ�. $(^NameDA) ��ġ�����ϱ� ���ؼ��� �ݵ�� ���뿡 �����ϼž� �մϴ�."
  !endif
!endif
!ifndef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifdef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "���뿡 �����ϼ̴ٸ� �Ʒ� ���û��ڸ� ������ �ּ���. $(^NameDA) ��ġ�����ϱ� ���ؼ��� �ݵ�� ���뿡 �����ϼž� �մϴ�."
  !endif
!endif
!ifdef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "���뿡 �����ϼ̴ٸ� ù ��° ������ ������ �ּ���. $(^NameDA) ��ġ�����ϱ� ���ؼ��� �ݵ�� ���뿡 �����ϼž� �մϴ�."
  !endif
!endif

; COMPONENTS PAGE
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_CAPTION ": ������� ����"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_SUBTITLE "��ġ�� $(^Name) �� ������Ҹ� �����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TITLE "������� ����"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TEXT_DESCRIPTION_TITLE "����"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TEXT_DESCRIPTION_INFO  "������ ������ ������Ʈ ���� ���콺�� �̵���Ű�ʽÿ�"

!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_CAPTION ": ������� ����"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_SUBTITLE "��ġ�����Ϸ��� $(^Name) �� ������Ҹ� �����մϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TITLE "������� ����"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TEXT_DESCRIPTION_TITLE "����"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TEXT_DESCRIPTION_INFO  "������ ������ ������Ʈ ���� ���콺�� �̵���Ű�ʽÿ�"

; DIRECTORY PAGE
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_CAPTION ": ��ġ ���� ����"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_TOP "��ġ������� �Ʒ� ������ $(^Name) �� ��ġ�մϴ�.\r\n\r\n�⺻ ������ ��ġ�Ϸ��� �Ʒ� ������ �״�� ��ġ�Ͻʽÿ�. �ٸ� ������ ��ġ�Ϸ��� ã�ƺ��� ��ư�� �����ʽÿ�. $_CLICK"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_DESTINATION "��ġ ���丮"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_BROWSE "ã�ƺ���"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_BROWSEDIALOG "������ ������ �ּ��� :"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TITLE "��ġ ��ġ ����"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_SUBTITLE "$(^Name) �� ��ġ�� ������ �����մϴ�."

!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_CAPTION ": ��ġ ���� ����"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_TOP "��ġ������� �Ʒ������κ��� $(^Name) �� ��ġ�����մϴ�.\r\n\r\n�� �����κ��� ��ġ�����Ϸ��� ������ �����ʽÿ�. �ٸ� �����κ��� ��ġ�����Ϸ��� ã�ƺ��� ��ư�� �����ʽÿ�."
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_DESTINATION "��ġ ���丮"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_BROWSE "ã�ƺ���"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_BROWSEDIALOG "������ ������ �ּ��� :"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TITLE "��ġ ��ġ ����"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_SUBTITLE "$(^Name) �� ��ġ������ ������ �����մϴ�."

; START MENU PAGE
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_CAPTION    ": ���� �޴� ����"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_TITLE      "���� �޴� ���� ����"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_SUBTITLE   "$(^Name) �� ���� ���� �޴� ����������� ���� ������ �����ϼ��� : "
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_TEXT       "$(^Name) �� ���� ���� �޴� ����������� ������ �����ϼ��� :"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_CHECKBOX   "���� �޴� ������ ������ �ʽ��ϴ�"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_FOLDER     "$(^Name)"

!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_CAPTION  ": ���� �޴� ����"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_TITLE    "���� �޴� ���� ����"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_SUBTITLE "���� �޴� ����������� ������ ������ �����ϼ��� :"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_TEXT     "���� �޴� ����������� ������ ������ �����ϼ��� :"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_CHECKBOX "���� �޴� ������ �������� �ʽ��ϴ�"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_FOLDER   "$(^Name)"

; INSTALL CONFIRM PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_CAPTION ": ��ġ Ȯ��"
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_SUBTITLE "��ġ������� $(^Name) ��ġ�� ���� �غ� �����ƽ��ϴ�."
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TITLE "��ġ Ȯ��"
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TEXT_TOP "��ġ������� $(^Name) �� ��ġ�� �غ� �Ǿ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TEXT_BOTTOM "$_CLICK"

!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_CAPTION ": ��ġ���� Ȯ��"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_SUBTITLE "��ġ������� $(^Name) ��ġ���Ÿ� ���� �غ� �����ƽ��ϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TITLE "��ġ���� Ȯ��"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TEXT_TOP "��ġ������� $(^Name) �� ��ġ������ �غ� �Ǿ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TEXT_BOTTOM "����Ϸ��� ������ ��������."

; INSTFILES PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_CAPTION ": ���� ����"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_SUBTITLE "$(^Name) �� ��ġ�ϴ� ���� ��ٷ��ּ���."
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_TITLE "��ġ��..."
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_DONE_TITLE "��ġ �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_DONE_SUBTITLE "$(^Name) �� ��� ������Ұ� ���������� ����Ǿ����ϴ�."

!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_CAPTION ": ���� ����"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_SUBTITLE "$(^Name) �� ��ġ�����ϴ� ���� ��ٷ��ּ���."
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_TITLE "��ġ������..."
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_DONE_TITLE "��ġ���� �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_DONE_SUBTITLE "$(^Name) �� ��� ������Ұ� ���������� ���ŵǾ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_FAIL_TITLE "��ġ ����"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_FAIL_SUBTITLE "$(^Name) ��ġ�� ���������� �Ϸ���� ���Ͽ����ϴ�.."
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_FAIL_TITLE "��ġ���� ����"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_FAIL_SUBTITLE "$(^Name) ��ġ���Ű� �����Ͽ����ϴ�."

; INSTALL SUCCESS PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_CAPTION ": ��ġ ����"
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_SUBTITLE "$(^Name) �� ���������� ��ġ�Ͽ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TITLE "��ġ�Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TEXT_TOP    "$(^Name) �� ���������� ��ġ�Ǿ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TEXT_BOTTOM "�����Ϸ��� �ݱ⸦ ��������."

!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_CAPTION ": ��ġ���� ����"
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_SUBTITLE "$(^Name) �� ���������� ��ġ�����Ͽ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TITLE "��ġ���� �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TEXT_TOP    "$(^Name) �� ���������� ��ġ�����Ͽ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TEXT_BOTTOM "�����Ϸ��� �ݱ⸦ ��������."

; FINISH PAGE

!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TITLE "��ġ �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_SUBTITLE "$(^Name) �� ���������� ��ġ�Ͽ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CAPTION ": ��ġ �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_TOP "$(^Name) ��ġ�Ϸ���"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_TOP_ALT "NSIS ��ġ������ �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_RUN "$(^Name) �� ���������� ��ġ�Ͽ����ϴ�.\r\n\r\n� �۾��� �Ͻðڽ��ϱ�?"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_REBOOT "��ġ������� ������ �����Ͽ����ϴ�.\r\n\r\n��ġ�� �Ϸ��Ϸ��� ��ǻ�͸� ������ؾ��մϴ�. ���� ��ǻ�͸� ������Ͻðڽ��ϱ�?"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT "$(^Name) ��ġ�� ���������� �Ϸ��Ͽ����ϴ�.\r\n\r\n��ġ�����縦 �����Ϸ��� $(XPUI_BUTTONTEXT_CLOSE) �� ��������."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CHECKBOX_RUN "���� $(^Name) �����մϴ�"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CHECKBOX_DOCS "$(^Name) �� ���� ������ ���ϴ�"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_RADIOBUTTON_REBOOT "��, ���� �������մϴ�."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_RADIOBUTTON_NOREBOOT "�ƴϿ�, ���߿� �ϰڽ��ϴ�."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_REBOOT_MESSAGEBOX "��ġ������� ��ǻ�͸� ������Ϸ��� �մϴ�.$\r$\n$\r$\n�۾��� �����ϰ� Ȯ���� ������ ��Ǫǻ�͸� ������մϴ�."

!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TITLE "��ġ���� �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_SUBTITLE "$(^Name) �� ���������� ��ġ�����Ͽ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_CAPTION ": ��ġ���� �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_TOP "$(^Name) ��ġ���ſϷ���"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_TOP_ALT "NSIS ��ġ������ �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_REBOOT "��ġ������� ������ �����Ͽ����ϴ�.\r\n\r\n��ġ���Ÿ� �Ϸ��Ϸ��� ��ǻ�͸� ������ؾ��մϴ�. ���� ��ǻ�͸� ������Ͻðڽ��ϱ�?"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_RUN "��ġ������� $(^Name) �� ���������� �����Ͽ����ϴ�.\r\n\r\n� �۾��� �Ͻðڽ��ϱ�?"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT "��ġ������� $(^Name) �� ���������� �����Ͽ����ϴ�.\r\n\r\n��ġ�����縦 �����Ϸ��� $(XPUI_BUTTONTEXT_CLOSE) �� ��������."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_RADIOBUTTON_REBOOT "��, ���� �������մϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_RADIOBUTTON_NOREBOOT "�ƴϿ�, ���߿� �ϰڽ��ϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_CHECKBOX_RUN "${XPUI_FINISHPAGE_CHECKBOX_RUN}"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_CHECKBOX_DOCS "${XPUI_FINISHPAGE_CHECKBOX_DOCS}"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_REBOOT_MESSAGEBOX "${XPUI_FINISHPAGE_REBOOT_MESSAGEBOX}"

; ABORT PAGE
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TEXT_TOP "NSIS ��ġ������ �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TEXT "$(^Name) ��ġ�� ����ڿ����� �Ϸ���� ���߽��ϴ�.\r\n\r\n�ý����� ������� �ʾҽ��ϴ�. ���߿� ��ġ�Ϸ��� �� �����縦 �����ϼ���.\r\n\r\n\r\n\r\n\r\n��ġ�����縦 �����Ϸ��� �ݱ⸦ ��������."
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TITLE "��ġ�� �ߴܵǾ����ϴ�."
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_SUBTITLE "$(^Name) ��ġ�� �Ϸ���� �ʾҽ��ϴ�."
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_CAPTION ": ��ġ�� ��ҵǾ����ϴ�"

!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TEXT_TOP "NSIS ��ġ���Ÿ����� �Ϸ�"
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TEXT "$(^Name) ��ġ���Ű� ����ڿ����� �Ϸ���� ���߽��ϴ�.\r\n\r\n�ý����� ������� �ʾҽ��ϴ�. ���߿� ��ġ�����Ϸ��� �� �����縦 �����ϼ���.\r\n\r\n\r\n\r\n\r\n��ġ�����縦 �����Ϸ��� �ݱ⸦ ��������."
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TITLE "��ġ���Ű� �Ϸ���� �ʾҽ��ϴ�"
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_SUBTITLE "$(^Name) ��ġ���Ű� �Ϸ���� �ʾҽ��ϴ�."
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_CAPTION ": ��ġ���Ű� ��ҵǾ����ϴ�"

; +-----------+
; | UNINSTALL |
; +-----------+

; MOST OF THE UNINSTALL PAGES ARE TAKEN CARE OF USING THE PAGE MODE SYSTEM
; THE XPUI CONFIRM, UNINSTFILES, AND SUCCESS PAGES USE THE PAGE MODE SYSTEM,
; BUT THE NSIS-STYLE UNINSTALL CONFIRM PAGE SIMPLY USES A NON-PAGE-MODE METHOD.

; UNINST CONFIRM PAGE (NSIS)
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_CAPTION ": ��ġ���� Ȯ��"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_SUBTITLE "$(^Name) �� �����մϴ�"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TITLE "$(^Name) ��ġ����"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TEXT_TOP "�Ʒ� �������� $(^Name) �� �����˴ϴ�. ��ġ���Ÿ� �����Ϸ��� ��ġ���Ÿ� ��������."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TEXT_FOLDER "��ġ���� ���� :"

!insertmacro XPUI_LANGUAGEFILE_END
