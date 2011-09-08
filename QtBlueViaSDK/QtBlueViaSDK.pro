QT       += network xml

QT       -= gui

TARGET = qtbluevia
TEMPLATE = lib

DEFINES += QTBLUEVIASDK_LIBRARY

SOURCES += qtblueviasdk.cpp \
    clients/qtblueviaoauth.cpp \
    data/common/qtblueviauserid.cpp \
    data/messaging/qtblueviaabstractmessage.cpp \
    data/messaging/sms/qtblueviasmsmessage.cpp \
    clients/qtblueviasmsclient.cpp

HEADERS += qtblueviasdk.h\
    clients/qtblueviaoauth.h \
    qtblueviasdkglobal.h \
    data/common/qtblueviauserid.h \
    data/messaging/qtblueviaabstractmessage.h \
    data/messaging/sms/qtblueviasmsmessage.h \
    clients/qtblueviasmsclient.h

INCLUDEPATH += /usr/local/include clients data data/common data/messaging data/messaging/sms
LIBS += -L/usr/local/lib -lqtrest

header_files.files = $$HEADERS
header_files.path = /usr/local/include/libqtblueviasdk
INSTALLS += header_files

target.path = /usr/local/lib
INSTALLS += target
