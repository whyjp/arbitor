;NSIS ExperienceUI - Language File
;Compatible with ExperienceUI 1.09�

;Language: Spanish (1034)
;Par Matze <matze@gravure-hebdo.com>

;--------------------------------

!insertmacro XPUI_LANGUAGEFILE_BEGIN "Spanish"

; Use only ASCII characters (if this is not possible, use the English name)
!insertmacro XPUI_UNSET XPUI_LANGNAME
!insertmacro XPUI_DEFAULT XPUI_LANGNAME "Espa�ol"

; BUTTONS
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_NEXT   Siguiente
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_BACK   Atr�s
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_CANCEL Cancelar
!insertmacro XPUI_DEFAULT XPUI_BUTTONTEXT_CLOSE  Cerrar

!insertmacro XPUI_DEFAULT XPUI_ABORTWARNING_TEXT "Usted est� a punto de salir del setup.$\n$\nSi usted ahora sale, $(^Name) no ser� instalado.$\n$\n�Est� seguro de que desea salir de la instalaci�n de $(^Name)?"

; +---------+
; | INSTALL |
; +---------+

; WELCOME PAGE
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TEXT_TOP "Bienvenido al Asistente de Instalaci�n de $(^Name)"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TEXT "Este programa instalar� $(^Name) en su ordenador.\r\n\r\nSe recomienda que cierre todas las dem�s aplicaciones antes de iniciar la instalaci�n. Esto har� posible actualizar archivos relacionados con el sistema sin tener que reiniciar su ordenador.\r\n\r\n"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_TITLE "Bienvenido"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_SUBTITLE "Bienvenido al Instalaci�n de $(^Name)."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE_CAPTION " "

!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TEXT_TOP "Bienvenido al Asistente de desinstalaci�n de $(^Name)"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TEXT "Este programa desinstalar� $(^Name) en su ordenador.\r\n\r\nSe recomienda que cierre todas las dem�s aplicaciones antes de iniciar la desinstalaci�n. Esto har� posible actualizar archivos relacionados con el sistema sin tener que reiniciar su ordenador.\r\n\r\n"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_TITLE "Bienvenido"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_SUBTITLE "Bienvenido al desinstalaci�n de $(^Name)."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE_CAPTION " "

; WELCOME PAGE STYLE 2
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE2_TEXT_TOP "Bienvenido al Asistente de Instalaci�n NSIS de $(^Name)"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE2_TEXT "Bienvenido al Instalaci�n de $(^Name). Este programa instalar� $(^Name) en su ordenador"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE2_TITLE "Bienvenido"
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE2_SUBTITLE "Bienvenido al Instalaci�n de $(^Name)."
!insertmacro XPUI_DEFAULT XPUI_WELCOMEPAGE2_CAPTION " "

!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE2_TEXT_TOP "Bienvenido al Asistente de Desinstalaci�n NSIS de $(^Name)"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE2_TEXT "Bienvenido al Desinstalaci�n de $(^Name). Este programa desinstalar� $(^Name) en su ordenador"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE2_TITLE "Bienvenido"
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE2_SUBTITLE "Bienvenido al Desinstalaci�n de $(^Name)."
!insertmacro XPUI_DEFAULT XPUI_UNWELCOMEPAGE2_CAPTION " "

; LICENSE PAGE
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_CAPTION ": Acuerdo de licencia"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_RADIOBUTTONS_TEXT_ACCEPT "Acepto todos los t�rminos del acuerdo"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_RADIOBUTTONS_TEXT_DECLINE "No acepto todos los t�rminos del acuerdo"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_CHECKBOX "Acepto todos los t�rminos del acuerdo"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_SUBTITLE "Por favor revise los t�rminos de la licencia antes de instalar $(^Name)."
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TITLE "Acuerdo de licencia"
!insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_TOP "Presione Avanzar P�gina para ver el resto del acuerdo."
!ifndef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "Si acepta todos los t�rminos del acuerdo, seleccione Acepto para continuar. Debe aceptar el acuerdo para instalar $(^Name)."
  !endif
!endif
!ifndef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifdef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "Si acepta los t�rminos del acuerdo, marque abajo la casilla. Debe aceptar los t�rminos para instalar $(^Name)."
  !endif
!endif
!ifdef XPUI_LICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_LICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_LICENSEPAGE_TEXT_BOTTOM "Si acepta los t�rminos del acuerdo, seleccione abajo la primera opci�n. Debe aceptar los t�rminos para instalar $(^Name)."
  !endif
!endif

!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_CAPTION ": Acuerdo de licencia"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_RADIOBUTTONS_TEXT_ACCEPT "Acepto todos los t�rminos del acuerdo"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_RADIOBUTTONS_TEXT_DECLINE "No acepto todos los t�rminos del acuerdo"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_CHECKBOX "Acepto todos los t�rminos del acuerdo"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_SUBTITLE "Por favor revise los t�rminos de la licencia antes de desinstalar $(^Name)."
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TITLE "Acuerdo de licencia"
!insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_TOP "Presione Avanzar P�gina para ver el resto del acuerdo."
!ifndef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "Si acepta todos los t�rminos del acuerdo, seleccione Acepto para continuar. Debe aceptar el acuerdo para desinstalar $(^Name)."
  !endif
!endif
!ifndef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifdef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "Si acepta los t�rminos del acuerdo, marque abajo la casilla. Debe aceptar los t�rminos para desinstalar $(^Name)."
  !endif
!endif
!ifdef XPUI_UNLICENSEPAGE_RADIOBUTTONS
  !ifndef XPUI_UNLICENSEPAGE_CHECKBOX
    !insertmacro XPUI_DEFAULT XPUI_UNLICENSEPAGE_TEXT_BOTTOM "Si acepta los t�rminos del acuerdo, seleccione abajo la primera opci�n. Debe aceptar los t�rminos para desinstalar $(^Name)."
  !endif
!endif

; COMPONENTS PAGE
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_CAPTION ": Selecci�n de componentes"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_SUBTITLE "Seleccione qu� caracter�sticas de $(^Name) desea instalar."
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TITLE "Selecci�n de componentes"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TEXT_DESCRIPTION_TITLE "Descripci�n"
!insertmacro XPUI_DEFAULT XPUI_COMPONENTSPAGE_TEXT_DESCRIPTION_INFO  "Sit�e el rat�n encima de un componente para ver su descripci�n"

!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_CAPTION ": Selecci�n de componentes"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_SUBTITLE "Seleccione qu� caracter�sticas de $(^Name) desea desinstalar."
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TITLE "Selecci�n de componentes"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TEXT_DESCRIPTION_TITLE "Descripci�n"
!insertmacro XPUI_DEFAULT XPUI_UNCOMPONENTSPAGE_TEXT_DESCRIPTION_INFO  "Sit�e el rat�n encima de un componente para ver su descripci�n"

; DIRECTORY PAGE
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_CAPTION ": Elegir lugar de instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_TOP "El programa de instalaci�n instalar� $(^Name) en el siguiente directorio.$\r$\n$\r$\nPara instalar en un directorio diferente, presione Examinar y seleccione otro directorio. $_CLICK"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_DESTINATION "Repertorio de instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_BROWSE "Examinar"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TEXT_BROWSEDIALOG "Elegir Repertorio:"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_TITLE "Elegir lugar de instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_DIRECTORYPAGE_SUBTITLE "Elija el directorio para instalar $(^Name)."

!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_CAPTION ": Elegir lugar de instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_TOP "El programa de desinstalaci�n desinstalar� $(^Name) en el siguiente directorio.$\r$\n$\r$\nPara desinstalar en un directorio diferente, presione Examinar y seleccione otro directorio."
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_DESTINATION "Repertorio de instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_BROWSE "Examinar"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TEXT_BROWSEDIALOG "Elegir Repertorio:"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_TITLE "Elegir lugar de instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_UNDIRECTORYPAGE_SUBTITLE "Elija el directorio para desinstalar $(^Name)."

; START MENU PAGE
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_CAPTION    ": Carpeta del Men� Inicio"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_TITLE      "Elegir Carpeta del Men� Inicio"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_SUBTITLE   "Elija una Carpeta del Men� Inicio para los accesos directos de $(^Name):"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_TEXT       "Elija una Carpeta del Men� Inicio para los accesos directos de to $(^Name):"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_CHECKBOX   "No crear accesos directos"
!insertmacro XPUI_DEFAULT XPUI_STARTMENUPAGE_FOLDER     "$(^Name)"

!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_CAPTION    ": Carpeta del Men� Inicio"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_TITLE      "Elegir Carpeta del Men� Inicio"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_SUBTITLE   "Elija una Carpeta del Men� Inicio para desinstalar los accesos directos de $(^Name):"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_TEXT       "Elija una Carpeta del Men� Inicio para desinstalar los accesos directos de to $(^Name):"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_CHECKBOX   "No desinstalar accesos directos"
!insertmacro XPUI_DEFAULT XPUI_UNSTARTMENUPAGE_FOLDER     "$(^Name)"

; INSTALL CONFIRM PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_CAPTION ": Confirmar Instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_SUBTITLE "Setup tiene bastante informaci�n y es listo instalar $(^Name)."
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TITLE "Confirmar Instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TEXT_TOP "Setup es listo instalar $(^Name) en su computadora."
!insertmacro XPUI_DEFAULT XPUI_INSTCONFIRMPAGE_TEXT_BOTTOM "$_CLICK"

!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_CAPTION ": Confirmar Instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_SUBTITLE "Setup tiene bastante informaci�n y es listo desinstalar $(^Name)."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TITLE "Confirmar Instalaci�n"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TEXT_TOP "Setup es listo desinstalar $(^Name) de su computadora."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_TEXT_BOTTOM "Presione Siguiente para continuar."

; INSTFILES PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_CAPTION ": Copiar Archivos"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_SUBTITLE "Por favor espere mientras $(^Name) se instala."
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_TITLE "Instalando"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_DONE_TITLE "Instalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_DONE_SUBTITLE "Todos los componentes de $(^Name) fueron copiados en su sistema."

!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_CAPTION ": Desinstalando Archivos"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_SUBTITLE "Por favor espere mientras $(^Name) se desinstala."
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_TITLE "Desinstalando"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_DONE_TITLE "Desinstalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_DONE_SUBTITLE "Todos los componentes de $(^Name) fueron quitados de su sistema."

!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_FAIL_TITLE "Instalaci�n incompletada"
!insertmacro XPUI_DEFAULT XPUI_INSTFILESPAGE_FAIL_SUBTITLE "Instalaci�n de $(^Name) no se complet� correctamente."
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_FAIL_TITLE "Desinstalaci�n incompletada"
!insertmacro XPUI_DEFAULT XPUI_UNINSTFILESPAGE_FAIL_SUBTITLE "Desinstalaci�n de $(^Name) no se complet� correctamente."

; INSTALL SUCCESS PAGE
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_CAPTION ": Instalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_SUBTITLE "La instalaci�n de $(^Name) se ha completado correctamente"
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TITLE "Instalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TEXT_TOP    "$(^Name) ha sido instalado en su sistema."
!insertmacro XPUI_DEFAULT XPUI_INSTSUCCESSPAGE_TEXT_BOTTOM "Presione Terminar para cerrar este asistente."

!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_CAPTION ": Desinstalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_SUBTITLE "La desinstalaci�n de $(^Name) se ha completado correctamente"
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TITLE "Desinstalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TEXT_TOP    "$(^Name) ha sido desinstalado en su sistema."
!insertmacro XPUI_DEFAULT XPUI_UNINSTSUCCESSPAGE_TEXT_BOTTOM "Presione Terminar para cerrar este asistente."

; FINISH PAGE

!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TITLE "Instalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_SUBTITLE "La instalaci�n de $(^Name) se ha completado correctamente."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CAPTION ": Instalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_TOP "Completando el Asistente de Instalaci�n de $(^Name)"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_TOP_ALT "Completando el Asistente de Instalaci�n NSIS"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_RUN "$(^Name) ha sido instalado de su sistema.\r\n\r\n�Qu� acciones usted desean realizarse?"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT_REBOOT "Instalaci�n completando copiar archivos en su sistema.\r\n\r\nSu ordenador debe ser reiniciado para completar la instalaci�n de $(^Name). �Desea reiniciar ahora?"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_TEXT "$(^Name) ha sido instalado de su sistema.\r\n\r\nPresione $(XPUI_BUTTONTEXT_CLOSE) para cerrar este asistente."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CHECKBOX_RUN "Iniciar $(^Name) ahora"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_CHECKBOX_DOCS "Leer la documentaci�n de $(^Name)"
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_RADIOBUTTON_REBOOT "Si, reiniciar su ordenador ahora."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_RADIOBUTTON_NOREBOOT "No, reiniciar su ordenador m�s tarde."
!insertmacro XPUI_DEFAULT XPUI_FINISHPAGE_REBOOT_MESSAGEBOX "Setup est� alrededor reiniciar su ordenador.$\r$\n$\r$\nPor favor excepto y cierre todos los archivos y los documentos abiertos, i presione OK para reiniciar su ordenador."

!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TITLE "Desinstalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_SUBTITLE "La desinstalaci�n de $(^Name) se ha completado correctamente."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_CAPTION ": Desinstalaci�n Completada"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_TOP "Completando el Asistente de Desinstalaci�n de $(^Name)"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_TOP_ALT "Completando el Asistente de Desinstalaci�n NSIS"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_REBOOT "Instalaci�n completando copiar archivos en su sistema.\r\n\r\nSu ordenador debe ser reiniciado para completar la desinstalaci�n de $(^Name). �Desea reiniciar ahora?"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT_RUN "$(^Name) ha sido desinstalado de su sistema.\r\n\r\n�Qu� acciones usted desean realizarse?"
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_TEXT "$(^Name) ha sido desinstalado de su sistema.\r\n\r\nPresione $(XPUI_BUTTONTEXT_CLOSE) para cerrar este asistente."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_RADIOBUTTON_REBOOT "Si, reiniciar su ordenador ahora."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_RADIOBUTTON_NOREBOOT "No, reiniciar su ordenador m�s tarde."
!insertmacro XPUI_DEFAULT XPUI_UNFINISHPAGE_REBOOT_MESSAGEBOX "${XPUI_FINISHPAGE_REBOOT_MESSAGEBOX}"

; ABORT PAGE
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TEXT_TOP "Completando el Asistente de Instalaci�n NSIS"
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TEXT "El Asistente fue interrumpido antes $(^Name) ha sido instalado en su sistema.\r\n\r\nSu sistema no se ha modificado.  Para instalar este programa m�s tarde, reinicia este\r\nassistente.\r\n\r\n\r\n\r\n\r\nPresione Terminar para cerrar este asistente."
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_TITLE "Instalaci�n incompletada"
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_SUBTITLE "Instalaci�n de $(^Name) no se complet� correctamente."
!insertmacro XPUI_DEFAULT XPUI_ABORTPAGE_CAPTION ": Instalaci�n Anulada"

!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TEXT_TOP "Completando el Asistente de Desinstalaci�n NSIS"
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TEXT "El Asistente fue interrumpido antes $(^Name) ha sido desinstalado en su sistema.\r\n\r\nSu sistema no se ha modificado.  Para instalar este programa m�s tarde, reinicia este assistente.\r\n\r\n\r\n\r\n\r\nPresione Terminar para cerrar este asistente."
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_TITLE "Desinstalaci�n incompletada"
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_SUBTITLE "Desinstalaci�n de $(^Name) no se complet� correctamente."
!insertmacro XPUI_DEFAULT XPUI_UNABORTPAGE_CAPTION ": Instalaci�n Anulada"

; +-----------+
; | UNINSTALL |
; +-----------+

; MOST OF THE UNINSTALL PAGES ARE TAKEN CARE OF USING THE PAGE MODE SYSTEM
; THE XPUI CONFIRM, UNINSTFILES, AND SUCCESS PAGES USE THE PAGE MODE SYSTEM,
; BUT THE NSIS-STYLE UNINSTALL CONFIRM PAGE SIMPLY USES A NON-PAGE-MODE METHOD.

; UNINST CONFIRM PAGE (NSIS)
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_CAPTION ": Confirmar Desinstalaci�n"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_SUBTITLE "Desinstalar $(^Name) de su sistema."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TITLE "Desinstalar $(^Name)"
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TEXT_TOP "$(^Name) sea desinstalado de la carpeta siguiente.  Presione Desinstalar para iniciar la Desinstalaci�n."
!insertmacro XPUI_DEFAULT XPUI_UNINSTCONFIRMPAGE_NSIS_TEXT_FOLDER "Desinstalar de:"

!insertmacro XPUI_LANGUAGEFILE_END
