QT       += network xml

QT       -= gui

TARGET = qtbluevia
TEMPLATE = lib

DEFINES += QTBLUEVIASDK_LIBRARY

SOURCES += qtblueviasdk.cpp \
    clients/qtblueviaoauth.cpp \
    clients/qtblueviasms.cpp \
    data/common/qtblueviauserid.cpp \
    data/messaging/qtblueviaabstractmessage.cpp

HEADERS += qtblueviasdk.h\
    clients/qtblueviaoauth.h \
    qtblueviasdkglobal.h \
    clients/qtblueviasms.h \
    data/common/qtblueviauserid.h \
    data/messaging/qtblueviaabstractmessage.h

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lqtrest

header_files.files = $$HEADERS
header_files.path = /usr/local/include/libqtblueviasdk
INSTALLS += header_files

target.path = /usr/local/lib
INSTALLS += target
