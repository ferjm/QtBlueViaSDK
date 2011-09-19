#include "qtblueviasmsclient.h"
#include "libqtrest/qtrestientity.h"
#include "libqtrest/qtrestoauthdata.h"
#include "libqtrest/qtrestxmlserializer.h"
#include "libqtrest/qtrestxmlparser.h"

#include <QPair>

QtBlueViaSmsClient::QtBlueViaSmsClient(IAuthentication *authentication,QObject *parent) :
    QtRestClient(1,parent)
{
    this->setAuthenticationData(authentication);    
}

QtBlueViaSmsClient::~QtBlueViaSmsClient()
{

}

void QtBlueViaSmsClient::sendSms(QString message, QtBlueViaUserId address)
{
    QtBlueViaSmsMessage sms(address,message);
    this->sendSms(sms);
}

void QtBlueViaSmsClient::sendSms(QString message, QList<QtBlueViaUserId> addresses)
{
    QtBlueViaSmsMessage sms(addresses,message);
    this->sendSms(sms);
}

void QtBlueViaSmsClient::sendSms(QtBlueViaSmsMessage message)
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
    namespaces.insert(NamespaceId::tns2,"http://www.w3.org/2001/XMLSchema-instance");
    namespaces.insert(NamespaceId::tns3,"http://www.telefonica.com/schemas/UNICA/REST/sms/v1/UNICA_API_REST_sms_types_v1_0.xsd");
    XMLSerializer serializer("",namespaces);
    QString serializedBody = serializer.serialize(smsText);
    delete smsText;


    HttpRequest *request = authenticatedRequest();
    //TODO: settings
    request->setRequestEndpoint(QUrl("https://api.bluevia.com/services/REST/SMS/outbound/requests?version=v1"));
    request->setHttpMethod(HttpRequest::POST);
    request->setAuthHeader();    
    request->setRequestBody(QByteArray(serializedBody.toAscii()));
    request->setHeader(QByteArray("Content-Type"),QByteArray("application/xml"));
    request->setHeader(QByteArray("Accept"),QByteArray("*/*"));
    connect(&this->httpConnector,
            SIGNAL(headersRetrieved(QList<QNetworkReply::RawHeaderPair>)),
           this,
           SLOT(onSmsSent(QList<QNetworkReply::RawHeaderPair>)));
    this->httpConnector.httpRequest(request);
    delete request;
}

void QtBlueViaSmsClient::getDeliveryStatus(QString resourceUrl)
{
    HttpRequest *request = authenticatedRequest();
    //TODO: settings
    request->setRequestEndpoint(QUrl(resourceUrl+"?version=v1"));
    request->setHttpMethod(HttpRequest::GET);
    request->setAuthHeader();
    connect(&this->httpConnector,
           SIGNAL(requestFinished(QByteArray)),
           this,
           SLOT(onStatusRetrieved(QByteArray)));
    QByteArray smsResult = this->httpConnector.httpRequest(request);
}

void QtBlueViaSmsClient::onSmsSent(QList<QNetworkReply::RawHeaderPair> headers)
{    
    for(int i = 0; i < headers.size(); i++) {
        if(headers.at(i).first == QString("Location")) {
            emit smsSent(headers.at(i).second);
            return;
        }
    }
}

void QtBlueViaSmsClient::onStatusRetrieved(QByteArray status)
{
    XMLParser parser;
    try {
        IEntity *entity = parser.parse(status,status.size());
        if((entity != NULL)&&(entity->getId() != Id::NULLID)) {
            QList<QPair<QString,QString> > deliveryStatusList;
            if(entity->getId() == Id::smsDeliveryStatus) {
                IEntity::itConstEntities begin,end;
                entity->getEntityList(begin,end);
                if(begin != end)
                {
                    for(IEntity::itConstEntities it = begin; it != end; it++ )
                    {
                        IEntity *sit = dynamic_cast<IEntity *>(*it);
                        if((sit != NULL) && (sit->getId() == Id::smsDeliveryStatus)) {
                            IEntity *address = sit->getEntity(Id::address);
                            IEntity *phoneNumber = address->getEntity(Id::phoneNumber);
                            QString addressValue = phoneNumber->getValue();
                            IEntity *deliveryStatusEntity = sit->getEntity(Id::deliveryStatus);
                            QString deliveryStatusValue = deliveryStatusEntity->getValue();
                            deliveryStatusList.append(qMakePair(addressValue,deliveryStatusValue));
                        }
                    }
                } else {
                    return;
                }
            } else {
                //TODO: error handling
                return;
            }
            emit deliveryStatusRetrieved(deliveryStatusList);
        }
    } catch (XMLParserException e) {

    }
}
