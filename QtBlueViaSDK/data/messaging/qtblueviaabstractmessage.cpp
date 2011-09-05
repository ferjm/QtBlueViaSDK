#include "qtblueviaabstractmessage.h"

QtBlueViaAbstractMessage::QtBlueViaAbstractMessage()
{
}

QtBlueViaAbstractMessage::QtBlueViaAbstractMessage(QtBlueViaUserId address)
{
    this->addAddress(address);
}

QtBlueViaAbstractMessage::QtBlueViaAbstractMessage(QList<QtBlueViaUserId> addresses)
{
    this->_addresList = addresses;
}

void QtBlueViaAbstractMessage::addAddress(QtBlueViaUserId address)
{
    this->_addresList.append(address);
}

bool QtBlueViaAbstractMessage::removeAddress(QtBlueViaUserId address)
{
    return this->_addresList.removeAll(address);
}

void QtBlueViaAbstractMessage::clearAddressList()
{
    this->_addresList.clear();
}

void QtBlueViaAbstractMessage::setOriginAddress(QtBlueViaUserId originAddress)
{
    this->_originAddress = originAddress;
}

QtBlueViaUserId QtBlueViaAbstractMessage::getOriginAddress()
{
    return this->_originAddress;
}

QList<QtBlueViaUserId> QtBlueViaAbstractMessage::getDestinationAddresses()
{
    return this->_addresList;
}
