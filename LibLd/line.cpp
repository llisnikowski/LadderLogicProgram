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

void Line::paint(QPainter *painter)
{
    if(!ldPainter_) return;
    ldPainter_->drawLine(*painter, size());
}



} //namespace Ld
