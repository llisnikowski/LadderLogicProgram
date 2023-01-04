#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "drag.hpp"
#include "addressField.hpp"

namespace Ld {

/*!
 * \brief Address jest klasą udostępniającą właściwość adress
 * za pomocą obiektu LdProperty::AddressField
 *
 * Klasa dziedziczy z klasy Drag udostępniając mechanizm przenoszenia.
 */
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
