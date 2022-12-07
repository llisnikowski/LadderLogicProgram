#include "address.hpp"

namespace LdProperty {

Address::Address(QQuickItem *parent)
    :TextField{parent}
{
}

Address::~Address()
{
}

Address &Address::operator=(const Address &address)
{
    if(this != &address){
        TextField::operator=(address);
    }
    return *this;
}


Type Address::getType() const
{
    return Type::Address;
}


} // namespace LdProperty




QDataStream & operator<<(QDataStream &stream, const LdProperty::Address &textField)
{
    stream << static_cast<const LdProperty::TextField&>(textField);
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::Address &textField)
{
    stream >> static_cast<LdProperty::TextField&>(textField);
    return stream;
}



