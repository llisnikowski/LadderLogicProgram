#include "emptyDrop.hpp"

namespace Ld {

EmptyDrop::EmptyDrop(QQuickItem *parent)
    :Drop(parent)
{

}

Ld::Base *EmptyDrop::clone(QQuickItem *parent)
{
    EmptyDrop *copyObject = new EmptyDrop{parent};
    return copyObject;
}

Ld::Type EmptyDrop::getType() const
{
    return Type::EmptyDrop;
}

/*!
 * \brief Funkcja rysująca obiekt na ekranie
 */
void EmptyDrop::paint(QPainter *)
{
}

QByteArray EmptyDrop::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType());
    return itemData;
}


} //namespace Ld


