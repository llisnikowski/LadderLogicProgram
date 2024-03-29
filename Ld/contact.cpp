/*!
 * \file contact.cpp
 * \author Łukasz Liśnikowski
*/

#include "contact.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include <QRegularExpression>

namespace Ld {

/*!
 * \brief Konstructor klasy Contact
 * \param parent: rodzic/element nadrzędny
 */
Contact::Contact(QQuickItem *parent)
    :Input(parent), type_{this}
{
    addProperty(&type_);
    type_.setModel({"-| |-", "-|/|-"});
    QObject::connect(&type_, &LdProperty::ComboboxField::valueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&type_, &LdProperty::ComboboxField::itemFocus,
                     this, [this](bool focus){if(focus) emit clicked();});

    address_.setPlaceholder("I/Q/M/T/C/P##");
    address_.setRegExp("^([IiQqTtCc](0?\\d|[1-2]\\d|3[01]))"
                       "|([Mm](\\d{1,2}))"
                       "|([Pp](0?[0-3]))$");
}

Base *Contact::clone(QQuickItem *parent)
{
    Contact *copyObject = new Contact{parent};
    copyObject->address_ = this->address_;
    copyObject->type_ = this->type_;
    return copyObject;
}

Type Contact::getType() const
{
    return Type::Contact;
}

/*!
 * \brief Funkcja rysująca obiekt na ekranie
 */
void Contact::paintBase(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawContact();

    if(type_.getValue()){
        painterLd.drawContactSlash();
    }
}

QByteArray Contact::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_ << type_;
    return itemData;
}

LdProperty::TypeField &Contact::getPropertyType()
{
    return type_;
}



} //namespace Ld
