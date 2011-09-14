/***************************************************************************
 *   Copyright (C) 2011 Fernando Jiménez Moreno <ferjmoreno@gmail.com>     *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

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

    QString getRetrievedAccessToken();
    QString getRetrievedAccessTokenSecret();
    QString getRetrievedRequestToken();
    QString getRetrievedRequesTokenSecret();

private:
    QString _consumerKey;
    QString _consumerSecret;
    QString _requestToken;
    QString _requestTokenSecret;
    QString _accessToken;
    QString _accessTokenSecret;

    OAuth *oAuth;

signals:
    void requestTokenRetrieved(QString token, QString tokenSecret, QUrl authorizationUrl);
    void accessTokenRetrieved(QString token, QString tokenSecret);

public slots:
    void onTemporaryTokenReceived(QString token, QString tokenSecret, QUrl authorizationUrl);
    void onAccTokensReceived(QString token, QString tokenSecret);
    void onError(QMultiMap<QString,QString> errorMap);
};

#endif // QTBLUEVIAOAUTH_H
