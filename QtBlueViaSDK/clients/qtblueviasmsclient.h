#ifndef QTBLUEVIASMSCLIENT_H
#define QTBLUEVIASMSCLIENT_H

#include "libqtrest/qtrestclient.h"
#include "qtblueviauserid.h"
#include "qtblueviasmsmessage.h"

class QtBlueViaSmsClient : public QtRestClient
{
    Q_OBJECT
public:
    explicit QtBlueViaSmsClient(IAuthentication *authentication,QObject *parent = 0);
    ~QtBlueViaSmsClient();
    /**
      Allows to send an SMS to a single address. It returns a string containing the SMSID
      of the sent SMS
      @param message The text of the message
      @param address The address of the recipient of the message
      */
    QString sendSms(QString message,QtBlueViaUserId address);
    /**
      Allows to send an SMS to multiple addresses. It returns a string containing the SMSID
      of the sent SMS
      @param message The text of the message
      @param addresses The addresses of the recipients of the message
      */
    QString sendSms(QString message,QList<QtBlueViaUserId> addresses);

    void getDeliveryStatus(QString smsId);

private:
    QString sendSms(QtBlueViaSmsMessage message);

signals:

public slots:

};

#endif // QTBLUEVIASMSCLIENT_H
