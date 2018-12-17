#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T10:44:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ARecorder
TEMPLATE = app

INCLUDEPATH += inc \
               ../Qwt/include

SOURCES += main.cpp\
        src/mainwindow.cpp \
        src/adc.cpp \
        ADCsdk/Alf.cpp \
        src/crusher.cpp \
        src/parammodel.cpp \
        src/paramsaver.cpp \
        src/csv.cpp \
        src/filecopydialog.cpp \
        recoderdata.cpp \
        graphdatamodel.cpp \
        expfilter.cpp \
        src/setupkoefdialog.cpp

HEADERS += inc/mainwindow.h \
        inc/adc.h \
        ADCsdk/ADC_CONST.h \
        ADCsdk/DllClient.h \
        ADCsdk/IADCDevice.h \
        ADCsdk/IFactory.h \
        ADCsdk/alf.h \
        inc/crusher.h \
        inc/parammodel.h \
        inc/paramsaver.h \
        inc/csv.h \
        inc/filecopydialog.h \
        recoderdata.h \
        timescaledraw.h \
        graphdatamodel.h \
        expfilter.h \
        inc/setupkoefdialog.h

FORMS += forms/mainwindow.ui \
        forms/filecopydialog.ui \
        forms/setupkoefdialog.ui

CONFIG(release, debug|release) {
    LIBS = -L../Qwt/lib -lqwt
}

CONFIG(debug, debug|release) {
    LIBS = -L../Qwt/lib -lqwtd
}

DEFINES -= UNICODE

RESOURCES += \
        resource.qrc

RC_FILE = arecorder.rc
