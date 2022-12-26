#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "drag.hpp"
#include "addressField.hpp"

namespace Ld {

class Address : public Drag
{
    Q_OBJECT
public:
    explicit Address(QQuickItem *parent = nullptr);

    Type getType() const override;
    LdProperty::AddressField &getAddress();

protected:
    LdProperty::AddressField address_;
};

} // namespace Ld

#endif // ADDRESS_HPP
