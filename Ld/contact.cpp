/*!
 * \file contact.cpp
 * \author Łukasz Liśnikowski
*/

#include "contact.hpp"
#include "painter.hpp"
#include <QDebug>
#include "address.hpp"
#include <QPainter>

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


void Contact::paint(QPainter *painter)
{
    if(ldPainter_)
        ldPainter_->drawContact(painter, size(), getSelectedFlag()
                        | (1 << (type_.getValue() + Painter::contactType)));

    painter->setPen(QPen(Qt::white, 2));
    if(type_.getValue()){
        painter->drawLine(QLineF{64*0.42, 64/2+64*0.08,
                                 64-64*0.42, 64/2-64*0.08});
    }
}

QByteArray Contact::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_ << type_;
    return itemData;
}



} //namespace Ld
