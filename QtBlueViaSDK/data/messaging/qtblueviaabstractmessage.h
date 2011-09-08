#ifndef QTBLUEVIAABSTRACTMESSAGE_H
#define QTBLUEVIAABSTRACTMESSAGE_H

#include <QList>

#include "qtblueviauserid.h"

/**
  Abstract SMS class that represents the different messages that will
  be sent using the SMS/MMS Client API.
  This Type is composed of the following fields:
  <ul>
    <li>addressList: mandatory. QList. Min ocurrences 1</li>
    <li>originAddress: mandatory. String</li>
  </ul>
  */
class QtBlueViaAbstractMessage
{
public:
    QtBlueViaAbstractMessage();
    /**
      Instantiates a new message with a destination address
      @param address Destination address
      */
    QtBlueViaAbstractMessage(QtBlueViaUserId address);
    /**
      Instantiates a new message with a list of destination addresses
      @param addresses Destination addresses
      */
    QtBlueViaAbstractMessage(QList<QtBlueViaUserId> addresses);
    /**
      Add address
      @param address Message destination address
      */
    void addAddress(QtBlueViaUserId address);
    /**
      Removes a given destination address
      @return true if the address was successfully removed
      */
    bool removeAddress(QtBlueViaUserId address);
    /**
      Clear the destination address list
      */
    void clearAddressList();
    /**
      Sets the origin address
      @param originAddress
      */
    void setOriginAddress(QtBlueViaUserId originAddress);
    /**
      Gets the origin address
      @return QtBlueViaUserId origin address
      */
    QtBlueViaUserId getOriginAddress();
    /**
      Get the destination address list
      @return QList<QtBlueViaUserId> destination addresses
      */
    QList<QtBlueViaUserId> getDestinationAddresses();

    /**
      isValid
    */
    bool isValid() {
        //TODO
        return true;
    }

protected:
    QList<QtBlueViaUserId> _addresList;
    QtBlueViaUserId _originAddress;

};

#endif // QTBLUEVIAABSTRACTMESSAGE_H
