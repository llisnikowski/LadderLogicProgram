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

    address_.setPlaceholder("I/Q/M/T/C/P[00-15]");
    address_.setRegExp("^([IiQqMmTtCc]((0?\\d)|(1[0-5]))$|^([pP]0?[0-7]))$");
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
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawContact();

    if(type_.getValue()){
        painterLd.drawContactSlash();
    }

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
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
