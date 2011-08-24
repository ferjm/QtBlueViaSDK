#include "qtblueviaoauth.h"

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
}

QtBlueViaOAuth::~QtBlueViaOAuth()
{
    if(oAuth != NULL) delete oAuth;
}

void QtBlueViaOAuth::getRequestToken()
{
    if(oAuth == NULL)
        oAuth = new OAuth(_consumerKey,_consumerSecret,this);
    oAuth->getRequestToken(QUrl(OAUTH_REQUEST_TOKEN_URI),QUrl(OAUTH_AUTHORIZATION_URI),HttpRequest::POST);
    connect(oAuth, SIGNAL(temporaryTokenReceived(QString,QString,QUrl)), this, SLOT(onTemporaryTokenReceived(QString,QString,QUrl)));
}

void QtBlueViaOAuth::getAccessToken(QString requestToken, QString requestTokenSecret, QString verificationCode)
{
    if(oAuth == NULL)
        oAuth = new OAuth(_consumerKey,_consumerSecret,this);
    oAuth->getAccessToken(requestToken,requestTokenSecret,verificationCode,QUrl(OAUTH_ACCESS_TOKEN_URI),HttpRequest::POST);
    connect(oAuth, SIGNAL(accessTokenReceived(QString,QString)), this, SLOT(onAccTokensReceived(QString,QString)));
}

void QtBlueViaOAuth::onTemporaryTokenReceived(QString token, QString tokenSecret, QUrl authorizationUrl)
{
    this->_requestToken = token;
    this->_requestTokenSecret = tokenSecret;
    qDebug() << "Token: " << token;
    qDebug() << "TokenSecret: " << tokenSecret;
    qDebug() << "Authorization URL: " << authorizationUrl.toString();
}

void QtBlueViaOAuth::onAccTokensReceived(QString token, QString tokenSecret)
{
    this->_accessToken = token;
    this->_accessTokenSecret = tokenSecret;
    qDebug() << "Token: " << token;
    qDebug() << "TokenSecret: " << tokenSecret;
}
