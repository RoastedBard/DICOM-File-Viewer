#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T21:00:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTGuiDICOMFileViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src/VR_Classes/Type_Elements/ByteElement.cpp \
    src/VR_Classes/Type_Elements/DoubleElement.cpp \
    src/VR_Classes/Type_Elements/FloatElement.cpp \
    src/VR_Classes/Type_Elements/SignedIntElement.cpp \
    src/VR_Classes/Type_Elements/StringElement.cpp \
    src/VR_Classes/Type_Elements/UnsignedIntElement.cpp \
    src/VR_Classes/AbstractDICOMDataElement.cpp \
    src/Common/DICOMFile.cpp

HEADERS  += mainwindow.h \
    src/VR_Classes/Type_Elements/ByteElement.h \
    src/VR_Classes/Type_Elements/DoubleElement.h \
    src/VR_Classes/Type_Elements/FloatElement.h \
    src/VR_Classes/Type_Elements/SignedIntElement.h \
    src/VR_Classes/Type_Elements/StringElement.h \
    src/VR_Classes/Type_Elements/UnsignedIntElement.h \
    src/VR_Classes/AbstractDICOMDataElement.h \
    src/VR_Classes/AE_Element.h \
    src/VR_Classes/AS_Element.h \
    src/VR_Classes/AT_Element.h \
    src/VR_Classes/CommonElementData.h \
    src/VR_Classes/CS_Element.h \
    src/VR_Classes/DA_Element.h \
    src/VR_Classes/DICOMElementFabric.h \
    src/VR_Classes/DS_Element.h \
    src/VR_Classes/DT_Element.h \
    src/VR_Classes/FD_Element.h \
    src/VR_Classes/FL_Element.h \
    src/VR_Classes/IS_Element.h \
    src/VR_Classes/LO_Element.h \
    src/VR_Classes/LT_Element.h \
    src/VR_Classes/OB_Element.h \
    src/VR_Classes/OD_Element.h \
    src/VR_Classes/OF_Element.h \
    src/VR_Classes/OL_Element.h \
    src/VR_Classes/OW_Element.h \
    src/VR_Classes/PN_Element.h \
    src/VR_Classes/SH_Element.h \
    src/VR_Classes/SL_Element.h \
    src/VR_Classes/SQ_Element.h \
    src/VR_Classes/SS_Element.h \
    src/VR_Classes/ST_Element.h \
    src/VR_Classes/TM_Element.h \
    src/VR_Classes/UC_Element.h \
    src/VR_Classes/UI_Element.h \
    src/VR_Classes/UL_Element.h \
    src/VR_Classes/UN_Element.h \
    src/VR_Classes/UR_Element.h \
    src/VR_Classes/US_Element.h \
    src/VR_Classes/UT_Element.h \
    src/Common/DICOMFile.h \
    src/Common/DICOMTag.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../External/mc3lib/ -lmc3adll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../External/mc3lib/ -lmc3adlld

INCLUDEPATH += $$PWD/../External/mc3inc
DEPENDPATH += $$PWD/../External/mc3inc

RESOURCES +=
