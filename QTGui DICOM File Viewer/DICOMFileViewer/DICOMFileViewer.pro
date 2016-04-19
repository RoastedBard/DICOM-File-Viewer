#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T13:17:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DICOMFileViewer
TEMPLATE = app

SOURCES += main.cpp \
    AbstractDICOMDataElement.cpp \
    ByteElement.cpp \
    DICOMFile.cpp \
    mainwindow.cpp
HEADERS  += mainwindow.h \
    AbstractDICOMDataElement.h \
    AE_Element.h \
    AS_Element.h \
    AT_Element.h \
    ByteElement.h \
    CommonElementData.h \
    CS_Element.h \
    DA_Element.h \
    DICOMElementFabric.h \
    DICOMFile.h \
    DICOMTag.h \
    DoubleElement.h \
    DS_Element.h \
    DT_Element.h \
    FD_Element.h \
    FL_Element.h \
    FloatElement.h \
    IS_Element.h \
    LO_Element.h \
    LT_Element.h \
    OB_Element.h \
    OD_Element.h \
    OF_Element.h \
    OL_Element.h \
    OW_Element.h \
    PN_Element.h \
    SH_Element.h \
    SignedIntElement.h \
    SL_Element.h \
    SQ_Element.h \
    SS_Element.h \
    ST_Element.h \
    StringElement.h \
    TM_Element.h \
    UC_Element.h \
    UI_Element.h \
    UL_Element.h \
    UN_Element.h \
    UnsignedIntElement.h \
    UR_Element.h \
    US_Element.h \
    UT_Element.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-DICOMFileViewer-Desktop_Qt_5_5_1_MSVC2012_32bit-Debug/External/mc3lib/ -lmc3adll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-DICOMFileViewer-Desktop_Qt_5_5_1_MSVC2012_32bit-Debug/External/mc3lib/ -lmc3adlld

INCLUDEPATH += $$PWD/../build-DICOMFileViewer-Desktop_Qt_5_5_1_MSVC2012_32bit-Debug/External/mc3inc
DEPENDPATH += $$PWD/../build-DICOMFileViewer-Desktop_Qt_5_5_1_MSVC2012_32bit-Debug/External/mc3inc

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-DICOMFileViewer-Desktop_Qt_5_5_1_MSVC2012_32bit-Debug/External/mc3lib/libmc3adll.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-DICOMFileViewer-Desktop_Qt_5_5_1_MSVC2012_32bit-Debug/External/mc3lib/libmc3adlld.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-DICOMFileViewer-Desktop_Qt_5_5_1_MSVC2012_32bit-Debug/External/mc3lib/mc3adll.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-DICOMFileViewer-Desktop_Qt_5_5_1_MSVC2012_32bit-Debug/External/mc3lib/mc3adlld.lib
