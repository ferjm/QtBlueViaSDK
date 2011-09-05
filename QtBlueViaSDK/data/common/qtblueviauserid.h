#ifndef QTBLUEVIAUSERID_H
#define QTBLUEVIAUSERID_H

#include <QString>

/**
  \class QtBlueViaUserId
  Class representing UserId identification. This class may be used to identify
  the user on the request. For example, when sending an SMS, the recipient of the SMS
  may be identified using this class.
  There are 6 types of UserIds types:
  <ul>
  <li>PhoneNumber</li>
  <li>AnyUri</li>
  <li>IPV4</li>
  <li>IPV6</li>
  <li>Alias</li>
  <li>OtherId</li>
  </ul>
*/
class QtBlueViaUserId
{
public:
    /**
      Enum Type to indicate the type of vale that identifies the user
     */
    enum UserIdType { PHONE_NUMBER, ANY_URI, IPV4_ADDRESS, IPV6_ADDRESS, ALIAS, OTHER_ID };

    QtBlueViaUserId() {};

    /**
      Constructor
      Instantiates a new QtBlueViaUserId
      */
    QtBlueViaUserId(UserIdType type, QString userIdValue);

    bool operator==(const QtBlueViaUserId &other);

    /**
      Gets the UserId type
      @return the UserId type
      */
    UserIdType getType() const;
    /**
      Sets the UserId type
      @param type the type of the UserId
      */
    void setType(UserIdType type);
    /**
      Gets the UserId value for the type set
      @return the UserId value
      */
    QString getUserIdValue() const;
    /**
      Sets the UserId value
      @param userIdValue
      */
    void setUserIdValue(QString userIdValue);
    /**
      Gets the value of other type name
      @return QString
      */
    QString getOtherType();
    /**
      When the type use id "OtherType", the type value must be set using this method
      @param otherType
      */
    void setOtherType(QString otherType);
    /**
      Validates the UserId
      */
    bool isValid() {
        //TODO
        return true;
    }

private:
    UserIdType _type;
    QString _userIdValue;
    QString _otherType;

};


#endif // QTBLUEVIAUSERID_H
