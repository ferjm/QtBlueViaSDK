#ifndef QTBLUEVIASMSCLIENT_H
#define QTBLUEVIASMSCLIENT_H

#include <QMultiMap>

#include "libqtrest/qtrestclient.h"
#include "libqtrest/qtrestoauthdata.h"
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
    void sendSms(QString message,QtBlueViaUserId address);
    /**
      Allows to send an SMS to multiple addresses. It returns a string containing the SMSID
      of the sent SMS
      It emits smsSent signal
      @param message The text of the message
      @param addresses The addresses of the recipients of the message
      */
    void sendSms(QString message,QList<QtBlueViaUserId> addresses);

    /**
      Gets the status of the sent SMS.
      It emits deliveryStatusRetrieved signal
      @param QString resourceUrl Url of the SMS resource
      */
    void getDeliveryStatus(QString resourceUrl);

private:
    void sendSms(QtBlueViaSmsMessage message);
    QStringList errorList;

signals:
    void smsSent(QString);
    void error(QString);
    void deliveryStatusRetrieved(QList<QPair<QString,QString> >);

public slots:
    void onSmsSent(QList<QNetworkReply::RawHeaderPair>);
    void onSmsError(QByteArray);
    void onSmsError(QString);
    void onStatusRetrieved(QByteArray);

};

#endif // QTBLUEVIASMSCLIENT_H
