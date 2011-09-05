#include "qtblueviasms.h"

QtBlueViaSms::QtBlueViaSms(IAuthentication *authentication,QObject *parent) :
    QtRestClient(1,parent)
{
    this->setAuthenticationData(authentication);
}

QtBlueViaSms::~QtBlueViaSms()
{

}
