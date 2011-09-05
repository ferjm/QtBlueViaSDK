#ifndef QTBLUEVIASMS_H
#define QTBLUEVIASMS_H

#include "libqtrest/qtrestclient.h"

class QtBlueViaSms : public QtRestClient
{
    Q_OBJECT
public:
    explicit QtBlueViaSms(IAuthentication *authentication,QObject *parent = 0);
    ~QtBlueViaSms();
    void sendSms();
signals:

public slots:

};

#endif // QTBLUEVIASMS_H
