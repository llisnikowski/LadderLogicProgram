/*!
 * \file coil.cpp
 * \author Łukasz Liśnikowski
*/

#include "coil.hpp"
#include "painter.hpp"
#include "type.hpp"
#include <QDebug>

namespace Ld {

/*!
 * \brief Konstructor klasy Coil
 * \param parent: rodzic/element nadrzędny
 */
Coil::Coil(QQuickItem *parent)
    :Output(parent)
{
}

Base *Coil::clone(QQuickItem *parent)
{
    Coil *copyObject = new Coil{parent};
    copyObject->address_ = this->address_;
    return copyObject;
}

Type Coil::getType() const
{
    return Type::Coil;
}


void Coil::paint(QPainter *painter)
{
    if(!ldPainter_) return;
    ldPainter_->drawCoil(*painter, size());
}

QByteArray Coil::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_;
    return itemData;
}


} //namespace Ld
