/*!
 * \file node.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "node.hpp"

namespace Ld {

/*!
 * \brief Konstructor klasy Node
 * \param parent: rodzic/element nadrzędny
 */
Node::Node(QQuickItem *parent)
    :Base(parent)
{
}

Base *Node::clone(QQuickItem *parent)
{
    Base *copyObject = new Node{parent};
    return copyObject;
}

void Node::paint(QPainter *painter)
{

}

Type Node::getType() const
{
    return Type::Node;
}

QByteArray Node::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType());
    return itemData;
}




} //namespace Ld
