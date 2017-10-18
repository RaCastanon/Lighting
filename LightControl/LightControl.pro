#-------------------------------------------------
#
# Project created by QtCreator 2017-10-02T23:22:20
#
#-------------------------------------------------

QT += core gui
QT += serialport
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LightControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    methods.cpp

HEADERS  += mainwindow.h \
    methods.h

FORMS    += mainwindow.ui

INCLUDEPATH += "C:\OpenCV\include"

LIBS += -L"C:\OpenCV\lib"\
        -llibopencv_core300\
        -llibopencv_imgproc300\
        -llibopencv_imgcodecs300\
        -llibopencv_highgui300\
        -llibopencv_videoio300
