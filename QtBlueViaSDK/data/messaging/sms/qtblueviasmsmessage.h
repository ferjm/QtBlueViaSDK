#ifndef QTBLUEVIASMSMESSAGE_H
#define QTBLUEVIASMSMESSAGE_H

#include "qtblueviaabstractmessage.h"

class QtBlueViaSmsMessage : public QtBlueViaAbstractMessage
{    
public:
    /**
      Instantiates a new SMS with a destination address and a message
      @param address Destination address
      @param message Message to be sent
      */
    QtBlueViaSmsMessage(QtBlueViaUserId address,QString message);
    /**
      Instantiates a new SMS with a list of destination addresses and a message
      @param addresses List of destination addresses
      @param message Message to be sent
      */
    QtBlueViaSmsMessage(QList<QtBlueViaUserId> addresses, QString message);

    QString getMessage();

private:
    QString _message;


};

#endif // QTBLUEVIASMSMESSAGE_H
