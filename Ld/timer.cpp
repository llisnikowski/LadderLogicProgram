#include "timer.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include "type.hpp"

namespace Ld {

Timer::Timer(QQuickItem *parent)
    :Output(parent)
{
}

Base *Timer::clone(QQuickItem *parent)
{
    Timer *copyObject = new Timer{parent};
    copyObject->address_ = this->address_;
    return copyObject;
}

void Timer::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawCoil();
    painterLd.printCenterLetter('T');

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

Type Timer::getType() const
{
    return Type::Timer;
}

QByteArray Timer::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_;
    return itemData;
}


} //namespace Ld
