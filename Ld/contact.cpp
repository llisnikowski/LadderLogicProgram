/*!
 * \file contact.cpp
 * \author Łukasz Liśnikowski
*/

#include "contact.hpp"
#include "painter.hpp"
#include <QDebug>
#include "address.hpp"

namespace Ld {

/*!
 * \brief Konstructor klasy Contact
 * \param parent: rodzic/element nadrzędny
 */
Contact::Contact(QQuickItem *parent)
    :Input(parent)
{
}

Base *Contact::clone(QQuickItem *parent)
{
    Contact *copyObject = new Contact{parent};
    copyObject->address_ = this->address_;
    return copyObject;
}

Type Contact::getType() const
{
    return Type::Contact;
}


void Contact::paint(QPainter *painter)
{
    if(ldPainter_)
        ldPainter_->drawContact(painter, size(), getSelectedFlag());
}

QByteArray Contact::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_;
    return itemData;
}



} //namespace Ld
