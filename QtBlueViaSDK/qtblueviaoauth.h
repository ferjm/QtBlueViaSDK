#ifndef QTBLUEVIAOAUTH_H
#define QTBLUEVIAOAUTH_H

#include <QObject>
#include <QUrl>

#include "libqtrest/qtrestoauth.h"

class QtBlueViaOAuth : public QObject
{
    Q_OBJECT
public:
    explicit QtBlueViaOAuth(QString consumerKey,
                            QString consumerSecret,
                            QObject *parent = 0);
    ~QtBlueViaOAuth();

    void getRequestToken();
    void getAccessToken(QString requestToken, QString requestTokenSecret, QString verificationCode);

private:
    QString _consumerKey;
    QString _consumerSecret;
    QString _requestToken;
    QString _requestTokenSecret;
    QString _accessToken;
    QString _accessTokenSecret;

    OAuth *oAuth;

signals:

public slots:
    void onTemporaryTokenReceived(QString token, QString tokenSecret, QUrl authorizationUrl);
    void onAccTokensReceived(QString token, QString tokenSecret);

};

#endif // QTBLUEVIAOAUTH_H
