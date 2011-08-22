#-------------------------------------------------
#
# Project created by QtCreator 2011-08-22T17:03:20
#
#-------------------------------------------------

QT       += network xml

QT       -= gui

TARGET = QtBlueViaSDK
TEMPLATE = lib

DEFINES += QTBLUEVIASDK_LIBRARY

SOURCES += qtblueviasdk.cpp

HEADERS += qtblueviasdk.h\
        QtBlueViaSDK_global.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/libqtblueviasdk
INSTALLS += header_files

target.path = /usr/local/lib
INSTALLS += target
