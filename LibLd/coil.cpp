/*!
 * \file coil.cpp
 * \author Łukasz Liśnikowski
*/

#include "coil.hpp"
#include "painter.hpp"

namespace Ld {

/*!
 * \brief Konstructor klasy Coil
 * \param parent: rodzic/element nadrzędny
 */
Coil::Coil(QQuickItem *parent)
    :Output(parent)
{
}


void Coil::paint(QPainter *painter)
{
    if(!ldPainter_) return;
    ldPainter_->drawCoil(*painter);
}


} //namespace Ld