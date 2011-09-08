#include "qtblueviasmsclient.h"
#include "libqtrest/qtrestientity.h"
#include "libqtrest/qtrestoauthdata.h"
#include "libqtrest/qtrestxmlserializer.h"

QtBlueViaSmsClient::QtBlueViaSmsClient(IAuthentication *authentication,QObject *parent) :
    QtRestClient(1,parent)
{
    this->setAuthenticationData(authentication);
    /*QStringList properties;
    properties.add("smsText");
    properties.add("address");
    properties.add("phoneNumber");
    properties.add("message");
    properties.add("originAddress");
    properties.add("alias");
    this->setPropertiesTags(properties);*/
}

QtBlueViaSmsClient::~QtBlueViaSmsClient()
{

}

QString QtBlueViaSmsClient::sendSms(QString message, QtBlueViaUserId address)
{
    QtBlueViaSmsMessage sms(address,message);
    return this->sendSms(sms);
}

QString QtBlueViaSmsClient::sendSms(QString message, QList<QtBlueViaUserId> addresses)
{
    QtBlueViaSmsMessage sms(addresses,message);
    return this->sendSms(sms);
}

QString QtBlueViaSmsClient::sendSms(QtBlueViaSmsMessage message)
{
    IEntity *smsText = new IEntity(NamespaceId::tns,Id::smsText);
    for(int i=0;i<message.getDestinationAddresses().size();i++) {
        IEntity *address = new IEntity(NamespaceId::tns,Id::address);
        //TODO: create different userId types
        IEntity *phoneNumber = new IEntity(NamespaceId::tns1,Id::phoneNumber,((QtBlueViaUserId)message.getDestinationAddresses().at(i)).getUserIdValue());
        address->addEntity(phoneNumber);
        smsText->addEntity(address);
    }
    IEntity *sms = new IEntity(NamespaceId::tns,Id::message,message.getMessage());
    smsText->addEntity(sms);
    QString token = ((OAuthData*)this->authenticationData)->getToken();
    IEntity *originAddress = new IEntity(NamespaceId::tns,Id::originAddress,new IEntity(NamespaceId::tns1,Id::alias, token));
    smsText->addEntity(originAddress);
    QMultiMap<int,QString> namespaces;
    namespaces.insert(NamespaceId::tns,"http://www.telefonica.com/schemas/UNICA/REST/sms/v1/");
    namespaces.insert(NamespaceId::tns1,"http://www.telefonica.com/schemas/UNICA/REST/common/v1");
    XMLSerializer serializer("",namespaces);
    QString serializedBody = serializer.serialize(smsText);
    delete smsText;
    HttpRequest *request = authenticatedRequest();
    //TODO: settings
    request->setRequestEndpoint(QUrl("https://api.bluevia.com/services/REST/SMS_Sandbox/outbound/requests?version=v1"));
    request->setHttpMethod(HttpRequest::POST);
    request->setAuthHeader();
    request->setRequestBody(QByteArray(serializedBody.toAscii()));
    request->setHeader(QByteArray("Content-Type"),QByteArray("application/xml"));
    connect(&this->httpConnector,
           SIGNAL(requestFinished(QByteArray)),
           this,
           SLOT(onSmsSent(QByteArray)));
    QByteArray smsResult = this->httpConnector.httpRequest(request);
    delete request;
}

void QtBlueViaSmsClient::getDeliveryStatus(QString smsId)
{
    HttpRequest *request = authenticatedRequest();
    //TODO: settings
    request->setRequestEndpoint(QUrl("https://api.bluevia.com/services/REST/SMS_Sandbox/outbound/requests/"+smsId+"/deliverystatus?version=v1"));
    request->setHttpMethod(HttpRequest::GET);
    request->setAuthHeader();
    connect(&this->httpConnector,
           SIGNAL(requestFinished(QByteArray)),
           this,
           SLOT(onSmsSent(QByteArray)));
    QByteArray smsResult = this->httpConnector.httpRequest(request);
}
