#include "address.hpp"


namespace Ld {

Ld::Address::Address(QQuickItem *parent)
    :Drag{parent}, address_{this}
{
    address_.setPropertyName("Adres");
    addProperty(&address_);
    QObject::connect(&address_, &LdProperty::TextField::itemFocus,
                     this, [this](bool focus){if(focus) emit clicked();});
}

Type Address::getType() const
{
    return Type::Address;
}



} // namespace Ld

