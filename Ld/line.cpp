/*!
 * \file line.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "line.hpp"
#include <QPainter>
#include "painterLd.hpp"

namespace Ld {

/*!
 * \brief Konstructor klasy Line
 * \param parent: rodzic/element nadrzędny
 */
Line::Line(QQuickItem *parent)
    :Drop(parent)
{
}

Base *Line::clone(QQuickItem *parent)
{
    Base *copyObject = new Line{parent};
    return copyObject;
}

Type Line::getType() const
{
    return Type::Line;
}

void Line::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawLine();

    if(droppingItem_){
        painterLd.fillColor();
    }

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

QByteArray Line::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType());
    return itemData;
}




} //namespace Ld
