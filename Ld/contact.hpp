/*!
 * \file contact.hpp
 * \author Łukasz Liśnikowski
*/

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include "input.hpp"
#include "typeField.hpp"

namespace Ld {

/*!
 * \brief Klasa Coil udostępnia symbol styku z języka LD.
 */
class Contact : public Input
{
    Q_OBJECT
public:
    explicit Contact(QQuickItem *parent = nullptr);

    Base *clone(QQuickItem *parent = nullptr) override;

    Type getType() const override;
    void paint(QPainter *painter) override;
    QByteArray getData() const override;
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);

    LdProperty::TypeField &getPropertyType();

protected:
    LdProperty::TypeField type_;

};



} //namespace Ld

#endif // CONTACT_HPP
