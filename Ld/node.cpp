/*!
 * \file node.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "node.hpp"
#include <QPainter>
#include "painterLd.hpp"

namespace Ld {

Node::Node(QQuickItem *parent)
    :Base(parent)
{
}

Base *Node::clone(QQuickItem *parent)
{
    Base *copyObject = new Node{parent};
    return copyObject;
}

/*!
 * \brief Funkcja rysująca obiekt na ekranie
 */
void Node::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawNode(true, isNextLine, isTopLine, isBottomLine);

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
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

/*!
 * \brief Funkcja ustawiająca wyświetlane linie podczas rysowania
 */
void Node::displayLine(bool right, bool top, bool bottom)
{
    isNextLine = right;
    isTopLine = top;
    isBottomLine = bottom;
    update();
}




} //namespace Ld
