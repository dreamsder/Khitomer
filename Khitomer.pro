#/*********************************************************************
#Khitomer - Sistema de facturación
#Copyright (C) <2012-2025>  <Cristian Montano>
#
#Este archivo es parte de Khitomer.
#
#Khitomer es software libre: usted puede redistribuirlo y/o modificarlo
#bajo los términos de la Licencia Pública General GNU publicada
#por la Fundación para el Software Libre, ya sea la versión 3
#de la Licencia, o (a su elección) cualquier versión posterior.
#
#Este programa se distribuye con la esperanza de que sea útil, pero
#SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita
#MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO.
#Consulte los detalles de la Licencia Pública General GNU para obtener
#una información más detallada.
#
#Debería haber recibido una copia de la Licencia Pública General GNU
#junto a este programa.
#En caso contrario, consulte <http://www.gnu.org/licenses/>.
#*********************************************************************/

# Add more folders to ship with the application, here
folder_01.source = qml/ProyectoQML
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT       += core gui svg
QT       += network
QT       += sql


#symbian:TARGET.UID3 = 0xEFEB4275

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
#symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    moduloclientes.cpp \
    modulotipoclientes.cpp \
    modulotipoclasificacion.cpp \
    modulousuarios.cpp \
    modulolistaproveedor.cpp \
    moduloarticulos.cpp \
    moduloarticulosbarra.cpp \
    moduloliquidaciones.cpp \
    modulolistasprecios.cpp \
    modulolistaprecioarticulos.cpp \
    moduloivas.cpp \
    modulomonedas.cpp \
    Utilidades/utilidadesdemenu.cpp \
    moduloperfiles.cpp \
    Utilidades/utilidadesxml.cpp \
    modulolistatipodocumentos.cpp \
    Utilidades/database.cpp \
    modulolistaimpresoras.cpp \
    modulodocumentos.cpp \
    modulomediosdepago.cpp \
    moduloreportesmenu.cpp \
    moduloreportes.cpp \
    Utilidades/moduloconfiguracion.cpp \
    modulorubros.cpp \
    modulosubrubros.cpp \
    modulobancos.cpp \
    modulotarjetascredito.cpp \
    modulocuentasbancarias.cpp \
    modulotipocheques.cpp \
    modulolineasdepago.cpp \
    modulototalchequesdiferidos.cpp \
    modulobusquedainteligente.cpp \
    modulopaises.cpp \
    modulodepartamentos.cpp \
    modulolocalidades.cpp \
    Mantenimientos/mantenimientobatch.cpp \
    Mantenimientos/controlesmantenimientos.cpp \
    Mantenimientos/dialogoswidget.cpp \
    modulomodelosdeimpresion.cpp \
    modulogenericocombobox.cpp \
    moduloformasdepago.cpp \
    funciones.cpp \
    json/base64.cpp \
    CFE/crearclavecifrada.cpp \
    modulotipodocumentocliente.cpp \
    modulotipoprocedenciacliente.cpp \
    CFE/modulo_cfe_parametrosgenerales.cpp \
    json/json.cpp \
    modulotipopromocion.cpp \
    modulopromociones.cpp \
    QrCode/qrcode.cpp \
    Utilidades/waitingdlg.cpp \
    Utilidades/wsdatabase.cpp \
    modulotipogarantia.cpp \
    moduloreportesperfilesusuarios.cpp \
    modulotipodocumentoperfilesusuarios.cpp \
    moduloreportesconfiguracion.cpp \
    csvreader.cpp \
    fileselector.cpp \
    proxy/modulo_configuracionproxy.cpp \
    modulolimitesaldocuentacorriente.cpp \
    modulolistadescuentosrecargos.cpp \
    modulodocumentoslineasajustes.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    moduloclientes.h \
    modulotipoclientes.h \
    modulotipoclasificacion.h \
    modulousuarios.h \
    modulolistaproveedor.h \
    moduloarticulos.h \
    moduloarticulosbarra.h \
    moduloliquidaciones.h \
    modulolistasprecios.h \
    modulolistaprecioarticulos.h \
    moduloivas.h \
    modulomonedas.h \
    Utilidades/utilidadesdemenu.h \
    moduloperfiles.h \
    Utilidades/utilidadesxml.h \
    modulolistatipodocumentos.h \
    Utilidades/database.h \
    modulolistaimpresoras.h \
    modulodocumentos.h \
    modulomediosdepago.h \
    moduloreportesmenu.h \
    moduloreportes.h \
    Utilidades/moduloconfiguracion.h \
    modulorubros.h \
    modulosubrubros.h \
    modulobancos.h \
    modulotarjetascredito.h \
    modulocuentasbancarias.h \
    modulotipocheques.h \
    modulolineasdepago.h \
    modulototalchequesdiferidos.h \
    modulobusquedainteligente.h \
    modulopaises.h \
    modulodepartamentos.h \
    modulolocalidades.h \
    Mantenimientos/mantenimientobatch.h \
    Mantenimientos/controlesmantenimientos.h \
    Mantenimientos/dialogoswidget.h \
    modulomodelosdeimpresion.h \
    modulogenericocombobox.h \
    moduloformasdepago.h \
    funciones.h \
    curl/curl.h \
    curl/curlbuild.h \
    curl/curlrules.h \
    curl/curlver.h \
    curl/easy.h \
    curl/mprintf.h \
    curl/multi.h \
    curl/stdcheaders.h \
    curl/system.h \
    curl/typecheck-gcc.h \
    json/base64.h \
    CFE/crearclavecifrada.h \
    json/base64_nibbleandahalf.h \
    modulotipodocumentocliente.h \
    modulotipoprocedenciacliente.h \
    CFE/modulo_cfe_parametrosgenerales.h \
    json/json.h \
    json/json.hpp \
    modulotipopromocion.h \
    modulopromociones.h \
    curl4/curl.h \
    curl4/typecheck-gcc.h \
    curl4/system.h \
    curl4/multi.h \
    curl4/urlapi.h \
    curl4/easy.h \
    curl4/curlver.h \
    curl4/mprintf.h \
    curl4/stdcheaders.h \
    QrCode/qrcode.hpp \
    Utilidades/waitingdlg.h \
    Utilidades/wsdatabase.h \
    modulotipogarantia.h \
    moduloreportesperfilesusuarios.h \
    modulotipodocumentoperfilesusuarios.h \
    moduloreportesconfiguracion.h \
    csvreader.h \
    fileselector.h \
    proxy/modulo_configuracionproxy.h \
    modulolimitesaldocuentacorriente.h \
    modulolistadescuentosrecargos.h \
    modulodocumentoslineasajustes.h

RESOURCES += \
    Imagenes.qrc \
    Fuente.qrc




win32:DEFINES  += WIN32
unix:DEFINES     += UNIX
win64:DEFINES  += WIN64


win32:INCLUDEPATH += "%systemdrive%\Khitomer\ExcelWin"
win64:INCLUDEPATH += "%systemdrive%\Khitomer\ExcelWin"

win32:INCLUDEPATH += "%systemdrive%\Khitomer\chilkatWin\include"
win64:INCLUDEPATH += "%systemdrive%\Khitomer\chilkatWin\include"

unix:INCLUDEPATH += "/opt/Khitomer/lib"
unix:INCLUDEPATH += "/opt/Khitomer/lib/lib32"
unix:INCLUDEPATH += "/opt/Khitomer/lib/lib64"

#unix:INCLUDEPATH += "lib"
#unix:INCLUDEPATH += "lib/lib32"
#unix:INCLUDEPATH += "lib/lib64"

win32:LIBS += -lBasicExcelWin -L"%systemdrive%\Khitomer\ExcelWin"
win64:LIBS += -lBasicExcelWin -L"%systemdrive%\Khitomer\ExcelWin"

win32:LIBS += -lchilkat-9.5.0 -L"%systemdrive%\Khitomer\chilkatWin"
win64:LIBS += -lchilkat-9.5.0 -L"%systemdrive%\Khitomer\chilkatWin"

unix:LIBS += -lBasicExcel -L"/opt/Khitomer/lib"  -lboost_system -lresolv -lpthread -lcurl  -lcrypt -lm -lcrypto
unix32:LIBS += -lchilkat-9.5.0 -L"/opt/Khitomer/lib/lib32"  -lboost_system -lresolv -lpthread -lcurl   -lcrypt -lm -lcrypto
unix64:LIBS += -lchilkat-9.5.0 -L"/opt/Khitomer/lib/lib64"  -lboost_system -lresolv -lpthread -lcurl   -lcrypt -lm -lcrypto


#unix:LIBS += -lBasicExcel -L"lib"  -lboost_system -lresolv -lpthread -lcurl  -lcrypt -lm -lcrypto
#unix32:LIBS += -lchilkat-9.5.0 -L"lib/lib32"  -lboost_system -lresolv -lpthread -lcurl   -lcrypt -lm -lcrypto
#unix64:LIBS += -lchilkat-9.5.0 -L"lib/lib64"  -lboost_system -lresolv -lpthread -lcurl   -lcrypt -lm -lcrypto


win32:INCLUDEPATH += "%systemdrive%\OpenSSL-Win32\include"
win64:INCLUDEPATH += "%systemdrive%\OpenSSL-Win64\include"


win32:LIBS +=  -L"%systemdrive%\OpenSSL-Win32\lib\MinGW"  -lssl-1_1 -lcrypto-1_1
win64:LIBS +=  -L"%systemdrive%\OpenSSL-Win64\lib\MinGW"  -lssl-1_1 -lcrypto-1_1


win32:INCLUDEPATH += "$$PWD/curl"
win64:INCLUDEPATH += "$$PWD/curl"
win32:LIBS += "%systemdrive%\Khitomer\curlWin\libcurl.dll"
win64:LIBS += "%systemdrive%\Khitomer\curlWin\libcurl.dll"



#TRANSLATIONS = main_qml_en.ts
#CODECFORTR      = UTF-8
#CODECFORSRC     = UTF-8



#CONFIG += c++11


#QMAKE_CXXFLAGS += -std=c++11

DISTFILES += \
    qml/ProyectoQML/OpcionesDeMenu/MenuGarantias.qml \
    qml/ProyectoQML/Listas/ListaGenerica.qml \
    qml/ProyectoQML/Controles/CuadroListaGarantias.qml \
    qml/ProyectoQML/Controles/ComboBoxListaTipoDocumentosClientesFacturacion.qml \
    qml/ProyectoQML/consultarest.js \
    qml/ProyectoQML/Listas/ListaPrecioArticulosNueva.qml \
    qml/ProyectoQML/Controles/BusquedaReportes.qml \
    qml/ProyectoQML/Controles/LoadingQML.qml \
    qml/ProyectoQML/OpcionesDeMenu/ABMDescuentosRecargos.qml




