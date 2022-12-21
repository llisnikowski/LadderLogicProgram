#include "LdProperty/base.hpp"


namespace LdProperty{

Base::Base(QQuickItem *parent)
    : QQuickItem{parent}, propertyName_{}
{
}

Base &Base::operator=(const Base &base)
{
    if(this != &base){
    }
    return *this;
}

void Base::setPropertyName(QString propertyName){
    propertyName_ = propertyName;
    emit propertyNameChanged();
}


} // namespace LdProperty



QDataStream & operator<<(QDataStream &stream, const LdProperty::Base &base)
{
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::Base &base)
{
    return stream;
}



