#include "qtblueviasmsmessage.h"

QtBlueViaSmsMessage::QtBlueViaSmsMessage(QtBlueViaUserId address,QString message) :
    QtBlueViaAbstractMessage(address)
{
    this->_message = message;
}


QtBlueViaSmsMessage::QtBlueViaSmsMessage(QList<QtBlueViaUserId> addresses, QString message) :
    QtBlueViaAbstractMessage(addresses)
{
    this->_addresList = addresses;
}

QString QtBlueViaSmsMessage::getMessage()
{
    return this->_message;
}
