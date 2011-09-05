#include "qtblueviauserid.h"

QtBlueViaUserId::QtBlueViaUserId(UserIdType type,QString userIdValue)
{
    this->_type = type;
    this->_userIdValue = userIdValue;
}

bool QtBlueViaUserId::operator ==(const QtBlueViaUserId &other)
{
    return ((this->_type == other.getType()) && (this->_userIdValue == other.getUserIdValue()));
}

QtBlueViaUserId::UserIdType QtBlueViaUserId::getType() const
{
    return this->_type;
}

void QtBlueViaUserId::setType(UserIdType type)
{
    this->_type = type;
}

QString QtBlueViaUserId::getUserIdValue() const
{
    return this->_userIdValue;
}

void QtBlueViaUserId::setUserIdValue(QString userIdValue)
{
    this->_userIdValue = userIdValue;
}

QString QtBlueViaUserId::getOtherType()
{
    return this->_otherType;
}

void QtBlueViaUserId::setOtherType(QString otherType)
{
    this->_otherType = otherType;
}
