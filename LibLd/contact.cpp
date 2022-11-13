/*!
 * \file contact.cpp
 * \author Łukasz Liśnikowski
*/

#include "contact.hpp"
#include "painter.hpp"
#include <QDebug>

namespace Ld {

/*!
 * \brief Konstructor klasy Contact
 * \param parent: rodzic/element nadrzędny
 */
Contact::Contact(QQuickItem *parent)
    :Input(parent)
{
}


void Contact::paint(QPainter *painter)
{
    if(!ldPainter_) return;
    ldPainter_->drawContact(*painter);
}


} //namespace Ld
