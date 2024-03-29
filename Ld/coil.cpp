/*!
 * \file coil.cpp
 * \author Łukasz Liśnikowski
*/

#include "coil.hpp"
#include "painterLd.hpp"
#include "type.hpp"
#include <QDebug>
#include <QPainter>
#include <QRectF>
#include <QRegularExpression>

namespace Ld {

/*!
 * \brief Konstructor klasy Coil
 * \param parent: rodzic/element nadrzędny
 */
Coil::Coil(QQuickItem *parent)
    :Output{parent}, type_{this}
{
    addProperty(&type_);
    type_.setModel({"Normal", "Set", "Reset"});
    QObject::connect(&type_, &LdProperty::ComboboxField::valueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&type_, &LdProperty::ComboboxField::itemFocus,
                     this, [this](bool focus){if(focus) emit clicked();});

    address_.setPlaceholder("Q/M##");
    address_.setRegExp("^([Qq](0?\\d|[1-2]\\d|3[01]))|([Mm](\\d{1,2}))$");

}

Base *Coil::clone(QQuickItem *parent)
{
    Coil *copyObject = new Coil{parent};
    copyObject->address_ = this->address_;
    copyObject->type_ = this->type_;
    return copyObject;
}

Type Coil::getType() const
{
    return Type::Coil;
}

/*!
 * \brief Funkcja rysująca obiekt na ekranie
 */
void Coil::paintBase(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawCoil();

    if(type_.getValue() == 1){
        painterLd.printCenterLetter('S');
    }
    else if(type_.getValue() == 2){
        painterLd.printCenterLetter('R');
    }
}


QByteArray Coil::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_ << type_;
    return itemData;
}

LdProperty::TypeField &Coil::getPropertyType()
{
    return type_;
}


} //namespace Ld
