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

Type Base::getType() const
{
    return Type::Base;
}

QByteArray Base::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("LdProperty") << static_cast<int>(getType());
    return itemData;
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



