/*!
 * \file line.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "line.hpp"
#include "painter.hpp"

namespace Ld {

/*!
 * \brief Konstructor klasy Line
 * \param parent: rodzic/element nadrzędny
 */
Line::Line(QQuickItem *parent)
    :Drop(parent)
{
}

Type Line::getType() const
{
    return Type::Line;
}

void Line::paint(QPainter *painter)
{
    if(!ldPainter_) return;
    ldPainter_->drawLine(*painter, size());
}

QByteArray Line::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType());
    return itemData;
}




} //namespace Ld
