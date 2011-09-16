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

#include "qtblueviaoauth.h"
#include "libqtrest/qtrest.h"

//TODO: Use QSettings and split uri
#define OAUTH_REQUEST_TOKEN_URI "https://api.bluevia.com/services/REST/Oauth/getRequestToken"
#define OAUTH_AUTHORIZATION_URI "https://connect.bluevia.com/authorise?oauth_token="
#define OAUTH_ACCESS_TOKEN_URI "https://api.bluevia.com/services/REST/Oauth/getAccessToken"

QtBlueViaOAuth::QtBlueViaOAuth(QString consumerKey,
                               QString consumerSecret,
                               QObject *parent) :
    QObject(parent),
    _consumerKey(consumerKey),
    _consumerSecret(consumerSecret)
{
    oAuth = NULL;

    /*QStringList properties;
    properties.append("ClientException");
    properties.append("exceptionCategory");
    properties.append("exceptionId");
    properties.append("text");
    QtRest::getInstance()->addProperties(properties);*/

    QStringList errors;
    errors.append("ClientException");

    oAuth = new OAuth(_consumerKey,_consumerSecret,this);
    oAuth->setTagErrorList(errors);
}

QtBlueViaOAuth::~QtBlueViaOAuth()
{
    if(oAuth != NULL) delete oAuth;
}

void QtBlueViaOAuth::getRequestToken()
{
    if(oAuth == NULL)
        oAuth = new OAuth(_consumerKey,_consumerSecret,this);
    connect(oAuth, SIGNAL(temporaryTokenReceived(QString,QString,QUrl)), this, SLOT(onTemporaryTokenReceived(QString,QString,QUrl)));
    oAuth->getRequestToken(QUrl(OAUTH_REQUEST_TOKEN_URI),QUrl(OAUTH_AUTHORIZATION_URI),HttpRequest::POST);    
}

void QtBlueViaOAuth::getAccessToken(QString requestToken, QString requestTokenSecret, QString verificationCode)
{
    if(oAuth == NULL)
        oAuth = new OAuth(_consumerKey,_consumerSecret,this);
    connect(oAuth, SIGNAL(accessTokenReceived(QString,QString)), this, SLOT(onAccTokensReceived(QString,QString)));
    connect(oAuth, SIGNAL(error(QMultiMap<QString,QString>)),this,SLOT(onError(QMultiMap<QString,QString>)));
    oAuth->getAccessToken(requestToken,requestTokenSecret,verificationCode,QUrl(OAUTH_ACCESS_TOKEN_URI),HttpRequest::POST);
}

void QtBlueViaOAuth::onTemporaryTokenReceived(QString token, QString tokenSecret, QUrl authorizationUrl)
{
    this->_requestToken = token;
    this->_requestTokenSecret = tokenSecret;
    qDebug() << "Token: " << token;
    qDebug() << "TokenSecret: " << tokenSecret;
    qDebug() << "Authorization URL: " << authorizationUrl.toString();
    emit requestTokenRetrieved(token,tokenSecret,authorizationUrl);
}

void QtBlueViaOAuth::onAccTokensReceived(QString token, QString tokenSecret)
{
    this->_accessToken = token;
    this->_accessTokenSecret = tokenSecret;
    qDebug() << "Token: " << token;
    qDebug() << "TokenSecret: " << tokenSecret;
    emit accessTokenRetrieved(token,tokenSecret);
}

void QtBlueViaOAuth::onError(QMultiMap<QString,QString> errorMap)
{
    QList<QString> values = errorMap.values("text");
    for (int i = 0; i < values.size(); ++i)
        qDebug() << values.at(i);
}

QString QtBlueViaOAuth::getRetrievedAccessToken() {
    return this->_accessToken;
}

QString QtBlueViaOAuth::getRetrievedAccessTokenSecret() {
    return this->_accessTokenSecret;
}

QString QtBlueViaOAuth::getRetrievedRequestToken() {
    return this->_requestToken;
}

QString QtBlueViaOAuth::getRetrievedRequesTokenSecret() {
    return this->_requestTokenSecret;
}
