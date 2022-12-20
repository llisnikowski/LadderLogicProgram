#include "LdProperty/base.hpp"


namespace LdProperty{

Base::Base(QQuickItem *parent)
    : QQuickItem{parent}
{
}

Base &Base::operator=(const Base &base)
{
    if(this != &base){
        setPropertyName(base.propertyName_);
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
    stream << base.getPropertyName();
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::Base &base)
{
    QString name;
    stream >> name;
    base.setPropertyName(name);
    return stream;
}



