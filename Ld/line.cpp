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
    :Drop(parent), displayType_{}
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

/*!
 * \brief Funkcja rysująca obiekt na ekranie
 */
void Line::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    if(droppingItem_){
        painterLd.fillColor();
    }
    if(displayType_ == invisible) return;

    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawLine();

    if(displayType_ == fromLeft
        || displayType_ == fromLeftToRigth){
        painterLd.drawLineStart();
    }
    if(displayType_ == toRight
        || displayType_ == fromLeftToRigth){
        painterLd.drawLineEnd();
    }

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

void Line::setDisplayType(DisplayType displayType)
{
    displayType_ = displayType;
    update();
}

QByteArray Line::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType());
    return itemData;
}




} //namespace Ld
