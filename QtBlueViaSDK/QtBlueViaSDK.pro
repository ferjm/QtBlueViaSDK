QT       += network xml

QT       -= gui

TARGET = qtbluevia
TEMPLATE = lib

DEFINES += QTBLUEVIASDK_LIBRARY

SOURCES += qtblueviasdk.cpp \
    qtblueviaoauth.cpp

HEADERS += qtblueviasdk.h\
    qtblueviaoauth.h \
    qtblueviasdkglobal.h

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lqtrest

header_files.files = $$HEADERS
header_files.path = /usr/local/include/libqtblueviasdk
INSTALLS += header_files

target.path = /usr/local/lib
INSTALLS += target
