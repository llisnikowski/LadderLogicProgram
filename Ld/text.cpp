#include "text.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include "type.hpp"

namespace Ld {

Text::Text(QQuickItem *parent)
    :Output{parent}
{

}

Base *Text::clone(QQuickItem *parent)
{
    Text *copyObject = new Text{parent};
    copyObject->address_ = this->address_;
    return copyObject;
}

void Text::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawCoil();
    painterLd.printCenterLetter('X');

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

Type Text::getType() const
{
    return Type::Timer;
}

QByteArray Text::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_;
    return itemData;
}


} //namespace Ld
