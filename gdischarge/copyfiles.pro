#-------------------------------------------------
#
# Project created by QtCreator 2019-05-31T18:31:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GD.V1.2.B0001.QR1.H1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    gdischargeservice.cpp \
    channelthreadone.cpp \
    logger.cpp \
    entityfile.cpp \
    entitydisk.cpp \
    keypress.cpp

HEADERS += \
    mainwindow.h \
    gdischargeservice.h \
    channelthreadone.h \
    logger.h \
    entityfile.h \
    entitydisk.h \
    keypress.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qtresources.qrc
