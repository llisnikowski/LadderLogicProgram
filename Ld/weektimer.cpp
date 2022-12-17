#include "weektimer.hpp"
#include <QPainter>
#include "painterLd.hpp"

namespace Ld {

Weektimer::Weektimer(QQuickItem *parent)
    :Input{parent}
{

}

Base *Weektimer::clone(QQuickItem *parent)
{
    Weektimer *copyObject = new Weektimer{parent};
    copyObject->address_ = this->address_;
    return copyObject;
}

void Weektimer::paint(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawContact();
    painterLd.printCenterLetter('Z');

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

Type Weektimer::getType() const
{
    return Type::Weektimer;
}

QByteArray Weektimer::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_;
    return itemData;
}


} //namespace Ld
